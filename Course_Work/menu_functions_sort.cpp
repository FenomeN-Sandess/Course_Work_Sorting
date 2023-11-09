
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>

#include "classes.h"


// Пузырьковая сортировка
void menu::functions::sorting::bubble_sorting(std::vector <double> vector)
{
	// Упорядочивание в порядке возрастания методом пузырьковой сортировки
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
		// Если нет обменов во внутреннем цикле, то массив уже отсортирован
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

void menu::functions::sorting::pyramid_sorting(std::vector<double> vector) {

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

// Быстрая сортировка

// Сортировка выбором