#include "stdafx.h"

Player::Player()
{
	col = new ObRect();
	col->SetWorldPos(Vector2(-500.0f, -200.0f));
	col->scale = Vector2(96.0f, 96.0f);
	col->isFilled = false;

	//머리
	//머리의 방향순서
	//아래 : 0, 오른쪽 : 1, 위 : 2, 왼 : 3
	head = new ObImage(L"playerHeads.png");
	head->scale = Vector2(32.0f, 29.0f) * 2.0f;
	head->maxFrame = Int2(2, 4);
	head->SetParentRT(*col);
	//head->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	//몸
	//몸 방향순서
	//위,아래 : 0 , 오른쪽 : 1, 왼쪽 : 2
	body = new ObImage(L"playerBody.png");
	body->scale = Vector2(36.0f, 29.0f);
	body->maxFrame = Int2(6, 3);
	body->SetParentRT(*col);
	body->SetLocalPosY(-25.0f);
	




	//frameY[Dir_R] = 0;
	//frameY[Dir_T] = 1;
	//frameY[Dir_L] = 2;
	//frameY[Dir_B] = 3;
	//frameY[Dir_RB] = 4;
	//frameY[Dir_LB] = 5;
	//frameY[Dir_LT] = 6;
	//frameY[Dir_RT] = 7;

	plState = PlayerState::IDLE;
}

Player::~Player()
{
	SafeDelete(col);

}

void Player::Update()
{
	lastPos = col->GetWorldPos();

	switch (plState)
	{
	case PlayerState::IDLE:
		Idle();
		break;
	case PlayerState::WALK:
		Walk();
		break;
	case PlayerState::ATTACK:
		Attack();
		break;
	case PlayerState::ITEMUSE:
		ItemUse();
		break;
	}

	col->Update();
	body->Update();
	head->Update();

}

void Player::Render()
{
	col->Render();
	body->Render();
	head->Render();

}

void Player::StepBack() //벽 타일맵에 막힐시
{
	col->SetWorldPos(lastPos);

	col->Update();
	body->Update();
	head->Update();

}

void Player::Idle()
{	
	Input();
	
	//Idle->Walk
	if (moveDir != Vector2(0.0f, 0.0f))
	{
		plState = PlayerState::WALK;
		body->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	}
	//Idle->Attack
	if (INPUT->KeyPress(VK_UP) ||
		INPUT->KeyPress(VK_DOWN) ||
		INPUT->KeyPress(VK_RIGHT) ||
		INPUT->KeyPress(VK_LEFT) )
	{
		plState = PlayerState::ATTACK;
	}
}

void Player::Walk()
{
	Input();

	col->MoveWorldPos(moveDir * 200.0f * DELTA);

	//Walk -> Idle
	if (moveDir == Vector2(0.0f, 0.0f)) //움직이지 않으니 방향x
	{
		plState = PlayerState::IDLE;
		body->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		head->frame.x = 0;
		body->frame.x = 0;
	}

	//Walk -> Attack
	if (INPUT->KeyPress(VK_SPACE))
	{

	}
}

void Player::Attack()
{
	Input();

	if (INPUT->KeyUp())
	{

	}
}

void Player::ItemUse()
{
	Input();
}


void Player::Input()
{
	moveDir = Vector2(0.0f, 0.0f);

	//움직임

	//아래
	if (INPUT->KeyPress('S'))
	{
		moveDir.y = -1.0f;
		//head->frame.y = 0;
		body->frame.y = 0;
	}
	//위
	else if (INPUT->KeyPress('W'))
	{
		moveDir.y = 1.0f;
		//head->frame.y = 2;
		body->frame.y = 0;
	}
	//좌
	if (INPUT->KeyPress('A'))
	{
		moveDir.x = -1.0f;
		//head->frame.y = 3;
		body->frame.y = 2;
	}
	//우
	else if (INPUT->KeyPress('D'))
	{
		moveDir.x = 1.0f;
		//head->frame.y = 1;
		body->frame.y = 1;
	}


	//공격키
	if (INPUT->KeyPress(VK_DOWN))
	{
		head->frame.y = 0;
		head->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}
	else if (INPUT->KeyPress(VK_UP))
	{
		head->frame.y = 2;
		head->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}
	else if (INPUT->KeyPress(VK_LEFT))
	{
		head->frame.y = 3;
		head->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{
		head->frame.y = 1;
		head->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}


	//아이템 사용
	if (INPUT->KeyDown(VK_SPACE))
	{

	}
	
	moveDir.Normalize();
}


