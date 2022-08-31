#pragma once

enum class PlayerState
{
	IDLE,
	WALK,
	ROLL,
	ATTACK
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
	ObImage*	walk;
	ObImage*	roll;
	ObImage*	head;
	ObImage*	body;


	PlayerState plState;
	
	float		rollTime;

	Vector2		lastPos;

public:
	void Idle();
	void Walk();
	void Roll();

	void Input();

public:
	Player();
	~Player();

	void Update();
	void Render();

	void StepBack();
};

