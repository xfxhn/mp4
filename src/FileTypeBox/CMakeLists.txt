

add_library(FileTypeBox OBJECT FileTypeBox.cpp)


target_include_directories(FileTypeBox
        PUBLIC ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )