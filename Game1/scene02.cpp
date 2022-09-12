#include "stdafx.h"

scene02::scene02()
{
	cout << "'hello" << endl;
    //m.lock();
    ////Sleep(1000);
    //loadingCount++;
    map = new ObTileMap();
    map->file = "NormalMap1.txt";
    map->Load();
    map->CreateTileCost();
    //map->SetWorldPos(Vector2(0.0f, 0.0f));

    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;

    //m.unlock();
}

scene02::~scene02()
{
}

Player* scene02::getPlayer()
{
    return pl;
}

ObTileMap* scene02::getMap()
{
    return map;
}

void scene02::setPlayer(Player* _player)
{
    pl = _player;
}

void scene02::Init()
{
}

void scene02::Release()
{
}

void scene02::Update()
{
    cout << map->GetWorldPos().x << " " << map->GetWorldPos().y << endl;
    map->Update();
    pl->Update();
    bg->Update();
    CAM->position = pl->GetPos();
}

void scene02::LateUpdate()
{
}

void scene02::Render()
{
    bg->Render();
    map->Render();
    pl->Render();
}

void scene02::ResizeScreen()
{
}
