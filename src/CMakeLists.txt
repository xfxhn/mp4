



add_executable(MP4Decoder main.cpp)
add_subdirectory(bitStream)
add_subdirectory(decoder)
add_subdirectory(box)
add_subdirectory(fileTypeBox)
add_subdirectory(movieBox)
add_subdirectory(trackBox)
add_subdirectory(mediaBox)
add_subdirectory(mediaInformationBox)
add_subdirectory(dataInformationBox)
add_subdirectory(sampleTableBox)
add_subdirectory(test)


target_include_directories(MP4Decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/test
        )
target_link_libraries(MP4Decoder
        PRIVATE decoder bitStream box fileTypeBox movieBox trackBox mediaBox
        mediaInformationBox dataInformationBox sampleTableBox test
        )
