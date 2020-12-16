//#pragma once
//#include "Obj.h"
//#include <vector>
//#include <map>
//#include <list>
//#include <functional>
//
//#define CHAR_SIZE_X 32
//#define CHAR_SIZE_Y 52
//
//#define BASE_PLAYER_ID 5
//
//enum class DIR              //プレイヤーの向き
//{
//    DOWN,       //下
//    LEFT,       //左
//    RIGHT,      //右
//    UP,         //上
//    DETH,       //死
//    MAX
//};
//
//enum class CHAR_TYPE
//{
//    OPE,                    // 自分が操作するキャラタイプ
//    REV,                    // 受信したデータで動かすタイプ
//};
//
//class Char:
//    public Obj
//{
//public:
//    Char(Vector2 pos, BaseScene& scene);
//    void Draw() override;
//    void Update();
//    void UpdateOpe() override;
//    void UpdateAuto() override;
//    void UpdateNet() override;
//    int GetID();
//    ~Char();
//private:
//    std::function<void(void)> updFunc_;				// 関数ポインタ
//
//    static int charID_;             // キャラのID（生成された順番）
//    int Image[20];                  // キャラのアニメーション画像バンドル
//    int AnimFrame;                  // アニメ用のフレーム
//    int Frame;                      // キャラ特融のフレーム
//    DIR dir_;                       // 方向
//    CHAR_TYPE type_;                // 自分のキャラのタイプ
//    std::vector < std::pair<int, int>> KeyLog;
//    BaseScene& scene_;
//};
//
