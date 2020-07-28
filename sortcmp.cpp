#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10
#define RESIZE 2

using namespace std;

int comp(const void *a, const void *b) {
	if (fabs(*(double *)a) > fabs(*(double *)b)) {
		return 1;
	} else if (fabs(*(double *)a) < fabs(*(double *)b)) {
		return -1;
	} else {
		return 0;
	}
}

int *step_precnt(int n) { //генерация массива, хранящего длинны шага сортировки Шелла
	int *steps = (int *) malloc(SIZE * sizeof(int));
	int size = SIZE;
	int last_step = 0;
	int k = 0;

	while (3 * last_step <= n) {
		if (k >= size - 1) {
			size *= RESIZE;
			steps = (int *) realloc(steps, size * sizeof(int));
		}

		if (k % 2) {
			steps[k] = 8 * pow(2, k) - 6 * pow(2, (k + 1) / 2) + 1;
		} else {
			steps[k] = 9 * pow(2, k) - 9 * pow(2, k / 2) + 1;
		}

		last_step = steps[k];
		++k;
	}

	steps = (int *) realloc(steps, k * sizeof(int));

	steps[k - 1] = 0;

	return steps;
}

void shell_sort(double *arr, int n) { //сортировка массива методом Шелла
	int *steps = step_precnt(n); //предрассчет массива с длиннами шага сортировки
	int k = 0;
	int total_cmp = 0;
	int total_swaps = 0;

	while (steps[k]) {
		k++;
	}

	for (int i = k - 1; i >= 0; --i) {
		int step = steps[i];

		for (int j = step; j < n; ++j) {
			double tmp = arr[j];
			int q;

			for (q = j; (q >= step) && (total_cmp++, fabs(tmp) > fabs(arr[q - step])); q -= step) {
				arr[q] = arr[q - step];
				++total_swaps;
			}

			arr[q] = tmp;
		}
	}

	printf("Колличество сравнений в сортировке Шелла: %d, колличество обменов: %d\n", total_cmp, total_swaps);

	free(steps);
}

void bubble_sort(double *arr, int n) { //сортировка массива 'пузырьком'
	int total_cmp = 0;
	int total_swaps = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			++total_cmp;

			if (fabs(arr[j]) < fabs(arr[j + 1])) {
				++total_swaps;

				double tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	printf("Колличество сравнений в сортировке 'пузырьком': %d, колличество обменов: %d\n", total_cmp, total_swaps);
}

void gen_arr(double *arr, int n, int k, int min, int max) { //генерация рандомного массива
	for (int i = 0; i < n; ++i) {
		double f = min + (double)rand() / RAND_MAX * (max - min);

		arr[i] = f;
	}

	if (k == 1) { //сортировка по неубыванию
		qsort(arr, n, sizeof(double), comp);
	} else if (k == 2) { //сортировка по невозрастанию
		qsort(arr, n, sizeof(double), comp);

		for (int i = 0; i < n / 2; ++i) {
			double tmp;

			tmp = arr[i];
			arr[i] = arr[n - i - 1];
			arr[n - i - 1] = tmp;
		}
	}
}

int main(int argc, char **argv) {
	printf("Введите колличество запросов: ");

	int m;

	scanf("%d", &m);

	double *arr1 = NULL;
	double *arr2 = NULL;

	for (int i = 0; i < m; ++i) {
		printf("Тип генерируемого массива: 1 - неубывающий по модулю, 2 - невозрастающий по модулю, 3 - рандомный ");

		int k;

		scanf("%d", &k);

		printf("Введите размер массива: ");

		int n;

		scanf("%d", &n);

		arr1 = (double *) realloc(arr1, n * sizeof(double));

		gen_arr(arr1, n, k, -1, 1);

		arr2 = (double *) realloc(arr2, n * sizeof(double));

		for (int j = 0; j < n; ++j) {
			printf("%lf ", arr1[j]);

			arr2[j] = arr1[j];
		}
		printf("\n");

		shell_sort(arr1, n);
		bubble_sort(arr2, n);
	}

	free(arr1);
	free(arr2);

	return 0;
}