#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
	col = new ObRect();
	col->collider = COLLIDER::RECT;
	col->scale = Vector2(32.0f, 32.0f);
	col->isFilled = false;
	col->visible = true;
	col->SetWorldPos(Vector2(1000.0f, 1000.0f));
	col->visible = false;

	bullet = new ObImage(L"tear.png");
	bullet->SetParentRT(*col);
	bullet->maxFrame = Int2(8, 4);
	bullet->scale = Vector2(32.0f, 32.0f) * 2.0f;
	bullet->frame.x = 0;
	bullet->frame.y = 2;

	bulletDead = new ObImage(L"tear_explode.png");
	//bulletDead->SetParentRT(*col);
	bulletDead->scale = Vector2(64.0f, 64.0f);
	bulletDead->maxFrame.x = 16;
	bulletDead->visible = false;

	isfire = false;
	isBlock = false;

	SOUND->AddSound("tear_fire.wav", "PLATTACK");//공격소리
	SOUND->AddSound("tear_destroy.wav", "TEARPOP");//눈물 터지는 소리

	damage = 1.0f;
}

PlayerBullet::~PlayerBullet()
{
	SafeDelete(col);
	SafeDelete(bullet);
}

bool PlayerBullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	SOUND->Stop("PLATTACK");
	if (!isfire)
	{
		col->visible = false;
		bullet->visible = true;
		bulletDead->visible = false;
		isfire = true;
		isBlock = false;
		col->SetWorldPos(firePos);
		this->fireDir = fireDir;
		this->scalar = scalar;
		SOUND->Play("PLATTACK");
		return true;
	}

	return false;
}

void PlayerBullet::Update()
{
	lastPos = col->GetWorldPos();
	
	if (!isfire) return;

	Vector2 velocity = fireDir * scalar;
	col->MoveWorldPos(velocity * DELTA);
	col->rotation = Utility::DirToRadian(velocity) - DIV2PI;

	col->Update();
	bullet->Update();
	bulletDead->Update();
}

void PlayerBullet::LateUpdate()
{

}


void PlayerBullet::Render()
{
	if (!isfire) return;

	col->Render();
	bullet->Render();
	bulletDead->Render();
	
}

void PlayerBullet::ChangeLevel(int level)
{
	
}

void PlayerBullet::StepBack() //벽 타일맵에 막힐시
{
	//위치, 싱글톤 이펙트매니저

	col->SetWorldPos(lastPos); //벽 위치에서

	col->Update();
	bullet->Update();
	bulletDead->SetWorldPos(lastPos);
	bulletDead->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
	bulletDead->visible = true;
	bulletDead->Render();
	isfire = false;
	isBlock = true;
	
}

void PlayerBullet::playTearEffect()
{
	Vector2 _lastPost;
	col->visible = false;
	bullet->visible = false;
	bulletDead->visible = true;

	_lastPost = bullet->GetWorldPos();
	col->SetWorldPos(Vector2(-666.0f, 666.0f));

	bulletDead->SetWorldPos(_lastPost);
	bulletDead->ChangeAnim(ANIMSTATE::ONCE, 0.05f);

	col->Update();
	bulletDead->Update();
	SOUND->Play("TEARPOP");

	//isfire = false;
}


