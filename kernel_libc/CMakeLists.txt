set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(kernel_libc STATIC
        assert.c
        error_handling.c
        format.c
        io.c
        math.c
        memory_functions.c
        string.c
        unistd.c
        stdlib.c
)
target_include_directories(kernel_libc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(kernel_libc kernel memory)