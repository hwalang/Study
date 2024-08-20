#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void InitPrefixSum(const vector<vector<int>>& grid, vector<vector<int>>& prefix)
{
	int N = grid.size();
	int M = grid[0].size();
	prefix.assign(N, vector<int>(M, 0));
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			prefix[y][x] = grid[y][x];
			if (y > 0) prefix[y][x] += prefix[y - 1][x];				// (y, x) + (y - 1, x)까지의 합
			if (x > 0) prefix[y][x] += prefix[y][x - 1];				// (y, x) + (y, x - 1)까지의 합
			if (y > 0 && x > 0) prefix[y][x] -= prefix[y - 1][x - 1];	// (y, x) - (y - 1, x - 1)까지의 합
		}
	}
}

// 구간 합
int GetSum(const vector<vector<int>>& prefix, int y1, int x1, int y2, int x2)
{
	int sum = prefix[y2][x2];
	if (y1 > 0) sum -= prefix[y1 - 1][x2];
	if (x1 > 0) sum -= prefix[y2][x1 - 1];
	if (y1 > 0 && x1 > 0) sum += prefix[y1 - 1][x1 - 1];
	return sum;
}

int GetMaxSum(const vector<vector<int>>& grid)
{
	int N = grid.size();
	int M = grid[0].size();

	vector<vector<int>> prefix;
	InitPrefixSum(grid, prefix);

	int maxSum = INT_MIN;

	// 첫 번째 직사각형
	for (int y1 = 0; y1 < N; ++y1) {
		for (int x1 = 0; x1 < M; ++x1) {
			for (int y2 = y1; y2 < N; ++y2) {
				for (int x2 = x1; x2 < M; ++x2) {
					int sumRect1 = GetSum(prefix, y1, x1, y2, x2);

					// 두 번째 직사각형
					for (int yy1 = 0; yy1 < N; ++yy1) {
						for (int xx1 = 0; xx1 < M; ++xx1) {
							for (int yy2 = yy1; yy2 < N; ++yy2) {
								for (int xx2 = xx1; xx2 < M; ++xx2) {
									if (yy1 > y2 || yy2 < y1 || xx1 > x2 || xx2 < x1) {
										int sumRect2 = GetSum(prefix, yy1, xx1, yy2, xx2);
										maxSum = max(maxSum, sumRect1 + sumRect2);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return maxSum;
}

int main()
{
	int N, M;
	cin >> N >> M;

	vector<vector<int>> grid(N, vector<int>(M));
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			cin >> grid[y][x];
		}
	}

	cout << GetMaxSum(grid);
}