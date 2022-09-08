#pragma once
class scene02 : public Scene
{
private:
	Player* pl;
	Monster* mon;

	ObImage* spike; //������ũ ����
	ObRect* spikeCol;

	ObImage* rock; //����
	ObRect* rockCol;

	ObImage* doors[4]; //�����¿� ��
	ObRect* doorsCol[4];

	ObRect* bg; //�������

	ObTileMap* map;

	//��ã��� ����
	vector<Tile*> PlWay;

	//�̵���ų ��ġ
	Vector2		PlDest;
	Vector2		PlSour;

	//����
	float		g;

public:
	scene02();
	~scene02();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

