#include "stdafx.h"

SceneGoldRoom::SceneGoldRoom()
{
    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;

    map = new ObTileMap();
    map->file = "itemMap.txt";
    map->Load();
    map->CreateTileCost();
    map->SetWorldPos(Vector2(900.0f, -900.0f));
    map->Update();

    doorsCol = new ObRect();
    doorsCol->scale = Vector2(64.0f * 1.5f, 64.0f);
    doorsCol->SetWorldPos(Vector2(map->GetWorldPos().x + 50.0f, map->GetWorldPos().y + 300.0f));
    doorsCol->collider = COLLIDER::RECT;
    doorsCol->isFilled = false;
    doorsCol->Update();

    door = new ObImage(L"doorOpenLeft.png");
    door->SetParentRT(*doorsCol);
    door->scale = Vector2(64.0f, 64.0f) * 2.0f;

    satanItemCol = new ObRect();
    satanItemCol->scale = Vector2(50.0f, 55.0f);
    satanItemCol->collider = COLLIDER::RECT;
    satanItemCol->SetWorldPos(Vector2(1300.0f, -600.0f));
    satanItemCol->isFilled = false;

    satanItem = new ObImage(L"satanItem.png");
    satanItem->SetParentRT(*satanItemCol);
    satanItem->scale = Vector2(40.0f, 45.0f);

}

SceneGoldRoom::~SceneGoldRoom()
{
}

Player* SceneGoldRoom::getPlayer()
{
	return pl;
}

ObTileMap* SceneGoldRoom::getMap()
{
	return map;
}

void SceneGoldRoom::setPlayer(Player* _player)
{
	pl = _player;
}

void SceneGoldRoom::Init()
{
}

void SceneGoldRoom::Release()
{
}

void SceneGoldRoom::Update()
{
    cout << "R map pos : " << map->GetWorldPos().x << " " << map->GetWorldPos().y << endl;
    cout << "R map scale : " << map->scale.x << " " << map->scale.y << endl;
    cout << "R pl pos " << pl->getCol()->GetWorldPos().x << " " << pl->getCol()->GetWorldPos().y << endl;
    cout << "R door pos " << doorsCol->GetWorldPos().x << " " << doorsCol->GetWorldPos().y << endl;
    
    bg->Update();
    map->Update();
    doorsCol->Update();
    door->Update();

    satanItemCol->Update();
    satanItem->Update();

    pl->Update();

    CAM->position = Vector2(map->GetWorldPos().x + 500.0f,
        map->GetWorldPos().y + 400.0f);
}

void SceneGoldRoom::LateUpdate()
{
    //¾ÆÀÌÅÛ È¹µæ
    if (satanItemCol->Intersect(pl->getCol()))
    {
        satanItemCol->visible = false;
        satanItemCol->collider = COLLIDER::NONE;
        satanItem->visible = false;
        pl->plBodyState = PlayerHeadBodyState::EVIL;
        pl->moveSpeed = 400.0f;
    }

    //¹® ÁøÀÔ½Ã
    if (doorsCol->Intersect(pl->getCol()))
    {
        Scene01* _scene01 = new Scene01();
        pl->getCol()->SetWorldPos(Vector2(310.0f, 0.0f));
        _scene01->pl = pl;
        SCENE->AddScene("Scene01", _scene01);
        SCENE->ChangeScene("Scene01");
    }

    Int2 on;

    if (map->WorldPosToTileIdx(pl->GetPos(), on))
    {
        ImGui::Text("TileState %d", map->GetTileState(on));
    }

    vector<Vector2>& Foot = pl->GetFoot();

    //ÇÃ·¹ÀÌ¾î
    for (int i = 0; i < 4; i++)
    {
        Int2 on;
        if (map->WorldPosToTileIdx(Foot[i], on))
        {
            if (map->GetTileState(on) == TILE_WALL || map->GetTileState(on) == TILE_WATER)
            {
                pl->StepBack();
            }
        }
    }

    //´«¹°
    for (int j = 0; j < MAX; j++)
    {
        Foot = pl->tear[j].GetFoot();

        for (int i = 0; i < 4; i++)
        {
            Int2 on;
            if (map->WorldPosToTileIdx(Foot[i], on))
            {
                if (map->GetTileState(on) == TILE_WALL)
                {
                    if (map->GetTileState(on) == TILE_WALL)
                    {
                        pl->tear[j].playTearEffect();
                    }
                }
            }
        }
    }
}

void SceneGoldRoom::Render()
{
    bg->Render();
    map->Render();
    doorsCol->Render();
    door->Render();
    satanItemCol->Render();
    satanItem->Render();

    pl->Render();
}

void SceneGoldRoom::ResizeScreen()
{
}
