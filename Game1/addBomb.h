#pragma once
class addBomb
{
private:
    int         bombNum = 1;
    ObImage*    addBombImage; //ÆøÅº ¼ö·® ´Ã¸®±â
    ObImage*    addBombImageDouble; //ÆøÅº ¼ö·® ´Ã¸®±â2
    
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

