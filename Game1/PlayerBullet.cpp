#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
	col = new ObRect();
	col->collider = COLLIDER::RECT;
	col->isFilled = false;

	bullet = new ObImage("");


	isfire = false;


}

PlayerBullet::~PlayerBullet()
{
}

bool PlayerBullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	return false;
}

void PlayerBullet::Update()
{
}

void PlayerBullet::Render()
{
}
