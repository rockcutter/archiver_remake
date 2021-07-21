#include <memory>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>

#include "FileTransfer.h"


namespace filesystem = std::filesystem;
namespace chrono = std::chrono;
using namespace std::chrono_literals;



FileTransfer::FileTransfer(int argc, char* argv[]) :destination(""), currentDir("") {
	this->currentDir = filesystem::path(argv[0]).parent_path();

	for (int i = 1; i < argc; i++) {
		this->fileArray.push_back(argv[i]);
	}
	return;
}

std::vector<filesystem::path> FileTransfer::GetDestinationArray() {
	if (this->destinationArray.size() == 0) {
		this->SetDestinationArray();
	}
	return this->destinationArray;
}

void FileTransfer::SetDestinationArray() {
	for (auto p : std::filesystem::directory_iterator(this->currentDir)) {
		if (p.is_directory()) {
			this->destinationArray.push_back(p);
		}
	}
	return;
}

void FileTransfer::Transfer(int dirNum) {
	filesystem::path dirPath;
	dirPath = this->destinationArray[dirNum] / this->ChangeTimeToName();

	filesystem::create_directory(dirPath);

	for (filesystem::path& p : this->fileArray) {
		rename(p, dirPath / p.filename());
	}
}

std::string FileTransfer::ChangeTimeToName() {
	std::time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	std::tm cal;
	::localtime_s(&cal, &now);

	std::string name =
		std::to_string(cal.tm_year + 1900) + "_" +
		std::to_string(cal.tm_mon + 1) + "_" +
		std::to_string(cal.tm_mday) + "_" +
		std::to_string(cal.tm_hour) + "_" +
		std::to_string(cal.tm_min) + "_" +
		std::to_string(cal.tm_sec);

	return name;
}