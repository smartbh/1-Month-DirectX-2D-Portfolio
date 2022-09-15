#include "stdafx.h"

addCoin::addCoin(int _num)
{
	coinNum = _num;

	coinCol = new ObRect();
	coinCol->scale = Vector2(65.0f, 40.0f);
	coinCol->collider = COLLIDER::RECT;
	coinCol->isFilled = false;

	coinImage = new ObImage(L"coin1.png");
	coinImage->SetParentRT(*coinCol);
	coinImage->scale = Vector2(65.0f, 40.0f);

	coinDoubleCol = new ObRect();
	coinDoubleCol->scale = Vector2(65.0f, 40.0f);
	coinDoubleCol->collider = COLLIDER::RECT;
	coinDoubleCol->isFilled = false;

	coinDoubleImage = new ObImage(L"coin2.png");
	coinDoubleImage->SetParentRT(*coinDoubleCol);
	coinDoubleImage->scale = Vector2(65.0f, 40.0f);
}

addCoin::~addCoin()
{
}

void addCoin::Update()
{
	switch (coinNum)
	{
	case 1:
		coinCol->Update();
		coinImage->Update();
		break;
	case2:
		coinDoubleCol->Update();
		coinDoubleImage->Update();
		break;
	}
}

void addCoin::Render()
{
	switch (coinNum)
	{
	case 1:
		coinCol->Render();
		coinImage->Render();
		break;
	case2:
		coinDoubleCol->Render();
		coinDoubleImage->Render();
		break;
	}
}

void addCoin::getPlayerCoin()
{

}