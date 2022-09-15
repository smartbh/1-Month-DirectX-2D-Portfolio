#pragma once
class addCoin
{
private:
	int			coinNum = 1;

	ObRect*		coinCol;
	ObImage*	coinImage;

	ObRect*		coinDoubleCol;
	ObImage*	coinDoubleImage;
public:
	void        getPlayerCoin();
public:
	addCoin(int _num);
	~addCoin();

	void		Update();
	void		Render();
};

