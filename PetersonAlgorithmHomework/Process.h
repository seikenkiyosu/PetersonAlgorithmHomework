#pragma once
enum state { sleep, active, passive, leader, lost };
int undef = -1;


class Process {
	int id;					//�v���Z�Xid
	state state;			//���[�_���ۂ��̏��
	int cp;					//�i�͕킵�Ă���j�v���Z�X���ʎq
	int win;				//���[�_id

	public:
		Process();
		~Process();
		void OneMessage();
		void TwoMessage();
	private:

};

Process::Process() {

	state = sleep;
	win = undef;
}

Process::~Process() {

}

void Process::OneMessage() {

}

void Process::TwoMessage() {

}
