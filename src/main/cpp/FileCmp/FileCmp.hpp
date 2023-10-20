#pragma once

#include <filesystem>
#include <vector>

class FileCmp {
public:
    FileCmp(std::filesystem::path, std::filesystem::path, size_t scale_parametr = 1);
    FileCmp() = delete;
    FileCmp(const FileCmp&) = delete;
    ~FileCmp() = default;

    size_t evaluate();

private:
    std::vector<char>* createFileStorage(std::filesystem::path);
    bool checkMatch(const std::vector<char>&, const std::vector<char>&, size_t, size_t);

    const std::filesystem::path first_file_;
    const std::filesystem::path second_file_;
    const size_t scale_parametr_;
};