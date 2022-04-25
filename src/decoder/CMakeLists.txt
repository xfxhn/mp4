
add_library(decoder OBJECT decoder.cpp)


target_include_directories(decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PUBLIC ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/fileTypeBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/movieBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/sampleEntry
        )