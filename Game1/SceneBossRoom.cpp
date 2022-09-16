#include "stdafx.h"

SceneBossRoom::SceneBossRoom()
{
    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;

    map = new ObTileMap();
    map->file = "leftMap.txt";
    map->Load();
    map->CreateTileCost();
    map->SetWorldPos(Vector2());

    doorCol = new ObRect();
    doorImage = new ObImage(L"");

}

SceneBossRoom::~SceneBossRoom()
{
}

void SceneBossRoom::Init()
{
}

void SceneBossRoom::Release()
{
}

void SceneBossRoom::Update()
{
}

void SceneBossRoom::LateUpdate()
{
}

void SceneBossRoom::Render()
{
}

void SceneBossRoom::ResizeScreen()
{
}
