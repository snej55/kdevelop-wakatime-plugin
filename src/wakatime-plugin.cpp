#include "wakatime-plugin.h"

#include <debug.h>

#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(wakatime_pluginFactory, "wakatime-plugin.json", registerPlugin<WakatimePlugin>(); )

WakatimePlugin::WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("wakatime-plugin"), parent, metaData)
{
    Q_UNUSED(args);

    qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Hello world, my plugin is loaded!";
}

WakatimePlugin::~WakatimePlugin() noexcept
{
}


// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "wakatime-plugin.moc"
#include "moc_wakatime-plugin.cpp"
