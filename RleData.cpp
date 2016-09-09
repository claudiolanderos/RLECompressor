#include "RleData.h"
#include "iostream"

void RleData::Compress(const char* input, size_t inSize)
{
	// set mSize = 0 and delete mData
    int currIndex = 0;
    delete[] mData;
    mSize = 0;
    
    mData = new char[inSize*2];
    
    while(currIndex < inSize)
    {
        //Handle edge cases first
        if(currIndex == inSize-1)
        {
            mData[mSize++] = 1;
            mData[mSize] = input[currIndex];
            return;
        }
        else if(currIndex < inSize-2 && input[currIndex] != input[currIndex+1] && input[currIndex+1] == input[currIndex+2])
        {
            mData[mSize++] = 1;
            mData[mSize++] = input[currIndex++];
        }
        else if(input[currIndex] == input[currIndex+1])
        {
            same(input, currIndex, inSize);
        }
        else {
            int size = 0;
            char* placeHolder = &mData[mSize];
            mSize++;
            while(currIndex < inSize && input[currIndex] != input[currIndex+1] && size < 127)
            {
                mData[mSize++] = input[currIndex];
                size++;
                currIndex++;
                
                //If last element add it to mData
                if(currIndex == inSize-1)
                {
                    mData[mSize++] = input[currIndex];
                }
            }
            
            size *= -1;
            *placeHolder = size;
        }
        
    }
    
}

void RleData::same(const char*& input, int& currIndex, const size_t inSize)
{
    char letter = input[currIndex];
    int size = 2;
    bool same = true;
    currIndex++;
    
    while(same && currIndex < inSize-1)
    {
        if(input[currIndex] == input[currIndex+1] && size < 127)
        {
            size++;
            currIndex++;
        }
        else {
            same = false;
        }
    }
    
    currIndex++;
    mData[mSize++] = size;
    mData[mSize++] = letter;
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