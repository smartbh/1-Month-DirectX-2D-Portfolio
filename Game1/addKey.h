#pragma once
class addKey
{
private:
	ObRect*		keyCol;
	ObImage*	keyImage;
public:
	void        getPlayerKey();
	ObRect*		getKeyCol() { return keyCol; }
public:
	addKey();
	~addKey();

	void		Update();
	void		Render();

};

