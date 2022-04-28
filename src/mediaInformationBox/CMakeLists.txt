

add_library(mediaInformationBox OBJECT mediaInformationBox.cpp)

target_include_directories(mediaInformationBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/dataInformationBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/sampleTableBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
        )