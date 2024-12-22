#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>

std::string soundex(const std::string& name) {
    // Проверка на наличие недопустимых символов
    if (!std::all_of(name.begin(), name.end(), [](char c) { return std::isalpha(c); })) {
        return "0000";
    }

    // Приведение к верхнему регистру
    std::string upper_name = name;
    std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(), ::toupper);

    // Запоминаем первую букву
    char first_letter = upper_name[0];

    // Удаляем h и w, кроме первой буквы
    std::string filtered_name;
    filtered_name += first_letter; // добавляем первую букву
    std::copy_if(upper_name.begin() + 1, upper_name.end(), std::back_inserter(filtered_name),
                 [](char c) { return c != 'H' && c != 'W'; });

    // Заменяем согласные на цифры
    std::unordered_map<char, char> soundex_map = {
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    };

    std::string soundex_code;
    soundex_code += first_letter; // добавляем первую букву

    // Заменяем согласные на цифры
    for (char c : filtered_name) {
        if (soundex_map.count(c)) {
            char code = soundex_map[c];
            // Добавляем код, если он не равен последнему добавленному коду
            if (soundex_code.back() != code) {
                soundex_code += code;
            }
        }
    }

    // Удаляем гласные (a, e, i, o, u, y) кроме первой буквы
    soundex_code.erase(std::remove_if(soundex_code.begin() + 1, soundex_code.end(),
                                       [](char c) { return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y'; }),
                       soundex_code.end());

    // Обрезаем до 4 символов и добавляем нули, если нужно
    soundex_code.resize(4, '0');

    return soundex_code;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: soundex <name>" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    std::string result = soundex(name);
    std::cout << result << std::endl;

    return 0;
}