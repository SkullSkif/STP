#include "normpath.hpp"
#include <vector>
#include <string_view>

std::string normpath(const std::string& path) {
    if (path.empty() || path.front() != '/') {
        throw std::invalid_argument("invalid argument, not an absolute path");
    }
    if (path.find(' ') != std::string::npos) {
        throw std::domain_error("domain_error, spaces are not allowed");
    }

    std::vector<std::string> components;
    std::string_view current = path;
    size_t pos = 0;

    while ((pos = current.find('/')) != std::string::npos) {
        std::string_view segment = current.substr(0, pos);
        if (segment == "..") {
            if (!components.empty()) {
                components.pop_back();
            }
        } else if (segment != "." && !segment.empty()) {
            components.push_back(std::string(segment));
        }
        current.remove_prefix(pos + 1);
    }

    if (!current.empty() && current != "." && current != "..") {
        components.push_back(std::string(current));
    }

    if (components.size() == 0) {
        throw std::runtime_error("runtime_error, cannot normalize path");
    }

    std::string normalized_path = "/" + components[0];
    for (size_t i = 1; i < components.size(); ++i) {
        normalized_path += "/" + components[i];
    }

    return normalized_path;
}
