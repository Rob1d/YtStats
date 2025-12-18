cmake_minimum_required(VERSION 3.16)

project(YtStats VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets QuickControls2 QuickDialogs2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appYtStats
    main.cpp
)

qt_add_qml_module(appYtStats
    URI YtStats
    VERSION 1.0
    SOURCES
        modules/FileLoader/FileLoader.hpp
        modules/FileLoader/FileLoader.cpp
    QML_FILES
        Main.qml
        modules/FileLoader/FileLoaderBtn.qml
)

target_include_directories(appYtStats PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/modules/FileLoader)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appYtStats PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appYtStats
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appYtStats
    PRIVATE Qt6::Quick Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appYtStats
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
