#pragma once

class Scene01 : public Scene
{
private:
	
	Monster* mon;

	ObImage*		tutorial1;
	ObImage*		tutorial2;
	ObImage*		tutorial3;
	ObImage*		tutorial4;

	ObImage*		spike; //스파이크 실험
	ObRect*			spikeCol;

	ObImage*		rock; //바위
	ObRect*			rockCol;

	ObImage*		doors[4]; //전후좌우 순
	

	ObRect*			bg; //검은배경

	ObTileMap*		map;

	//길찾기용 변수
	vector<Tile*>	PlWay;

	//이동시킬 위치
	Vector2			PlDest;
	Vector2			PlSour;

	//비율
	float			g;

	Vector2 la;

public:
	Player*			pl;
	ObRect* doorsCol[4];

	Scene01();
	~Scene01();

	Player*			getPlayer();
	void			setPlayer(Player* _player);
	ObTileMap*		getMap();


public:
	virtual void	Init() override;
	virtual void	Release() override; //해제
	virtual void	Update() override;
	virtual void	LateUpdate() override;//갱신
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

