add_library(audioSampleEntry OBJECT audioSampleEntry.cpp)

target_include_directories(audioSampleEntry
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/xiaofeng
        )