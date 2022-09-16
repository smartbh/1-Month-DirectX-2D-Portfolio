#pragma once
class SceneBossRoom : public Scene
{
private:
	ObRect*			bg; //검은배경
	Monster*		mon;
	ObTileMap*		map;

public:
	Player*			pl;
	ObRect*			doorCol;
	ObImage*		doorImage;


public:
	SceneBossRoom();
	~SceneBossRoom();

	virtual void	Init() override;
	virtual void	Release() override; //해제
	virtual void	Update() override;
	virtual void	LateUpdate() override;//갱신
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

