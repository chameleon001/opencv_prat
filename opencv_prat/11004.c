/*
�� N�� A1, A2, ..., AN�� �־�����. A�� �������� �������� ��, �տ������� K��° �ִ� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
�Է�

ù° �ٿ� N(1 �� N �� 5,000,000)�� K (1 �� K �� N)�� �־�����.

��°���� A1, A2, ..., AN�� �־�����. (-109 �� Ai �� 109)
���

A�� �������� ��, �տ������� K��° �ִ� ���� ����Ѵ�.
���� �Է�

5 2
4 1 2 3 5

���� ���

2
*/
#include <iostream>

#include <algorithm>

#include <cstdio>

using namespace std;

int main()

{

	int n, k, num[5000000];

	cin >> n >> k;

	for (int i = 0; i < n; ++i)

		scanf("%d", &num[i]);

	sort(num, num + n);

	cout << num[k - 1];

}

