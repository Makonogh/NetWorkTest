#pragma once
#include "Obj.h"

enum class ITEM_TYPE        //アイテムの種類は四種類（FIREが8なのはタイルセットの8番目だから）
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
    Item(Vector2 pos, ITEM_TYPE item);              // 座標、色
    void Draw(int* TileImg) override;               // 引数はタイルセットの画像バンドルのアドレス
    ~Item();
private:
    ITEM_TYPE item_;                                // 色
};


