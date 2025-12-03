#include <iostream>
#include <Windows.h>
#include <conio.h>


STARTUPINFO si;
PROCESS_INFORMATION piApp;

DWORD IDt[2] = {1, 2};
HANDLE threads[2];

int menu();

void incCount() {
	int count = 0;
	while (true) {
		std::cout << count << std::endl;
		count++;
		Sleep(3000);
		if (menu() == 0)
			break;
	}
}

void StartAndFinishProcess(const wchar_t* nameProcess) {

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t process[256];
	wcscpy_s(process, nameProcess);

	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, 0, NULL, NULL, &si, &piApp)) {
		std::cout << "Дочерний процесс не создан" << std::endl;
		_getch();
	}
	else {
		std::cout << "Дочерний процесс создан" << std::endl;
	}

}

void StartThread(const wchar_t* nameProcess) {

	wchar_t process[256];
	wcscpy_s(process, nameProcess);
	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAndFinishProcess, process, 0, &IDt[0]);
	Sleep(1000);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)incCount, NULL, 0, &IDt[1]);
	
	WaitForSingleObject(threads[0], INFINITE);
	WaitForSingleObject(threads[1], INFINITE);

}

int menu() {
	while (true) {
		char c;
		std::cin >> c;
		switch (c)
		{
		case '1':
			StartThread(L"winword.exe ");
			break;
		case '2':
			StartThread(L"excel.exe ");
			break;
		case '3':
			StartThread(L"mspaint.exe ");
			break;
		case '4':
			StartThread(L"notepad.exe ");
			break;
		case 'd':
			TerminateThread(threads[0], 2);
			TerminateThread(threads[1], 3);
			TerminateProcess(piApp.hProcess, 1);
			CloseHandle(piApp.hThread);
			CloseHandle(piApp.hProcess);
			std::cout << "Потоки завершины " << std::endl;
			std::cout << "Программа завершена" << std::endl;
			return 0;
		default:
			std::cout << "Неверно выбранное действие" << std::endl;
			break;
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "ru");

	std::cout << "Выберете какой процесс открыть: " << std::endl;
	std::cout << "1. Word" << std::endl;
	std::cout << "2. Excel" << std::endl;
	std::cout << "3. Paint" << std::endl;
	std::cout << "4. Notepad" << std::endl;
	std::cout << "5. Введите d для завершения программы" << std::endl;

	menu();
}
