#pragma once
class PlayerBullet
{
public:
	ObRect*		col;
	ObImage*	bullet;
	ObImage*	bulletDead;
	Vector2		fireDir;
	Vector2		lastPos;
	vector<Vector2> foot;
	float		scalar;
	float		tearBoomTime;

	bool		isfire;

	PlayerBullet();
	~PlayerBullet();

	bool		Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
	void		Update();
	void		Render();

private:
	int			level;

public:
	float			damage;

	int			GetLevel() { return level; } //ÃÑ¾Ë ·¹º§
	void		ChangeLevel(int level); // ÃÑ¾Ë·¹º§ÀÌ ¿Ã¶ó°¡¸é °¹¼ö³ª ÆÄ¿ö °­ÇØÁö°Ô
	void		StepBack();

	void		tearBoom(); //º®¿¡ ´ê¾ÒÀ»½Ã ´«¹° ÅÍÁü

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

