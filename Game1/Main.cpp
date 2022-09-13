#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	//ÀÍ¸í ½ºÄÚÇÁ
	{
		Scene01* temp = new Scene01();
		SCENE->AddScene("Scene01", temp);
	}

	SCENE->ChangeScene("Scene01");

}

void Main::Release()
{
	
}

void Main::Update()
{
	SCENE->Update();
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