#include "stdafx.h"

MonsterFlies::MonsterFlies()
{
	col = new ObRect();
	col->isFilled = false;
	col->scale = Vector2(34.0f, 14.0f);

	img = new ObImage(L"fly.png");
	img->SetParentRT(*col);
	img->scale = Vector2(34.0f, 14.0f);
	img->maxFrame.x = 2;
	img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	range[0] = new ObCircle();
	range[0]->isFilled = false;
	float scale = (float)MonsterFliesState::LOOK * 2.0f;
	range[0]->scale = Vector2(scale, scale);
	range[0]->SetParentRT(*col);

	range[1] = new ObCircle();
	range[1]->isFilled = false;
	scale = (float)MonsterFliesState::MOVE * 2.0f;
	range[1]->scale = Vector2(scale, scale);
	range[1]->SetParentRT(*col);

	range[2] = new ObCircle();
	range[2]->isFilled = false;
	scale = (float)MonsterFliesState::ATTACK * 2.0f;
	range[2]->scale = Vector2(scale, scale);
	range[2]->SetParentRT(*col);

	monsterState = MonsterFliesState::IDLE;
}

MonsterFlies::~MonsterFlies()
{
}

void MonsterFlies::Update()
{
	if (isDamaged) //update¿¡, isDamaged°¡ true¸é
	{
		hitDuration -= DELTA;

		img->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);

		if (hitDuration < 0.0f)
		{
			img->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			hp--;
			isDamaged = false;
		}

	}


	Vector2 dis = target - GetPos();
	distance = dis.Length();

	switch (monsterState)
	{
	case MonsterFliesState::IDLE:
		Idle();
		break;
	case  MonsterFliesState::LOOK:
		Look();
		break;
	case  MonsterFliesState::MOVE:
		Move();
		break;
	case MonsterFliesState::DEAD:
		Dead();
		break;
	}
	if (hp <= 0)
		monsterState = MonsterFliesState::DEAD;

	col->Update();
	img->Update();
	range[0]->Update();
	range[1]->Update();
	range[2]->Update();
}

void MonsterFlies::Render()
{
	col->Render();
	img->Render();
	range[0]->Render();
	range[1]->Render();
	range[2]->Render();
}

void MonsterFlies::Idle()
{
	//idle -> look
	if (distance < (float)MonsterFliesState::LOOK)
	{
		monsterState = MonsterFliesState::LOOK;
	}
}

void MonsterFlies::Look()
{
	//look -> idle
	if (distance > (float)MonsterFliesState::LOOK)
	{
		monsterState = MonsterFliesState::IDLE;
	}

	//look -> move
	if (distance < (float)MonsterFliesState::MOVE)
	{
		monsterState = MonsterFliesState::MOVE;
	}
}

void MonsterFlies::Move()
{
	moveDir = target - GetPos();
	moveDir.Normalize();

	col->MoveWorldPos(moveDir * 50.0f * DELTA);

	//move -> look
	if (distance > (float)MonsterFliesState::MOVE)
	{
		monsterState = MonsterFliesState::LOOK;
	}
}

void MonsterFlies::Dead()
{
	col->visible = false;
	col->collider = COLLIDER::NONE;
	img->visible = false;
	range[0]->visible = false;
	range[1]->visible = false;
	range[2]->visible = false;

	col->SetWorldPos(Vector2(9999.0f, 9999.0f));
	col->Update();
	img->Update();
	range[0]->Update();
	range[1]->Update();
	range[2]->Update();

	isDead = true;

	monsterState = MonsterFliesState::IDLE;
}

void MonsterFlies::hit()
{
	isDamaged = true;
	hitDuration = 0.3f;
}