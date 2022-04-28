add_library(metaBox OBJECT metaBox.cpp)

target_include_directories(metaBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/mediaBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
        )