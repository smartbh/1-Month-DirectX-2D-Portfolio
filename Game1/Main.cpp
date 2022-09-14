#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	//Item = new ObImage();
	//ItemBar = new ObImage();
	//coin = new ObImage();
	//key = new ObImage();
	coin = new ObImage(L"coinUI.png");
	coin->scale = Vector2(33.0f, 22.0f) * 2.0f;
	coin->space = SPACE::SCREEN;
	coin->SetWorldPos(Vector2(-600.0f, 100.0f));

	key = new ObImage(L"keyUI.png");
	key->scale = Vector2(33.0f, 22.0f) * 2.0f;
	key->space = SPACE::SCREEN;
	key->SetWorldPos(Vector2(-600.0f, 50.0f));

	Bomb = new ObImage(L"bombUI.png");
	Bomb->scale = Vector2(33.0f, 22.0f) * 2.0f;
	Bomb->space = SPACE::SCREEN;
	Bomb->SetWorldPos(Vector2(-600.0f, 0.0f));

	//ÀÍ¸í ½ºÄÚÇÁ
	{
		Scene01* temp = new Scene01();
		SCENE->AddScene("Scene01", temp);
	}
	SOUND->AddSound("background2.wav", "BGM");


	SCENE->ChangeScene("Scene01");

}

void Main::Release()
{
	
}

void Main::Update()
{
	SOUND->Play("BGM");
	SCENE->Update();
	coin->Update();
	key->Update();
	Bomb->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	//                                          L  T        R       B
	DWRITE->RenderText(L"¾È³ç\n¾È³ç", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
		30.0f, L"ÈÞ¸Õ¸ÅÁ÷Ã¼", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
	SCENE->Render();
	coin->Render();
	key->Render();
	Bomb->Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400,800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}