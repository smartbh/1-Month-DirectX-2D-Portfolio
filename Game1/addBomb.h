#pragma once
class addBomb
{
private:
    int         bombNum;
    ObImage*    addBombImage; //��ź ���� �ø���
    ObImage*    addBombImageDouble; //��ź ���� �ø���2
    
public:
    ObRect*     addBombCol;
    ObRect*     addBombColDouble;

    void        getPlayerBomb();
public:
    addBomb();
    addBomb(int _num);
    ~addBomb();


    void		Update();
    void		Render();
};

