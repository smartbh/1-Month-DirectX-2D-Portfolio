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

	void		setBomb(); // ��ź ����
	void		explodeBomb(); //��ź ��Ʈ����
	void		Update();
	void		Render();

};

