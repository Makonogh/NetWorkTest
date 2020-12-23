#pragma once
#include "Obj.h"
#include <vector>
#include <map>
#include <list>
#include <functional>

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

enum class PLAY_TYPE
{
    OPE,                    // 自分が操作するキャラタイプ
    REV,                    // 受信したデータで動かすタイプ
};

class Player :
    public Obj
{
public:
    Player(Vector2 pos, BaseScene& scene);
    void Draw() override;
    void Update();
    void UpdateOpe() override;
    void UpdateAuto() override;
    void UpdateRev() override;
    bool GetFlag() override;
    int GetID();
    ~Player();
private:
    std::function<void(void)> updFunc_;				// 関数ポインタ

    static unsigned int charID_;             // キャラのID（生成された順番）
    unsigned int myID_;
    int Image_[20];                  // キャラのアニメーション画像バンドル
    int AnimFrame_;                  // アニメ用のフレーム
    int Frame_;                      // キャラ特融のフレーム
    bool DethFlag_;                 // 死んでるかフラグ 
    DIR dir_;                       // 方向
    PLAY_TYPE playType_;                // 自分のキャラのタイプ
    std::vector < std::pair<int, int>> KeyLog;
    BaseScene& scene_;
    int old;
    int now;
};

