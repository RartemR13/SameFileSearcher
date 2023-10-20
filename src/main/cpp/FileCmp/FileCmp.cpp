#include "FileCmp.hpp"

#include <stdexcept>
#include <fstream>
#include <vector>

FileCmp::FileCmp(std::filesystem::path first_file, std::filesystem::path second_file, size_t scale_parametr) :
    first_file_(first_file),
    second_file_(second_file),
    scale_parametr_(scale_parametr)
{
    if (scale_parametr < 1) {
        throw std::invalid_argument("Scale parametr must be greater or equal then 1.");
    }
}

std::vector<char>* FileCmp::createFileStorage(std::filesystem::path file) {
    std::ifstream file_read_stream(file.string().c_str(), std::ios::binary | std::ios::ate);

    std::vector<char>* storage_ptr = new std::vector<char>(file_read_stream.tellg());
    file_read_stream.read(storage_ptr->data(), storage_ptr->size());
    file_read_stream.close();

    return storage_ptr;
}

bool FileCmp::checkMatch(const std::vector<char>& first, const std::vector<char>& second,
                         size_t first_pos, size_t second_pos) {
    
    size_t len = scale_parametr_;
    len = std::min(len, first.size() - first_pos);
    len = std::min(len, second.size() - second_pos);

    size_t l = first_pos - 1;
    size_t r = second_pos - 1;

    for (size_t i = 0; i < len; ++i) {
        if (first[l] != second[r]) {
            return false;
        }
    }

    return true;
}

size_t FileCmp::evaluate() {
    auto first_storage_ptr = createFileStorage(first_file_);
    auto first_storage = std::move(*first_storage_ptr);
    delete first_storage_ptr;

    auto second_storage_ptr = createFileStorage(second_file_);
    auto second_storage = std::move(*second_storage_ptr);
    delete second_storage_ptr;

    size_t first_size = first_storage.size() / scale_parametr_ + (first_storage.size() % scale_parametr_ > 0);
    size_t second_size = first_storage.size() / scale_parametr_ + (first_storage.size() % scale_parametr_ > 0);

    std::vector<std::vector<size_t>> levenstein_dist(first_size + 1, 
        std::vector<size_t>(second_size + 1, std::numeric_limits<size_t>::max()));

    for (size_t i = 0; i <= first_size; ++i) {
        for (size_t j = 0; j <= second_size; ++j) {
            if (i == 0) {
                levenstein_dist[i][j] = j;
                continue;
            }

            if (j == 0) {
                levenstein_dist[i][j] = i;
                continue;
            }

            auto match = checkMatch(first_storage, second_storage, i, j);
            levenstein_dist[i][j] = std::min(levenstein_dist[i][j], levenstein_dist[i-1][j-1] + (1 - match));

            levenstein_dist[i][j] = std::min(levenstein_dist[i][j], levenstein_dist[i-1][j] + 1);
            levenstein_dist[i][j] = std::min(levenstein_dist[i][j], levenstein_dist[i][j-1] + 1);
        }
    }

    return levenstein_dist[first_size][second_size];
}