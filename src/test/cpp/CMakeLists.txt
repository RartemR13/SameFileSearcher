add_executable(FastFileCmpTest FastFileCmpTest.cpp)
target_link_libraries(FastFileCmpTest
    PRIVATE Catch2::Catch2WithMain
    PRIVATE FastFileCmp
)

add_subdirectory(FileCmp)
add_test(FileCmpTest FileCmpTest)