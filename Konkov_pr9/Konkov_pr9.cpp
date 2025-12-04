#include <iostream>
#include <Windows.h>
#include <conio.h>

HANDLE threads[3];

STARTUPINFO si;
PROCESS_INFORMATION pi;

STARTUPINFO si2;
PROCESS_INFORMATION pi2;



wchar_t appname[] = L"C:\\файлы\\c++\\Konkov_pr9\\ConsoleApplication1\\x64\\Debug\\dotch.exe ";
wchar_t word[] = L"winword.exe";
wchar_t excel[] = L"excel.exe ";
wchar_t paint[] = L"mspaint.exe ";
wchar_t notepad[] = L"notepad.exe ";
 

void countInc() {
	int count = 0;
	while (true) {
		std::cout << count << std::endl;
		std::cout << ": ";
		count++;
		Sleep(1000);
	}
}

int Process() {
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(appname, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		std::cout << "Ошибка" << std::endl;
		return 0;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	return 0;
}

int StartApp(const wchar_t* nameProcess) {
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);

	wchar_t process[256];
	wcscpy_s(process, nameProcess);
	Sleep(1000);
	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, NULL, NULL, NULL, &si2, &pi2)) {
		std::cout << "Ошибка" << std::endl;
		return 0;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	return 0;
}


void Start(const wchar_t* nameProcess) {

	wchar_t process[256];
	wcscpy_s(process, nameProcess);
	if (threads[0] == NULL || threads[1] == NULL) {
		threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)countInc, NULL, 0, NULL);
		Sleep(300);
		threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Process, NULL, 0, NULL);
	}
	threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartApp, process, 0, NULL);
	_getch();
}

void menu() {
	std::cout << "Выберете какой процесс открыть: " << std::endl;
	std::cout << "1. Word" << std::endl;
	std::cout << "2. Excel" << std::endl;
	std::cout << "3. Paint" << std::endl;
	std::cout << "4. Notepad" << std::endl;
	std::cout << "5. Введите d для завершения программы" << std::endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	menu();
	char c;
	while (true) {
		std::cin >> c;
		switch (c) {
		case '1':
			Start(word);
			break;
		case '2':
			Start(excel);
			break;
		case '3':
			Start(paint);
			break;
		case '4':
			Start(notepad);
			break;
		case 'd':
		case 'в':
		case 'D':
		case 'В':
			TerminateThread(threads[0], 0);
			WaitForSingleObject(threads[0], 1000);
			CloseHandle(threads[0]);
			threads[0] = NULL;

			TerminateProcess(pi.hProcess, 0);
			WaitForSingleObject(pi.hProcess, 1000);
			TerminateThread(threads[1], 0);
			WaitForSingleObject(threads[1], 1000);
			CloseHandle(threads[1]);
			threads[1] = NULL;

			TerminateProcess(pi2.hProcess, 0);
			WaitForSingleObject(pi2.hProcess, 1000);
			TerminateThread(threads[2], 0);
			WaitForSingleObject(threads[2], 1000);
			CloseHandle(threads[2]);
			threads[2] = NULL;

			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			CloseHandle(pi2.hProcess);
			CloseHandle(pi2.hThread);
			return 0;
		}
	}
	
	
}
