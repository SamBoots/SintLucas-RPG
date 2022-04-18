#include "Character.h"
#include "Utils.h"

#include <iostream>

//Why a .cpp file? This article explains it well in combination with the header.: https://www.geeksforgeeks.org/header-files-in-c-cpp-and-its-uses/
//In short, you place definitions here, you get your declerations from the .h file, which for our case is Character.h.

Character::Character()
{
	maxHitPoints = RandUintMinMax(10, 20);
	hitPoints = maxHitPoints;
	strength = RandUintMinMax(2, 8);
}

Character::Character(int a_HP, int a_Strength)
{
	maxHitPoints = a_HP;
	hitPoints = maxHitPoints;
	strength = a_Strength;
}

Character::~Character()
{}

bool Character::TakeDamage(int a_DamageTaken)
{
	//If the damage would reduce it to 0 or lower hp return false, this indicates that it has died.
	if (hitPoints <= a_DamageTaken)
	{
		hitPoints = 0;
		return false;
	}
	//Else just deduct Hitpoints equal to the damage taken.
	hitPoints -= a_DamageTaken;
	 
	return true;

}


Enemy::Enemy()
	: Character()
{
	name = "default";
}

Enemy::Enemy(int a_HP, int a_Strength, const char* a_Name)
	: Character(a_HP, a_Strength)
{
	name = a_Name;
}

Enemy::~Enemy()
{

}

void Enemy::PrintStats() const
{
	std::cout << "Creature: " << name << "\n  Current HP: " << hitPoints << "\n Strength: " << strength << std::endl << std::endl;
}


Player::Player()
	: Character()
{}

Player::Player(int a_HP, int a_Strength)
	: Character(a_HP, a_Strength)
{}

Player::~Player()
{}

void Player::PrintStats() const
{
	std::cout << "The Player.\n  Current HP: " << hitPoints << "\n Strength: " << strength << std::endl << std::endl;
}
