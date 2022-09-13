#include "stdafx.h"

scene02::scene02()
{
    map = new ObTileMap();
    map->file = "NormalMap1.txt";
    map->Load();
    map->CreateTileCost();
    //map->SetWorldPos(Vector2(0.0f, 0.0f));

    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;


    doorsCol[0] = new ObRect();
    doorsCol[0]->scale = Vector2(64.0f, 64.0f * 1.5f);
    doorsCol[0]->SetWorldPos(Vector2(map->GetWorldPos().x + 400.0f, map->GetWorldPos().y + 50.0f));
    doorsCol[0]->collider = COLLIDER::RECT;
    doorsCol[0]->isFilled = false;

    doors[0] = new ObImage(L"doorOpenDown.png");
    doors[0]->SetParentRT(*doorsCol[0]);
    doors[0]->scale = Vector2(64.0f, 64.0f) * 2.0f;

    doorsCol[0]->Update();
    doors[0]->Update();
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
    //문에 들어가면 다른 씬 나오게

    if (doorsCol[0]->Intersect(pl->getCol()))
    {

        Scene01* _scene01 = new Scene01();
        pl->getCol()->SetWorldPos(Vector2(_scene01->getMap()->GetWorldPos().x / 2.0f
            , _scene01->getMap()->GetWorldPos().y / 2.0f));
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
            if (map->GetTileState(on) == TILE_WALL)
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
                    EFFECT->EffectPlay(pl->tear[j].GetPos(), 0);
                    EFFECT->Update();
                    pl->tear[j].StepBack();
                    pl->tear[j].isfire = false;
                }
            }
        }
    }
}

void scene02::Render()
{
    bg->Render();
    map->Render();
    EFFECT->Render();
    doorsCol[0]->Render();
    doors[0]->Render();
    pl->Render();
}

void scene02::ResizeScreen()
{
}
