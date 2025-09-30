cmake_minimum_required(VERSION 3.16)

project(compu-graph-1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(compu-graph-1
    main.cpp
    Window.cpp
    Window.h
    CanvasContainer.cpp
    CanvasContainer.h
    # linewidget.cpp
    # linewidget.h
    # mainwindow.cpp
    # mainwindow.h
    # mainwindow.ui
)

target_link_libraries(compu-graph-1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(compu-graph-1 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS compu-graph-1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
