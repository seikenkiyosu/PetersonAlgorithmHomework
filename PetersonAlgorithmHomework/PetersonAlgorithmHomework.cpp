// PetersonAlgorithmHomework.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include<iostream>
#include "Process.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/**************INPUT*****************/
int n;			//�v���Z�X�̐�
int DataNum = 100;
/************************************/


//��Ɨp�ϐ�
int MessageNum;
int MaxMessageNum;
int MinMessageNum;
int SumMessageNum;
double AveMessageNum;

void ShowProcess(Process p[]);
bool IsAlgorithmOver(Process p[]);

int main() {
	srand((unsigned)time(NULL));
	for (n = 10; n <= 500; n += 10) {
		MaxMessageNum = 0; MinMessageNum = 1000000; SumMessageNum = 0; AveMessageNum = 0.0;
		for (int Data = 0; Data < DataNum; Data++) {
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
			//ShowProcess(process);
			MessageNum = 0;
			int round = 1;
			while (!IsAlgorithmOver(process)) {
				//cout << "~~~~Round" << round++ << "~~~~" << endl;
				for (int i = 0; i < n; i++) {
					if (process[i].state == active) {
						/* OneMessage */
						Process *message = &process[i];
						do {									//active�ȃv���Z�X�ɏo��܂�forwarding
							message->win = process[i].id;
							MessageNum++;
							message = message->link;
						} while (message->state != active);
						if (message == &process[i]) { continue; }
						message->one = process[i].id;
						/* TwoMessage */
						message = &process[i];
						do {
							message = message->link;
							MessageNum++;
						} while (message->state != active || message->one == process[i].id);
						message->two = process[i].id;
						/* cp & state�X�V */
						process[i].RenewCp();
					}
				}
			}
			//cout << "~~~~~~~~~~~~~~~~~~~~~FINISH!!~~~~~~~~~~~~~~~~~~~~~" << endl;
			//ShowProcess(process);
			//cout << "The number of Messages = " << MessageNum << endl;
			delete[] process;
			delete[] processorder;
			/* MessageData���W */
			if (MaxMessageNum < MessageNum) MaxMessageNum = MessageNum;
			if (MinMessageNum > MessageNum) MinMessageNum = MessageNum;
			SumMessageNum += MessageNum;
		}
		AveMessageNum = (double)SumMessageNum / (double)n;
		//cout << "~~~~~~~~~~ n = " << n << "~~~~~~~~~~" << endl;
		//cout << "���b�Z�[�W���ϒl :\t" << AveMessageNum << endl;
		//cout << "���b�Z�[�W�ő�l :\t" << MaxMessageNum << endl;
		//cout << "���b�Z�[�W�ŏ��l :\t" << MinMessageNum << endl;
		cout << MinMessageNum << endl;
	}

	/* ��������� */
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
