#include <gtest/gtest.h>
#include <filesystem>
#include <ranges>
#include "lexer.hpp"
#include "ram.hpp"

namespace fs = std::filesystem;

std::stringstream readFile(const std::filesystem::path& filePath) {
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error(std::string("File does not exist: ") + filePath.string());
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + filePath.string());
    }

    std::string line;
    std::stringstream stream;
    while (std::getline(file, line)) {
        stream << line << std::endl;
    }
    file.close();
    return stream;
}

std::vector<int> parseOutputString(const std::string& str) {
    std::istringstream iss(str);
    std::vector<int> numbers;
    std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(numbers));
    return numbers;
}

std::vector<std::string> getFiles(const std::string& directoryPath) {
    std::vector<fs::directory_entry> filteredEntries;

    std::copy_if(
        fs::directory_iterator(directoryPath),
        fs::directory_iterator(),
        std::back_inserter(filteredEntries),
        [](const fs::directory_entry& entry) {
            return entry.is_regular_file();
        }
    );

    std::vector<std::string> files;
    std::transform(
        filteredEntries.begin(),
        filteredEntries.end(),
        std::back_inserter(files),
        [](const fs::directory_entry& entry) {
            return entry.path().string();
        }
    );

    return files;
}

std::unordered_map<int, std::string> single_answers;

class MyTestEnvironment final : public ::testing::Environment {
public:
    ~MyTestEnvironment() override {}

    void SetUp() override {
        file_path_ = "../test/data/single/";
        auto single_files = getFiles(file_path_);
        std::sort(std::begin(single_files), std::end(single_files), std::less<std::string>());

        size_t num = 1;
        for(auto&& file: single_files) {
            single_answers.emplace(num++, file);
        }
    }

    void TearDown() override {}
private:
    std::string file_path_;
};

::testing::Environment* const my_env = ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);


class FooTest: public testing::TestWithParam<int> {};

INSTANTIATE_TEST_SUITE_P(foo, FooTest, ::testing::Values(1,2,3,4,5,6,7,8,9));


TEST_P(FooTest, Test1) {
    try {
        auto file = single_answers.at(GetParam());
        auto stream = readFile(file);
        auto driver = std::make_unique<my_impl::Driver>(stream);
        driver->parse();

        EXPECT_EQ(std::stoi(driver->output()), GetParam());
        
    }
    catch(const std::exception& excep) {
        FAIL() << excep.what();
    }
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

