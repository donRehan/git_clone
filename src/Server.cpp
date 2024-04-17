#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <string>
#include <zlib.h>
namespace fs = std::filesystem;

void init() {
    if (!fs::exists(".git")) {
	fs::create_directory(".git");
	fs::create_directory(".git/objects");
	fs::create_directory(".git/refs");

	std::ofstream head(".git/HEAD");
	head << "ref: refs/heads/main" << std::endl;
	head.close();
    } else {
	std::cout << "Already a git repository" << std::endl;
    }
}

void cat_file(std::string hash)
{
	// git cat-file -p <hashh>
		// Check first two characters of the hash to find the directory
		// Confirm the hash is present through the remaining string 
			// Wont consider this case for this project
		// Decompress the file and then print its contents "pretty print"
			// How do we decompress ??
			// zlib.h , inflateInit2, inflate, inflateEnd
	// END
	std::string directory = hash.substr(0,2);
	std::string file = hash.substr(2);

	//TODO check if it reads actual files first :: WORKS
	std::string path = ".git/objects/" + directory + "/" + file;
	
	//TODO decrypt the zlib file into a stream && readable format
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
	std::cout << "Usage: git COMMAND [OPTIONS]" << std::endl;
	return 1;
    }

    std::string command = argv[1];

    // TODO consider "git init ."
    if (command == "init") {
	init();
	std::cout << "Initialized an empty git directory" << std::endl;
    } else if (command == "cat-file") {
	if (argc < 3 || (argv[2] == "-p")) {
	    std::cout << "ERROR : Only cat-file -p available" << std::endl;
	    return 1;
	}
	std::cout << "works !" << std::endl;
	// TODO implement cat-file
	cat_file(argv[3]);
    } else {
	std::cout << "Command not found" << std::endl;
	return 1;
    }

	//Blob handling || blobs format blob <size>\0<content>
	//AFTER DECOMPRESSING from Zlib
	//
	//EXAMPLE
	//hello world would look like this 
	//blob 11\0hello world
}

// git clone 
	// init
		// this command initializes a directory with the following layout if
		// not already present
		// .git/
		// ├── objects
		// ├── refs
		// ├── HEAD content (ref: refs/heads/main)
	// git cat-file -p <hashh>
		// Check first two characters of the hash to find the directory
		// Confirm the hash is present through the remaining string 
		// Decompress the file and then print its contents "pretty print"
			// How do we decompress ??
			// zlib.h , inflateInit2, inflate, inflateEnd
		// END
