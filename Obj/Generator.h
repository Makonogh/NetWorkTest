#pragma once
#include "Obj.h"

#define EXP_LEN_DEF 3           // 炎の長さ
#define EXP_SPEED 10            // 炎が伸びるスピード
#define EXP_ANIM 7              // 炎のコマ数

enum class EXP_TYPE
{
    NON, 
    GZ,                 // 爆発の中心点グラウンドゼロ
    MID,                // 爆発の真ん中
    END,                // 爆発の終着点
};

class Generator :
    public Obj
{
public:
    Generator(Vector2 pos,BaseScene& scene);
    void Update() override;
    ~Generator();
private:
    int ExpLength_;             // ボムの爆発の長さ
    int NowLength_;             // 今伸びてる長さ
    int frame_;                 // 生成されてからカウント開始のフレーム
    BaseScene& scene_;
};
