#pragma once
#include "MiniCppUnit.hpp"
#include "RleData.h"
#include <iostream>
#include <iomanip>

// Helper functions
bool buffersAreSame(const char* expected, const char* actual, size_t size);
void runCompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);
void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize);

// IMPORTANT NOTE --
// The tests all use "sizeof" to find the size of the input
// buffer. However, remember that this only works because the
// character arrays are statically allocated.
// If you just have a pointer to a C-style string, "sizeof"
// will return the size of the pointer type (either 4 or 8).
class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(CompressionTests, "Testing Compression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive runs test");
		// TODO: Add more Compression test cases
        TEST_CASE_DESCRIBE(testLongPositiveRuns, "Long positive runs test");
        TEST_CASE_DESCRIBE(testLongNegativeRuns, "Long negative runs test");
        TEST_CASE_DESCRIBE(testAlternatingPositiveNegativeRuns, "alternating runs test");
        TEST_CASE_DESCRIBE(testReallyLongPositiveRun, "really long runs test");
        TEST_CASE_DESCRIBE(testSingleCharacterRun, "Single character run test");
        TEST_CASE_DESCRIBE(testSingleCharacterPositiveRun, "Single character positive run test");
        TEST_CASE_DESCRIBE(testSingleCharacterEnding, "Single character ending run test");

	}
	
	void testBasicPositiveRuns()
	{
		char test[] = "aaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbc"
			"ccdddaaabbbcccdddaaabbbcccdddaaabbbcccdddaaabbbcccddd";
		char expected[] = "\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d"
			"\x03" "a" "\x03" "b" "\x03" "c" "\x03" "d";
		
		runCompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testLongPositiveRuns()
    {
        char test[] = "aaaaaaa"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb";
        char expected[] = "\x07" "a" "\x78" "b";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testLongNegativeRuns()
    {
        char test[] =   "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "ababababab"
                        "abababa";
        char expected[] = "\x81" "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "ababababab"
        "abababa";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testAlternatingPositiveNegativeRuns()
    {
        char test[] =   "qwertyuio"
                        "aaaaaaaaaa"
                        "qwertyuio"
                        "aaaaaaaaaa"
                        "qwertyuio"
                        "aaaaaaaaaa"
                        "qwertyuio"
                        "aaaaaaaaaa"
                        "qwertyuio"
                        "aaaaaaaaaa"
                        "qwertyuio";
        
        char expected[] =   "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o"
                            "\xA" "a"
                            "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o"
                            "\xA" "a"
                            "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o"
                            "\xA" "a"
                            "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o"
                            "\xA" "a"
                            "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o"
                            "\xA" "a"
                            "\xf7" "q" "w" "e" "r" "t" "y" "u" "i" "o";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testReallyLongPositiveRun()
    {
        char test[] = "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb"
                    "bbbbbbbbbb";
        
        char expected[] = "\x8C" "b";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testSingleCharacterRun()
    {
        char test[] = "a";
        
        char expected[] = "\x01" "a";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testSingleCharacterPositiveRun()
    {
        char test[] = "bbbaccc";
        
        char expected[] = "\x03" "b"
                            "\x01" "a"
                            "\x03" "c";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
    
    void testSingleCharacterEnding()
    {
        char test[] = "bbbccca";
        
        char expected[] = "\x03" "b"
        "\x03" "c"
        "\x01" "a";
        
        runCompressionTest(test, sizeof(test) -1, expected, sizeof(expected) -1);
    }
};

class DecompressionTests : public TestFixture<DecompressionTests>
{
public:
	TEST_FIXTURE_DESCRIBE(DecompressionTests, "Testing Decompression...")
	{
		TEST_CASE_DESCRIBE(testBasicPositiveRuns, "Basic positive run test");
		// TODO: Add more Decompression test  cases
        TEST_CASE_DESCRIBE(testBasicNegativeRuns, "Basic negative run test");
        TEST_CASE_DESCRIBE(testAlternatingPositiveNegativeRuns, "Alternating positive negative runs test");

	}
	
    void testBasicPositiveRuns()
    {
        char test[] = "\x28" "x";
        char expected[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
	void testBasicNegativeRuns()
	{
		char test[] = "\x81" "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyuiop"
                                "qwertyu";
		char expected[] = "qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyu";
		
		runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
	}
    
    void testAlternatingPositiveNegativeRuns()
    {
        char test[] =   "\xf7" "qwertyuio"
                        "\xA" "a"
                        "\xf7" "qwertyuio"
                        "\xA" "a"
                        "\xf7" "qwertyuio"
                        "\xA" "a"
                        "\xf7" "qwertyuio"
                        "\xA" "a"
                        "\xf7" "qwertyuio"
                        "\xA" "a";
        char expected[] =   "qwertyuio"
                            "aaaaaaaaaa"
                            "qwertyuio"
                            "aaaaaaaaaa"
                            "qwertyuio"
                            "aaaaaaaaaa"
                            "qwertyuio"
                            "aaaaaaaaaa"
                            "qwertyuio"
                            "aaaaaaaaaa";
        
        runDecompressionTest(test, sizeof(test) - 1, expected, sizeof(expected) - 1);
    }
    
};

REGISTER_FIXTURE(CompressionTests);
REGISTER_FIXTURE(DecompressionTests);

bool buffersAreSame(const char* expected, const char* actual, size_t size)
{
	if (actual == nullptr)
	{
		std::cerr << std::endl << "Actual data is null." << std::endl;
		return false;
	}

	bool retVal = true;

	for (size_t i = 0; i < size; i++)
	{

		if (expected[i] != actual[i])
		{
            
			retVal = false;
			std::cerr << std::endl
				<< "Expected 0x" << std::hex << static_cast<unsigned>(expected[i])
				<< " at index " << std::dec << i << " but saw 0x"
				<< std::hex << static_cast<unsigned>(actual[i]) << std::endl;
			break;
		}
	}

	return retVal;
}

void runCompressionTest(char* test, size_t testSize, 
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Compress(test, testSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}

void runDecompressionTest(char* test, size_t testSize,
	char* expected, size_t expectedSize)
{
	RleData r;
	r.Decompress(test, testSize, expectedSize);
	ASSERT_TEST_MESSAGE(buffersAreSame(expected, r.mData, expectedSize),
		"Buffer mismatch (see above for details)");
}
