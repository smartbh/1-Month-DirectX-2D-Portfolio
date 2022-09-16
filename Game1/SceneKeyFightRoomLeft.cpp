#include "stdafx.h"
SceneKeyFightRoomLeft::SceneKeyFightRoomLeft()
{
    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;

    map = new ObTileMap();
    map->file = "leftMap.txt";
    map->Load();
    map->CreateTileCost();
    map->SetWorldPos(Vector2(-999.0f, 999.0f));

    doorsCol = new ObRect();
    doorsCol->scale = Vector2(64.0f * 1.5f, 64.0f);
    doorsCol->SetWorldPos(Vector2(map->GetWorldPos().x, map->GetWorldPos().y));
    doorsCol->collider = COLLIDER::RECT;
    doorsCol->isFilled = false;

    door = new ObImage(L"doorRight.png");
    door->SetParentRT(*doorsCol);
    door->scale = Vector2(64.0f, 64.0f) * 2.0f;

    doorOpen = new ObImage(L"doorOpenRight.png");
    doorOpen->SetParentRT(*doorsCol);
    doorOpen->scale = Vector2(64.0f, 64.0f) * 2.0f;

    addKeyItem = new addKey();
    addKeyItem->getKeyCol()->SetWorldPos(Vector2(-770.0f, 1220.0f));

    for (int i = 0; i < 3; i++)
    {
        flies[i].SetPos(Vector2(-770.0f + i * 20.0f, 1220.0f));
    }
}

SceneKeyFightRoomLeft::~SceneKeyFightRoomLeft()
{
}

void SceneKeyFightRoomLeft::Init()
{
}

void SceneKeyFightRoomLeft::Release()
{
}

void SceneKeyFightRoomLeft::Update()
{
    if (monsterDeadLeftRoom > 0) //몬스터가 한마리라도 남아있을경우
    {
        doorsCol->collider = COLLIDER::NONE;
        door->visible = true;
        doorOpen->visible = false;
    }
    else // 몬스터가 모두 죽었을시
    {
        monsterDeadLeftRoom = 0;
        doorsCol->collider = COLLIDER::RECT;
        door->visible = false;
        doorOpen->visible = true;
    }
    cout << "map pos : "<< map->GetWorldPos().x << " " << map->GetWorldPos().y << endl;
    cout << "map scale : "<< map->scale.x << " " << map->scale.y << endl;
    cout << "pl pos " << pl->getCol()->GetWorldPos().x << " " << pl->getCol()->GetWorldPos().y << endl;
    cout << "door pos " << doorsCol->GetWorldPos().x << " " << doorsCol->GetWorldPos().y << endl;
    cout << "mosterCount " << mosterCount << endl;

    bg->Update();
    map->Update();
    doorsCol->Update();
    door->Update();
    doorOpen->Update();
    pl->Update();
    addKeyItem->Update();
    for (int i = 0; i < 3; i++)
    {
        flies[i].SetTarget(pl->GetPos());
        flies[i].Update();
    }
    CAM->position = Vector2(map->GetWorldPos().x + 600.0f,
        map->GetWorldPos().y + 400.0f);
}

void SceneKeyFightRoomLeft::LateUpdate()
{
    if (addKeyItem->getKeyCol()->Intersect(pl->getCol()))
    {
        addKeyItem->getPlayerKey();
        pl->addKey();
    }

    //문 진입시
    if (doorsCol->Intersect(pl->getCol()))
    {
        Scene01* _scene01 = new Scene01();
        pl->getCol()->SetWorldPos(Vector2(-500.0f, 0.0f));
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

    //플레이어
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

    //눈물
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

    //몬스터와 플레이어 상호작용
    //눈물
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (flies[i].getCol()->Intersect(pl->tear[j].col))
            {
                pl->tear[j].playTearEffect();
                flies[i].hit();
            }
        }
    }


    //플레이어
    for (int i = 0; i < 3; i++)
    {
        if (flies[i].getCol()->Intersect(pl->getCol()))
        {
            pl->hit();
        }
    }


    //폭탄
    for (int i = 0; i < 99; i++)
    {

        if (pl->getCol()->Intersect(pl->playerBombs[i].getBombRange()))
        {
            pl->hit();
            pl->playerBombs[i].bombbRangeColOff();
        }
        else
        {
            pl->playerBombs[i].bombbRangeColOff();
        }

    }

}

void SceneKeyFightRoomLeft::Render()
{
    bg->Render();
    map->Render();
    doorsCol->Render();
    door->Render();
    doorOpen->Render();
    addKeyItem->Render();
    for (int i = 0; i < 3; i++)
    {
        flies[i].Render();
    }

    pl->Render();
}

void SceneKeyFightRoomLeft::ResizeScreen()
{
}
