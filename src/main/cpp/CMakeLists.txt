add_library(FastFileCmp FastFileCmp.cpp)
target_link_libraries(FastFileCmp PRIVATE FileCmp)

add_executable(main main.cpp)

add_subdirectory(FileCmp)