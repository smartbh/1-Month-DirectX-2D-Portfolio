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

	int GetLevel() { return level; } //�Ѿ� ����
	void ChangeLevel(int level); // �Ѿ˷����� �ö󰡸� ������ �Ŀ� ��������
};

