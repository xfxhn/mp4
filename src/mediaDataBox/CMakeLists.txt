add_library(mediaDataBox OBJECT mediaDataBox.cpp)

target_include_directories(mediaDataBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )