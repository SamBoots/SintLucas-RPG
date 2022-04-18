#pragma once

//Why a Header file? This article explains it well: https://www.geeksforgeeks.org/header-files-in-c-cpp-and-its-uses/
//In short, you place declerations here and you define the declerations in the .cpp file, which in our case is Character.cpp.

class Character
{
public:
	Character();
	Character(int a_HP, int a_Strength);
	//Virtual destructor, this needed if this class will be inherited from, else you can get into problems with the destructor. https://www.geeksforgeeks.org/virtual-destructor/
	virtual ~Character() = 0;

	//virtual function for polymorphism. We make this function = 0 so that this class is a pure virtual. That means we cannot initalize this class, only it's non-pure virtual childeren.
	virtual void PrintStats() const = 0;

	//Functions that all characters will use.
		//returns false if it's hitpoints is equal or below 0.
	bool TakeDamage(int a_DamageTaken);

	//We can also put definitions inside the headerfile, up to your judgement. For just getting values in our case is one reason why to do that.
	const int DealDamage() const { return strength; }
	//If hitpoints is equal or lower then 0 then it will return false, else it will return true.
	bool IsAlive() const 
	{ 
		if (hitPoints <= 0)
			return false;

		//return true if it has more then 1 hit point.
		return true;
	};

	//Protected is like private but the childeren can access it.
protected:
	//variables that all characters will use.
	int maxHitPoints;
	int hitPoints;
	int strength;
};

//An enemy, it inherits from Character so it has everything that is not private from character and can use it as if it's part of Enemy. https://www.geeksforgeeks.org/polymorphism-in-c/
class Enemy : public Character
{
public:
	Enemy();
	Enemy(int a_HP, int a_Strength, const char* a_Name);
	~Enemy();

	//In order to override a virtual function it needs to have the same name as the function from the inherited class. 
	//You can also then use virtual or override to show that this is indeed an overwritten. This is not required but good to know if it's an inherited function.
	//We overwrite PrintStats() because we also want to include it's name in the print to console.
	virtual void PrintStats() const override;
	const char* GetName() const { return name; }

private:
	const char* name;
};

//Very simple linked list, we can only push to the head and delete the head. Just look up linked list C and you will find a million resources, but here is one from a familiar site https://www.geeksforgeeks.org/data-structures/linked-list/
struct EnemyNode
{
	Enemy enemy;
	EnemyNode* next = nullptr;
};

//This function accepts the head and changes the head to the newly created node.
//*& is used because we will directly modify the pointer and return that.
//You can also decide that this function returns an enemyNode pointer that is represented as the head. Up to you.
static void Enemy_PushHead(EnemyNode*& a_Head, Enemy& a_Enemy)
{
	//Create the new node and set the current head as it's next in line.
	EnemyNode* newNode = new EnemyNode;
	newNode->enemy = a_Enemy;
	newNode->next = a_Head;

	//Change the head to the new node.
	a_Head = newNode;
}

//This function will delete the head and shove it's next in line as the new head.
static void Enemy_DeleteHead(EnemyNode*& a_Head)
{
	//Cache old node for deletion.
	EnemyNode* oldHead = a_Head;
	//The head is now the next in line of oldHead.
	a_Head = a_Head->next;
	//Delete the old now that a_Head is the next in line.
	delete oldHead;
}


//The player, the player has healStrength in case we want to give it an ability where it can heal itself. Else it's completely the same as a normal character.
class Player : public Character
{
public:
	Player();
	Player(int a_HP, int a_Strength);
	~Player();

	//We overwrite PrintStats() because we also want to include it's healStrength in the print to console.
	virtual void PrintStats() const override;

private:
	//Default value of healStrength is 10 unless the constructor or something else changes it.
	const int healStrength = 10;
};
