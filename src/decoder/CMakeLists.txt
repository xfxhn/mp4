
add_library(decoder OBJECT decoder.cpp)


target_include_directories(decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PUBLIC ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/FileTypeBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/movieBox
        )