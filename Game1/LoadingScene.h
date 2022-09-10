#pragma once

class LoadingScene : public Scene
{
public:
	ObImage* bg;
	ObRect* rc;
	thread* t1;

	Player* pl;

public:
	LoadingScene();
	~LoadingScene();

	Player* getPlayer();
	void	setPlayer(Player* _player);

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

