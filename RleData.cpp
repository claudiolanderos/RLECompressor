#include "RleData.h"
#include "iostream"

void RleData::Compress(const char* input, size_t inSize)
{
	// set mSize = 0 and delete mData
    int currSize = 0;
    int currIndex = 0;
    const char* first = input;
    const char* second = nullptr;
    delete[] mData;
    mSize = 0;
    
    mData = new char[inSize*2];
   
    //Handle edge cases first
    if(inSize != 1)
    {
        second = &input[1];
    }
    
    while(currSize < inSize)
    {
        //Handle edge cases first
        if(inSize == 1)
        {
            mData[mSize++] = 1;
            mData[mSize] = input[currIndex];
            return;
        }
       /*
        if(input[currIndex] != input[currIndex+1])
        {
            mData[mSize++] = 1;
            mData[mSize++] = input[currIndex];
            currIndex++;
            first++;
            second++;
        }
        */
        if(input[currIndex] == input[currIndex+1])
        {
            same(first, second, currSize);
        }
        else {
            int size = 0;
            char* placeHolder = &mData[mSize];
            mSize++;
            while(input[currIndex] != input[currIndex+1] && currSize < inSize)
            {
                mData[mSize++] = *first;
                size++;
                currSize++;
                first++;
                second++;
            }
            
            size *= -1;
            *placeHolder = size;
        }
        
    }
    
}

void RleData::same(const char*& first, const char*& second, int& currSize)
{
    char letter = *first;
    int size = 2;
    int x = 2;
    bool same = true;
    currSize +=2;
    
    while(same)
    {
        first++;
        second++;
        
        if(*first == *second)
        {
            x++;
            size++;
            currSize++;
        }
        else {
            same = false;
        }
    }
    
    
    mData[mSize++] = size;
    mData[mSize++] = letter;
    first++;
    second++;
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
    //First delete previous data
    delete[] mData;
    mSize = 0;
    
    //Allocate memory for output data
    mData = new char[inSize*2];
    int currIndex = 0;
    int code = input[0];

    while(currIndex < inSize)
    {
        code = input[currIndex];
        currIndex++;
        if(code > 0)
        {
            for(int i = 0; i < code; i++)
            {
                mData[mSize++] = input[currIndex];
            }
            currIndex++;
        }
        else {
            for(int i = 0; i > code; i--)
            {
                mData[mSize++] = input[currIndex++];
            }
        }
    }
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}