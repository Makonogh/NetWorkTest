#pragma once
#include <array>
#include "Controller.h"

struct KeyInput :
    public Controller
{
   ContType GetType(void) override;
   bool Setup(int no) override;
   bool Update(void) override;
   int GetID(void) override;
private:
    std::array<char, 256> keyData_;
    std::map<InputID, int> inputTbl_;
};

