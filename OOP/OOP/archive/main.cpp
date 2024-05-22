#include <iostream>
#include <stdexcept>
#include "Archive.h"

int getNumberInput(const std::string& prompt) {
    int num;
    std::cout << prompt;
    std::cin >> num;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input. Please enter a valid number.");
    }
    return num;
}

void displayArchive(const std::vector<int>& mass) {
    std::cout << "Архив: {";
    if (mass.empty()) {
        std::cout << "<пусто>}";
    }
    else {
        for (size_t i = 0; i < mass.size() - 1; ++i) {
            std::cout << mass[i] << ", ";
        }
        std::cout << mass.back() << "}";
    }
}

void displayMatches(const std::vector<int>& matches, int num) {
    std::cout << "Номера элементов со значением " << num << ": ";
    if (matches.empty()) {
        std::cout << "Совпадений нет.";
    }
    else {
        for (size_t i = 0; i < matches.size() - 1; ++i) {
            std::cout << matches[i] << ", ";
        }
        std::cout << matches.back();
    }
}

int main() {
    setlocale(LC_ALL, "");

    Archive archive;

    while (true) {
        system("cls");
        displayArchive(archive.getArchive());

        std::cout << "\n\nМеню:\n";
        std::cout << "1. Вставить\n";
        std::cout << "2. Удалить\n";
        std::cout << "3. Найти\n";
        std::cout << "4. Очистить массив\n";
        std::cout << "5. Выход\n";

        try {
            
            int choice = getNumberInput("Ваш выбор: ");

            switch (choice) {
            case 1: {
                int num = getNumberInput("Введите число для вставки: ");
                archive.insertElement(num);
                break;
            }
            case 2: {
                std::cout << "Выберете тип удаления:\n";
                std::cout << "1. По номеру\n";
                std::cout << "2. По значению\n";
                int deleteChoice = getNumberInput("Ваш выбор: ");
                int num = getNumberInput("Какой элемент удалить: ");
                if (deleteChoice == 1) {
                    archive.deleteElementByNumber(num);
                }
                else if (deleteChoice == 2) {
                    archive.deleteElementByValue(num);
                }
                else {
                    std::cout << "Неверный выбор для удаления.\n";
                }
                break;
            }
            case 3: {
                int num = getNumberInput("Какой элемент найти: ");
                std::vector<int> matches = archive.findElement(num);
                displayMatches(matches, num);
                break;
            }
            case 4:
                archive.clearArchive();
                break;
            case 5:
                return 0;
            default:
                std::cout << "У Вас нет такого выбора.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}