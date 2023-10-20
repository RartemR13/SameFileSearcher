add_executable(FileCmpTest FileCmpTest.cpp)
target_link_libraries(FileCmpTest 
    PRIVATE Catch2::Catch2WithMain
    PRIVATE FileCmp
)
