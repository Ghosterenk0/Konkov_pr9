#include <iostream>
#include <Windows.h>
#include <conio.h>

void incCount() {
	int count = 0;
	while (true) {
		std::cout << count << std::endl;
		count++;
	}
}

void StartProcess(wchar_t app) {

}

int main()
{
	setlocale(LC_ALL, "ru");

	wchar_t app;
	std::cout << "Выберете какой процесс открыть: " << std::endl;
	std::cout << "1. Word" << std::endl;
	std::cout << "2. Excel" << std::endl;
	std::cout << "3. Paint" << std::endl;
	std::cout << "4. Notepad" << std::endl;
	char c;
	std::cin >> c;
	switch (c)
	{
	case '1':
		app = L'word.exe';
		break;
	case '2':
		app = L'excel.exe';
		break;
	case '3':
		app = L'mspaint.exe';
		break;
	case '4':
		app = L'notepad.exe';
		break;
	default:
		std::cout << "Неверно выбранное действие" << std::endl;
		break;
	}
}
