#pragma once

enum state { sleep, active, passive, leader, lost };
enum massagetype { one, two };


class Process {
public:
	bool isstartprocess;	//�n���v���Z�X���ۂ�
	int id;					//�v���Z�Xid(���C���ŏ�����)

	state state;			//���[�_���ۂ��̏��
	int cp;					//�i�͕킵�Ă���j�v���Z�X���ʎq
	int win;				//���[�_id

	int one;				//one���b�Z�[�W�p�o�b�t�@
	int two;				//two���b�Z�[�W�p�o�b�t�@

	Process *link;			//�����N

public:
	Process();
	~Process();
	void RenewCp();
	void send(massagetype , int );
};

