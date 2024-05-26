#include <iostream>
#include "archive.h"
#include "utilities.h"

enum Actions { EXIT, INSERT, FIND, REMOVE, CLEAN };

int main() {
    TArchive<int> archive;
    size_t n, pos;
    int* values = nullptr;
    int user;

    bool exit = false;
    bool success;
    InputSystem::InsertMode mode;

    while (!exit) {
        system("cls");
        OutputSystem::show(archive);
        std::cout << "Menu:\n 1. insert,\n 2. find,\n 3. delete,\n 4. clean,\n 0. exit.\nYour choose: ";
        std::cin >> user;

        size_t* positions = nullptr;  // Объявляем и инициализируем переменную здесь

        switch (user) {
        case Actions::EXIT:
            exit = true;
            break;
        case Actions::INSERT:
            if (values != nullptr) { delete[] values; values = nullptr; }
            values = InputSystem::insert<int>(n, pos, mode);
            success = false;
            if (mode == InputSystem::InsertMode::OneValue) {
                try {
                    archive.insert(values[0], pos);
                    success = true;
                }
                catch (std::exception& err) {
                    std::cerr << err.what() << std::endl;
                }
            }
            else if (mode == InputSystem::InsertMode::SeveralValues) {
                try {
                    archive.insert(values, n, pos);
                    success = true;
                }
                catch (std::exception& err) {
                    std::cerr << err.what() << std::endl;
                }
            }
            if (success) {
                OutputSystem::insert();
            }
            system("pause");
            break;
        case Actions::FIND:
            std::cout << "Input value to find: ";
            int value;
            std::cin >> value;
            positions = archive.find_all(value);  // Используем positions здесь
            if (positions) {
                std::cout << "Found at positions: ";
                for (size_t i = 1; i <= positions[0]; ++i) {
                    std::cout << positions[i] << " ";
                }
                delete[] positions;  // Не забываем освобождать память
            }
            else {
                std::cout << "Value not found.";
            }
            std::cout << std::endl;
            system("pause");
            break;
        case Actions::REMOVE:
            std::cout << "Input position to remove: ";
            std::cin >> pos;
            try {
                archive.remove_by_index(pos);
            }
            catch (std::exception& err) {
                std::cerr << err.what() << std::endl;
            }
            system("pause");
            break;
        case Actions::CLEAN:
            archive.clear();
            OutputSystem::insert();
            system("pause");
            break;
        }
    }

    if (values != nullptr) { delete[] values; }
    return 0;
}