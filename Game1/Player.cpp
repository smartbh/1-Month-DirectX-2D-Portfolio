#include "stdafx.h"

Player::Player()
{
	coinUI = new ObImage(L"coinUI.png");
	coinUI->scale = Vector2(33.0f, 22.0f) * 2.0f;
	coinUI->space = SPACE::SCREEN;
	coinUI->SetWorldPos(Vector2(-650.0f, 250.0f));

	keyUI = new ObImage(L"keyUI.png");
	keyUI->scale = Vector2(33.0f, 22.0f) * 2.0f;
	keyUI->space = SPACE::SCREEN;
	keyUI->SetWorldPos(Vector2(-650.0f, 200.0f));

	BombUI = new ObImage(L"bombUI.png");
	BombUI->scale = Vector2(33.0f, 22.0f) * 2.0f;
	BombUI->space = SPACE::SCREEN;
	BombUI->SetWorldPos(Vector2(-650.0f, 150.0f));

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
	head->SetLocalPosY(10.0f);
	head->SetParentRT(*col);

	//��
	//�� �������
	//��,�Ʒ� : 0 , ������ : 1, ���� : 2
	body = new ObImage(L"playerBody.png");
	body->scale = Vector2(36.0f, 29.0f);
	body->maxFrame = Int2(6, 3);
	body->SetParentRT(*col);
	body->SetLocalPosY(-15.0f);
	

	attackSpeed = 1.0f;
	moveSpeed = 200.0f;
	attackDuration = 0.5f;
	hitDuration = 0.5f;
	hp = 3.0f;
	key = 0;
	goldKey = 0;
	coin = 0;
	bomb = 0;

	SOUND->AddSound("player_hurts.wav", "HURT");
	
	isDamaged = false;

	plState = PlayerState::IDLE;
}

Player::~Player()
{
	SafeDelete(col);
	SafeDelete(head);
	SafeDelete(body);
}

void Player::addKey()
{
	key++;
}

void Player::addCoin()
{
	coin++;
}

void Player::addBomb()
{
	bomb++;
}

void Player::Update()
{
	//cout << playerBomb.size() << endl;
	cout << hp << endl;
	//cout <<  << endl;
	//TileScale
	ImGui::SliderFloat2("AttackSpeed", &attackSpeed, 0.01f, 100.0f);

	//TileSize
	ImGui::SliderFloat2("MoveSpeed", &moveSpeed, 0.01f, 1000.0f);


	if (isDamaged) //update��, isDamaged�� true��
	{
		hitDuration -= DELTA;

		head->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);
		body->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 0.5f);
		

		if (hitDuration < 0.0f)
		{
			SOUND->Stop("HURT");
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
		//if (abs((col->GetWorldPos() - tear[i].col->GetWorldPos()).x) > maxRange ||
		//	abs((col->GetWorldPos() - tear[i].col->GetWorldPos()).y) > maxRange)
		//	tear[i].playTearEffect();
	}

	for (int i = 0; i < 99; i++)
	{
		if (playerBombs->getIsbombset())
			playerBombs[i].Update();
		
	}

	coinUI->Update();
	keyUI->Update();
	BombUI->Update();
}

void Player::Render()
{
	coinUI->Render();
	keyUI->Render();
	BombUI->Render();

	wstring bombString = to_wstring(bomb);
	wstring keyString = to_wstring(key);
	wstring coinString = to_wstring(coin);
	//bomb
	//coin
	//key
	//                             -650.0f, 150.0f             L  T        R       B
	DWRITE->RenderText(coinString, RECT{ 80,137,(long)app.GetWidth(),(long)app.GetHalfHeight() },
		30.0f, L"�޸ո���ü", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

	//                             -650.0f, 150.0f             L  T        R       B
	DWRITE->RenderText(keyString, RECT{ 80,187,(long)app.GetWidth(),(long)app.GetHalfHeight() },
		30.0f, L"�޸ո���ü", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

	//                             -650.0f, 150.0f             L  T        R       B
	DWRITE->RenderText(bombString, RECT{ 80,237,(long)app.GetWidth(),(long)app.GetHalfHeight() },
		30.0f, L"�޸ո���ü", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

	col->Render();
	body->Render();
	head->Render();

	for (int i = 0; i < MAX; i++)
	{
		tear[i].Render();
	}

	//for (auto i : playerBomb)
	//{
	//	i.Render();
	//}

	for (int i = 0; i < 99; i++)
	{
		if(playerBombs->getIsbombset())
			playerBombs[i].Render();
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

	//if (hp <= 0)
	//{
	//	plState = PlayerState::DEAD;
	//}
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

	//if (hp <= 0)
	//{
	//	plState = PlayerState::DEAD;
	//}

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
			attackDuration = 0.5f;
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
			attackDuration = 0.5f;
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
			attackDuration = 0.5f;
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
			attackDuration = 0.5f;
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
		if (bomb > 0)
		{
			cout << "��ź ����" << endl;
			for (int i = 0; i < 99; i++)
			{
				if (!playerBombs[i].getIsbombset()) //���� false��
				{
					playerBombs[i].setBomb(col->GetWorldPos());
					bomb--;
					if (bomb < 0) bomb = 0;
					break;
				}
			}


			//for (auto i : playerBomb) 
			//{
			//	cout << i.getIsbombset() << endl;
			//	cout << "��ź �ݺ���" << endl;
			//	if (!i.getIsbombset()) //���� isBombSet�� false�� ��ź ��ġ
			//	{
			//		cout << "��ź ��ġ" << endl;
			//		i.setBomb(col->GetWorldPos());
			//		cout << i.getIsbombset() << endl;
			//		bomb--;
			//		if (bomb < 0) bomb = 0;
			//		break;
			//	}
			//}
		}
	}
	
	moveDir.Normalize();
}

void Player::hit()
{
	isDamaged = true;
	hitDuration = 0.5f;
	SOUND->Play("HURT");
}

ObRect* Player::getCol()
{
	return col;
}



