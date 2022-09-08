#include "stdafx.h"

Player::Player()
{
	col = new ObRect();
	col->SetWorldPos(Vector2(-500.0f, -200.0f));
	col->scale = Vector2(48.0f, 60.0f);
	col->isFilled = false;
	//col->pivot = OFFSET_B;

	//�Ӹ�
	//�Ӹ��� �������
	//�Ʒ� : 0, ������ : 1, �� : 2, �� : 3
	head = new ObImage(L"playerHeads.png");
	head->scale = Vector2(32.0f, 29.0f) * 2.0f;
	head->maxFrame = Int2(2, 4);
	head->SetLocalPosY(40.0f);
	head->SetParentRT(*col);

	//��
	//�� �������
	//��,�Ʒ� : 0 , ������ : 1, ���� : 2
	body = new ObImage(L"playerBody.png");
	body->scale = Vector2(36.0f, 29.0f);
	body->maxFrame = Int2(6, 3);
	body->SetParentRT(*col);
	body->SetLocalPosY(15.0f);
	
	attackSpeed = 1.0f;
	moveSpeed = 200.0f;

	attackDuration = 0.1f;
	hitDuration = 0.5f;

	hp = 3.0f;

	isDamaged = false;

	plState = PlayerState::IDLE;
}

Player::~Player()
{
	SafeDelete(col);

}

void Player::Update()
{
	cout << "hp : " << hp << endl;
	//TileScale
	ImGui::SliderFloat2("TearSpeed", &attackSpeed, 1.0f, 10.0f);

	//TileSize
	ImGui::SliderFloat2("MoveSpeed", &moveSpeed, 1.0f, 10.0f);


	if (isDamaged) //update��, isDamaged�� true��
	{
		hitDuration -= DELTA;

		head->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);
		body->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);


		if (hitDuration < 0.0f)
		{
			head->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			body->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			hp--;
			isDamaged = false;
		}

	}



	lastPos = col->GetWorldPos();

	switch (plState)
	{
	case PlayerState::IDLE:
		Idle();
		break;
	case PlayerState::WALK:
		Walk();
		break;
	case PlayerState::DEAD:
		break;
	}

	col->Update();
	body->Update();
	head->Update();

	for (int i = 0; i < MAX; i++)
	{
		tear[i].Update();
	}

}

void Player::Render()
{
	col->Render();
	body->Render();
	head->Render();

	for (int i = 0; i < MAX; i++)
	{
		tear[i].Render();
	}

}

void Player::StepBack() //�� Ÿ�ϸʿ� ������
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
}

void Player::Walk()
{
	Input();

	col->MoveWorldPos(moveDir * moveSpeed * DELTA);

	//Walk -> Idle
	if (moveDir == Vector2(0.0f, 0.0f)) //�������� ������ ����x
	{
		plState = PlayerState::IDLE;
		body->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		head->frame.x = 0;
		body->frame.x = 0;
	}

}

void Player::Input()
{
	moveDir = Vector2(0.0f, 0.0f);

	//������

	//�Ʒ�
	if (INPUT->KeyPress('S'))
	{
		moveDir.y = -1.0f;
		head->frame.y = 0;
		body->frame.y = 0;
	}
	//��
	else if (INPUT->KeyPress('W'))
	{
		moveDir.y = 1.0f;
		head->frame.y = 2;
		body->frame.y = 0;
	}
	//��
	if (INPUT->KeyPress('A'))
	{
		moveDir.x = -1.0f;
		head->frame.y = 3;
		body->frame.y = 2;
	}
	//��
	else if (INPUT->KeyPress('D'))
	{
		moveDir.x = 1.0f;
		head->frame.y = 1;
		body->frame.y = 1;
	}


	//����Ű
	if (INPUT->KeyPress(VK_DOWN))
	{
		head->frame.y = 0;
		head->ChangeAnim(ANIMSTATE::LOOP, attackDuration);

		attackDuration -= DELTA;
		if (attackDuration > 0.0f)
		{

		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{
				if (!tear[i].isfire)
				{
					tear[i].Shoot(DOWN, attackSpeed * 100.0f + moveSpeed, col->GetWorldPos());

					break;
				}
			}
			attackDuration = 1.0f;
		}
	}

	else if (INPUT->KeyPress(VK_UP))
	{
		head->frame.y = 2;
		head->ChangeAnim(ANIMSTATE::LOOP, attackSpeed - 0.8f);

		attackDuration -= DELTA;
		if (attackDuration > 0.0f)
		{

		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{
				if (!tear[i].isfire)
				{
					tear[i].Shoot(UP, attackSpeed * 100.0f + moveSpeed, col->GetWorldPos());

					break;
				}
			}
			attackDuration = 1.0f;
		}
	}
	else if (INPUT->KeyPress(VK_LEFT))
	{
		head->frame.y = 3;
		head->ChangeAnim(ANIMSTATE::LOOP, attackSpeed - 0.8f);

		attackDuration -= DELTA;
		if (attackDuration > 0.0f)
		{

		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{
				if (!tear[i].isfire)
				{
					tear[i].Shoot(LEFT, attackSpeed * 100.0f + moveSpeed, col->GetWorldPos());

					break;
				}
			}
			attackDuration = 1.0f;
		}
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{
		head->frame.y = 1;
		head->ChangeAnim(ANIMSTATE::LOOP, attackSpeed - 0.8f);

		attackDuration -= DELTA;
		if (attackDuration > 0.0f)
		{

		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{
				if (!tear[i].isfire)
				{
					tear[i].Shoot(RIGHT, attackSpeed * 100.0f + moveSpeed, col->GetWorldPos());

					break;
				}
			}
			attackDuration = 1.0f;
		}
	}


	//���� ���ҽ� �Ӹ� ����� ������
	if (INPUT->KeyUp(VK_UP) ||
		INPUT->KeyUp(VK_DOWN) ||
		INPUT->KeyUp(VK_RIGHT) ||
		INPUT->KeyUp(VK_LEFT))
	{
		head->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		head->frame.x = 0;
	}


	//������ ��� (�����̽���)
	if (INPUT->KeyDown(VK_SPACE))
	{

	}

	//��ź��� (EŰ)
	if (INPUT->KeyDown('E'))
	{

	}
	
	moveDir.Normalize();
}

void Player::hit()
{
	isDamaged = true;
	hitDuration = 1.0f;

	//if (hitDuration > 0.0f)
	//{

	//}
	//else
	//{
	//	for (int i = 0; i < MAX; i++)
	//	{
	// 
	//	}
	//	attackDuration = 1.0f;
	//}
}

ObRect* Player::getCol()
{
	return col;
}



