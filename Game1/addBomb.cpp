#include "stdafx.h"

addBomb::addBomb()
{

    addBombCol = new ObRect();
    addBombCol->scale = Vector2(32.0f, 32.0f);
    addBombCol->collider = COLLIDER::RECT;
    addBombCol->isFilled = false;

    addBombImage = new ObImage(L"bomb_add.png");
    addBombImage->SetParentRT(*addBombCol);
    addBombImage->scale = Vector2(32.0f, 32.0f);

    addBombColDouble = new ObRect();
    addBombColDouble->scale = Vector2(32.0f, 32.0f);
    addBombColDouble->collider = COLLIDER::RECT;
    addBombColDouble->isFilled = false;

    addBombImage = new ObImage(L"bomb_add2.png");
    addBombImage->SetParentRT(*addBombColDouble);
    addBombImage->scale = Vector2(32.0f, 32.0f);

    bombNum = 1;
}

addBomb::addBomb(int _num)
{
    bombNum = _num;

    addBombCol = new ObRect();
    addBombCol->scale = Vector2(32.0f, 32.0f);
    addBombCol->collider = COLLIDER::RECT;
    addBombCol->isFilled = false;

    addBombImage = new ObImage(L"bomb_add.png");
    addBombImage->SetParentRT(*addBombCol);
    addBombImage->scale = Vector2(32.0f, 32.0f);

    addBombColDouble = new ObRect();
    addBombColDouble->scale = Vector2(32.0f, 32.0f);
    addBombColDouble->collider = COLLIDER::RECT;
    addBombColDouble->isFilled = false;

    addBombImageDouble = new ObImage(L"bomb_add2.png");
    addBombImageDouble->SetParentRT(*addBombColDouble);
    addBombImageDouble->scale = Vector2(32.0f, 32.0f);
}

addBomb::~addBomb()
{

}

void addBomb::Update()
{
    switch (bombNum)
    {
    case 1:
        addBombCol->Update();
        addBombImage->Update();
        break;
    case 2:
        addBombColDouble->Update();
        addBombImageDouble->Update();
        break;
    }
}

void addBomb::Render()
{
    switch (bombNum)
    {
    case 1:
        addBombCol->Render();
        addBombImage->Render();
        break;
    case 2:
        addBombColDouble->Render();
        addBombImageDouble->Render();
        break;
    }
}

void addBomb::getPlayerBomb() //ÇÃ·¹ÀÌ¾î°¡ ÆøÅºÀ» ¸ÔÀ¸¸é
{
    addBombCol->visible = false;
    addBombCol->collider = COLLIDER::NONE;

    addBombImage->visible = false;


    addBombColDouble->visible = false;
    addBombColDouble->collider = COLLIDER::NONE;

    addBombImageDouble->visible = false;
}
