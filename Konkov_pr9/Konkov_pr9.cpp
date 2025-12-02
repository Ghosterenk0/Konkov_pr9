#include <iostream>
#include <Windows.h>
#include <conio.h>

void incCount() {
	int count = 0;
	while (true) {
		std::cout << count << std::endl;
		Sleep(3000);
		count++;
	}
}

void StartAndFinishProcess(const wchar_t* nameProcess) {
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t process[256];
	wcscpy_s(process, nameProcess);

	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, 0, NULL, NULL, &si, &piApp)) {
		std::cout << "Дочерний процесс не создан" << std::endl;
		_getch();
	}
	std::cout << "Дочерний процесс создан" << std::endl;
	while (true) {
		char c;
		std::cout << "Введите d чтобы завершить процесс: ";
		std::cin >> c;
		if (c == 'd') {
			TerminateProcess(piApp.hProcess, 1);
			std::cout << "Процесс завершен" << std::endl;
			break;
		}
	}

	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
}

void StartThread(const wchar_t* nameProcess) {

	wchar_t process[256];
	wcscpy_s(process, nameProcess);

	DWORD IDPotokSp;
	HANDLE potocSp = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAndFinishProcess, process, 0, &IDPotokSp);

	DWORD IDPotoc;
	HANDLE potokinc = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)incCount, NULL, 0, &IDPotoc);

	WaitForSingleObject(potocSp, INFINITE);
	WaitForSingleObject(potokinc, INFINITE);
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
		StartThread(L"word.exe ");
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
	default:
		std::cout << "Неверно выбранное действие" << std::endl;
		break;
	}
	return 0;
}
