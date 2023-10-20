#include <filesystem>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <stdexcept>
#include <algorithm>

std::vector<std::filesystem::path> FileList(std::filesystem::path directory) {
    struct stat directory_stat = {};
    if (stat(directory.string().c_str(), &directory_stat) == 0 && !(directory_stat.st_mode & S_IFDIR)) {
        throw std::invalid_argument("It is not directory");
    }

    std::vector<std::filesystem::path> ret;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();

        std::reverse(outfilename_str.begin(), outfilename_str.end());
        outfilename_str.resize(outfilename_str.find('/'));
        std::reverse(outfilename_str.begin(), outfilename_str.end());

        ret.push_back(outfilename_str);
    }

    return ret;
} 