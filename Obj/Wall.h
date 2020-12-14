#pragma once
#include "Obj.h"

enum class COLOR        //壁の色二種類（BLUEが5なのはタイルセットの5番目だから）
{
    BLUE = 5,
    RED,
    BREAK
};

class Wall :
    public Obj
{
public:
    Wall(Vector2 pos,COLOR color);              // 座標、色
    void Draw(int* TileImg) override;           // 引数はタイルセットの画像バンドルのアドレス
    ~Wall();
private:
    COLOR color_;                               // 色
};

