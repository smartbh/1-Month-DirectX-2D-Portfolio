#pragma once
class SceneGoldRoom : public Scene
{
	//오른쪽에 만들기
	//열쇠 없으면 못들어가게
private:
	ObRect*			bg; //검은배경

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
	virtual void	Release() override; //해제
	virtual void	Update() override;
	virtual void	LateUpdate() override;//갱신
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

