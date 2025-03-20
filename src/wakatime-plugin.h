#ifndef WAKATIME_PLUGIN_H
#define WAKATIME_PLUGIN_H

#include <interfaces/iplugin.h>

class WakatimePlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    // KPluginFactory-based plugin wants constructor with this signature
    WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args);

    ~WakatimePlugin();
};

#endif // WAKATIME_PLUGIN_H
