



add_executable(MP4Decoder main.cpp)

add_subdirectory(bitStream)
add_subdirectory(decoder)
add_subdirectory(box)
add_subdirectory(FileTypeBox)

target_link_libraries(MP4Decoder
        PRIVATE decoder bitStream box FileTypeBox
        )
target_include_directories(MP4Decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/decoder
        )