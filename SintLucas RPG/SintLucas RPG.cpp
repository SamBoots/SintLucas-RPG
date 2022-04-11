// SintLucas RPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <iostream>

static unsigned int MATH_RANDOMSEED = 5;

/// <summary>
/// Get a Random unsigned int between 0 and INT_MAX.
/// </summary>
static unsigned int RandomUInt()
{
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 13, MATH_RANDOMSEED ^= MATH_RANDOMSEED >> 17;
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 5;
	return MATH_RANDOMSEED;
}

/// <summary>
/// Get a Random unsigned int between 0 and maxValue.
/// </summary>
static unsigned int RandomUIntMax(unsigned int maxValue)
{
	return RandomUInt() % maxValue;
}

/// <summary>
/// Get a Random unsigned int between min and max value.
/// </summary>
static unsigned int RandUintMinMax(unsigned int min, unsigned int max)
{
	return RandomUInt()% (max + 1 - min) + min;
}


int main()
{
	auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
	MATH_RANDOMSEED = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count());

	unsigned int intArray[10];

	for (size_t i = 0; i < 10; i++)
	{
		intArray[i] = RandUintMinMax(10, 20);
		std::cout << intArray[i] << std::endl;
	}

    std::cout << "Hello World!\n";
}