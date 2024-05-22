#pragma once
#include <vector>

class Archive {
private:
    std::vector<int> mass;

public:
    Archive();

    void insertElement(int num);
    void deleteElementByNumber(int num);
    void deleteElementByValue(int num);
    std::vector<int> findElement(int num) const;
    void clearArchive();
    const std::vector<int>& getArchive() const;
};