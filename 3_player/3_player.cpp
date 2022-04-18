// enemies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>

//Now we have moved some code to different files, you can get them by including the headers.
#include "Utils.h"
#include "Character.h"

#include <iostream>

int main()
{
	//Getting system time for the random.
	auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
	MATH_RANDOMSEED = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count());

	unsigned int randomSize = RandUintMinMax(20, 30);

	//The start of the linked list, also known as the Head.
	EnemyNode* enemyNodeHead = nullptr;
	for (unsigned int i = 0; i < randomSize; i++)
	{
		//Create new enemies and push them as the head in the linked list.
		Enemy enemy(RandUintMinMax(10, 20), RandUintMinMax(2, 8), "Skeleton");
		//This function takes the a Node and an Enemy to create a new node in the list.
		Enemy_PushHead(enemyNodeHead, enemy);
	}

	std::cout << "The linked list has " << randomSize << " enemy entries \n";

	{
		//Iterate through all the nodes and print the enemy stats.
		EnemyNode* nodeIterator = enemyNodeHead;
		//Using a while loop until we hit a node with an empty next value.
		while (nodeIterator != nullptr)
		{
			nodeIterator->enemy.PrintStats();
			//After we print the enemy stats we change the iterator to point to the next element in the linked list.
			nodeIterator = nodeIterator->next;
		}
	}

	//Initalize the player and call it's parameterized constructor.
	Player player(30, 10);
	//Again, using a while loop until we hit a node with an empty next value. This will happen when all enemies have died.
	while (enemyNodeHead != nullptr)
	{
		//The damage the player will do to the enemy, cached so we can also print it.
		const int damageDealth = player.DealDamage();
		std::cout << "The player attacks the " << enemyNodeHead->enemy.GetName() << " for " << damageDealth << " damage! \n";
		if (!enemyNodeHead->enemy.TakeDamage(damageDealth))
		{
			//If the enemy died we delete him from the Linked list and move the next element as the head of the linked list.
			Enemy_DeleteHead(enemyNodeHead);
		}
	}

	std::cout << "The player has slain all enemies! \n";
}
