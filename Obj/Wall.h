#pragma once
#include "Obj.h"

enum class COLOR        //�ǂ̐F���ށiBLUE��6�Ȃ̂̓^�C���Z�b�g��6�Ԗڂ�����j
{
    BLUE = 7,
    RED
};

class Wall :
    public Obj
{
public:
    Wall(Vector2 pos,COLOR color);              // ���W�A�F
    void Draw(int* TileImg) override;           // �����̓^�C���Z�b�g�̉摜�o���h���̃A�h���X
    ~Wall();
private:
    COLOR color_;                               // �F
};

