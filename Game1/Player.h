#pragma once
#define MAX 30

enum class PlayerState
{
	IDLE,
	WALK,
	DEAD
};

//������ �Ծ����� ���� �ٲٱ�
enum class PlayerHeadBodyState
{
	NORMAL,
	EVIL
};


class Player : public Character
{
private:
	ObImage*	walk;
	ObImage*	roll;
	ObImage*	head;
	ObImage*	body;


	PlayerState plState;
	
	float		rollTime;

	float		attackSpeed;
	float		damage;
	Vector2		lastPos;

public:

	void Idle();
	void Walk();
	void Attack();
	void ItemUse();

	void Input();

	PlayerBullet tear[MAX];

public:
	Player();
	~Player();

	void Update();
	void Render();

	void StepBack();
};

