find_package(Qt5 COMPONENTS Core Gui REQUIRED)

set(HEADERS
    common.h
    model.h
    plugin.h
    pluginstorage.h
)

set(SOURCES
    model.cpp
    plugin.cpp
    pluginstorage.cpp
)

add_definitions(
    -DNANOSPECTRUM_MODEL_LIBRARY
)

add_project_library(nanospectrum-model ${SOURCES})
target_link_libraries(nanospectrum-model Qt5::Core Qt5::Gui)
