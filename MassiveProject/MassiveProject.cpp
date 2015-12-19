// MassiveProject.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int mass[100] = { 10, 45, 14, 32, 5, 15, 11, 69, 78, 12, 45 };
	int i, N = sizeof(mass) / sizeof(int);

	srand(mass[0]);
	for (i = 11; i < N; i++) {
		mass[i] = (unsigned char)rand();
	}

	for (i = 0; i < N; ++i) {
		printf("%8d", mass[i]);
		if (!(i % 9)) printf("\n");
	}

	int k = 0;
	for (i = 11; i < N; i++) {
		if (k != i / 10) {
			k = i / 10;
			srand(mass[k]);
		}
		if (mass[i] % 2)
			mass[i] += (unsigned char)rand();
		else mass[i] -= (unsigned char)rand();
	}

	printf("\n");
	for (i = 0; i < N; ++i) {
		printf("%8d", mass[i]);
		if (!(i % 9)) printf("\n");
	}

	int min = mass[0], max = mass[0], sum = mass[0];
	for (i = 1; i < N; i++) {
		if (min > mass[i]) min = mass[i];
		if (max < mass[i]) max = mass[i];
		sum += mass[i];
	}
	float sr_s = sum / N, sr_n = sum / (N - 1);
	printf("\nmin = %8d,\tmax = %8d,\tsum = %8d\nsr_s = %8.4f,\tsr_n = %8.4f\n", min, max, sum, sr_s, sr_n);

	system("pause");

	return 0;
}

