#pragma once
#include "BaseScene.h"
class ResultScene :
    public BaseScene
{
public:
    ResultScene();
    ~ResultScene();
    uniqueScene Update(uniqueScene own) override;					// Abvf[g
    void Draw() override;											// æ`æ(Obj©çÌp³)
private:

};

