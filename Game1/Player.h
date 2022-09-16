#pragma once
#define MAX 999

enum class PlayerState
{
	IDLE,
	WALK,
	ITEMUSE,
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
	ObImage*				plItemUse;

	PlayerState				plState;

	Vector2					lastPos;

	bool					isDamaged;

	float					animationPlayTime;

public:

	float					attackSpeed;
	float					attackDuration;
	float					hitDuration;
	float					moveSpeed;
	float					hp;

	int						key; //�� ���� ����
	int						goldKey; //Ȳ�ݹ� ����
	int						bomb; //��ź
	int						coin; //����

	float					maxRange = 200.0f;

	ObImage*				ItemUI;
	ObImage*				ItemBarUI;
	ObImage*				coinUI;
	ObImage*				keyUI;
	ObImage*				BombUI;
	ObImage*				Hp[3];

	Bomb					playerBombs[99];

	void					Idle();
	void					Walk();
	void					ItemUse();
	void					Dead();

	void					Input();

	PlayerBullet			tear[MAX];
	PlayerHeadBodyState		plBodyState;

	ObImage*				head;
	ObImage*				body;

	ObImage*				headEvil;
	ObImage*				bodyEvil;

public:
	Player();
	~Player();
	ObRect*					getCol();

	float					getAttackSpeed() { return attackSpeed; }
	float					getAttackDuration() { return attackDuration; }
	float					getHitDuration() { return hitDuration; }
	float					getmoveSpeed() { return moveSpeed; }
	float					getHp() { return hp; }

	void					addKey();
	void					addCoin();
	void					addBomb();
	
	void					subtractKey() { key--; }
	void					subtractCoin() { coin--; }
	void					subtractBomb() { bomb--; }

	void					Update();
	void					Render();
	void					hit();
	void					StepBack();
};

