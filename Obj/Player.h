#pragma once
#include "Obj.h"
#include <vector>
#include <map>
#include <list>
#include <functional>

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

enum class PLAY_TYPE
{
    OPE,                    // ���������삷��L�����^�C�v
    REV,                    // ��M�����f�[�^�œ������^�C�v
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
    std::function<void(void)> updFunc_;				// �֐��|�C���^

    static unsigned int charID_;             // �L������ID�i�������ꂽ���ԁj
    unsigned int myID_;
    int Image_[20];                  // �L�����̃A�j���[�V�����摜�o���h��
    int AnimFrame_;                  // �A�j���p�̃t���[��
    int Frame_;                      // �L�������Z�̃t���[��
    bool DethFlag_;                 // ����ł邩�t���O 
    DIR dir_;                       // ����
    PLAY_TYPE playType_;                // �����̃L�����̃^�C�v
    std::vector < std::pair<int, int>> KeyLog;
    BaseScene& scene_;
    int old;
    int now;
};

