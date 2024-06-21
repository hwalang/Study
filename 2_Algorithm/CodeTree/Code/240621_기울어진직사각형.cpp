#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

const int MAX_N = 20;
int grid[MAX_N][MAX_N];

// grid ������ ������ ������ true
bool InRanged(int x, int y, int N)
{
	return y >= 0 && y < N && x >= 0 && x < N;
}

// ������� ���簢���� �����ϴ� ��
int GetSumOfRhombus(int x, int y, int len1, int len2, int N)
{
	// 1, 2, 3, 4�� �̵� ����
	pair<int, int> dir[] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };

	int sum = 0;
	int nextX, nextY;
	int curX = x, curY = y;

	// �ߺ� �ڵ带 �ϳ��� ��ġ�⿣ ��ȯ��( next��ǥ�� sum�� )�� 2��
	// 1�� ����
	for (int i = 1; i <= len1; ++i) {
		nextX = curX + dir[0].first;
		nextY = curY + dir[0].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 2�� ����
	for (int i = 1; i <= len2; ++i) {
		nextX = curX + dir[1].first;
		nextY = curY + dir[1].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 3�� ����
	for (int i = 1; i <= len1; ++i) {
		nextX = curX + dir[2].first;
		nextY = curY + dir[2].second;
		if (!InRanged(nextX, nextY, N)) return -1;

		sum += grid[nextX][nextY];
		curX = nextX;
		curY = nextY;
	}

	// 4�� ����
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

// ���� ��ǥ���� ���� �� �ִ� ���� ū ���簢���� ���� �� �ִ����� ��ȯ�Ѵ�.
int GetMaxSumOfRhombus(int x, int y, int N)
{
	int maxSum = 0;

	// len1: 1, 3�� ������ ����
	// len2: 2, 4�� ������ ���� - ���� ���� ���̸� ����
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

	// �ֻ�� + �� ��, ���´�, �ֿ���� ����
	for (int x = 2; x < N; ++x) {
		for (int y = 1; y < N - 1; ++y) {
			maxSum = max(maxSum, GetMaxSumOfRhombus(x, y, N));
		}
	}

	cout << maxSum;
}