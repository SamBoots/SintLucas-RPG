// enemies.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

//Normally you would have the declarations in a .h file and all the implementations inside a .cpp file, you can see this in 3_Player project how that is done.
class Enemy
{
public:
	//Default constructor.
	Enemy();
	//Parameterized constructor, also known as constructor overloading.
	Enemy(const char* a_Name, int a_HP, int a_Strength);
	//Destructor, this will be called when it's deleted or out of scope if it's allocated on the stack.
	~Enemy();

	//function to print the stats.
	void PrintStats();

private:
	//Strings are in const char*, you can also include <string> and use std::string for more safety.
	const char* name;

	int hitPoints;
	int strength;
};

//Default constructor definition.
Enemy::Enemy()
{
	name = "default";
	hitPoints = RandUintMinMax(10, 20);
	strength = RandUintMinMax(2, 8);
}

//Parameterized constructor definition.
Enemy::Enemy(const char* a_Name, int a_HP, int a_Strength)
{
	name = a_Name;
	hitPoints = a_HP;
	strength = a_Strength;
}

//Destructor definition.
Enemy::~Enemy()
{
	//Here you delete dynamically allocated members, or maybe something else. This called before the object is removed.
}

void Enemy::PrintStats()
{
	std::cout << "Creature: " << name << "\n  HP: " << hitPoints << "\n Strength: " << strength << std::endl << std::endl;
}

int main()
{
	//Getting system time for the random.
	auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
	MATH_RANDOMSEED = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count());

	unsigned int randomSize = RandUintMinMax(20, 30);

	//Instead of an int array we go for a random size of enemies.
	Enemy* enemyArray = new Enemy[randomSize];

	std::cout << "The array it's size is: " << randomSize << std::endl;

	for (size_t i = 0; i < randomSize; i++)
	{
		//Since all your enemies use the default constructor, the enemies have random health between 10 and 20 with a random strength within 2 and 8.
		enemyArray[i].PrintStats();
	}

	//Do not forget to delete your dynamic array.
	delete[] enemyArray;
}
