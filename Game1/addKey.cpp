#include "stdafx.h"

addKey::addKey()
{
	keyCol = new ObRect();
	keyCol->scale = Vector2(28.0f, 32.0f);
	keyCol->collider = COLLIDER::RECT;
	keyCol->isFilled = false;
	keyCol->visible = false;

	keyImage = new ObImage(L"key.png");
	keyImage->SetParentRT(*keyCol);
	keyImage->scale = Vector2(28.0f, 32.0f);
}

addKey::~addKey()
{
}

void addKey::Update()
{
	keyCol->Update();
	keyImage->Update();
}

void addKey::Render()
{
	keyCol->Render();
	keyImage->Render();
}

void addKey::getPlayerKey()
{
	keyCol->visible = false;
	keyCol->collider = COLLIDER::NONE;

	keyImage->visible = false;
}