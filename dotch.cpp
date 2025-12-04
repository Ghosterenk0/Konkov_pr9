#include <iostream>
#include <windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    HANDLE CountThread = (HANDLE)(ULONG_PTR)atoi(argv[1]);
    std::cout << "1. Приостановить поток" << std::endl;
    std::cout << "2. Возобновить поток" << std::endl;
    
    while (true) {
        char c;
        std::cin >> c;
        switch (c) {
        case '1':
            SuspendThread(CountThread);
            std::cout << "Поток приостановлен" << std::endl;
            break;
        case '2':
            ResumeThread(CountThread);
            std::cout << "Поток возобновлен" << std::endl;
            break;
        default:
            std::cout << "Неверно выбранное действие" << std::endl;
            break;
        }
    }
}
