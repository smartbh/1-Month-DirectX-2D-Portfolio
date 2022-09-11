#pragma once
class Bomb
{
private:
	ObImage*	bombImg;
	ObRect*		bombCol;

	bool		isBombSet;
public:
	Bomb();
	~Bomb();

	void		setBomb(); // ÆøÅº ³õ±â
	void		explodeBomb(); //ÆøÅº ÅÍÆ®¸®±â
	void		Update();
	void		Render();

};

