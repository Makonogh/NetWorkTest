#pragma once
#include <DxLib.h>
#include <list>

enum class NetWorkMode
{
	NON,			// ���ݒ�
	OFFLINE,		
	HOST,
	GUEST,
	MAX
};

enum class ActiveState
{
	Non,			// ���ݒ�
	Wait,			// �ڑ��ҋ@���(�z�X�g)
	Init,			// ��������(�Q�[���J�n�������A�����Ŏg��)
	Stanby,			// ��������񑗐M�ς݂̊J�n�܂�(�z�X�g�p)
	Play,			// �Q�[���v���C��
	OFFLINE
};

struct PlayerBundle
{
	int NWHandle;			// �l�b�g���[�N�̃n���h��
	unsigned int CharID;	// 1�`�v���C���[����
	bool Connect;			// �ڑ����ꂽ���ǂ���(GuestStanby��������true,���Ȃ�������false)
};

using ListInt = std::list<PlayerBundle>;				// �l�b�g���[�N�n���h��,�L����

class NetWorkState
{
public:
	NetWorkState();
	virtual ~NetWorkState();
	virtual NetWorkMode GetMode(void) { return NetWorkMode::OFFLINE; };
	ActiveState GetActive_(void);
	virtual ActiveState ConnectHost(IPDATA hostIP);
	virtual bool Update(void);
	bool SetActive(ActiveState active);		// ��ԕύX����
	bool CloseNetWork(void);
	ListInt GetPlayerList();
private:
	virtual bool CheckNetWork(void) { return false; };	
protected:
 	const int portNum_ = 8086;				// �|�[�g�i���o�[
	ActiveState active_;					// �A�N�e�B�u
	ListInt playerlist_;
};
