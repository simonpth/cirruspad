cmake_minimum_required(VERSION 3.16)

project(cirruspad VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appcirruspad
    main.cpp
)

qt_add_qml_module(appcirruspad
    URI cirruspad
    VERSION 1.0
    QML_FILES
        Main.qml
        Dashboard.qml
        NoteView.qml
        TodoView.qml
        Sidebar.qml
        WorkspaceLoader.qml
        CreateItemDialog.qml
        RenameDialog.qml
    RESOURCES
        assets/icons/folder.svg
        assets/icons/note.svg
        assets/icons/todo.svg

    SOURCES
        filesystemnode.h filesystemnode.cpp
        foldernode.h foldernode.cpp
        filenode.h
        notenode.h notenode.cpp
        todonode.h todonode.cpp
        filesystemmodel.h filesystemmodel.cpp
        maincontroller.h maincontroller.cpp

)

set_target_properties(appcirruspad PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcirruspad
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appcirruspad
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
