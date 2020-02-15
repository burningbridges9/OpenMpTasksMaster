// 7th.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	int a[12], b[12], c[12];
#pragma omp parallel for schedule(static,12/3) num_threads(4)
	for (int i = 0; i < 12; i++)
	{
		printf("Amount of threads: %i;\nThread number: %i;\n", omp_get_num_threads(), omp_get_thread_num());
		a[i] = rand() % 10 + 1;
		b[i] = rand() % 10 + 1;
		printf("a[%i] = %i\n", i, a[i]);
		printf("b[%i] = %i\n", i, b[i]);
	}
	printf("all A:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", a[i]);
	}
	printf("\nall B:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", b[i]);
	}
	printf("\n");
#pragma omp parallel for schedule(dynamic,12/4) num_threads(3)
	for (int i = 0; i < 12; i++)
	{
		printf("Amount of threads: %i;\nThread number: %i;\n", omp_get_num_threads(), omp_get_thread_num());
		c[i] = a[i] + b[i];
		printf("c[%i] = %i\n", i, c[i]);
	}
	printf("\nall C:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", c[i]);
	}
	system("pause");
	return 0;
}