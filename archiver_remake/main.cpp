#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include "FileTransfer.h"
#include "OpenExplorer.h"

#define DEBUG

int InputInteger();

int main(int argc, char* argv[]) {
#ifdef DEBUG
	char debugArgv[] = "test";
	argc = 2;
	argv[1] = debugArgv;
#endif
	if (argc < 2) {
		OpenExplorer(argv[0]);
		return 0;
	}
	std::cout << "archiver-remake" << std::endl << "this>> ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}
	std::cout << std::endl ;

	FileTransfer ft(argc, argv);
	if (ft.GetDestinationArray().size() == 0) {
		std::cout << "Destination directory not found." << std::endl << "Press enter to exit...";
		std::getchar();
		return 0;
	}

	//ディレクトリ列挙
	for (auto p : ft.GetDestinationArray()) {
		static int i = 0;
		std::cout << "[" << i << "]: " << p.filename().string() << std::endl;
		i++;
	}
	//ディレクトリ指定
	int dirNum = -1;
	while (dirNum < 0 || dirNum > ft.GetDestinationArray().size()) {
		 dirNum = ::InputInteger();
	}
	try {
		ft.Transfer(dirNum);
	}
	catch (std::filesystem::filesystem_error& e) {
		std::cout << e.what() << std::endl;
		::getchar();
		::getchar();
	}

	return 0;
}

int InputInteger() {
	int in = NULL;
	std::string inString;
	while (true) {
		std::cin >> inString;
		try {
			in = std::stoi(inString);
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		break;
	}
	return in;
}