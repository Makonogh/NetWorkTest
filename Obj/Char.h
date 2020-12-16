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
//enum class DIR              //�v���C���[�̌���
//{
//    DOWN,       //��
//    LEFT,       //��
//    RIGHT,      //�E
//    UP,         //��
//    DETH,       //��
//    MAX
//};
//
//enum class CHAR_TYPE
//{
//    OPE,                    // ���������삷��L�����^�C�v
//    REV,                    // ��M�����f�[�^�œ������^�C�v
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
//    std::function<void(void)> updFunc_;				// �֐��|�C���^
//
//    static int charID_;             // �L������ID�i�������ꂽ���ԁj
//    int Image[20];                  // �L�����̃A�j���[�V�����摜�o���h��
//    int AnimFrame;                  // �A�j���p�̃t���[��
//    int Frame;                      // �L�������Z�̃t���[��
//    DIR dir_;                       // ����
//    CHAR_TYPE type_;                // �����̃L�����̃^�C�v
//    std::vector < std::pair<int, int>> KeyLog;
//    BaseScene& scene_;
//};
//
