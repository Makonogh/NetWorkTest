#pragma once
#include "Obj.h"
#include <vector>
#include <map>
#include <list>

#define CHAR_SIZE_X 32
#define CHAR_SIZE_Y 52

#define BASE_PLAYER_ID 5

enum class DIR              //�v���C���[�̌���
{
    DOWN,       //��
    LEFT,       //��
    RIGHT,      //�E
    UP,         //��
    DETH,       //��
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
    static int charID_;             // �L������ID�i�������ꂽ���ԁj
    int Image[20];                  // �L�����̃A�j���[�V�����摜�o���h��
    int AnimFrame;                  // �A�j���p�̃t���[��
    int Frame;
    DIR dir_;                       // ����
   
    std::vector < std::pair<int, int>> KeyLog;
    BaseScene& scene_;
};

