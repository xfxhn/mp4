





add_library(movieBox OBJECT movieBox.cpp)

target_include_directories(movieBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/trackBox
        PRIVATE ${PROJECT_SOURCE_DIR}/src/userDataBox
        )