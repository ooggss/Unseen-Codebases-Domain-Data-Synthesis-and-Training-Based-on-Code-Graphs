#  _               _ 
# | |__   _____  _(_)
# | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
# | | | |  __/>  <| | Version 1.0
# |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

set(EXECUTABLE_NAME unit_tests)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*_new_test_case_*.cpp")

add_executable(${EXECUTABLE_NAME} ${TEST_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} gtest gtest_main)
target_include_directories(${EXECUTABLE_NAME} PRIVATE 
    ../include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
gtest_discover_tests(${EXECUTABLE_NAME})

# Copy data directory from tests folder
add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tests/data ${CMAKE_CURRENT_BINARY_DIR}/data)

INSTALL(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

