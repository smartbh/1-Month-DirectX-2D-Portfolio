#pragma once

enum class MonsterFliesState
{
	IDLE,
	LOOK = 500,
	MOVE = 300,
	ATTACK = 100,
	DEAD = 50
};

class MonsterFlies : public Character
{
private:
	ObImage*		img;
	MonsterFliesState	monsterState;
	ObCircle*		range[3];
	float			distance;

	bool			scaleSwitching;
	bool			isDamaged = false;
	float			hitDuration = 0.3f;
public:
	int				hp = 3;
	bool			isDead = false;
	ObRect*			getCol() { return col; }
public:
	MonsterFlies();
	~MonsterFlies();

	void			Update();
	void			Render();

	void			Idle();
	void			Look();
	void			Move();
	void			Dead();
	void			hit();
};

