#pragma once
#include "Obj.h"
class Bomb :
    public Obj
{
public:
    Bomb(Vector2 pos, int color);              // ���W�A�F
    void Draw(int* TileImg) override;           // �����̓^�C���Z�b�g�̉摜�o���h���̃A�h���X
    ~Bomb();
private:
    int length;
};

