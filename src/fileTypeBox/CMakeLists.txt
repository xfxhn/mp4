add_library(fileTypeBox OBJECT fileTypeBox.cpp)


target_include_directories(fileTypeBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )