#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <functional> 


void bubble_sorting(std::vector <double> vector); /* ����������� ���������� */
void pyramid_sorting(std::vector <double> vector); /* ������������� ����������*/
void insertion_sorting(std::vector<double> vector); // ���������� ���������
void selection_sorting(std::vector<double> vector); // ���������� ���������
void quick_sorting(std::vector<double> vector); // ������� ����������

class functions { /* ����� ��� ������ � ��������� */
protected:
	std::fstream file;	// ������ ������ ��� ������ � ������ ������ �� ����� � � ����
	std::ofstream outfile;
	std::ifstream inputfile;
	int C = 1000;																			//��������� (������ ������� �������)
	std::vector <double> vect;																/* ������������ ������ � ������� double */
	std::vector <double> trial_vect;														/* ��������� ������ */
	std::string path_to_file = "Results_of_sortings.txt";								    // ���� � �����
	std::vector <int> diff_par = { 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 }; // ������ � ������� ���������� ���������

	
	void print_table(const std::vector<std::vector<double>>& data);
	void save_time(void view_sorting(std::vector <double> vector), std::vector<std::vector<double>>& view_time, int n);
	void save_data(std::vector<std::vector<double>>& sort_time);
	void download_data(std::vector<std::vector<double>>& sort_time);

public:
	functions() : bubble_time(2, std::vector<double>(11, 0.0)), pyramid_time(2, std::vector<double>(11, 0.0)),
		insertion_time(2, std::vector<double>(11, 0.0)), quick_time(2, std::vector<double>(11, 0.0)),
		selection_time(2, std::vector<double>(11, 0.0)) {}

	std::vector<std::vector<double>> bubble_time;											// �������� ������� bubble_time
	std::vector<std::vector<double>> pyramid_time;										    // �������� ������� pyramid_time
	std::vector<std::vector<double>> insertion_time;										
	std::vector<std::vector<double>> quick_time;
	std::vector<std::vector<double>> selection_time;

	void generate();																		/*��������� �������*/
	void sorting();																			/*��������� ���������� � ��������� ����� � ������*/
	void saving();																			/* ���������� ������ � ����*/
	void downloading();																		/* ������ ������ �� �����*/
	void show(); 																			/* �������� ������ � �������*/
	bool check_content_massive(std::vector<std::vector<double>> sorting_time);
	void reset_data();																		// �������� ������ 
	void display();																			/* ���������� ������ � ������� */
	bool empty_data();
};

