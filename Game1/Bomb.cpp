#include "stdafx.h"

Bomb::Bomb()
{
	bombCol = new ObRect();
	bombCol->scale = Vector2(32.0f, 32.0f);
	bombCol->collider = COLLIDER::RECT;
	bombCol->isFilled = false;
	
	bombImg = new ObImage(L"bomb_state1.png");
	bombImg->SetParentRT(*bombCol);
	bombImg->scale = Vector2(32.0f, 32.0f);

	bombRange = new ObCircle();
	bombRange->SetParentRT(*bombCol);
	bombRange->scale = Vector2(60.0f, 60.0f);
	bombRange->collider = COLLIDER::CIRCLE;
	bombRange->isFilled = false;
	bombRange->color = Color(0.8f, 0.5f, 0.5f, 0.5f);

	isBombSet = false;

	bombTime = 3.0f;

	
}

Bomb::~Bomb()
{
	SafeDelete(bombCol);
	SafeDelete(bombImg);
	SafeDelete(bombRange);
}

void Bomb::setBomb(Vector2 _locatedBomb)
{
	bombCol->SetWorldPos(_locatedBomb);
	bombCol->Update();
	isBombSet = true;
}

void Bomb::explodeBomb()
{
	bombCol->Update();
	EFFECT->EffectPlay(bombCol->GetWorldPos(), 1);//ÆøÅº Æø¹ß ÀÌÆåÆ® ÇØÁÖ±â
}

void Bomb::Update()
{

	if (isBombSet) {
		bombCol->Update();
		bombImg->Update();
		EFFECT->Update();
		bombTime -= DELTA;
		if (bombTime > 0.0f)
		{
			bombImg->color = Color(RANDOM->Float(0.5f, 1.0f), RANDOM->Float(0.5f, 1.0f), 
									RANDOM->Float(0.5f, 1.0f), 0.5f);
		}
		else
		{
			bombCol->Update();
			bombImg->Update();
			explodeBomb();
			bombTime = 1.0f;
			isBombSet = false;
			bombImg->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
		}
	}
}

void Bomb::Render()
{

	if (isBombSet) {
		bombCol->Render();
		bombImg->Render();
		EFFECT->Render();
	}
}
		
