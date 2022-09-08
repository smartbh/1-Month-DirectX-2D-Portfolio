#pragma once
#define MAX 30

enum class PlayerState
{
	IDLE,
	WALK,
	DEAD
};

//¾ÆÀÌÅÛ ¸Ô¾úÀ»½Ã »ö±ò ¹Ù²Ù±â
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
	float       hitDuration;
	float		moveSpeed;
	float		hp;

	int			key; //¹® ¿©´Â ¿­¼è
	int			goldKey; //È²±Ý¹æ ¿­¼è
	int			bomb; //ÆøÅº

	Vector2		lastPos;

	bool		isDamaged;

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
	void hit();
	ObRect* getCol();
	void StepBack();
};

