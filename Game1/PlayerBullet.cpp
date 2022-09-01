#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
	col = new ObRect();
	col->collider = COLLIDER::RECT;
	col->scale = Vector2(10.0f, 10.0f);
	col->isFilled = false;
	col->visible = true;

	bullet = new ObImage(L"tear.png");
	bullet->SetParentRT(*col);
	bullet->maxFrame = Int2(8, 4);
	bullet->scale = Vector2(32.0f, 32.0f);
	bullet->frame.x = 0;
	bullet->frame.y = 2;


	isfire = false;
}

PlayerBullet::~PlayerBullet()
{
	SafeDelete(col);
	SafeDelete(bullet);
}

bool PlayerBullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	if (!isfire)
	{
		isfire = true;

		col->SetWorldPos(firePos);
		this->fireDir = fireDir;
		this->scalar = scalar;

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
}

void PlayerBullet::Render()
{
	if (!isfire) return;

	col->Render();
	bullet->Render();
}

void PlayerBullet::ChangeLevel(int level)
{

}

void PlayerBullet::StepBack() //�� Ÿ�ϸʿ� ������
{
	col->SetWorldPos(lastPos);

	col->Update();
	bullet->Update();

}