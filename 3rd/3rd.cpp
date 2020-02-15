// 3rd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
using namespace std;


///
int main()
{
	int b = 1;
	int a = 1;

	printf("before parallel:\na = %i,\nb = %i\n", a, b);
#pragma omp parallel private(a) firstprivate(b) num_threads(2)
	{
		int a = 1;
		printf("in parallel, thread: %i\na = %i,\nb = %i\n", omp_get_thread_num(), a, b);
		a = a + omp_get_thread_num();
		b = b + omp_get_thread_num();
		printf("a + #thread = %i,\nb + #thread = %i\n", a, b);
	}
	printf("after parallel:\na = %i,\n b = %i\n", a, b);

	int c, d;
	c = d = 10;

	printf("before parallel:\nc = %i,\nd = %i\n", c, d);
#pragma omp parallel shared(c) private(d) num_threads(4)
	{
		d = 10;
		printf("in parallel, thread: %i\na = %i,\nb = %i\n", omp_get_thread_num(), c, d);
		c = c - omp_get_thread_num();
		d = d - omp_get_thread_num();
		printf("a - number_of_thread = %i,\nb - number_of_thread = %i\n", c, d);
	}
	printf("after parallel:\na = %i,\n b = %i\n", c, d);
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
