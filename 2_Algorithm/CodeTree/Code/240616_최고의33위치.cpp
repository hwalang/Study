#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 20;

int GetNumOfCoin(const int& x, const int& y, const int baseGrid[MAX_N][MAX_N])
{
	int coin = 0;

	// 시작점을 기준으로 3 * 3 격자 내부의 동전수를 구함
	for (int i = x; i < x + 3; ++i) {
		for (int j = y; j < y + 3; ++j) {
			if (baseGrid[i][j] == 1) {
				++coin;					// 0과 1만 존재하기 떄문에 coin += baseGrid[i][j];도 가능
			}
		}
	}

	return coin;
}

int GetMaxCoin(const int& N, const int baseGrid[MAX_N][MAX_N])
{
	int maxCoin = 0;

	// N * N 격자를 순회
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i + 2 >= N || j + 2 >= N) continue;
			// 최대 동전수 갱신
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

	// 3*3 격자 내부에 존재할 수 있는 최대 동전 갯수를 반환
	int maxCoin = GetMaxCoin(N, baseGrid);

	cout << maxCoin;
}