

add_library(mediaBox OBJECT mediaBox.cpp handlerBox.cpp)


target_include_directories(mediaBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/mediaInformationBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
        )