// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RLEFile.h"

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

std::string getFileExt(const std::string& s) {
    
    //Taken from the C++ Cookbook
    size_t i = s.rfind('.', s.length());
    if (i != std::string::npos) {
        return(s.substr(i+1, s.length() - i));
    }
    
    return("");
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		// Just the tests
		Part1Tests();
	}
	else
	{
        RleFile rleFile;
		// TODO: Get the file name from argv[1] and either compress/decompress
        std::string path = argv[1];
        std::string ext = getFileExt(path);
        
        if(ext == "rl1")
        {
            rleFile.ExtractArchive(path);
        }
        else
        {
            rleFile.CreateArchive(path);
        }
        
        
	}
	return 0;
}


