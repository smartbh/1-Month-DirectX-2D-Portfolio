#include "stdafx.h"

EffectManger::EffectManger()
{
	tearBoom = new ObImage(L"tear_explode.png");
	tearBoom->scale = Vector2(64.0f, 64.0f);
	tearBoom->maxFrame.x = 16;
	tearBoom->visible = true;

	BombBoom = new ObImage(L"BombExplosion.png");
	BombBoom->scale = Vector2(96.0f, 96.0f);
	BombBoom->maxFrame.x = 16;
	BombBoom->visible = true;
}

EffectManger::~EffectManger()
{
}

void EffectManger::EffectPlay(Vector2 _playLocation, int num)
{
	//매개변수로 위치, enumtype이 있어야한다. 정수로 받음
	switch (num)
	{
		//케이스 0 = 눈물, 1 = 폭탄
	case 0:
		tearBoom->visible = true;
		tearBoom->SetWorldPos(_playLocation);
		tearBoom->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		tearBoom->Render();
		break;
	case 1:
		BombBoom->visible = true;
		BombBoom->SetWorldPos(_playLocation);
		BombBoom->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		BombBoom->Render();
		break;
	default:
		break;
	}
}

void EffectManger::Release()
{
}

void EffectManger::Update()
{
	tearBoom->Update();
	BombBoom->Update();
}

void EffectManger::LateUpdate()
{
}

void EffectManger::Render()
{
	tearBoom->Render();
	BombBoom->Render();
}
