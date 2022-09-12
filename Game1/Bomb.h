#pragma once
class Bomb
{
private:
	ObImage*		bombImg;
	ObRect*			bombCol;
	ObCircle*		bombRange;

	bool			isBombSet;
	float			bombTime;
public:
	Bomb();
	~Bomb();

	bool		getIsbombset() { return isBombSet;  }
	void		setBomb(Vector2 _locatedBomb); // ÆøÅº ³õ±â
	void		explodeBomb(); //ÆøÅº ÅÍÆ®¸®±â
	void		Update();
	void		Render();

};

