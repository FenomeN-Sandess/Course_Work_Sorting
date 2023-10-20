

/// ���� � ������������� ������� ������ func

#pragma once
#include <iostream> // ����������� ���������� ��� ����������� ����� � ������
#include <string> // ����� � �������� � ����������� ��� ����������� ������ �� �������� 
#include <vector> // ����������� ���������� ��� �������� ������������� �������� ������ 
#include <iomanip> // ����������� ���������� ��� ���������� ������ � �������. ������������ � ������� ��� ������ ������� ���������
#include <chrono> // ����������� ���������� C++ � ��������� ������������ ��� "����������"
#include <fstream> // ����������� ���������� C++. ������������ ��� ������ � ������ ������ �� ����� � � ����.
#include <SFML/Graphics.hpp>
//#include <Windows.h>

#include "classes.h"

void menu::functions::generate() { 

	vect.clear(); //�������� ��������� � �������
	for (int iter = 0; iter < C ; iter++) {
		vect.push_back(rand() % 5000 + 1); //���������� ������� �������
	}

	std::cout << "Generation complete\n" << std::endl;
}

void menu::functions::sorting()
{
	for (int n = 0; n <= 10; n++) {

		
		// �������� ����� ������� �� n

		for (int j = 0; j < diff_par[n]; j++) {
			trial_vect.push_back(vect[j]); // ���������� ������� �� ������ - ������ ���������������� �������
		}
		
		auto start = std::chrono::high_resolution_clock::now(); //���������� �������� �������
		Sort.bubble_sorting(trial_vect); //���������� ����������� ����������
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> bubble_duration = end - start; //����� �� ������� ��������� ����������
		Info.bubble_time[0][n] = diff_par[n]; // ���������� �������� ������� ����������� ���������
		Info.bubble_time[1][n] = bubble_duration.count(); // ���������� ������� ������� �������� ���������� ����� � ��������

		start = std::chrono::high_resolution_clock::now();
		Sort.pyramid_sorting(trial_vect); //���������� ������������� ����������
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> pyramid_duration = end - start;
		Info.pyramid_time[0][n] = diff_par[n];
		Info.pyramid_time[1][n] = pyramid_duration.count();

		trial_vect.clear(); //�������� �������� �������
	}
}

void menu::functions::saving()
{
	file.open(path_to_file); //�������� ����� ��� ��� �������� 
	if (!file.is_open()) { //�������� �� ��������
		std::cout << "File opening error\n";
	}
	else {
		//������ �������, ����������� ������ � ������� ���������� ����������, � ����.

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 11; j++) {
				file.write(reinterpret_cast<char*>(&Info.bubble_time[i][j]), sizeof(double));
				file.write(reinterpret_cast<char*>(&Info.pyramid_time[i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

void menu::functions::downloading()
{
	file.open(path_to_file); // �������� ����� (�� ��������!)
	if (!file.is_open()) {
		std::cout << "File opening error";
	}
	else {
		// ������ �������, ����������� ������ � ������� ���������� ����������, �� �����
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 11; j++) {
				file.read(reinterpret_cast<char*>(&Info.bubble_time[i][j]), sizeof(double));
				file.read(reinterpret_cast<char*>(&Info.pyramid_time[i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

void print_table(const std::vector<std::vector<double>>& data) {
	const char separator = ' ';
	const int nameWidth = 15;
	const int numWidth = 12;

	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << std::setw(nameWidth + 3) << std::setfill('-') << ""; // ������� �������
		for (size_t j = 0; j < data[i].size(); ++j) {
			std::cout << std::setw(numWidth + 3) << std::setfill('-') << "";
		}
		std::cout << std::endl;

		std::string res = (static_cast<int>(i) == 0 ? "n" : "t (s)");
		std::cout << std::setw(nameWidth) << std::setfill(separator) << "| Row " + res + " |";
		for (size_t j = 0; j < data[i].size(); ++j) {
			std::cout << std::setw(numWidth) << std::setfill(separator) << data[i][j] << " |";
		}
		std::cout << std::endl;
	}

	std::cout << std::setw(nameWidth + 3) << std::setfill('-') << "";
	for (size_t j = 0; j < data[0].size(); ++j) {
		std::cout << std::setw(numWidth + 3) << std::setfill('-') << "";
	}
	std::cout << std::endl;
}

void menu::functions::show() {

	std::cout << "Bubble Table" << std::endl;
	print_table(Info.bubble_time);
	std::cout << "\nPyramid Table" << std::endl;
	print_table(Info.pyramid_time);
	std::cout << std::endl;

}


void menu::functions::display()
{
}

