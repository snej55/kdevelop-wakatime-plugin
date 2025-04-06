#include "wakatime-plugin.h"

#include <debug.h>

#include <KLocalizedString>
#include <KPluginFactory>

#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>

#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#include <QSql>

#include <iostream>

K_PLUGIN_FACTORY_WITH_JSON(wakatime_pluginFactory, "wakatime-plugin.json", registerPlugin<WakatimePlugin>(); )

WakatimePlugin::WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("wakatime-plugin"), parent, metaData)
{
    Q_UNUSED(args);

    updateLastHeartbeat({});
    checkWakatimeBin();
    addListeners();

    qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Wakatime plugin is loaded!";
}

WakatimePlugin::~WakatimePlugin()
{
        delete m_lastHeartBeat;
        m_lastHeartBeat = nullptr;
}

void WakatimePlugin::addListeners()
{
    // connect documentController signals to WakatimePlugin slots
    connect(KDevelop::ICore::self()->documentController(), &KDevelop::IDocumentController::documentJumpPerformed, this, &WakatimePlugin::documentJumpPerformed);
    connect(KDevelop::ICore::self()->documentController(), &KDevelop::IDocumentController::documentClosed, this, &WakatimePlugin::documentClosed);
    connect(KDevelop::ICore::self()->documentController(), &KDevelop::IDocumentController::documentOpened, this, &WakatimePlugin::documentOpened);
    connect(KDevelop::ICore::self()->documentController(),&KDevelop::IDocumentController::documentSaved, this, &WakatimePlugin::documentSaved);
    connect(KDevelop::ICore::self()->documentController(), &KDevelop::IDocumentController::documentActivated, this, &WakatimePlugin::documentActivated);
}

QString WakatimePlugin::getWakatimeBinDir()
{
        return QStandardPaths::findExecutable(QStringLiteral("wakatime"));
}

void WakatimePlugin::checkWakatimeBin()
{
        if (getWakatimeBinDir().isEmpty()) {
                qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Unable to find wakatime executable. Please make sure it is installed.";
                setErrorDescription(i18n("Unable to find wakatime executable. Please make sure it is installed."));
        }
}


QString WakatimePlugin::getProjectName(QUrl fileUrl)
{
        auto* projectController {KDevelop::ICore::self()->projectController()};

        QString fileName {fileUrl.fileName()};
        QString filePath {projectController->prettyFilePath(fileUrl, KDevelop::IProjectController::FormatPlain)};

        // make sure path doesn't end with '/'
        if (filePath.endsWith('/')) {
                filePath.chop(1); // remove last character
        }

        // if relative path means it's part of open project
        const bool isRelativeFilePath {QDir::isRelativePath(filePath)};
        if (isRelativeFilePath) {
                const qsizetype nameLength {filePath.indexOf(QLatin1Char(':'))};

                if (nameLength < 0) {
                        return filePath;
                } else {
                        return filePath.left(nameLength);
                }
        }
        return QString("");
}

QString WakatimePlugin::getFileName(QUrl fileUrl)
{
        return fileUrl.fileName();
}

void WakatimePlugin::passDocument(void* document, bool isWrite)
{
#ifdef DEBUG_OUTPUT
        std::cout << "Trying to send heartbeat!\n";
#endif
        KDevelop::IDocument* doc {static_cast<KDevelop::IDocument*>(document)};
        if (enoughTimePassed(QDateTime::currentDateTime()) || m_lastHeartBeat->fileUrl != doc->url()) {
#ifdef DEBUG_OUTPUT
                std::cout << "Enough time has passed!\n";
#endif
                QStringList options {buildHeartbeat(doc->url().path(), getProjectName(doc->url()), isWrite)};
                sendHeartbeat(options);
                updateLastHeartbeat(doc->url());
        } else {
#ifdef DEBUG_OUTPUT
                std::cout << "Not enough time has passed!\n";
#endif
        }
}

