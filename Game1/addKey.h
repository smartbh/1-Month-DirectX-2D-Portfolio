#pragma once
class addKey
{
private:
	ObRect*		keyCol;
	ObImage*	keyImage;
public:
	void        getPlayerKey();
public:
	addKey();
	~addKey();

	void		Update();
	void		Render();

};

