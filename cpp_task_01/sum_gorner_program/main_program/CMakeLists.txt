add_executable(main_program main.cpp)

include_directories(../rationals_lib)

target_link_libraries(main_program rationals_lib)