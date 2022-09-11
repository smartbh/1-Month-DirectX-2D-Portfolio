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

	isBombSet = false;
}

Bomb::~Bomb()
{
	SafeDelete(bombCol);
	SafeDelete(bombImg);
}

void Bomb::setBomb()
{
	isBombSet = true;
}

void Bomb::explodeBomb()
{
	EFFECT
}

void Bomb::Update()
{
	bombCol->Update();
	bombImg->Update();

}

void Bomb::Render()
{
	bombCol->Render();
	bombImg->Render();
}
