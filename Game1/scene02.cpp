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

    doorsCol = new ObRect();
    doorsCol->scale = Vector2(64.0f, 64.0f * 1.5f);
    doorsCol->SetWorldPos(Vector2(map->GetWorldPos().x + 400.0f, map->GetWorldPos().y + 50.0f));
    doorsCol->collider = COLLIDER::RECT;
    doorsCol->isFilled = false;

    doors = new ObImage(L"doorOpenDown.png");
    doors->SetParentRT(*doorsCol);
    doors->scale = Vector2(64.0f, 64.0f) * 2.0f;

    doorsCol->Update();
    doors->Update();

    for (int i = 0; i < 4; i++)
    {
        rockCol[i] = new ObRect();
        rockCol[i]->scale = Vector2(32.0f, 32.0f) * 2.0f;
        rockCol[i]->isFilled = false;
        rockCol[i]->collider = COLLIDER::RECT;

        rockImg[i] = new ObImage(L"Rock.png");
        rockImg[i]->SetParentRT(*rockCol[i]);
        rockImg[i]->scale = Vector2(32.0f, 32.0f) * 2.0f;
    }

    rockCol[0]->SetWorldPos(Vector2(map->GetWorldPos().x + 200.0f, 0.0f));
    rockCol[1]->SetWorldPos(Vector2(map->GetWorldPos().x + 600.0f, 0.0f));
    rockCol[2]->SetWorldPos(Vector2(map->GetWorldPos().x + 200.0f, map->GetWorldPos().y + 200.0f));
    rockCol[3]->SetWorldPos(Vector2(map->GetWorldPos().x + 600.0f, map->GetWorldPos().y + 200.0f));
    
    for (int i = 0; i < 4; i++)
    {
        rockCol[i]->Update();
        rockImg[i]->Update();
    }

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
    CAM->position = Vector2( -300.0f, -100.0f);

    for (int i = 0; i < 4; i++)
    {
        rockCol[i]->Update();
        rockImg[i]->Update();
    }
}

void scene02::LateUpdate()
{
    for(int i = 0; i<4; i++)
    {
        if (rockCol[i]->Intersect(pl->getCol()))
            pl->StepBack();
    }

    //문에 들어가면 다른 씬 나오게

    if (doorsCol->Intersect(pl->getCol()))
    {
        Scene01* _scene01 = new Scene01();
        pl->getCol()->SetWorldPos(Vector2(-100.0f, 110.0f));
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
                    if (map->GetTileState(on) == TILE_WALL)
                    {
                        pl->tear[j].playTearEffect();
                    }
                }
            }

            if(pl->tear[j].col->Intersect(rockCol[i]))
            {
                pl->tear[j].playTearEffect();
 /*               pl->tear[j].col->visible = true;
                pl->tear[j].bullet->visible = false;
                pl->tear[j].bulletDead->visible = true;

                la = pl->tear[j].bullet->GetWorldPos();
                pl->tear[j].col->SetWorldPos(Vector2(999.0f, 999.0f));

                pl->tear[j].bulletDead->SetWorldPos(la);
                pl->tear[j].bulletDead->ChangeAnim(ANIMSTATE::ONCE, 0.05f);

                pl->tear[j].col->Update();
                pl->tear[j].bulletDead->Update();*/
            }
        }

    }



    
}

void scene02::Render()
{
    bg->Render();
    map->Render();
    EFFECT->Render();
    for (int i = 0; i < 4; i++)
    {
        rockCol[i]->Render();
        rockImg[i]->Render();
    }
    doorsCol->Render();
    doors->Render();
    pl->Render();
}

void scene02::ResizeScreen()
{
}
