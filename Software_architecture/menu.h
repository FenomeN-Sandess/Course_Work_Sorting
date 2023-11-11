#pragma once
#include "functions.h"


class menu { /* ������� ����� �������, �������� ����� �������� ���� */
private: 
	functions* Func;
	bool State = false;
public:
	menu(functions* f) : Func(f) {}
	void start();																				/*������ ������ ����*/
	void end();																					/*���������� ������ ����*/
	void choice();	 																			/*������ ������������ ���� */

	menu() = default;
};
