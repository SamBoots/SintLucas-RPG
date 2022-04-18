// dynamic Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <chrono>
#include <iostream>

static unsigned int MATH_RANDOMSEED = 5;

//////////I choose Xorshift32 for the custom random. You can find information on it here: https://en.wikipedia.org/wiki/Xorshift //////////

/// <summary>
/// Get a Random unsigned int between 0 and INT_MAX.
/// </summary>
static unsigned int RandomUInt()
{
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 13, MATH_RANDOMSEED ^= MATH_RANDOMSEED >> 17;
	MATH_RANDOMSEED ^= MATH_RANDOMSEED << 5;
	return MATH_RANDOMSEED;
}

//////////Information on the % operator can be found here. https://www.cprogramming.com/tutorial/modulus.html

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
	return RandomUInt() % (max + 1 - min) + min;
}


//Function that returns a pointer of a random sized int array. Since size is a reference it will modify the parameter send.
unsigned int* GetArrayOfRandomInts(unsigned int& size)
{
	unsigned int randomSize = RandUintMinMax(20, 30);
	//Set the parameter that you will use to check the size.
	size = randomSize;
	//Create a pointer that points to an unsinged int array of a random size.
	unsigned int* intArray = new unsigned int[randomSize];

	std::cout << "The array it's size is: " << randomSize << std::endl;

	for (size_t i = 0; i < randomSize; i++)
	{
		//Initilize random values between 10 and 20.
		intArray[i] = RandUintMinMax(10, 20);
	}

	return intArray;
}

int main()
{
	//Getting system time for the random.
	auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
	MATH_RANDOMSEED = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count());

	//Since you send arraySize as a reference to GetArrayOfRandomInts the variable can be modified. Use arraySize to then know the size of the array that the intArray pointer points too.
	//Pointers that point to an array do not know the array size.
	unsigned int arraySize = 0;
	unsigned int* intArray = GetArrayOfRandomInts(arraySize);

	for (size_t i = 0; i < arraySize; i++)
	{
		std::cout << "index " << i << " it's value is: " << intArray[i] << std::endl;
	}

	//Use delete[] when deleting an dynamically allocated array. 
	//In short, use delete[] when using new T[value].
	//And use delete when just using new T;
	delete[] intArray;
}