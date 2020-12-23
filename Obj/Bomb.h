#pragma once
#include "Obj.h"
class Bomb :
    public Obj
{
public:
    Bomb(Vector2 pos, int color, std::chrono::system_clock::time_point time);              // 座標、色
    void Draw(int* TileImg) override;           // 引数はタイルセットの画像バンドルのアドレス
    ~Bomb();
private:
    int length_;
    int image_[14];
};

