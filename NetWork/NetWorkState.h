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

using ListInt = std::list<std::pair<int,unsigned int>>;				// �l�b�g���[�N�n���h��,�L����

class NetWorkState
{
public:
	NetWorkState();
	virtual ~NetWorkState();
	virtual NetWorkMode GetMode(void) { return NetWorkMode::OFFLINE; };
	ActiveState GetActive_(void);
	int GetnetHandle(void);
	virtual ActiveState ConnectHost(IPDATA hostIP);
	virtual bool Update(void);
	bool SetActive(ActiveState active);		// ��ԕύX����
	bool CloseNetWork(void);
private:
	virtual bool CheckNetWork(void) { return false; };	
protected:
 	const int portNum_ = 8086;				// �|�[�g�i���o�[
	ActiveState active_;					// �A�N�e�B�u
	int netHandle_ = 0;						// �l�b�g�n���h���i�[
	ListInt playerlist_;
};
