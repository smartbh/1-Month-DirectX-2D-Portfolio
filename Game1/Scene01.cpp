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

    m.lock();
    m.unlock();

    /// <summary>
    /// 문 제작
    /// </summary>
    {
        m.lock();//전후좌우순으로 생성
        //전
        doorsCol[0] = new ObRect();
        doorsCol[0]->scale = Vector2(64.0f, 64.0f) * 2.0f;
        doorsCol[0]->SetWorldPos(Vector2(-100.0f, 250.0f));
        doorsCol[0]->collider = COLLIDER::RECT;
        doorsCol[0]->isFilled = false;

        doors[0] = new ObImage(L"doorOpenUp.png");
        doors[0]->SetParentRT(*doorsCol[0]);
        doors[0]->scale = Vector2(64.0f, 64.0f) * 2.0f;

        doorsCol[0]->Update();
        doors[0]->Update();

        //후
        doorsCol[1] = new ObRect();
        doorsCol[1]->scale = Vector2(64.0f, 64.0f) * 2.0f;
        doorsCol[1]->SetWorldPos(Vector2(-100.0f, -300.0f));
        doorsCol[1]->collider = COLLIDER::RECT;
        doorsCol[1]->isFilled = false;

        doors[1] = new ObImage(L"doorOpenDown.png");
        doors[1]->SetParentRT(*doorsCol[1]);
        doors[1]->scale = Vector2(64.0f, 64.0f) * 2.0f;

        doorsCol[1]->Update();
        doors[1]->Update();

        //좌
        doorsCol[2] = new ObRect();
        doorsCol[2]->scale = Vector2(64.0f, 64.0f) * 2.0f;
        doorsCol[2]->SetWorldPos(Vector2(-600.0f, 0.0f));
        doorsCol[2]->collider = COLLIDER::RECT;
        doorsCol[2]->isFilled = false;

        doors[2] = new ObImage(L"doorOpenLeft.png");
        doors[2]->SetParentRT(*doorsCol[2]);
        doors[2]->scale = Vector2(64.0f, 64.0f) * 2.0f;

        doorsCol[2]->Update();
        doors[2]->Update();

        //우
        doorsCol[3] = new ObRect();
        doorsCol[3]->scale = Vector2(64.0f, 64.0f) * 2.0f;
        doorsCol[3]->SetWorldPos(Vector2(400.0f, 0.0f));
        doorsCol[3]->collider = COLLIDER::RECT;
        doorsCol[3]->isFilled = false;

        doors[3] = new ObImage(L"doorOpenRight.png");
        doors[3]->SetParentRT(*doorsCol[3]);
        doors[3]->scale = Vector2(64.0f, 64.0f) * 2.0f;

        doorsCol[3]->Update();
        doors[3]->Update();
        m.unlock();
    }

    /// <summary>
    /// 함정 연습
    /// </summary>
    {
        m.lock();
        spikeCol = new ObRect();
        spikeCol->scale = Vector2(64.0f, 64.0f);
        spikeCol->isFilled = false;
        spikeCol->collider = COLLIDER::RECT;
        spikeCol->SetWorldPos(Vector2(0.0f, 0.0f));
        m.unlock();

        m.lock();
        spike = new ObImage(L"spike.png");
        spike->scale = Vector2(64.0f, 64.0f);
        spike->SetParentRT(*spikeCol);
        m.unlock();
    }

    /// <summary>
    /// 튜토리얼 이미지들
    /// </summary>
    {
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
    }

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
    //mon = new Monster();
    m.unlock();

    m.lock();
    m.unlock();


}

Scene01::~Scene01()
{
    SafeDelete(pl);
    //SafeDelete(mon);
    SafeDelete(map);
}

Player* Scene01::getPlayer()
{
    return pl;
}

void Scene01::setPlayer(Player* _player)
{
    pl = _player;
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
    //mon->SetTarget(pl->GetPos());
    //mon->Update();
    map->Update();
    spike->Update();
    spikeCol->Update();
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
    
    //문에 들어가면 다른 씬 나오게
    for (int i = 0; i < 4; i++)
    {
        if (doorsCol[i]->Intersect(pl->getCol()))
        {
            switch (i)
            {
            case 0:
                //위
                scene02 * _scene02 = new scene02();
                _scene02->pl = pl;
                SCENE->AddScene("Scene02", _scene02);
                SCENE->ChangeScene("Scene02");
                break;
            //case 1:
            //    //아래
            //    break;
            //case 2:
            //    //왼
            //    break;
            //case 3:
            //    //오
            //    break;
            }
        }
    }

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
        }
    }

    if (spikeCol->Intersect(pl->getCol()))
    {
        pl->hit();
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
                    EFFECT->EffectPlay(pl->tear[j].GetPos(), 1);
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

    spike->Render();
    spikeCol->Render();

    doorsCol[0]->Render();
    doors[0]->Render();
    doorsCol[1]->Render();
    doors[1]->Render();
    doorsCol[2]->Render();
    doors[2]->Render();
    doorsCol[3]->Render();
    doors[3]->Render();

    EFFECT->Render();
    tutorial1->Render();
    tutorial2->Render();
    tutorial3->Render();
    tutorial4->Render();
    pl->Render();
    //mon->Render();
}

void Scene01::ResizeScreen()
{
}
