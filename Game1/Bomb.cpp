#include "stdafx.h"

Bomb::Bomb()
{
	bombCol = new ObRect();
	bombCol->scale = Vector2(32.0f, 32.0f) * 1.5f;
	bombCol->SetWorldPos(Vector2(9999.0f, 9999.0f));
	bombCol->collider = COLLIDER::RECT;
	bombCol->isFilled = false;
	
	bombImg = new ObImage(L"bomb_state1.png");
	bombImg->SetParentRT(*bombCol);
	bombImg->scale = Vector2(32.0f, 32.0f) * 1.5f;

	BombBoom = new ObImage(L"BombExplosion.png");
	BombBoom->SetParentRT(*bombCol);
	BombBoom->scale = Vector2(96.0f, 96.0f) * 1.5f;
	BombBoom->maxFrame.x = 16;

	bombRange = new ObCircle();
	bombRange->SetParentRT(*bombCol);
	bombRange->scale = Vector2(60.0f, 60.0f) * 2.5f;
	bombRange->collider = COLLIDER::NONE;
	bombRange->isFilled = false;
	bombRange->color = Color(0.8f, 0.5f, 0.5f, 0.5f);

	isBombSet = false;

	bombTime = 5.0f;

	SOUND->AddSound("bomb_explosion.wav", "BOMBEXPLODE");
}

Bomb::~Bomb()
{
	//SafeDelete(bombCol);
	//SafeDelete(bombImg);
	//SafeDelete(BombBoom);
	//SafeDelete(bombRange);
}

void Bomb::setBomb(Vector2 _locatedBomb)
{
	if (!isBombSet)
	{
		bombCol->visible = true;
		bombImg->visible = true;
		BombBoom->visible = false;
		bombRange->visible = false;

		isBombSet = true;
		bombCol->SetWorldPos(_locatedBomb);
	}
}

void Bomb::explodeBomb()
{
	bombCol->visible = true;
	bombImg->visible = false;
	BombBoom->visible = true;
	bombRange->visible = true;
	bombCol->collider = COLLIDER::NONE;
	bombRange->collider = COLLIDER::CIRCLE;
	BombBoom->SetWorldPos(bombCol->GetWorldPos());
	BombBoom->ChangeAnim(ANIMSTATE::ONCE, 0.05f);

	bombCol->Update();
	bombImg->Update();
	BombBoom->Update();
	SOUND->Play("BOMBEXPLODE");
}

void Bomb::Update()
{
	if (!isBombSet) return;
	
	if (!isBomBExplodeCheck)
	{
		cout << "1" << endl;
		bombTime -= DELTA;
		if (bombTime > 0.0f)
		{
			cout << bombTime << endl;
			bombImg->color = Color(RANDOM->Float(0.5f, 1.0f), RANDOM->Float(0.5f, 1.0f),
				RANDOM->Float(0.5f, 1.0f), 0.5f);
		}
		else
		{
			cout << "3" << endl;
			explodeBomb();
			bombTime = 1.0f;
			isBomBExplodeCheck = true;
			bombImg->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			SOUND->Play("BOMBEXPLODE");
		}
	}

	bombCol->Update();
	bombImg->Update();
	BombBoom->Update();
	bombRange->Update();
}

void Bomb::Render()
{
	bombCol->Render();
	bombImg->Render();
	BombBoom->Render();
	bombRange->Render();
}
		
