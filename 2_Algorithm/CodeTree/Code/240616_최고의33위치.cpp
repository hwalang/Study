#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 20;

int GetNumOfCoin(const int& x, const int& y, const int baseGrid[MAX_N][MAX_N])
{
	int coin = 0;

	// �������� �������� 3 * 3 ���� ������ �������� ����
	for (int i = x; i < x + 3; ++i) {
		for (int j = y; j < y + 3; ++j) {
			if (baseGrid[i][j] == 1) {
				++coin;					// 0�� 1�� �����ϱ� ������ coin += baseGrid[i][j];�� ����
			}
		}
	}

	return coin;
}

int GetMaxCoin(const int& N, const int baseGrid[MAX_N][MAX_N])
{
	int maxCoin = 0;

	// N * N ���ڸ� ��ȸ
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i + 2 >= N || j + 2 >= N) continue;
			// �ִ� ������ ����
			maxCoin = max(maxCoin, GetNumOfCoin(i, j, baseGrid));
		}
	}

	return maxCoin;
}

int main()
{
	int N;
	cin >> N;

	int baseGrid[MAX_N][MAX_N];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> baseGrid[i][j];
		}
	}

	// 3*3 ���� ���ο� ������ �� �ִ� �ִ� ���� ������ ��ȯ
	int maxCoin = GetMaxCoin(N, baseGrid);

	cout << maxCoin;
}