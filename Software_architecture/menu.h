#pragma once
#include "functions.h"


class menu { /* ������� ����� �������, �������� ����� �������� ���� */
private: 
	functions* Func;
	bool State = false;
public:
	menu(functions* f) : Func(f) {} // ����������� ������ � ������������ ������ �� ����� ������ Func
	void start();																				/*������ ������ ����*/
	void end();																					/*���������� ������ ����*/
	void choice();	 																			/*������ ������������ ���� */
};
