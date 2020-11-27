#pragma once
#include "Obj.h"
#include <vector>
#include <map>
#include <list>

#define CHAR_SIZE_X 32
#define CHAR_SIZE_Y 52

#define BASE_PLAYER_ID 5

enum class DIR              //プレイヤーの向き
{
    DOWN,       //下
    LEFT,       //左
    RIGHT,      //右
    UP,         //上
    DETH,       //死
    MAX
};

class Char:
    public Obj
{
public:
    Char(Vector2 pos, BaseScene& scene);
    void Draw() override;
    void UpdateDef() override;
    void UpdateAuto() override;
    void UpdateNet() override;
    int GetID();
    ~Char();
private:
    static int charID_;             // キャラのID（生成された順番）
    int Image[20];                  // キャラのアニメーション画像バンドル
    int AnimFrame;                  // アニメ用のフレーム
    int Frame;
    DIR dir_;                       // 方向
   
    std::vector < std::pair<int, int>> KeyLog;
    BaseScene& scene_;
};

