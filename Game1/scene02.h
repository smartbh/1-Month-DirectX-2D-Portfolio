#pragma once
class scene02 : public Scene
{
private:
	ObImage*		rockImg[4]; //����
	ObRect*			rockCol[4];

	addBomb*		addBombItem[2];

	ObRect*			bg; //�������

	ObTileMap*		map;

	//����
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
	virtual void	Release() override; //����
	virtual void	Update() override;
	virtual void	LateUpdate() override;//����
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

