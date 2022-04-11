#pragma once
class Character
{
public:
	Character();
	Character(int a_HP, int a_Strength);
	virtual ~Character() = 0;

	virtual void PrintStats() const = 0;
	//returns false if it's hitpoints is equal or below 0.
	bool TakeDamage(int a_DamageTaken);
	const int DealDamage() const { return strength; }

	bool IsAlive() const { return hitPoints; };

protected:
	int maxHitPoints;
	int hitPoints;
	int strength;
};

class Enemy : public Character
{
public:
	Enemy();
	Enemy(int a_HP, int a_Strength, const char* a_Name);
	~Enemy();

	virtual void PrintStats() const override;
	const char* GetName() const { return name; }

private:
	const char* name;
};

struct EnemyNode
{
	Enemy enemy;
	EnemyNode* next = nullptr;
};

static void Enemy_PushHead(EnemyNode*& a_Head, Enemy& a_Enemy)
{
	EnemyNode* newNode = new EnemyNode;
	newNode->enemy = a_Enemy;
	newNode->next = a_Head;

	a_Head = newNode;
}

static void Enemy_Pushback(EnemyNode*& a_Node, Enemy& a_Enemy)
{
	EnemyNode*& pushNext = a_Node;

	while (pushNext->next != nullptr)
	{
		pushNext = pushNext->next;
	}
	EnemyNode* newNode = new EnemyNode;
	newNode->enemy = a_Enemy;
	pushNext->next = newNode;
};

static void Enemy_Insert(EnemyNode* a_BackNode, Enemy& a_Enemy)
{
	if (a_BackNode == nullptr) return;

	EnemyNode* newNode = new EnemyNode;
	newNode->enemy = a_Enemy;
	newNode->next = a_BackNode->next;

	a_BackNode->next = newNode;
};

static void Enemy_DeleteHead(EnemyNode*& a_Head)
{
	EnemyNode* oldHead = a_Head;
	a_Head = a_Head->next;
	delete oldHead;
}


class Player : public Character
{
public:
	Player();
	Player(int a_HP, int a_Strength);
	~Player();

	virtual void PrintStats() const override;

private:
	const int healStrength = 10;
};
