#include "String.hpp"

// Конструктор по умолчанию
String::String() : data(new char[1]{ '\0' }), length(0) {}

// Конструктор от C-строки
String::String(const char* str) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    } else {
        length = 0;
        data = new char[1]{ '\0' };
    }
}

// Конструктор копирования
String::String(const String& other) : String(other.data) {}

// Оператор присваивания копированием
String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] data;  // Освобождаем старый массив
        data = new char[other.length + 1];
        std::strcpy(data, other.data);
        length = other.length;
    }
    return *this;
}

// Деструктор
String::~String() {
    delete[] data;
}

// Конструктор перемещения
String::String(String&& other) noexcept : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}

// Оператор присваивания перемещением
String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] data;  // Освобождаем старый массив
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

// Возвращает C-строку
const char* String::c_str() const {
    return data;
}

// Возвращает символ с проверкой индекса
char String::at(size_t idx) const {
    if (idx >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[idx];
}

// Возвращает размер строки
size_t String::size() const {
    return length;
}