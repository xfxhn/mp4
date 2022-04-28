


add_library(unknownBox OBJECT unknownBox.cpp)

target_include_directories(unknownBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )