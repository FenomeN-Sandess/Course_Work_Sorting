
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#pragma once

class sorting { //����� � �������� ����������
public:
	void bubble_sorting(std::vector <float> vector); /* ����������� ���������� */
	void pyramid_sorting(std::vector <float> vector); /* ������������� ����������*/
};


class menu { /* ����� ��� ������ � ���� */
private: 

	bool work_process = false;

protected:

	class functions { /* ����� ��� ������ � ��������� */
	protected:

		class info_time { /* �����, ���������� ������ ���������� �������� bubble_time � pyramid_time */
			/* ����� ������ ��� ��� ������ � ���� � ������ */
		public:
			std::vector<std::vector<double>> bubble_time; // �������� ������� bubble_time
			std::vector<std::vector<double>> pyramid_time; // �������� ������� pyramid_time

			// ���������� ������ info_time � ������������ �������� bubble_time � pyramid_time
			info_time() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)) {}
		};

		info_time Info; // ������ ������ info_time � ������� ��������� ������ menu

		std::fstream file; // ������ ������ ��� ������ � ������ ������ �� ����� � � ���� ��������������
		sorting Sort; // ������ ���������� ������ sorting � �������� ����������
		
		int C = 1000; //��������� (������ ������� �������)
		std::vector <float> vect; /* ������������ ������ � ������ ������� */
		std::vector <float> trial_vect; /* ��������� ������ */
		std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // ������ � ������� ���������� ���������


		std::string path_to_file = "Results_of_sortings.txt"; //���� � �����


	public:

		void generate(); /*��������� �������*/
		void sorting(); /*��������� ���������� � ��������� ����� � ������*/
		void saving(); /* ���������� ������ � ����*/
		void downloading(); /* ������������ �� �����*/
		void show(); /* �������� ������*/
		void display(); /* ���������� ������ */

	};

	functions Func; // ������ ������ functions � ������� ��������� ������ menu

public:

	void start(); /*������ ������ ����*/
	void end(); /*���������� ������ ����*/
	void choice(); /*����� ��������*/

};

