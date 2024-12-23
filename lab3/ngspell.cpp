#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <chrono>
#include <iterator>

// Функция для извлечения 3-грамм из слова
std::vector<std::string> extract_ngrams(const std::string& word) {
    std::vector<std::string> ngrams;
    for (size_t i = 0; i + 3 <= word.size(); ++i) {
        ngrams.push_back(word.substr(i, 3));
    }
    return ngrams;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <dict_file_path>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::vector<std::string>> ngram_index;
    std::string word;

    // Заполнение обратного индекса
    const auto start_indexing = std::chrono::steady_clock::now();
    while (file >> word) {
        if (word.size() < 3) continue; // Игнорируем слова короче 3 символов
        auto ngrams = extract_ngrams(word);
        for (const auto& ngram : ngrams) {
            ngram_index[ngram].push_back(word);
        }
    }
    const auto finish_indexing = std::chrono::steady_clock::now();
    const auto duration_indexing = std::chrono::duration_cast<std::chrono::microseconds>(finish_indexing - start_indexing);

    std::cout << "Indexing time: " << duration_indexing.count() << " microseconds" << std::endl;
    std::cout << "Type words for searching (enter :q to quit):" << std::endl;

    std::string query;
    while (std::getline(std::cin, query)) {
        if (query == ":q") break;
        
        auto query_ngrams = extract_ngrams(query);
        std::unordered_map<std::string, int> candidate_count;

        // Подсчет слов-кандидатов по 3-граммам
        for (const auto& ngram : query_ngrams) {
            if (ngram_index.find(ngram) != ngram_index.end()) {
                for (const auto& candidate : ngram_index[ngram]) {
                    candidate_count[candidate]++;
                }
            }
        }

        // Найти максимальное количество попаданий
        std::vector<std::pair<std::string, int>> candidates(candidate_count.begin(), candidate_count.end());
        if (!candidates.empty()) {
            std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
                return a.second > b.second || (a.second == b.second && a.first < b.first);
            });

            // Найти максимальный вес
            int max_count = candidates.front().second;
            std::set<std::string> result;
            for (const auto& candidate : candidates) {
                if (candidate.second == max_count) {
                    result.insert(candidate.first);
                }
            }

            // Вывод результата
            std::cout << result.size() << " candidates found:" << std::endl;
            for (const auto& res : result) {
                std::cout << res << std::endl;
            }
        } else {
            std::cout << "No candidates found." << std::endl;
        }
    }

    return 0;
}