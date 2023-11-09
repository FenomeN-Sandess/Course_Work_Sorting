
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 

#pragma once

class menu { /* ������� ����� ���� */
private: 

	bool State = false;

protected:

	/* ����� ��� ������ � ��������� */
	class functions { 
	protected:
		//����� � �������� ����������
		class sorting { 
		public:
			void bubble_sorting(std::vector <double> vector); /* ����������� ���������� */
			void pyramid_sorting(std::vector <double> vector); /* ������������� ����������*/
		};

		// �����, ���������� ������ ���������� �������� bubble_time � pyramid_time
		class info_time { 
			
		public:
			std::vector<std::vector<double>> bubble_time; // �������� ������� bubble_time
			std::vector<std::vector<double>> pyramid_time; // �������� ������� pyramid_time

			// ���������� ������ info_time � ������������ �������� bubble_time � pyramid_time
			info_time() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}
		};
		
		std::fstream file; // ������ ������ ��� ������ � ������ ������ �� ����� � � ���� ��������������
		info_time Info; // ������ ������ info_time � ������� ��������� ������ menu
		sorting Sort; // ������ ���������� ������ sorting � �������� ����������
		int C = 1000; //��������� (������ ������� �������)
		std::vector <double> vect; /* ������������ ������ � ������� double */
		std::vector <double> trial_vect; /* ��������� ������ */
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // ������ � ������� ���������� ���������
		std::string path_to_file = "Results_of_sortings.txt"; //���� � �����

		/*�������������� �������, ������������ ��� �������� �������*/
		void print_table(const std::vector<std::vector<double>>& data);
		void save_time(std::function<void(std::vector<double>)> view_sorting, std::vector<std::vector<double>>& view_time, int n);

	public:
		void generate(); /*��������� �������*/
		void sorting(); /*��������� ���������� � ��������� ����� � ������*/
		void saving(); /* ���������� ������ � ����*/
		void downloading(); /* ������ ������ �� �����*/
		void show(); /* �������� ������*/
		void display(); /* ���������� ������ */

	};

	functions Func; // ������ ������ functions � ������� ��������� ������ menu

public:

	void start(); /*������ ������ ����*/
	void end(); /*���������� ������ ����*/
	void choice(); /*����� ��������*/

};

