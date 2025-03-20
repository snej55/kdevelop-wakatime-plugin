set(wakatime-plugin_SRCS
    wakatime-plugin.cpp
)

ecm_qt_declare_logging_category(wakatime-plugin_SRCS
    HEADER debug.h
    IDENTIFIER PLUGIN_WAKATIME_PLUGIN
    CATEGORY_NAME "kdevelop.plugins.wakatime-plugin"
    DESCRIPTION "KDevelop plugin: wakatime-plugin"
    EXPORT WAKATIME_PLUGIN
)

kdevplatform_add_plugin(wakatime-plugin
    SOURCES ${wakatime-plugin_SRCS}
)

target_link_libraries(wakatime-plugin
    KDev::Interfaces
    KF6::I18n
    KF6TextEditor
)
