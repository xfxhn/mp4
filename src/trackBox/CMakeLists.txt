

add_library(trackBox OBJECT trackBox.cpp)


target_include_directories(trackBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/mediaBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/trackReferenceBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/UserDataBox
        )