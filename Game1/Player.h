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


	Vector2		lastPos;

	bool		isDamaged;

public:

	float		attackSpeed;
	float		attackDuration;
	float       hitDuration;
	float		moveSpeed;
	float		hp;

	int			key; //¹® ¿©´Â ¿­¼è
	int			goldKey; //È²±Ý¹æ ¿­¼è
	int			bomb; //ÆøÅº


	void Idle();
	void Walk();

	void Input();

	PlayerBullet tear[MAX];

public:
	Player();
	~Player();
	float getAttackSpeed() { return attackSpeed; }
	float getAttackDuration() { return attackDuration; }
	float getHitDuration() { return hitDuration; }
	float getmoveSpeed() { return moveSpeed; }
	float getHp() { return hp; }

	int getKey() { return key; }
	int getGoldKey() { return goldKey; }
	int getBomb() { return bomb; }

	void	setPlayerData(float	_attackSpeed,
		float _attackDuration, float _hitDuration,
		float _moveSpeed, float _hp, int _key, int _goldKey, int _bomb);

	void Update();
	void Render();
	void hit();
	ObRect* getCol();
	void StepBack();
};

