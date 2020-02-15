// 6th.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <random>
#include "6th.h"
using namespace std;
void NonParallelAverage(int N, int  a[10], int b[10])
{
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += a[i];
	}
	sum /= N;
	printf("\nnonparallel average(A) = %f\n", sum); sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += b[i];
	}
	sum /= N;
	printf("nonparallel average(B) = %f\n", sum);
}

void PrintArrays(int N, int  a[10], int  b[10])
{
	printf("A:\n");
	for (int i = 0; i < N; i++)
	{
		printf("%i ", a[i]);
	}
	printf("\nB:\n");
	for (int i = 0; i < N; i++)
	{
		printf("%i ", b[i]);
	}
}

double  ParellelForSumReduction(int N, int  a[10])
{
	double sum = 0;
#pragma omp parallel for reduction (+:sum)
	for (int i = 0; i < N; i++)
	{
		sum += a[i];
	}

	sum /= N;
	return sum;
}

double ParallelForSum(int N, int a[10])
{
	double sum = 0;
#pragma omp parallel for 
	for (int i = 0; i < N; i++)
	{
		sum += a[i];
	}

	sum /= N;
	return sum;
}

void FillArrays(int N, int *a, int * b)
{
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 10 + 1;
		b[i] = rand() % 10 + 1;
	}
}

void ParallelTests(int N, int  a[10], int  b[10])
{
	double sum = 0;
	sum = ParellelForSumReduction(N, a);
	printf("parallel + reduction average(A) = %f\n", sum);
	sum = ParellelForSumReduction(N, b);
	printf("parallel + reduction average(B) = %f\n", sum);
	sum = ParallelForSum(N, a);
	printf("parallel non reduction average(A) = %f\n", sum);
	sum = ParallelForSum(N, b);
	printf("parallel non reduction average(B) = %f\n", sum);
}

int main()
{
	int N = 10;
	int a[10], b[10];
	FillArrays(N, a, b);
	PrintArrays(N, a, b);
	NonParallelAverage(N, a, b);
	ParallelTests(N, a, b);
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
