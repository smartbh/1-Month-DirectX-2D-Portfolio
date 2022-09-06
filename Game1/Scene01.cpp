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

    //��Ŭ��������
    if (INPUT->KeyDown(VK_RBUTTON))
    {
        //   �����, ������
        Int2 sour, dest;
        //ã�Ҵ°�?
        bool isFind;

        isFind = map->WorldPosToTileIdx(pl->GetPos(), sour);
        isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);

        //�Ѵ� Ÿ�ϸ� ����������
        if (isFind)
        {
            //���� �����Ѵٸ�
            if (map->PathFinding(sour, dest, PlWay))
            {
                //�� �����ŭ �ݺ�
                for (int i = 0; i < PlWay.size(); i++)
                {
                    cout << "Way" << i << ":" << PlWay[i]->idx.x <<
                        "," << PlWay[i]->idx.y << endl;
                }
                g = 0.0f;
                PlSour = pl->GetPos();
                PlWay.pop_back(); //����� ����
                PlDest = PlWay.back()->Pos;
            }

        }

    }

    //���ߵ� ���� ������ ��
    if (!PlWay.empty())
    {
        //PlSour = pl->GetPos();
        pl->SetPos(Utility::Lerp(PlSour, PlDest, g));
        g += DELTA * 3.0f;

        //�������� ��������
        if (g > 1.0f)
        {
            g = 0.0f;
            PlSour = PlDest;
            PlWay.pop_back(); //�ǵޱ� ����
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
    //�÷��̾ ���Ϳ� �ε�����
    /*
    {
        hit �ִϸ��̼�(��½��½) �ѹ� �ϰ�
        ü�� 1 ���̰�
    }
    
    */


    //������ ���Ϳ� �ε�����
    /*
    {
        ���͵� ����������
        hit �ִϸ��̼�(��½��½) �ѹ� �ϰ�
        ü�� 1 ���̰�
        �� ���� damage�� �°�
    }
    */



    //������ �÷��̾� ���Ͱ� ���� �ε�����
    Int2 on;

    if (map->WorldPosToTileIdx(pl->GetPos(), on))
    {
        ImGui::Text("TileState %d", map->GetTileState(on));
    }

    vector<Vector2>& Foot = pl->GetFoot();

    //�÷��̾�
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

    //����
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

    //����
}

void Scene01::Render()
{
    bg->Render();
    //                                          L  T        R       B
    //DWRITE->RenderText(L"�ȳ�\n�ȳ�", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
    //    30.0f, L"�޸ո���ü", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
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
