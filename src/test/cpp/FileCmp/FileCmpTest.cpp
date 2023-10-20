#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "../../../main/cpp/FileCmp/FileCmp.hpp"

void CreateFileWith(const std::string name, const std::vector<char>& storage) {
    std::ofstream writer(name.c_str(), std::ios::trunc | std::ios::binary);
    writer.write(storage.data(), storage.size());
    writer.close();
}

TEST_CASE("Check Same Files, size 1") {
    CreateFileWith("first", {'A'});
    CreateFileWith("second", {'A'});

    FileCmp file_cmp(std::filesystem::path("first"), std::filesystem::path("second"));
    REQUIRE(file_cmp.evaluate() == 0);
}
