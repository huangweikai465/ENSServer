#包括文件
aux_source_directory(${PROJECT_SOURCE_DIR}/Src/cJSON SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/Src/Socket SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/Src/Log SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/Src/Server SRCS_SERVER)
#服务端库
add_library(${ENSSERVERLIBNAME} STATIC ${SRCS} ${SRCS_SERVER})

IF (UNIX)
	target_link_libraries(${ENSSERVERLIBNAME} pthread)
ELSEIF (WIN32)
	target_link_libraries(${ENSSERVERLIBNAME} Iphlpapi ws2_32)
ENDIF (UNIX)

