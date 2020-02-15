// 4th.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <random>
using namespace std;

int main()
{
	int a[10], b[10];
	for (int i = 0; i != 10; i++)
	{
		a[i] = rand() % 20 + 1;
		b[i] = rand() % 20 + 1;
	}
	printf("A array:\n");
	for (int i = 0; i != 10; i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\nB array:\n");
	for (int i = 0; i != 10; i++)
	{
		printf("%d  ", b[i]);
	}
	std::cout << std::endl;
	int min, max;
	omp_set_nested(0);

#pragma omp parallel num_threads(2) 
	{
#pragma omp master 
		{
			printf("thread num = %d\n", omp_get_thread_num());
			min = a[0];
			for (int i = 1; i < 10; i++)
			{
				if (min > a[i])
				{
					min = a[i];
				}
				else continue;
			}
			printf("min in array A = %d\n", min);
		}
#pragma omp single
		{
			printf("thread num = %d\n", omp_get_thread_num());
			max = b[0];
			for (int i = 1; i < 10; i++)
			{
				if (max < b[i])
					max = b[i];
				else continue;
			}
			printf("max in array B = %d\n", max);
		}
	}



	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
