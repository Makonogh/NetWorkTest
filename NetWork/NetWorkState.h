#pragma once

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
	bool SetActive(ActiveState active);
	bool CloseNetWork(void);
private:
	virtual bool CheckNetWork(void) { return false; };
protected:
 	const int portNum_ = 8086;
	ActiveState active_;
	int netHandle_ = 0;
};
