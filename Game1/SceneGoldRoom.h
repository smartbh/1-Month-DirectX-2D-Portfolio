#pragma once
class SceneGoldRoom : public Scene
{
	//�����ʿ� �����
	//���� ������ ������
private:
	ObRect*			bg; //�������

	ObTileMap*		map;

	ObImage*		satanItem;

	Monster*		mon;

public:
	SceneGoldRoom();
	~SceneGoldRoom();

	ObImage*		door;
	ObRect*			doorsCol;

	ObRect*			satanItemCol;

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

