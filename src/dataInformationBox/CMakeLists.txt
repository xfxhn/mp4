

add_library(dataInformationBox OBJECT dataInformationBox.cpp)

target_include_directories(dataInformationBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
        )