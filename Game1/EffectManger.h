#pragma once
enum class EffectList
{
	TEARBOOM,
	BOMB
};


class EffectManger : public Singleton<EffectManger>
{
private:
	ObImage*		tearBoom;
	ObImage*		BombBoom;

public:
    EffectManger();
    ~EffectManger();

    void    EffectPlay();
    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
};

