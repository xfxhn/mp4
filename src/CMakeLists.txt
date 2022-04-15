



add_executable(MP4Decoder main.cpp)

add_subdirectory(bitStream)
add_subdirectory(decoder)
add_subdirectory(box)
add_subdirectory(FileTypeBox)
add_subdirectory(movieBox)
add_subdirectory(trackBox)
add_subdirectory(mediaBox)
add_subdirectory(mediaInformationBox)

target_link_libraries(MP4Decoder
        PRIVATE decoder bitStream box FileTypeBox movieBox trackBox mediaBox mediaInformationBox
        )
target_include_directories(MP4Decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/decoder
        )