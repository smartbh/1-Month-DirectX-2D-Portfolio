#pragma once
class scene02 : public Scene
{
private:
	Player* pl;
	Monster* mon;

	ObImage* spike; //스파이크 실험
	ObRect* spikeCol;

	ObImage* rock; //바위
	ObRect* rockCol;

	ObImage* doors[4]; //전후좌우 순
	ObRect* doorsCol[4];

	ObRect* bg; //검은배경

	ObTileMap* map;

	//길찾기용 변수
	vector<Tile*> PlWay;

	//이동시킬 위치
	Vector2		PlDest;
	Vector2		PlSour;

	//비율
	float		g;

public:
	scene02();
	~scene02();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

