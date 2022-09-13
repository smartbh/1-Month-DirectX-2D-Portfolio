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

	SOUND->AddSound("tear_destroy.wav", "TEARPOP");//���� ������ �Ҹ�
	SOUND->AddSound("bomb_explosion.wav", "BOMBEXPLODE");//���� ������ �Ҹ�
}

EffectManger::~EffectManger()
{
}

void EffectManger::EffectPlay(Vector2 _playLocation, int num)
{
	//�Ű������� ��ġ, enumtype�� �־���Ѵ�. ������ ����
	switch (num)
	{
		//���̽� 0 = ����, 1 = ��ź
	case 0:
		//tearBoom->Update();
		tearBoom->visible = true;
		tearBoom->SetWorldPos(_playLocation);
		tearBoom->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		SOUND->Play("TEARPOP");
		//tearBoom->Render();
		break;
	case 1:
		//BombBoom->Update();
		BombBoom->visible = true;
		BombBoom->SetWorldPos(_playLocation);
		BombBoom->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		SOUND->Play("BOMBEXPLODE");
		//BombBoom->Render();
		break;
	default:
		tearBoom->visible = false;
		BombBoom->visible = false;
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
