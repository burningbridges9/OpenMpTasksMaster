// 9th.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#include <ctime>
#include "9th.h"
#include "windows.h"
using namespace std;



void TaskNine()
{
	const int N = 6;
	const int M = 8;

	int d[N][M];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			d[i][j] = (rand() + time(0)) % 100;

	int max = d[0][0],
		min = d[0][0];
	//cout << "max = " << max << endl << "min = " << min << endl;
	omp_set_num_threads(N);

#pragma omp parallel shared(max,min)
	{
		int loc_max = max;
		int loc_min = min;
#pragma omp for
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int element = d[i][j];
				if (element > loc_max) {
					loc_max = element;
				}
				if (element < loc_min) {
					loc_min = element;
				}

			}
		}
#pragma omp critical
		{
			if (max < loc_max) {
				max = loc_max;
			}
			if (min > loc_min) {
				min = loc_min;
			}
		}
	}

	cout << "d: " << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << d[i][j] << ' ';
		cout << endl;
	}
	cout << "max = " << max << endl << "min = " << min << endl;
}

void TaskTen()
{
	const int N = 30;
	int a[N];

	for (int i = 0; i < N; ++i)
		a[i] = (rand() + time(0)) % 10 + 1;
	//        
	//     for (int i = 0; i < N; ++i)
	//         cout << a[i] % 9 << " ";
	//     cout << endl;

	cout << " array: ";
	for (int i = 0; i < N; ++i)
		cout << a[i] << ' ';
	cout << endl;

	int count = 0;
#pragma omp parallel for 
	for (int i = 0; i < N; ++i)
	{

		if (a[i] % 9 == 0)
		{
#pragma omp atomic
			++count;
		}
	}

	cout << " count =" << count << endl;
}

void TaskEleven()
{
	const int N = 30;
	int a[N];

	for (int i = 0; i < N; ++i)
		a[i] = (rand() + time(0)) % 100 + 1;

	cout << " array: ";
	for (int i = 0; i < N; ++i)
		cout << a[i] << ' ';
	cout << endl;

	int max = a[0],
		count = 0;

#pragma omp parallel for num_threads(4) shared(max)
	for (int i = 0; i < N; ++i)
	{
		if (a[i] > max)
			if (a[i] % 7 == 0)
			{
#pragma omp critical 
				{
					if (a[i] > max)
						max = a[i];
				}
			}
	}

	cout << " max =" << max << endl;
}

void TaskThirteen()
{
	const int n = 30;
	int a[n] = { 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 };
	int p = 2;
	int sum = 0;
#pragma omp parallel for ordered
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * pow(p, (n - 1) - i);
		//printf("%i * (%i ^ %i)\n", a[i], p, n - 1 - i);
	}
	printf("number = %i\n", sum); // 756893125
}

void TaskFourteen()
{
	auto N = 210;
	auto NN = N * N;
	printf("Expected N = %i\n", NN);
	int sum = 0;
#pragma omp parallel for reduction (+:sum)
	for (int i = 0; i < N; i++)
	{
		sum += 2 * i + 1;
	}
	printf("Sum = %i\n", sum);
}

bool prime(int n) {
	for (int i = 2; i <= sqrt(n); i++)
		if (n%i == 0)
			return false;
	return true;
}

void TaskFifteen()
{
	printf("Enter numbers:\n");
	int a = 2; int b = 20;
	/*cin >> a >> b;*/
	printf("U entered numbers: %i and %i\n", a, b);
	int dif = abs(b - a);
	int defaultThreadsNum = 8;
	int threadsNum = dif > defaultThreadsNum ? dif / defaultThreadsNum : defaultThreadsNum - defaultThreadsNum % dif;

#pragma omp parallel for
	for (int i = 0; i < dif; i++)
	{
		int number = a + i;
		if (prime(number))
			printf("prime = %i\n", number);
	}
}

void TaskTwelveOne()
{
#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
		for (int i = nthreads - 1; i >= 0; i--)
		{
#pragma omp barrier
			{
				if (i == omp_get_thread_num())
				{
#pragma omp critical
					cout << "thread " << i << endl;
				}
			}
		}
	}
}

void TaskTwelveTwo()
{
#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
#pragma omp for ordered
		for (int i = nthreads - 1; i >= 0; i--)
		{
#pragma omp ordered
			{
				//#pragma omp critical
				cout << "thread " << i << endl;
			}
		}
	}
}

void TaskTwelveThree()
{
#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
		int threadNumber = omp_get_thread_num();
		int dif = nthreads - threadNumber;
		int chillTime = dif * 100;
		switch (dif)
		{
		case 1:
			Sleep(chillTime);
			cout << "thread " << threadNumber << endl;
			break;
		case 2:
			Sleep(chillTime);
			cout << "thread " << threadNumber << endl;
			break;
		case 3:
			Sleep(chillTime);
			cout << "thread " << threadNumber << endl;
			break;
		case 4:
			Sleep(chillTime);
			cout << "thread " << threadNumber << endl;
			break;
		}
	}
}

int main()
{
	//TaskNine();

	//TaskTen();

	//TaskEleven();

	//TaskTwelveOne();
	//TaskTwelveTwo();
	//TaskTwelveThree();
	TaskTwelveFour();
	//TaskThirteen();

	//TaskFourteen();

	//TaskFifteen();
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
