

add_library(sampleTableBox OBJECT sampleTableBox.cpp)

target_include_directories(sampleTableBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/visualSampleEntry
        )