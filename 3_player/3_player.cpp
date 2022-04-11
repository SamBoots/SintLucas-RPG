// enemies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>

#include "Utils.h"
#include "Character.h"

#include <iostream>

int main()
{
	auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
	MATH_RANDOMSEED = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count());

	unsigned int randomSize = RandUintMinMax(20, 30);
	EnemyNode* enemyNodeHead = nullptr;
	for (unsigned int i = 0; i < randomSize; i++)
	{
		Enemy enemy(RandUintMinMax(10, 20), RandUintMinMax(2, 8), "Skeleton");
		Enemy_PushHead(enemyNodeHead, enemy);
	}

	std::cout << "The linked list has " << randomSize << " enemy entries \n";

	{
		EnemyNode* nodeIterator = enemyNodeHead;
		while (nodeIterator != nullptr)
		{
			nodeIterator->enemy.PrintStats();
			nodeIterator = nodeIterator->next;
		}
	}

	Player player(30, 10);
	while (enemyNodeHead != nullptr)
	{
		const int damageDealth = player.DealDamage();
		std::cout << "The player attacks the " << enemyNodeHead->enemy.GetName() << "for " << damageDealth << " damage! \n";
		if (!enemyNodeHead->enemy.TakeDamage(damageDealth))
		{
			Enemy_DeleteHead(enemyNodeHead);
		}
	}

	std::cout << "The player has slain all enemies! \n";
}
