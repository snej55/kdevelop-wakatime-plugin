#ifndef WAKATIME_PLUGIN_H
#define WAKATIME_PLUGIN_H

#include <interfaces/iplugin.h>
#include <interfaces/icore.h>
#include <interfaces/idocument.h>

#include <QDateTime>

#define KDEV_WAKATIME_PLUGIN_VERSION "1.0.0"

struct HeartBeat {
    QDateTime time;
    QUrl fileUrl;
};

class WakatimePlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    // KPluginFactory-based plugin wants constructor with this signature
    WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args);

    ~WakatimePlugin();

    // connect KDevelop::documentController signals to Q_SLOTS
    void addListeners(); // done

    // get project name
    QString getProjectName(QUrl fileUrl); // done
    // get document name
    QString getFileName(QUrl fileUrl); // done

public Q_SLOTS:
    // document events
    void documentSwitched(void* document);
    void documentModified(void* document);
    void documentClosed(void* document);
    void documentSaved(void* document);
    void documentOpened(void* document);

protected:
    QStringList buildHeartbeat(QString file, QString project, bool isWrite) const; // done
    void sendHeartbeat(QStringList options); // done
    HeartBeat* getLastHeartbeat(); // done
    void updateLastHeartbeat(QUrl fileUrl); // done

    QString getWakatimeBinDir();
    void checkWakatimeBin();

    bool enoughTimePassed(QDateTime time) const;  // done

    HeartBeat* m_lastHeartBeat {nullptr};
};

class WakatimePluginView : public QObject
{
    Q_OBJECT

public:
    explicit WakatimePluginView(WakatimePlugin* plugin);

private:
    WakatimePlugin* m_wakatimePlugin {nullptr};
};

#endif // WAKATIME_PLUGIN_H
