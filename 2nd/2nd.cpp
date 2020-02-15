// 2nd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
using namespace std;


void CheckNumThreads(int val)
{
#pragma omp parallel num_threads(3) if(val>2) 
	if (omp_in_parallel())
	{
		printf("thread id: %i \n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
	}
	else
	{
#pragma omp parallel num_threads(1)
		{
			printf("single\n");
			printf("thread id: %i \n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}
}
int main()
{
	CheckNumThreads(1);
	CheckNumThreads(2);
	CheckNumThreads(3);
	getchar();
	system("pause");
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
