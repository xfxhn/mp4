



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
add_subdirectory(visualSampleEntry)
add_subdirectory(trackReferenceBox)
add_subdirectory(audioSampleEntry)
add_subdirectory(xiaofeng)
add_subdirectory(userDataBox)
add_subdirectory(metaBox)
add_subdirectory(mediaDataBox)
add_subdirectory(unknownBox)

target_include_directories(MP4Decoder
        PRIVATE ${PROJECT_SOURCE_DIR}/src/decoder
        )
target_link_libraries(MP4Decoder
        PRIVATE sampleEntry decoder bitStream box fileTypeBox movieBox trackBox mediaBox
        mediaInformationBox dataInformationBox sampleTableBox visualSampleEntry trackReferenceBox audioSampleEntry
        userDataBox unknownBox metaBox mediaDataBox
        )
