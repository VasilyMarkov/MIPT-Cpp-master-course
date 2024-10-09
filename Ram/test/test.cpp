#include <gtest/gtest.h>
#include <filesystem>
#include "lexer.hpp"

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

void createAndExecuteLexer(std::stringstream& input_stream) {
    yy::RamLexer lexer;
    lexer.switch_streams(input_stream, std::cout);
    while (lexer.yylex() != 0) {}
}

std::streambuf* setupLocalStreamBuffer(std::stringstream& buffer) {
    auto sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    return sbuf;
}

TEST(Ram, Test1) {
    try {
        auto input_stream = readFile("../test/data/1.in");
        std::stringstream buffer;
        auto local_buf = setupLocalStreamBuffer(buffer);

        createAndExecuteLexer(input_stream);

        std::stringstream out_buffer;
        out_buffer << std::cout.rdbuf(local_buf);
        
        EXPECT_EQ(std::stoi(out_buffer.str()), 3);
        
    }
    catch(const std::exception& excep) {
        FAIL() << excep.what();
    }
}

TEST(Ram, Test2) {
    try {
        auto input_stream = readFile("../test/data/2.in");
        std::stringstream buffer;
        auto local_buf = setupLocalStreamBuffer(buffer);

        createAndExecuteLexer(input_stream);

        std::stringstream out_buffer;
        out_buffer << std::cout.rdbuf(local_buf);
        
        EXPECT_EQ(std::stoi(out_buffer.str()), 4);
    }
    catch(const std::exception& excep) {
        FAIL() << excep.what();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

