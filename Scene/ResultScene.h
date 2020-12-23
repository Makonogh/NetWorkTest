#pragma once
#include "BaseScene.h"
class ResultScene :
    public BaseScene
{
public:
    ResultScene();
    ~ResultScene();
    uniqueScene Update(uniqueScene own) override;					// アップデート
    void Draw() override;											// 画像描画(Objからの継承)
private:

};

