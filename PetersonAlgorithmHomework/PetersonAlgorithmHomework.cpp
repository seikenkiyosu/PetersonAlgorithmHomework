// PetersonAlgorithmHomework.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include<iostream>
#include "Process.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/**************INPUT*****************/
int n = 30;			//�v���Z�X�̐�
int DataNum = 100;
/************************************/


//��Ɨp�ϐ�


void ShowProcess(Process p[]);
bool IsAlgorithmOver(Process p[]);

int main() {
	srand((unsigned)time(NULL));

	/* ���ʎq�̕��т������_���ɐݒ� */
	int *processorder = new int[n];
	for (int i = 0; i < n; i++) { processorder[i] = i + 1; }
	for (int i = 0; i < n; i++) {
		int j = rand() % n;
		int t = processorder[i];
		processorder[i] = processorder[j];
		processorder[j] = t;
	}

	/* �v���Z�X�̏����� */
	Process *process = new Process[n];
	for (int i = 0; i < n; i++) { process[i].id = processorder[i]; }
	for (int i = 0; i < n; i++) { process[i].link = &process[(i + 1) % n]; }
	
	/* ���C������ */
	ShowProcess(process);

	int round = 1;
	while (!IsAlgorithmOver(process)) {
		//cout << "~~~~Round" << round++ << "~~~~" << endl;
		for (int i = 0; i < n; i++) {
			if (process[i].state == active) {
				/* OneMessage */
				Process *message = &process[i];
				do {									//active�ȃv���Z�X�ɏo��܂�forwarding
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
				/* cp & state�X�V */
				process[i].RenewCp();
			}
		}
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~FINISH!!~~~~~~~~~~~~~~~~~~~~~" << endl;
	ShowProcess(process);

	/* ��������� */
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
