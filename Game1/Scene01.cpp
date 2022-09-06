#include "stdafx.h"

Scene01::Scene01()
{
    m.lock();
    bg = new ObRect();
    bg->scale = Vector2(10000.0f, 10000.0f);
    bg->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    bg->isFilled = true;
    m.unlock();

    m.lock();
    tutorial1 = new ObImage(L"tutorial1.png");
    tutorial1->scale = Vector2(50.0f, 67.0f) * 2.0f;
    tutorial1->SetWorldPosX(-400.0f);
    tutorial1->maxFrame.x = 2;
    tutorial1->ChangeAnim(ANIMSTATE::LOOP, 0.5f);
    tutorial1->visible = true;
    tutorial1->Update();
    m.unlock();

    m.lock();
    tutorial2 = new ObImage(L"tutorial2.png");
    tutorial2->scale = Vector2(62.0f, 67.0f) * 2.0f;
    tutorial2->SetWorldPosX(-200.0f);
    tutorial2->maxFrame.x = 2;
    tutorial2->ChangeAnim(ANIMSTATE::LOOP, 0.5f);
    tutorial2->visible = true;
    tutorial2->Update();
    m.unlock();

    m.lock();
    tutorial3 = new ObImage(L"tutorial3.png");
    tutorial3->scale = Vector2(46.0f, 67.0f) * 2.0f;
    tutorial3->SetWorldPosX(0.0f);
    tutorial3->maxFrame.x = 2;
    tutorial3->ChangeAnim(ANIMSTATE::LOOP, 0.5f);
    tutorial3->visible = true;
    tutorial3->Update();
    m.unlock();

    m.lock();
    tutorial4 = new ObImage(L"tutorial4.png");
    tutorial4->scale = Vector2(43.0f, 79.0f) * 2.0f;
    tutorial4->SetWorldPosX(200.0f);
    tutorial4->maxFrame.x = 2;
    tutorial4->ChangeAnim(ANIMSTATE::LOOP, 0.5f);
    tutorial4->visible = true;
    tutorial4->Update();
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    LIGHT->light.radius = 2000.0f;
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    pl = new Player();
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    mon = new Monster();
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    map = new ObTileMap();
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    map->file = "startMap.txt";
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    map->Load();
    m.unlock();

    m.lock();
    //Sleep(1000);
    loadingCount++;
    map->CreateTileCost();
    m.unlock();


}

Scene01::~Scene01()
{
    SafeDelete(pl);
    SafeDelete(mon);
    SafeDelete(map);
}

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
    ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    //우클릭햇을때
    if (INPUT->KeyDown(VK_RBUTTON))
    {
        //   출발점, 도착점
        Int2 sour, dest;
        //찾았는가?
        bool isFind;

        isFind = map->WorldPosToTileIdx(pl->GetPos(), sour);
        isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);

        //둘다 타일맵 위에있을때
        if (isFind)
        {
            //길이 존재한다면
            if (map->PathFinding(sour, dest, PlWay))
            {
                //길 사이즈만큼 반복
                for (int i = 0; i < PlWay.size(); i++)
                {
                    cout << "Way" << i << ":" << PlWay[i]->idx.x <<
                        "," << PlWay[i]->idx.y << endl;
                }
                g = 0.0f;
                PlSour = pl->GetPos();
                PlWay.pop_back(); //출발지 빼기
                PlDest = PlWay.back()->Pos;
            }

        }

    }

    //가야될 길이 존재할 때
    if (!PlWay.empty())
    {
        //PlSour = pl->GetPos();
        pl->SetPos(Utility::Lerp(PlSour, PlDest, g));
        g += DELTA * 3.0f;

        //도착지를 지났을때
        if (g > 1.0f)
        {
            g = 0.0f;
            PlSour = PlDest;
            PlWay.pop_back(); //맨뒷길 빼기
            if (!PlWay.empty())
                PlDest = PlWay.back()->Pos;
        }
    }
    bg->Update();
    pl->Update();
    mon->SetTarget(pl->GetPos());
    mon->Update();
    map->Update();
    CAM->position = pl->GetPos();
}

void Scene01::LateUpdate()
{
    //플레이어가 몬스터와 부딪힐시
    /*
    {
        hit 애니메이션(번쩍번쩍) 한번 하고
        체력 1 까이게
    }
    
    */


    //눈물이 몬스터에 부딪힐시
    /*
    {
        몬스터도 마찬가지로
        hit 애니메이션(번쩍번쩍) 한번 하고
        체력 1 까이게
        단 눈물 damage에 맞게
    }
    */



    //눈물과 플레이어 몬스터가 벽에 부딪힐시
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
            else if (map->GetTileState(on) == TILE_TRAP) //3
            {
                pl->hit();
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

    //몬스터
}

void Scene01::Render()
{
    bg->Render();
    //                                          L  T        R       B
    //DWRITE->RenderText(L"안녕\n안녕", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
    //    30.0f, L"휴먼매직체", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
    map->Render();
    EFFECT->Render();
    tutorial1->Render();
    tutorial2->Render();
    tutorial3->Render();
    tutorial4->Render();
    pl->Render();
    mon->Render();
}

void Scene01::ResizeScreen()
{
}
