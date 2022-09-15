#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	//coin = new ObImage(L"coinUI.png");
	//coin->scale = Vector2(33.0f, 22.0f) * 2.0f;
	//coin->space = SPACE::SCREEN;
	//coin->SetWorldPos(Vector2(-650.0f, 250.0f));

	//key = new ObImage(L"keyUI.png");
	//key->scale = Vector2(33.0f, 22.0f) * 2.0f;
	//key->space = SPACE::SCREEN;
	//key->SetWorldPos(Vector2(-650.0f, 200.0f));

	//Bomb = new ObImage(L"bombUI.png");
	//Bomb->scale = Vector2(33.0f, 22.0f) * 2.0f;
	//Bomb->space = SPACE::SCREEN;
	//Bomb->SetWorldPos(Vector2(-650.0f, 150.0f));

	//익명 스코프
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
	//coin->Update();
	//key->Update();
	//Bomb->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
	//coin->Render();
	//key->Render();
	//Bomb->Render();
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