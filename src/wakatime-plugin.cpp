#include "wakatime-plugin.h"

#include <debug.h>

#include <KPluginFactory>

#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>

#include <QDir>
#include <QStandardPaths>

K_PLUGIN_FACTORY_WITH_JSON(wakatime_pluginFactory, "wakatime-plugin.json", registerPlugin<WakatimePlugin>(); )

WakatimePlugin::WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("wakatime-plugin"), parent, metaData)
{
    Q_UNUSED(args);

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
    connect(KDevelop::ICore::self()->documentController(),
            &KDevelop::IDocumentController::documentJumpPerformed,
            this,
            &WakatimePlugin::documentModified);
    connect(KDevelop::ICore::self()->documentController(),
            &KDevelop::IDocumentController::documentClosed,
            this,
            &WakatimePlugin::documentClosed);
    connect(KDevelop::ICore::self()->documentController(),
            &KDevelop::IDocumentController::documentOpened,
            this,
            &WakatimePlugin::documentOpened);
    connect(KDevelop::ICore::self()->documentController(),
            &KDevelop::IDocumentController::documentSaved,
            this,
            &WakatimePlugin::documentSaved);
    connect(KDevelop::ICore::self()->documentController(),
            &KDevelop::IDocumentController::documentLoaded,
            this,
            &WakatimePlugin::documentSwitched);
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

void WakatimePlugin::documentSwitched(void* document)
{
        KDevelop::IDocument* doc {static_cast<KDevelop::IDocument*>(document)};
        if (enoughTimePassed(QDateTime::currentDateTime())) {

        }
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


bool WakatimePlugin::enoughTimePassed(QDateTime time) const
{
        return time.secsTo(m_lastHeartBeat->time) >= 1200000;
}

QStringList WakatimePlugin::buildHeartbeat(QString file, QString project, const bool isWrite) const
{
        QStringList options;
        options << "--entity" << file;

        // if project isn't empty
        if (!project.isEmpty()) {
                options << "--alternate-project" << project;
        }

        if (isWrite) {
                options << "--write";
        }

        QString pluginTitle {"kdevelop-wakatime-plugin"};
        pluginTitle.append(QString{KDEV_WAKATIME_PLUGIN_VERSION});
        options << "--plugin" << pluginTitle;

        // locate config path
        QString configPath {QStandardPaths::locate(QStandardPaths::HomeLocation, QStringLiteral(".wakatime.cfg"))};
        if (!configPath.isEmpty()) {
                options << "--config" << configPath;
        }

        return options;
}

void WakatimePlugin::sendHeartbeat(bool isWrite)
{
        QStringList arguments;

}

WakatimePluginView::WakatimePluginView(WakatimePlugin* plugin)
 : m_wakatimePlugin{plugin}
{
}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "wakatime-plugin.moc"
#include "moc_wakatime-plugin.cpp"