void WakatimePlugin::documentJumpPerformed(void* document)
{
        passDocument(document, false);
}


void WakatimePlugin::documentOpened(void* document)
{
        passDocument(document, false);
}

void WakatimePlugin::documentActivated(void* document)
{
        passDocument(document, false);
}

void WakatimePlugin::documentClosed(void* document)
{
        passDocument(document, false);
}

void WakatimePlugin::documentSaved(void* document)
{
        passDocument(document, true);
}

HeartBeat* WakatimePlugin::getLastHeartbeat()
{
        if (m_lastHeartBeat == nullptr)
        {
                QDateTime now {QDateTime::currentDateTime()};
                m_lastHeartBeat = new HeartBeat{now, {}};
        }
        return m_lastHeartBeat;
}

void WakatimePlugin::updateLastHeartbeat(QUrl filePath)
{
        QDateTime now {QDateTime::currentDateTime()};
        delete m_lastHeartBeat;
        m_lastHeartBeat = new HeartBeat{now, filePath};
}


bool WakatimePlugin::enoughTimePassed(QDateTime time) const
{
#ifdef DEBUG_OUTPUT
        std::cout << "Seconds since last heartbeat: " << m_lastHeartBeat->time.secsTo(time) << '\n';
#endif
        return m_lastHeartBeat->time.secsTo(time) >= 120; // check if time is greater than 2 minutes
}

QStringList WakatimePlugin::buildHeartbeat(QString file, QString project, const bool isWrite) const
{
        QStringList options;
        options << "--plugin" << "KDevelop kdevelop-wakatime";
        options << "--entity" << file;

        // if project isn't empty
        if (!project.isEmpty()) {
                options << "--alternate-project" << project;
        }

        if (isWrite) {
                options << "--write";
        }

        QString pluginTitle {"kdevelop"};
        options << "--plugin" << pluginTitle;

        // locate config path
        QString configPath {QStandardPaths::locate(QStandardPaths::HomeLocation, QStringLiteral(".wakatime.cfg"))};
        if (!configPath.isEmpty()) {
                options << "--config" << configPath;
        }

        return options;
}

void WakatimePlugin::sendHeartbeat(QStringList options)
{
        ++m_heartBeatNum;
#ifdef DEBUG_OUTPUT
        std::cout << "SENDING HEARTBEAT!" << '\n';
#endif
        // get wakatime-cli binary
        QString bin {getWakatimeBinDir()};

        // create new process to post heartbeat
        QProcess* sender {new QProcess{this}};
        sender->setProcessChannelMode(QProcess::MergedChannels);
        qCDebug(PLUGIN_WAKATIME_PLUGIN) << bin << options;
        sender->startDetached(bin, options);

        // handle errors
        if (!sender->waitForFinished()) {
                qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Heartbeat failed: " << sender->errorString();
        } else {
                if (sender->exitCode() == 102) {
                        qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Wakatime is offline! Coding activity will be synced when online.";
                        setErrorDescription(i18n("Wakatime is offline! Coding activity will be synced when online."));
                } else if (sender->exitCode() == 103) {
                        qCDebug(PLUGIN_WAKATIME_PLUGIN) << "An error occured while parsing $WAKATIME_HOME/.wakatime.cfg. Check $WAKATIME_HOME/.wakatime.log for more details.";
                        setErrorDescription(i18n("An error occured while parsing $WAKATIME_HOME/.wakatime.cfg. Check $WAKATIME_HOME/.wakatime.log for more details."));
                } else if (sender->exitCode() == 104) {
                        qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Invalid API key. Please make sure your API key is correct.";
                        setErrorDescription(i18n("Invalid API key. Please make sure your API key is correct."));
                }
        }
}

WakatimePluginView::WakatimePluginView(WakatimePlugin* plugin)
 : m_wakatimePlugin{plugin}
{
}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "wakatime-plugin.moc"
#include "moc_wakatime-plugin.cpp"
