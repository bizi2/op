#include "Archive.h"
#include <stdexcept>

Archive::Archive() {}

void Archive::insertElement(int num) {
    mass.push_back(num);
}

void Archive::deleteElementByNumber(int num) {
    if (num < 1 || num > static_cast<int>(mass.size())) {
        throw std::out_of_range("Index out of range.");
    }
    mass.erase(mass.begin() + num - 1);
}

void Archive::deleteElementByValue(int num) {
    auto it = std::remove(mass.begin(), mass.end(), num);
    mass.erase(it, mass.end());
}

std::vector<int> Archive::findElement(int num) const {
    std::vector<int> matches;
    for (size_t i = 0; i < mass.size(); ++i) {
        if (mass[i] == num) {
            matches.push_back(i + 1);
        }
    }
    return matches;
}

void Archive::clearArchive() {
    mass.clear();
}

const std::vector<int>& Archive::getArchive() const {
    return mass;
}