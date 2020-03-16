add_executable(main main.cpp)

include_directories(../custom_string_lib)

target_link_libraries(main custom_string_lib)