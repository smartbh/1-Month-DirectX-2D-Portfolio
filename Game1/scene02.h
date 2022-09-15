#pragma once
class scene02 : public Scene
{
private:
	ObImage*		rockImg[4]; //바위
	ObRect*			rockCol[4];

	addBomb*		addBombItem[2];

	ObRect*			bg; //검은배경

	ObTileMap*		map;

	//비율
	float			g;
	Vector2			la;

public:
	scene02();
	~scene02();

	ObImage*		doors;
	ObRect*			doorsCol;

	Player*			pl;

	Player*			getPlayer();
	ObTileMap*		getMap();
	void			setPlayer(Player* _player);

public:
	virtual void	Init() override;
	virtual void	Release() override; //해제
	virtual void	Update() override;
	virtual void	LateUpdate() override;//갱신
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

