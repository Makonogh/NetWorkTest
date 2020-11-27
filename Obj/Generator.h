#pragma once
#include "Obj.h"

#define EXP_LEN_DEF 3           // ���̒���
#define EXP_SPEED 10            // �����L�т�X�s�[�h
#define EXP_ANIM 7              // ���̃R�}��

enum class EXP_TYPE
{
    NON, 
    GZ,                 // �����̒��S�_�O���E���h�[��
    MID,                // �����̐^��
    END,                // �����̏I���_
};

class Generator :
    public Obj
{
public:
    Generator(Vector2 pos,BaseScene& scene);
    void Update() override;
    ~Generator();
private:
    int ExpLength_;             // �{���̔����̒���
    int NowLength_;             // ���L�тĂ钷��
    int frame_;                 // ��������Ă���J�E���g�J�n�̃t���[��
    BaseScene& scene_;
};
