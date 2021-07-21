#pragma once
#include <filesystem>
#include <vector>


class FileTransfer{
private:
	std::vector<std::filesystem::path> fileArray;
	std::vector<std::filesystem::path> destinationArray;
	std::filesystem::path currentDir;
	std::filesystem::path destination;
	std::string ChangeTimeToName();
	void SetDestinationArray();
public:
	FileTransfer(int argc, char* argv[]);
	void Transfer(int dirnum);
	std::vector<std::filesystem::path> GetDestinationArray();
};

