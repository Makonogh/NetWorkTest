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
    int _padInput = 0;                      // �p�b�h�̓��͏��
    int _connection = 0;                    // �ڑ����̕ۑ��ϐ� 
    int _id = 0;                            // �ڑ��p�b�h��ID�ۑ�
};

