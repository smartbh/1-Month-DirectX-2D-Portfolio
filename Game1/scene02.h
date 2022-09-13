#pragma once
class scene02 : public Scene
{
private:

	Monster*		mon;

	ObImage*		spike; //������ũ ����
	ObRect*			spikeCol;

	ObImage*		rockImg[4]; //����
	ObRect*			rockCol[4];

	ObRect*			bg; //�������

	ObTileMap*		map;

	//��ã��� ����
	vector<Tile*>	PlWay;

	//�̵���ų ��ġ
	Vector2			PlDest;
	Vector2			PlSour;

	//����
	float			g;

public:
	scene02();
	~scene02();

	ObImage* doors; //�����¿� ��
	ObRect* doorsCol;

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

