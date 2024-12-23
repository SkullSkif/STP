#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> frequency;
    const auto start_fill = std::chrono::steady_clock::now();
    
    std::string word;
    while (file >> word) {
        frequency[word]++;
    }
    
    const auto finish_fill = std::chrono::steady_clock::now();
    const auto duration_fill = std::chrono::duration_cast<std::chrono::microseconds>(finish_fill - start_fill);

    std::vector<std::pair<std::string, int>> sorted_freq(frequency.begin(), frequency.end());
    const auto start_sort = std::chrono::steady_clock::now();
    
    std::sort(sorted_freq.begin(), sorted_freq.end(), [](const auto& a, const auto& b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    });
    
    const auto finish_sort = std::chrono::steady_clock::now();
    const auto duration_sort = std::chrono::duration_cast<std::chrono::microseconds>(finish_sort - start_sort);

    for (size_t i = 0; i < std::min(sorted_freq.size(), size_t(10)); ++i) {
        std::cout << sorted_freq[i].second << " " << sorted_freq[i].first << std::endl;
    }

    std::cout << "build: " << duration_fill.count() << std::endl;
    std::cout << "sort: " << duration_sort.count() << std::endl;

    return 0;
}