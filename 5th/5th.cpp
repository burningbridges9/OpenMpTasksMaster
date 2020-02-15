// 5th.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <omp.h>
#include <random>

int main()
{
	int d[6][8];
	for (int i = 0; i != 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			d[i][j] = rand() % 10 + 1;
		}
	}
	printf("double dimensional array:\n");
	for (int i = 0; i != 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d  ", d[i][j]);
		}
		printf("\n");
	}

#pragma omp sections
	{
#pragma omp section //mid
		{
			double sum = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum += d[i][j];
				}
			}
			sum /= 6.0 * 8.0;
			printf("Average = %f\n", sum);
			printf("numOfThread = %i\n", omp_get_thread_num());
		}

#pragma omp section //minmax
		{
			int min, max;
			min = max = d[0][0];
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (min > d[i][j])
						min = d[i][j];

					if (max < d[i][j])
						max = d[i][j];
				}
			}

			printf("min = %i\n", min);
			printf("max = %i\n", max);
			printf("numOfThread = %i\n", omp_get_thread_num());
		}

#pragma omp section // %3=0
		{
			int count = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (d[i][j] % 3 == 0)
					{
						count++;
					}
					else continue;
				}
			}
			printf("count = %i\n", count);
			printf("numOfThread = %i\n", omp_get_thread_num());
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
