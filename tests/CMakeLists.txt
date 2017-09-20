add_executable(samples_test
        ../src/sample.hpp
        tests.cpp)

add_test(NAME samples_test
        COMMAND testDriver --exe $<TARGET_FILE:sample_test>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)