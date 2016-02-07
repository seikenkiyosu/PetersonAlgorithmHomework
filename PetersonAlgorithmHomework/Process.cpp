#include "stdafx.h"
#include "Process.h"
#include <cstdlib>

Process::Process() {
	int randomval = rand() % 2;
	isstartprocess = (randomval == 1) ? true : false;
	randomval = rand() % 2;
	state = (randomval == 1) ? active : passive;
	win = -1;			//‚Ü‚¾Œˆ‚Ü‚Á‚Ä‚È‚¢
	one = -1;
	two = -1;
}

Process::~Process() {

}

void Process::RenewCp() {
	int temp = id < one ? id : one;
	cp = temp < two ? temp : two;
	if (cp != one) { state = passive; cp = -1; }
	one = two = -1;
}

void Process::send(massagetype type, int Q) {

}
