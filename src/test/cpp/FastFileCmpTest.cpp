#include "../../main/cpp/FastFileCmp.cpp"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

void CreateFileWith(const std::string name, const std::vector<char>& storage) {
    std::ofstream writer(name.c_str(), std::ios::trunc | std::ios::binary);
    writer.write(storage.data(), storage.size());
    writer.close();
}

TEST_CASE("Check Big Files") {
    std::vector<char> big_file_first(10'000'000, 'A');
    std::vector<char> big_file_second(10'000'000, 'A');
    CreateFileWith("first", big_file_first);
    CreateFileWith("second", big_file_second);


    auto cmp_value = FastFileCmp(std::filesystem::path("first"), std::filesystem::path("second"));
    REQUIRE(cmp_value == 0);
}