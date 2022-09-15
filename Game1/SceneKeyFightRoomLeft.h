#pragma once
class SceneKeyFightRoomLeft : public Scene
{
private:
	ObRect*			bg; //�������
	ObTileMap*		map;

	ObImage*		door; //�����ʿ� �־��
	ObImage*		doorOpen; //�����ʿ� �־��
	
	addKey*			addKeyItem;

	MonsterFlies			flies[3]; //����

	//��ã��� ����
	vector<Tile*>	PlWay;

	//�̵���ų ��ġ
	Vector2			PlDest;
	Vector2			PlSour;

	//����
	float			g;
	int				mosterCount = 4;
public:
	Player*			pl;
	ObRect*			doorsCol;

	int				countMonsterOnMap() { return mosterCount; }
	void			reduceMonsterCountOnMap() { mosterCount--; }

	Player*			getPlayer() { return pl; }
	void			setPlayer(Player* _player) { pl = _player; }
	ObTileMap*		getMap() { return map; }

public:
	SceneKeyFightRoomLeft();
	~SceneKeyFightRoomLeft();

	virtual void	Init() override;
	virtual void	Release() override; //����
	virtual void	Update() override;
	virtual void	LateUpdate() override;//����
	virtual void	Render() override;
	virtual void	ResizeScreen() override;

};

