cmake_minimum_required(VERSION 3.0)

project(wakatime-plugin)

find_package(ECM "5.68.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

find_package(KDevPlatform 6.0.0 REQUIRED COMPONENTS
    Interfaces
    I18n
)

find_package(KF6I18n NO_MODULE REQUIRED)
ki18n_install(po)

add_subdirectory(src)

ecm_qt_install_logging_categories(
    EXPORT WAKATIME_PLUGIN
    FILE wakatime-plugin.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
