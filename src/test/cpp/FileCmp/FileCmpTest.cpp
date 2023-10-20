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

TEST_CASE("Check Different Files") {
    CreateFileWith("first", {'A', 'B', 'A'});
    CreateFileWith("second", {'B'});

    FileCmp file_cmp(std::filesystem::path("first"), std::filesystem::path("second"));
    REQUIRE(file_cmp.evaluate() == 2);
}

TEST_CASE("Check Big Files") {
    std::vector<char> big_file_first;
    for (int i = 0; i < 10'000; ++i) {
        if (i % 2 == 0) {
            big_file_first.push_back('A');
        } else {
            big_file_first.push_back('B');
        }
    }

    std::vector<char> big_file_second(10'000, 'B');
    CreateFileWith("first", big_file_first);
    CreateFileWith("second", big_file_second);

    FileCmp file_cmp(std::filesystem::path("first"), std::filesystem::path("second"));
    REQUIRE(file_cmp.evaluate() == 5'000);
}

TEST_CASE("Check with other scale parametr") {
    CreateFileWith("first", {'A', 'B', 'C', 'D'});
    CreateFileWith("second", {'A', 'B', 'A'});

    FileCmp file_cmp(std::filesystem::path("first"), std::filesystem::path("second"), 2);
    REQUIRE(file_cmp.evaluate() == 1);
}
