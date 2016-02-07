// PetersonAlgorithmHomework.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include<iostream>
#include "Process.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/**************INPUT*****************/
int n = 30;			//プロセスの数
int DataNum = 100;
/************************************/


//作業用変数


void ShowProcess(Process p[]);
bool IsAlgorithmOver(Process p[]);

int main() {
	srand((unsigned)time(NULL));

	/* 識別子の並びをランダムに設定 */
	int *processorder = new int[n];
	for (int i = 0; i < n; i++) { processorder[i] = i + 1; }
	for (int i = 0; i < n; i++) {
		int j = rand() % n;
		int t = processorder[i];
		processorder[i] = processorder[j];
		processorder[j] = t;
	}

	/* プロセスの初期化 */
	Process *process = new Process[n];
	for (int i = 0; i < n; i++) { process[i].id = processorder[i]; }
	for (int i = 0; i < n; i++) { process[i].link = &process[(i + 1) % n]; }
	
	/* メイン処理 */
	ShowProcess(process);

	int round = 1;
	while (!IsAlgorithmOver(process)) {
		//cout << "~~~~Round" << round++ << "~~~~" << endl;
		for (int i = 0; i < n; i++) {
			if (process[i].state == active) {
				/* OneMessage */
				Process *message = &process[i];
				do {									//activeなプロセスに出会うまでforwarding
					message->win = process[i].id;
					message = message->link;
				} while (message->state != active);
				if ( message == &process[i] ) { continue; }
				message->one = process[i].id;
				/* TwoMessage */
				message = &process[i];
				do {
					message = message->link;
				} while (message->state != active || message->one == process[i].id);
				message->two = process[i].id;
				/* cp & state更新 */
				process[i].RenewCp();
			}
		}
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~FINISH!!~~~~~~~~~~~~~~~~~~~~~" << endl;
	ShowProcess(process);

	/* メモリ解放 */
	delete[] process;
	delete[] processorder;
    return 0;
}

void ShowProcess(Process p[]) {
	for (int i = 0; i < n; i++) {
//		cout << "process" << i + 1 << " : " 
		cout << "id = " << p[i].id << endl;
		if (p[i].state == active)
			cout << "active" << endl;
		else
			cout << "nonactive" << endl;
		cout << "win = " << p[i].win << endl;
		cout << "one = " << p[i].one << ": two = " << p[i].two << endl;
		cout << "--" << endl;
	}
}

bool IsAlgorithmOver(Process p[]) {
	for (int i = 0; i < n; i++) {
		if (p[i].win == -1) return false;
		if (p[0].win != p[i].win) return false;
	}
	return true;
}
