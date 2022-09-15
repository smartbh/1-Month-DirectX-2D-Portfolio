#pragma once
class Bomb
{
private:
	ObImage*		bombImg;
	ObImage*		BombBoom;
	ObRect*			bombCol;
	ObCircle*		bombRange;

	bool			isBombSet;
	bool			isBomBExplodeCheck = false;
	float			bombTime;

public:
	bool		getIsbombset() { return isBombSet; }
	void		setBomb(Vector2 _locatedBomb); // ÆøÅº ³õ±â
	void		explodeBomb(); //ÆøÅº ÅÍÆ®¸®±â
	ObCircle*	getBombRange() { return bombRange; }
	ObRect* getBombCol() { return bombCol; }
	void		bombbRangeColOff() { bombCol->collider = COLLIDER::NONE; bombRange->collider = COLLIDER::NONE; }
public:
	Bomb();
	~Bomb();

	void		Update();
	void		Render();

};

