#pragma once

class Main : public Scene
{
private:
	Player*		pl;
	ObImage*	Item;
	ObImage*	ItemBar;
	ObImage*	coin;
	ObImage*	key;
	ObImage*	Bomb;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
