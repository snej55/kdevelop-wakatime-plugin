#include "wakatime-plugin.h"

#include <debug.h>

#include <KPluginFactory>

#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>

K_PLUGIN_FACTORY_WITH_JSON(wakatime_pluginFactory, "wakatime-plugin.json", registerPlugin<WakatimePlugin>(); )

WakatimePlugin::WakatimePlugin(QObject* parent, const KPluginMetaData& metaData, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("wakatime-plugin"), parent, metaData)
{
    Q_UNUSED(args);

    qCDebug(PLUGIN_WAKATIME_PLUGIN) << "Wakatime plugin is loaded!";
}

WakatimePlugin::~WakatimePlugin()
{
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

WakatimePluginView::WakatimePluginView(WakatimePlugin* plugin)
 : m_wakatimePlugin{plugin}
{

}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "wakatime-plugin.moc"
#include "moc_wakatime-plugin.cpp"
