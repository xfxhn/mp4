

add_library(userDataBox OBJECT userDataBox.cpp)

target_include_directories(userDataBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/mediaBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/metaBox
        )