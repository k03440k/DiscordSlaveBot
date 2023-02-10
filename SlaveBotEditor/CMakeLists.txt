cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(EDITOR_PROJECT_NAME SlaveBotEditor)

project(${EDITOR_PROJECT_NAME})

set(SCRIPT_PATH src/)
add_executable(${EDITOR_PROJECT_NAME}
    ${SCRIPT_PATH}main.cpp
)

#add_subdirectory(../Engine3DCore ${CMAKE_CURRENT_BINARY_DIR}/Engine3DCore)
target_link_libraries(${EDITOR_PROJECT_NAME} PRIVATE SlaveBotCore)
target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)