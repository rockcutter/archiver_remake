#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "OpenExplorer.h"

namespace filesystem = std::filesystem;

void OpenExplorer(std::string path) {
	constexpr char EXPLORER_PATH[] = "C:\\Windows\\explorer.exe ";

	filesystem::path currentDirPath = filesystem::path(path).parent_path();
	std::string cmdLine = EXPLORER_PATH + currentDirPath.string();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL,const_cast<char*>(cmdLine.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		std::cout << "CreateProcess Failed" << std::endl;
		return;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return;
}