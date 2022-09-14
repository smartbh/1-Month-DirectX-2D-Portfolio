#pragma once

class Scene01 : public Scene
{
private:
	
	Monster* mon;

	ObImage*		tutorial1;
	ObImage*		tutorial2;
	ObImage*		tutorial3;
	ObImage*		tutorial4;

	ObImage*		spike; //������ũ ����
	ObRect*			spikeCol;

	ObImage*		rock; //����
	ObRect*			rockCol;

	ObImage*		doors[4]; //�����¿� ��
	

	ObRect*			bg; //�������

	ObTileMap*		map;

	//��ã��� ����
	vector<Tile*>	PlWay;

	//�̵���ų ��ġ
	Vector2			PlDest;
	Vector2			PlSour;

	//����
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
	virtual void	Release() override; //����
	virtual void	Update() override;
	virtual void	LateUpdate() override;//����
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

