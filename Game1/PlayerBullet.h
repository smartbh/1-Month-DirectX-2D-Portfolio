#pragma once
class PlayerBullet
{
public:
	ObRect* col;
	ObImage* bullet;
	Vector2	fireDir;
	float	scalar;

	bool	isfire;

	PlayerBullet();
	~PlayerBullet();

	bool Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
	void Update();
	void Render();

private:
	int		 level;

public:

	ObImage* greenB[4];
	int damage;

	int GetLevel() { return level; } //총알 레벨
	void ChangeLevel(int level); // 총알레벨이 올라가면 갯수나 파워 강해지게
};

