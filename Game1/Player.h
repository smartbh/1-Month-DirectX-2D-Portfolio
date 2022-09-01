#pragma once
#define MAX 30

enum class PlayerState
{
	IDLE,
	WALK,
	DEAD
};

//아이템 먹었을시 색깔 바꾸기
enum class PlayerHeadBodyState
{
	NORMAL,
	EVIL
};


class Player : public Character
{
private:
	ObImage*	head;
	ObImage*	body;

	PlayerState plState;
	
	float		attackSpeed;
	float		attackDuration;
	float		moveSpeed;
	float		hp;

	Vector2		lastPos;

public:

	void Idle();
	void Walk();

	void Input();

	PlayerBullet tear[MAX];

public:
	Player();
	~Player();

	void Update();
	void Render();

	void StepBack();
};

