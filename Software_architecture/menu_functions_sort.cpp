#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include "functions.h"

// Пузырьковая сортировка
void bubble_sorting(std::vector <double> vector)
{
	int k = vector.size();
	bool swapped;
	for (int i = 0; i < k - 1; i++) {
		swapped = false;
		for (int j = 0; j < k - i - 1; j++) {
			if (vector[j] > vector[j + 1]) {
				std::swap(vector[j], vector[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

// Сортировка кучами
void heapify(std::vector<double>& arr, int n, int i) {

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
};

void pyramid_sorting(std::vector<double> vector) {

    int n = vector.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vector, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(vector[0], vector[i]);
        heapify(vector, i, 0);
    }
}

// Сортировка вставками
void insertion_sorting(std::vector<double> vector) {
    int n = vector.size();
    for (int i = 1; i < n; i++) {
        double key = vector[i];
        int j = i - 1;
        while (j >= 0 && vector[j] > key) {
            vector[j + 1] = vector[j];
            j = j - 1;
        }
        vector[j + 1] = key;
    }
}

// Быстрая сортировка
int partition(std::vector<double>& vector, int low, int high) {
    double pivot = vector[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (vector[j] < pivot) {
            i++;
            std::swap(vector[i], vector[j]);
        }
    }
    std::swap(vector[i + 1], vector[high]);
    return (i + 1);
}

void quick_sort_helper(std::vector<double> vector, int low, int high) {
    if (low < high) {
        int pi = partition(vector, low, high);
        quick_sort_helper(vector, low, pi - 1);
        quick_sort_helper(vector, pi + 1, high);
    }
}

void quick_sorting(std::vector<double> vector) {
    int low = 0;
    int high = vector.size() - 1;
    quick_sort_helper(vector, low, high);
}

// Сортировка выбором
void selection_sorting(std::vector<double> vector) {
    int n = vector.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (vector[j] < vector[min_index]) {
                min_index = j;
            }
        }
        std::swap(vector[i], vector[min_index]);
    }
}
