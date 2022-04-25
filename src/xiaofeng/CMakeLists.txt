add_library(sampleEntry OBJECT sampleEntry.cpp)


target_include_directories(sampleEntry
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )