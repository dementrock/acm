#include <stdio.h>
#include <string.h>
 
const int pow[] = {0,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912
};
const int powW[] = {0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
};
 
const int maxn = 103;
int n, color[maxn] = {0}, color_n, color_x, size[maxn << 1] = {0}, dpways[maxn][7] = {0}, answer_c;
bool edge[maxn][maxn] = {0}, dp[2][maxn] = {0}, answer_ok, answer[maxn];
 
int input() {
	scanf("%d", &n);
	int v;
	for (int u = 0; u < n; ++u)
		while (1) {
			scanf("%d", &v);
			if (!v)
				break;
			edge[u][v - 1] = 1;
		}
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < u; ++v)
			edge[u][v] = edge[v][u] = edge[u][v] && edge[v][u];
		edge[u][u] = 1;
	}
	return 0;
}
 
bool dye(int u) {
	int cx = color_x - color[u];
	for (int v = 0; v < n; ++v)
		if (!edge[u][v]) {
			if (color[v] == 0) {
				color[v] = cx;
				++size[cx];
				if (!dye(v))
					return false;
			} else if (color[v] != cx)
				return false;
		}
	return true;
}
 
bool work_dye() {
	color_n = 0;
	for (int i = 0; i < n; ++i)
		if (!color[i]) {
			color[i] = ++color_n;
			size[color_n] = 1;
			color_x = color_n + color_n + 1;
			if (!dye(i))
				return false;
			++color_n;
		}
	return true;
}
 
int work() {
	if (answer_ok = work_dye()) {
		dp[0][0] = true;
		int now = 0, pre = 1;
		for (int i = 1; i <= color_n; i += 2) {
			now = 1 - now;
			pre = 1 - pre;
			memset(dp[now], 0, sizeof(dp[now]));
			for (int j = n; j >= 0; --j)
				if (j - size[i] >= 0 && dp[pre][j - size[i]]) {
					dp[now][j] = true;
					memcpy(dpways[j], dpways[j - size[i]], sizeof(dpways[j]));
					dpways[j][powW[i]] |= pow[i];
				} else if (j - size[i+1] >= 0 && dp[pre][j - size[i+1]]) {
					dp[now][j] = true;
					memcpy(dpways[j], dpways[j - size[i+1]], sizeof(dpways[j]));
					dpways[j][powW[i+1]] |= pow[i+1];
				}
		}
		int arr[7];
		for (int i = n >> 1; i <= n; ++i)
			if (dp[now][i]) {
				memcpy(arr, dpways[i], sizeof(arr));
				break;
			} else if (n-i > 0 && dp[now][n-i]) {
				memcpy(arr, dpways[n-i], sizeof(arr));
				break;
			}
		answer_c = 0;
		for (int i = 0; i < n; ++i) {
			answer[i] = arr[powW[color[i]]] & pow[color[i]];
			answer_c += answer[i] ? 1 : 0;
		}
	}
	return 0;
}
 
int output() {
	if (answer_ok) {
		printf("%d", answer_c);
		for (int i = 0; i < n; ++i)
			if (answer[i])
				printf(" %d", i + 1);
		printf("\n%d", n - answer_c);
		for (int i = 0; i < n; ++i)
			if (!answer[i])
				printf(" %d", i + 1);
		printf("\n");
	} else
		printf("No solution\n");
	return 0;
}
 
int main() {
	
	input();
	work();
	output();
	return 0;
}
