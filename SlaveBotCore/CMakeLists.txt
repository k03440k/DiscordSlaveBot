#cmake --build . --config Release --target Engine3D
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(PROJECT_CORE_NAME SlaveBotCore)

project(${PROJECT_CORE_NAME})

set(PUBLIC_INCLUDE_PATH includes/SlaveBot/)
set(PRIVATE_INCLUDE_PATH src/headers/)
set(PRIVATE_SOURCE_PATH src/sources/)

set(BOT_PUBLIC_INCLDUES
	${PUBLIC_INCLUDE_PATH}test.hpp
	)
set(BOT_PRIVATE_INCLUDES
	
	)
set(BOT_PRIVATE_SOURCES
	
	)

set(ALL_INCLUDES
	${BOT_PUBLIC_INCLDUES}
	${BOT_PRIVATE_INCLUDES}
	${BOT_PRIVATE_SOURCES}
	)

add_library(${PROJECT_CORE_NAME} STATIC
	${ALL_INCLUDES}
	)
	
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ALL_INCLUDES}
)

add_subdirectory(../external/dpp ${CMAKE_CURRENT_BINARY_DIR}/dpp)
target_link_libraries(${PROJECT_CORE_NAME} PUBLIC dpp)

target_include_directories(${PROJECT_CORE_NAME} PUBLIC
    ..external/dpp/include
)

target_include_directories(${PROJECT_CORE_NAME} PUBLIC includes)
target_include_directories(${PROJECT_CORE_NAME} PRIVATE src)
target_compile_features(${PROJECT_CORE_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_CORE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set_target_properties(${PROJECT_CORE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(TARGET ${PROJECT_CORE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_CORE_NAME}>/res)