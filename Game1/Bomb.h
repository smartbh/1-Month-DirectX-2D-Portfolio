#pragma once
class Bomb
{
private:
	ObImage*	bombImg;
	ObRect*		bombCol;
public:
	Bomb();
	~Bomb();

	void		Update();
	void		Render();

};

