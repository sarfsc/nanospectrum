find_package(Qt5 COMPONENTS Widgets Qml LinguistTools REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
    aboutdialog.h
    commandlineoptions.h
    commandlineparser.h
    gui.h
    mainwindow.h
)

set(SOURCES
    aboutdialog.cpp
    commandlineparser.cpp
    gui.cpp
    mainwindow.cpp
)

set(UI_FORMS
    aboutdialog.ui
    mainwindow.ui
)

set(MOC_HEADERS
    aboutdialog.h
    mainwindow.h
)

set(TS_FILES
    i18n/gui_en.ts
    i18n/gui_ru.ts
)

set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})

qt5_add_translation(QM_FILES ${TS_FILES})

qt5_wrap_ui(UI_SOURCES ${UI_FORMS})
qt5_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_definitions(
    -DNANOSPECTRUM_GUI_LIBRARY
)

add_translation_resource(RESOURCES_SRC ${QM_FILES})

qt5_add_resources(LIB_RESOURCES ${RESOURCES_SRC} ${ICON_RESOURCES})

add_project_library(nanospectrum-gui ${UI_SOURCES} ${MOC_SOURCES} ${SOURCES} ${LIB_RESOURCES})
target_link_libraries(nanospectrum-gui Qt5::Widgets Qt5::Qml)
target_link_libraries(nanospectrum-gui nanospectrum-model)
