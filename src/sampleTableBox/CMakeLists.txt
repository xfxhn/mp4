

add_library(sampleTableBox OBJECT sampleTableBox.cpp)

target_include_directories(sampleTableBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        )