#pragma once
enum state { sleep, active, passive, leader, lost };
int undef = -1;


class Process {
	int id;					//プロセスid
	state state;			//リーダか否かの状態
	int cp;					//（模倣している）プロセス識別子
	int win;				//リーダid

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
