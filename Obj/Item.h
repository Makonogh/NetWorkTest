#pragma once
#include "Obj.h"

enum class ITEM_TYPE        //�A�C�e���̎�ނ͎l��ށiFIRE��8�Ȃ̂̓^�C���Z�b�g��8�Ԗڂ�����j
{
    FIRE_UP = 8,
    BOMB_UP,
    REMOTE,
    SPEED_UP,
};

class Item :
    public Obj
{
public:
    Item(Vector2 pos, ITEM_TYPE item);              // ���W�A�F
    void Draw(int* TileImg) override;               // �����̓^�C���Z�b�g�̉摜�o���h���̃A�h���X
    ~Item();
private:
    ITEM_TYPE item_;                                // �F
};


