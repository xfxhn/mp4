

add_library(box OBJECT box.cpp)

target_include_directories(box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        )