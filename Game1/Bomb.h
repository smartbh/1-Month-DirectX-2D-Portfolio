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
	void		setBomb(Vector2 _locatedBomb); // ��ź ����
	void		explodeBomb(); //��ź ��Ʈ����
	void		Update();
	void		Render();

};

