#ifndef UTILTY_H
#define UTILTY_H
#include <unordered_map>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>

namespace my_impl
{

namespace utility 
{

template <typename T, typename U>
inline void print(const std::unordered_map<T, U>& map) 
{
    for(auto&& [key, value] : map) {
        std::cout << "key: " << key 
        << " with value: " << value <<  std::endl;
    }
    
}

inline std::stringstream readFile(const std::filesystem::path& filePath) 
{
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

} //namespace utility

} // namespace my_impl

#endif //UTILTY_H