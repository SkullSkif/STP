#include <cstring>
#include <stdexcept>

class String {
public:
    // Конструктор по умолчанию
    String();

    // Конструктор от C-строки
    String(const char* str);

    // Конструктор копирования
    String(const String& other);

    // Оператор присваивания копированием
    String& operator=(const String& other);

    // Деструктор
    ~String();

    // Конструктор перемещения
    String(String&& other) noexcept;

    // Оператор присваивания перемещением
    String& operator=(String&& other) noexcept;

    // Возвращает C-строку
    const char* c_str() const;

    // Возвращает символ с проверкой индекса
    char at(size_t idx) const;

    // Возвращает размер строки
    size_t size() const;

private:
    char* data;
    size_t length;
};