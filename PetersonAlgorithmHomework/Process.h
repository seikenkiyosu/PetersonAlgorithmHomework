#pragma once

enum state { sleep, active, passive, leader, lost };
enum massagetype { one, two };


class Process {
public:
	bool isstartprocess;	//始動プロセスか否か
	int id;					//プロセスid(メインで初期化)

	state state;			//リーダか否かの状態
	int cp;					//（模倣している）プロセス識別子
	int win;				//リーダid

	int one;				//oneメッセージ用バッファ
	int two;				//twoメッセージ用バッファ

	Process *link;			//リンク

public:
	Process();
	~Process();
	void RenewCp();
	void send(massagetype , int );
};

