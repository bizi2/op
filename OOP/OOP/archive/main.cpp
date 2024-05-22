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
    std::cout << "�����: {";
    if (mass.empty()) {
        std::cout << "<�����>}";
    }
    else {
        for (size_t i = 0; i < mass.size() - 1; ++i) {
            std::cout << mass[i] << ", ";
        }
        std::cout << mass.back() << "}";
    }
}

void displayMatches(const std::vector<int>& matches, int num) {
    std::cout << "������ ��������� �� ��������� " << num << ": ";
    if (matches.empty()) {
        std::cout << "���������� ���.";
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

        std::cout << "\n\n����:\n";
        std::cout << "1. ��������\n";
        std::cout << "2. �������\n";
        std::cout << "3. �����\n";
        std::cout << "4. �������� ������\n";
        std::cout << "5. �����\n";

        try {
            
            int choice = getNumberInput("��� �����: ");

            switch (choice) {
            case 1: {
                int num = getNumberInput("������� ����� ��� �������: ");
                archive.insertElement(num);
                break;
            }
            case 2: {
                std::cout << "�������� ��� ��������:\n";
                std::cout << "1. �� ������\n";
                std::cout << "2. �� ��������\n";
                int deleteChoice = getNumberInput("��� �����: ");
                int num = getNumberInput("����� ������� �������: ");
                if (deleteChoice == 1) {
                    archive.deleteElementByNumber(num);
                }
                else if (deleteChoice == 2) {
                    archive.deleteElementByValue(num);
                }
                else {
                    std::cout << "�������� ����� ��� ��������.\n";
                }
                break;
            }
            case 3: {
                int num = getNumberInput("����� ������� �����: ");
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
                std::cout << "� ��� ��� ������ ������.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}