
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 
#include "menu_control.h"


#pragma once
void bubble_sorting(std::vector <double> vector); /* ����������� ���������� */
void pyramid_sorting(std::vector <double> vector); /* ������������� ����������*/


class menu { /* ������� ����� ���� */
private: 
	bool State = false;
	menu_control cl;
protected:
	class functions { /* ����� ��� ������ � ��������� */
	protected:
		std::vector<std::vector<double>> bubble_time;											// �������� ������� bubble_time
		std::vector<std::vector<double>> pyramid_time;										    // �������� ������� pyramid_time
		std::fstream file;																		// ������ ������ ��� ������ � ������ ������ �� ����� � � ����
		int C = 1000;																			//��������� (������ ������� �������)
		std::vector <double> vect;																/* ������������ ������ � ������� double */
		std::vector <double> trial_vect;														/* ��������� ������ */
		std::string path_to_file = "Results_of_sortings.txt";								    //���� � �����
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // ������ � ������� ���������� ���������

		/*�������������� �������, ������������ ��� �������� �������*/
		void print_table(const std::vector<std::vector<double>>& data);
		void save_time(void view_sorting(std::vector <double> vector), std::vector<std::vector<double>>& view_time, int n);
	public:
		functions() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}

		void generate();																		/*��������� �������*/
		void sorting();																			/*��������� ���������� � ��������� ����� � ������*/
		void saving();																			/* ���������� ������ � ����*/
		void downloading();																		/* ������ ������ �� �����*/
		void show();																			/* �������� ������*/
		void display();																			/* ���������� ������ */
	};

	functions Func; // ������ ������ functions � ������� ��������� ������ menu

public:
	void start();																				/*������ ������ ����*/
	void end();																				    /*���������� ������ ����*/
	void choice();																				/*����� ��������*/

	menu() = default;
};

