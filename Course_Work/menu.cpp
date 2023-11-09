
/// ���� � ������������� ������� ������ menu

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "classes.h"



void menu::start()
{

	std::cout << "Would you like to start a menu? enter y/n\n>>";
	std::string y_n;
	std::cin >> y_n;
	this->State = (y_n == "Y") or (y_n == "y") ? true : false;
}

void menu::end()
{

	std::cout << "Would you like to turn off the menu? enter y/n\n>>";
	std::string y_n;
	std::cin >> y_n;
	this->State = (y_n == "Y") or (y_n == "y") ? false : true;
}

void menu::choice()
{
	while (this->State) {
		int CHOICE;
		std::cout << "Choose action from list:\n1.Generate\n2.Calculate\n3.Save\n4.Download\n5.Display the table\n6.Display a plot\n7.Quit\n";
		std::cin >> CHOICE;
		switch (CHOICE)
		{
		case 1:
			Func.generate();
			// �������� ������� � ��� ���������� ���������� ������� �� 5000
			break;
		case 2:
			Func.sorting();
			// ���������� ���������� � ���������� ������� �� ����������
			break;
		case 3:
			Func.saving();
			// ���������� ���������� �������� � ����
			break;
		case 4:
			Func.downloading();
			// �������� �������� �� �����
			break;
		case 5:
			Func.show();
			// ����� ������� �� ������ �� �������� �� ����� + ������
			break;
		case 6:
			Func.display();
			// ����� ������� �� ������ �� ��������.
			break;
		case 7:
			end(); // ����� �� ����
			break;
		default:
			std::cout << "Please, choose action from list." << std::endl;
			break;
		}
	}
	}



