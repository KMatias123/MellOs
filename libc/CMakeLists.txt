set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(mellos_libc STATIC
        error_handling.c
        format.c
        math.c
        string.c
        assert.c
        memory_functions.c
        unistd.c
        memory_allocator/bitmap_allocator.c
)
target_include_directories(mellos_libc PUBLIC include)
target_link_libraries(mellos_libc utils)