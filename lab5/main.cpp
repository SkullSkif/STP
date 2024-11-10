#include <iostream>
#include "normpath.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: no path provided" << std::endl;
        return 1;
    }

    try {
        std::string normalized = normpath(argv[1]);
        std::cout << normalized << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::domain_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}