#include "utilities.h"

namespace InputSystem {

    template <typename T>
    T* insert(size_t& n, size_t& pos, InputSystem::InsertMode& mode) noexcept {
        T* value = nullptr;
        mode = Back;
        int user;
        std::cout << "Choose insert mode:\n";
        std::cout << "1 - to the back,\n";
        std::cout << "2 - to the front,\n";
        std::cout << "3 - at given position.\n";
        std::cout << "Your choose: ";
        std::cin >> user;
        if (user == 1) { mode = Back; }
        if (user == 2) { mode = Front; }
        if (user == 3) {
            std::cout << "How many values need to insert:\n";
            std::cout << "1 - one value,\n";
            std::cout << "2 - several values.\n";
            std::cout << "Your choose: ";
            std::cin >> user;
            if (user == 1) { mode = OneValue; }
            if (user == 2) { mode = SeveralValues; }
        }
        if (mode == Back || mode == Front || mode == OneValue) {
            n = 1;
            value = new T[n];
            std::cout << "Input value for insert: ";
            std::cin >> value[0];
        }
        if (mode == SeveralValues) {
            std::cout << "Input number of values for insert: ";
            std::cin >> n;
            value = new T[n];
            std::cout << "Input values for insert (between space): ";
            for (size_t i = 0; i < n; i++) {
                std::cin >> value[i];
            }
        }
        if (mode == OneValue || mode == SeveralValues) {
            std::cout << "Input position for insert: ";
            std::cin >> pos;
        }
        return value;
    }

    // явна€ специализаци€ шаблона функции insert дл€ типа int
    template int* insert<int>(size_t& n, size_t& pos, InputSystem::InsertMode& mode) noexcept;

}

namespace OutputSystem {

    void setCursor(int column, int line) {
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            coord
        );
    }

    void getCursor(int& column, int& line) noexcept {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            column = csbi.dwCursorPosition.X;
            line = csbi.dwCursorPosition.Y;
        }
        else {
            column = 0;
            line = 0;
        }
    }

    void insert() noexcept {
        std::cout << "Done." << std::endl;
    }

    template <typename T>
    void show(const TArchive<T>& archive) noexcept {
        std::cout << "Archive: { ";
        archive.print();
        if (!archive.empty()) {
            // стереть последнюю зап€тую
            int column; int line;
            getCursor(column, line);
            column -= 2;
            setCursor(column, line);
        }
        std::cout << " }\n";
    }

    // явна€ специализаци€ шаблона функции show дл€ типа int
    template void show<int>(const TArchive<int>& archive) noexcept;

}