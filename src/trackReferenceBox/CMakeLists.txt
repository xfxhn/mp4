add_library(trackReferenceBox OBJECT trackReferenceBox.cpp)


target_include_directories(
        trackReferenceBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
)