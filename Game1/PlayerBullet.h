#pragma once
class PlayerBullet
{
public:
	ObRect*		col;
	ObImage*	bullet;
	Vector2		fireDir;
	Vector2		lastPos;
	vector<Vector2> foot;
	float		scalar;

	bool		isfire;

	PlayerBullet();
	~PlayerBullet();

	bool		Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
	void		Update();
	void		Render();

private:
	int			level;

public:
	int			damage;

	int			GetLevel() { return level; } //총알 레벨
	void		ChangeLevel(int level); // 총알레벨이 올라가면 갯수나 파워 강해지게
	void		StepBack();

	Vector2 GetPos()
	{
		return col->GetWorldPos();
	}
	void SetPos(Vector2 pos)
	{
		col->SetWorldPos(pos);
	}


	vector<Vector2>& GetFoot()
	{
		foot.resize(4);

		foot[0] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(-10.0f, -10.0f);
		foot[1] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(10.0f, -10.0f);
		foot[2] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(-10.0f, 10.0f);
		foot[3] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(10.0f, 10.0f);

		return foot;
	}
};

