#pragma once
#include <array>
#include "Controller.h"
struct GamePad:
	public Controller
{
    ContType GetType(void) override;
    bool Setup(int no) override;
    bool Update(void) override;
    int GetID(void) override;
private:
    std::map<InputID, int> _inputTbl;
    int _padInput = 0;                      // パッドの入力情報
    int _connection = 0;                    // 接続数の保存変数 
    int _id = 0;                            // 接続パッドのID保存
};

