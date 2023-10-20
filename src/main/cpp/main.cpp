#include <iostream>

#include "FileList.cpp"
#include "FastFileCmp.cpp"

int main() {
    std::cout << "Enter a first directory: ";
    
    std::string first_dir;
    std::cin >> first_dir;
    std::filesystem::path first_dir_path(first_dir);

    std::cout << "Enter a second directory: ";

    std::string second_dir;
    std::cin >> second_dir;
    std::filesystem::path second_dir_path(second_dir);

    std::cout << "Enter a percent: ";
    size_t percent = 0;
    std::cin >> percent;

    auto first_dir_list = FileList(first_dir_path);
    auto second_dir_list = FileList(second_dir_path);

    std::vector<std::vector<size_t>> cmp_results(first_dir_list.size(), std::vector<size_t>(second_dir_list.size()));
    for (size_t i = 0; i < cmp_results.size(); ++i) {
        for (size_t j = 0; j < cmp_results[i].size(); ++j) {
            size_t max_size = std::max(GetFileSize(first_dir_list[i]), GetFileSize(second_dir_list[j]));
            cmp_results[i][j] = (1.0 * (max_size - FastFileCmp(first_dir_list[i], second_dir_list[j]))) / max_size * 100;
        }
    }

    std::vector<std::pair<size_t, size_t>> same;    
    for (size_t i = 0; i < cmp_results.size(); ++i) {
        for (size_t j = i + 1; j < cmp_results[i].size(); ++j) {
            if (cmp_results[i][j] == 100) {
                same.push_back({i, j});
            }
        }
    }

    std::vector<std::pair<size_t, size_t>> near;

    for (size_t i = 0; i < cmp_results.size(); ++i) {
        for (size_t j = i + 1; j < cmp_results[i].size(); ++j) {
            if (cmp_results[i][j] >= percent) {
                same.push_back({i, j});
            }
        }
    }

    std::cout << "Same Files:\n";

    for (auto pair : same) {
        std::cout << first_dir + "/" + first_dir_list[pair.first].string() + " - " +
                        second_dir + "/" + second_dir_list[pair.second].string() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Near Same\n";

    for (auto pair : near) {
        std::cout << first_dir + "/" + first_dir_list[pair.first].string() + " - " +
                        second_dir + "/" + second_dir_list[pair.second].string() << std::endl;
    }
}