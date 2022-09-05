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
	ObImage*	head;
	ObImage*	body;

	PlayerState plState;
	
	float		attackSpeed;
	float		attackDuration;
	float       hitDuration;
	float		moveSpeed;
	float		hp;

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

	void StepBack();
};

