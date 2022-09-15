#pragma once
class SceneKeyFightRoomLeft : public Scene
{
private:
	ObRect*			bg; //검은배경
	ObTileMap*		map;

	ObImage*		door; //오른쪽에 있어야
	ObImage*		doorOpen; //오른쪽에 있어야
	
	addKey*			addKeyItem;

	MonsterFlies			flies[3]; //몬스터

	//길찾기용 변수
	vector<Tile*>	PlWay;

	//이동시킬 위치
	Vector2			PlDest;
	Vector2			PlSour;

	//비율
	float			g;
	int				mosterCount = 4;
public:
	Player*			pl;
	ObRect*			doorsCol;

	int				countMonsterOnMap() { return mosterCount; }
	void			reduceMonsterCountOnMap() { mosterCount--; }

	Player*			getPlayer() { return pl; }
	void			setPlayer(Player* _player) { pl = _player; }
	ObTileMap*		getMap() { return map; }

public:
	SceneKeyFightRoomLeft();
	~SceneKeyFightRoomLeft();

	virtual void	Init() override;
	virtual void	Release() override; //해제
	virtual void	Update() override;
	virtual void	LateUpdate() override;//갱신
	virtual void	Render() override;
	virtual void	ResizeScreen() override;

};

