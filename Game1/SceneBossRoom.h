#pragma once
class SceneBossRoom : public Scene
{
private:
	ObRect*			bg; //�������
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
	virtual void	Release() override; //����
	virtual void	Update() override;
	virtual void	LateUpdate() override;//����
	virtual void	Render() override;
	virtual void	ResizeScreen() override;
};

