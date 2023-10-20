#include "FileCmp/FileCmp.hpp"
#include <fstream>
#include <cmath>

size_t GetFileSize(std::filesystem::path file) {
    std::ifstream file_read_stream(file.string().c_str(), std::ios::binary | std::ios::ate);
    size_t size = file_read_stream.tellg();
    file_read_stream.close();

    return size;
}

size_t FastFileCmp(std::filesystem::path first, std::filesystem::path second) {
    size_t first_file_size = GetFileSize(first);
    size_t second_file_size = GetFileSize(second);

    size_t min_size = std::min(first_file_size, second_file_size);

    int scale_parametr = std::max(1, static_cast<int>(std::pow(min_size, 3.0/5)));

    FileCmp file_cmp(first, second, scale_parametr);
    return file_cmp.evaluate();
}