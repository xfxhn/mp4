


add_library(visualSampleEntry OBJECT visualSampleEntry.cpp)

target_include_directories(visualSampleEntry PUBLIC ${PROJECT_SOURCE_DIR}/src/xiaofeng)

target_include_directories(visualSampleEntry
        PRIVATE ${PROJECT_SOURCE_DIR}/src/box
        PRIVATE ${PROJECT_SOURCE_DIR}/src/bitStream
        PRIVATE ${PROJECT_SOURCE_DIR}/src/unknownBox
        )



