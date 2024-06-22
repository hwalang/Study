#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

const int MAX_N = 20;
int grid[MAX_N][MAX_N];

// grid 밖으로 나가지 않으면 true
bool InRanged(int x, int y, int N)
{
	return y >= 0 && y < N && x >= 0 && x < N;
}

// 만들어진 직사각형에 존재하는 합
int GetSumOfRhombus(int x, int y, int len1, int len2, int N)
{
	// 1, 2, 3, 4번 이동 방향
	pair<int, int> dir[] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };

	int sum = 0;
	int nextX, nextY;
	int curX = x, curY = y;

	// 중복 코드를 하나로 합치기엔 반환값( next좌표와 sum값 )이 2개
	// 1번 방향
	for (int i = 1; i <= len1; ++i) {
		nextX = curX + dir[0].first;
		nextY = curY + dir[0].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 2번 방향
	for (int i = 1; i <= len2; ++i) {
		nextX = curX + dir[1].first;
		nextY = curY + dir[1].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 3번 방향
	for (int i = 1; i <= len1; ++i) {
		nextX = curX + dir[2].first;
		nextY = curY + dir[2].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 4번 방향
	for (int i = 1; i <= len2; ++i) {
		nextX = curX + dir[3].first;
		nextY = curY + dir[3].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	return sum;
}

// 현재 좌표에서 만들 수 있는 가장 큰 직사각형을 만든 뒤 최대합을 반환한다.
int GetMaxSumOfRhombus(int x, int y, int N)
{
	int maxSum = 0;

	// len1: 1, 3번 방향의 길이
	// len2: 2, 4번 방향의 길이 - 서로 같은 길이를 가짐
	for (int len1 = 1; len1 < N; ++len1) {
		for (int len2 = 1; len2 < N; ++len2) {
			maxSum = max(maxSum, GetSumOfRhombus(x, y, len1, len2, N));
		}
	}

	return maxSum;
}

int main()
{
	int N;
	cin >> N;

	for (int x = 0; x < N; ++x) {
		for (int y = 0; y < N; ++y) {
			cin >> grid[x][y];
		}
	}

	int maxSum = 0;

	// 최상단 + 그 밑, 최좌단, 최우단은 제외
	for (int x = 2; x < N; ++x) {
		for (int y = 1; y < N - 1; ++y) {
			maxSum = max(maxSum, GetMaxSumOfRhombus(x, y, N));
		}
	}

	cout << maxSum;
}