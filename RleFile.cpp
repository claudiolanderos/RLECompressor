#include "RLEFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FileSystem.h"

void RleFile::CreateArchive(const std::string& source)
{
    // Requires <fstream>
    std::ifstream::pos_type size;
    char* memblock;
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        double length = size;
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        
        // File data has now been loaded into memblock array
        
        mData.Compress(memblock, static_cast<unsigned int>(size));
        double compressedSize = mData.mSize;
        double percentage = ((length-compressedSize)/length)*100;
        std::cout<<"Compressed " <<percentage<<"%"<<std::endl;
        
        std::string filename = source + ".rl1";
        mHeader.fileName = source;
        mHeader.fileSize = (int)length;
        mHeader.fileNameLength = source.length();
        mHeader.sig[0] = 'R';
        mHeader.sig[1] = 'L';
        mHeader.sig[2] = 'E';
        mHeader.sig[3] = '\x01';
        
        // Open the file for output, in binary mode, and overwrite an existing file
        std::ofstream arc(filename, std::ios::out|std::ios::binary|std::ios::trunc);
        if (arc.is_open())
        {
            // Use arc.write function to write data here
            arc.write(mHeader.sig, 4);
            arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
            arc.write(reinterpret_cast<char*>(&(mHeader.fileNameLength)), 1);
            arc.write(mHeader.fileName.c_str(), (int)mHeader.fileNameLength);
            arc.write(mData.mData, mData.mSize);
        }
        
        // Make sure to clean up!
        delete[] memblock;
    }
}

void RleFile::ExtractArchive(const std::string& source)
{
    // Requires <fstream>
    std::ifstream::pos_type size;
    char* memblock;
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read(mHeader.sig, 4);
        
        if(strcmp(mHeader.sig, "RLE\x01") != 0)
        {
            std::cout<<"Error: Incorrect signature!" << std::endl;
            return;
        }
        
        char* temp = new char[200];
        file.read(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
        file.read(reinterpret_cast<char*>(&(mHeader.fileNameLength)), 1);
        file.read(temp, (int)mHeader.fileNameLength);
        mHeader.fileName = temp;
        file.read (memblock, mHeader.fileSize);
        file.close();
        // File data has now been loaded into memblock array

        
        // Open the file for output, in binary mode, and overwrite an existing file
        std::ofstream arc(mHeader.fileName, std::ios::out|std::ios::binary|std::ios::trunc);
        if (arc.is_open())
        {
            // Use arc.read function to read data here
            mData.Decompress(memblock, (long)size, mHeader.fileSize);
            arc.write(mData.mData, mData.mSize);
        }
        
        // Make sure to clean up!
        delete[] memblock;
    }
}
