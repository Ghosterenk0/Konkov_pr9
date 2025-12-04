#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

struct ProcessInfo {
public:
	int name;
	PROCESS_INFORMATION ProcessI;

	ProcessInfo() {}
	ProcessInfo(int a, PROCESS_INFORMATION proc) {
		name = a;
		ProcessI = proc;
	}
};

HANDLE threads[3];

STARTUPINFO si;
STARTUPINFO si2;
PROCESS_INFORMATION picons;

int size = 4;
int count = 0;
ProcessInfo* pi1 = new ProcessInfo[size];

ProcessInfo info;
PROCESS_INFORMATION pi;

wchar_t appname[] = L"C:\\Users\\st310-05\\Desktop\\konkov_pr9\\main\\x64\\Debug\\dotch.exe ";
wchar_t word[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\winword.exe";
wchar_t excel[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\excel.exe";
wchar_t paint[] = L"mspaint.exe";
wchar_t notepad[] = L"notepad.exe";


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
	
	HANDLE hCounterThread = threads[0];
	
	wchar_t arg[512];
	wsprintf(arg, L"%s%d", appname, (size_t)hCounterThread);

	SetHandleInformation(hCounterThread, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	if (!CreateProcess(NULL, arg, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &picons)) {
		std::cout << "Ошибка" << std::endl;
		return 0;
	}

	WaitForSingleObject(picons.hProcess, INFINITE);

	return 0;
}

int StartApp(const wchar_t* nameProcess) {
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);
	

	wchar_t process[256];
	wcscpy_s(process, nameProcess);
	Sleep(1000);
	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, NULL, NULL, NULL, &si2, &info.ProcessI)) {
		std::cout << "Ошибка" << std::endl;
		return 0;
	}


	if (count >= 4) {
		size *= 2;
		ProcessInfo* temp = pi1;
		pi1 = new ProcessInfo[size];
		for (int i = 0; i < count; i++)
		{
			pi1[i] = temp[i];
		}
		delete[] temp;
		pi1[count] = info;
		count++;
	}
	else {
		pi1[count] = info;
		count++;
	}

	WaitForSingleObject(info.ProcessI.hProcess, INFINITE);
	return 0;
}


void Start(const wchar_t* nameProcess, ProcessInfo info) {

	wchar_t process[256];
	wcscpy_s(process, nameProcess);
	if (threads[0] == NULL) {
		threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)countInc, NULL, 0, NULL);
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
	std::cout << "5. Закрыть процесс" << std::endl;
	std::cout << "6. Закрыть word" << std::endl;
	std::cout << "7. Закрыть excel" << std::endl;
	std::cout << "8. Закрыть paint" << std::endl;
	std::cout << "9. Закрыть notepad" << std::endl;
	std::cout << "Введите d для завершения программы" << std::endl;
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
			info = ProcessInfo(1, pi);
			Start(word, info);
			break;
		case '2':
			info = ProcessInfo(2, pi);
			Start(excel, info);
			break;
		case '3':
			info = ProcessInfo(3, pi);
			Start(paint, info);
			break;
		case '4':
			info = ProcessInfo(4, pi);
			Start(notepad, info);
			break;
		case '5':
			TerminateProcess(pi1[count].ProcessI.hProcess, 0);
			WaitForSingleObject(pi1[count].ProcessI.hProcess, 1000);

			CloseHandle(pi1[count].ProcessI.hProcess);
			CloseHandle(pi1[count].ProcessI.hThread);
			count--;
			break;
		case '6':
			for (int i = count; i >= 0; i--)
			{
				if (pi1[i].name == 1) {
					TerminateProcess(pi1[i].ProcessI.hProcess, 0);
					WaitForSingleObject(pi1[i].ProcessI.hProcess, 1000);

					CloseHandle(pi1[i].ProcessI.hProcess);
					CloseHandle(pi1[i].ProcessI.hProcess);
					count--;
					break;
				}
			}
			break;
		case '7':
			for (int i = count; i >= 0; i--)
			{
				if (pi1[i].name == 2) {
					TerminateProcess(pi1[i].ProcessI.hProcess, 0);
					WaitForSingleObject(pi1[i].ProcessI.hProcess, 1000);

					CloseHandle(pi1[i].ProcessI.hProcess);
					CloseHandle(pi1[i].ProcessI.hProcess);
					count--;
					break;
				}
			}
			break;
		case '8':
			for (int i = count; i >= 0; i--)
			{
				if (pi1[i].name == 3) {
					TerminateProcess(pi1[i].ProcessI.hProcess, 0);
					WaitForSingleObject(pi1[i].ProcessI.hProcess, 1000);

					CloseHandle(pi1[i].ProcessI.hProcess);
					CloseHandle(pi1[i].ProcessI.hProcess);
					count--;
					break;
				}
			}
			break;
		case '9':
			for (int i = count - 1; i >= 0; i--)
			{

				if (pi1[i].name == 4) {
					TerminateProcess(pi1[i].ProcessI.hProcess, 0);
					WaitForSingleObject(pi1[i].ProcessI.hProcess, 1000);

					CloseHandle(pi1[i].ProcessI.hProcess);
					CloseHandle(pi1[i].ProcessI.hProcess);
					count--;
					break;
				}
			}
			break;
		case 'd':
		case 'в':
		case 'D':
		case 'В':
			TerminateProcess(picons.hProcess, 0);
			WaitForSingleObject(picons.hProcess, 1000);
			CloseHandle(picons.hProcess);
			CloseHandle(picons.hThread);

			TerminateThread(threads[0], 0);
			WaitForSingleObject(threads[0], 1000);
			CloseHandle(threads[0]);
			threads[0] = NULL;

			TerminateThread(threads[1], 0);
			WaitForSingleObject(threads[1], 1000);
			CloseHandle(threads[1]);
			threads[1] = NULL;

			for (int i = 0; i < count; i++)
			{
				TerminateProcess(pi1[i].ProcessI.hProcess, 0);
				WaitForSingleObject(pi1[i].ProcessI.hProcess, 1000);
			}
			
			TerminateThread(threads[2], 0);
			WaitForSingleObject(threads[2], 1000);
			CloseHandle(threads[2]);
			threads[2] = NULL;


			for (int i = 0; i < count; i++)
			{
				CloseHandle(pi1[i].ProcessI.hProcess);
				CloseHandle(pi1[i].ProcessI.hThread);
			}
			delete[] pi1;
			return 0;
		}
	}


}
