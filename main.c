/*day 1*/
#if 0
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define STRSIZE 20
#define LINKSIZE 4

int link1, link2;
int arr1[LINKSIZE], arr2[LINKSIZE];

void link_print(int linksize, int num, int link_array[])
{
	for (int i = 0;;) {
		for (int j = i + 1; ;) {
			printf("[%d", link_array[i]);
			for (int k = j;; k++) {
				if (k - j < num - 1)
					printf(",%d", link_array[k]);
				else {
					printf("]");
					break;
				}
			}
			if (++j <= linksize - num + 1 && j < linksize)
				printf(",");
			else
				break;
		}
		if (++i <= linksize - num)
			printf(",");
		else
			break;
	}
}

void chip_set(int link, int num)
{
	if (link == 1)
		link_print(link1, num, arr1);
	else if (link == 2)
		link_print(link2, num, arr2);
}
void set_select(int is_odd1, int is_odd2, int odd_even,int num)
{
	if (is_odd1 ^ is_odd2) {
		if (odd_even)
			chip_set(1, num);
		else
			chip_set(2, num);
	}
	else {
		if (link1 < link2)
			chip_set(1, num);
		else if (link2 < link1)
			chip_set(2, num);
		else {
			chip_set(1, num);
			printf(",");
			chip_set(2, num);
		}
	}
}
char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char array[STRSIZE];
	char* end;
	int num,temp;

	end = s_gets(array, STRSIZE);
	scanf("%d", &num);

	while ((*end) && !isdigit(*end))end++;
	while (*end != '\0') {
		temp = strtol(end, &end, 10);
		if (temp > 3)
			arr2[link2++] = temp;
		else
			arr1[link1++] = temp;
		while ((*end) && !isdigit(*end))end++;
	}

	printf("[");
	if (num == 8 && link1 == 4 && link2 == 4) {
		for (int i = 0; i < 8; i++) {
			printf("%d", i);
			if (i == 7) {
				printf("]\n");
				return 0;
			}
			else
				printf(",");
		}
	}
	if (link1 < num && link2 < num) {
		printf("]\n");
		return 0;
	}
	else if (link1 < num) {
		chip_set(2, num);
	}
	else if (link2 < num) {
		chip_set(1, num);
	}
	else {
		int is_odd1 = link1 & 0x1;
		int is_odd2 = link2 & 0x1;
		switch (num) {
		case 1:
			set_select(is_odd1, is_odd2, is_odd1, num);
			break;

		case 2:
			set_select(is_odd1, is_odd2, is_odd2, num);
			break;

		case 4:
			chip_set(1, num);
			printf(",");
			chip_set(2, num);
			break;

		default:
			break;
		}
	}
	printf("]\n");
	return 0;
}
#endif

/*day 2*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

void savetime(Item item, int* time)
{
	static int count = 0;
	time[count++] = item.time;
}
int main(void)
{
	int taskA, taskB, mid, num;
	scanf_s("%d ,%d ,%d", &taskA, &taskB, &num);

	Tree timetree;
	Item* item = (Item*)malloc(sizeof(Item)*(num+1));

	mid = num / 2;
	InitializeTree(&timetree);
	for (int i = mid; i >= 0; i--) {
		item[i].time = i * taskA + (num - i) * taskB;
		AddItem(item + i, &timetree);
	}
	for (int j = mid + 1; j <= num; j++) {
		item[j].time = j * taskA + (num - j) * taskB;
		AddItem(item + j, &timetree);
	}
	int* time = (int*)malloc(sizeof(int) * timetree.size);
	Traverse(&timetree,time, savetime);
	printf("[");
	for (int i = 0; i < timetree.size; i++) {
		printf("%d",time[i]);
		if (i == timetree.size - 1)
			printf("]\n");
		else
			printf(",");
	}
	free(time);
	free(item);
	DeleteAll(&timetree);
	return 0;
}
#endif

/*day 3*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#define DAYSPERMONTH 30

typedef struct {
	int id;
	int insnum;
	int est;
}Staff;

InitializeStaff(Staff* staff, int n)
{
	for (int i = 0; i < n; i++) {
		staff[i].id = i;
		staff[i].insnum = 0;
		staff[i].est = 0;
	}
}

int compare(const void* a, const void* b)
{
	int ins1 = ((Staff*)a)->insnum;
	int ins2 = ((Staff*)b)->insnum;
	if (ins1 < ins2)
		return 1;
	else if (ins1 > ins2)
		return -1;
	else {
		int e1 = ((Staff*)a)->est;
		int e2 = ((Staff*)b)->est;
		if (e1 < e2)
			return -1;
		else if (e1 > e2)
			return 1;
		else {
			int id1 = ((Staff*)a)->id;
			int id2 = ((Staff*)b)->id;
			if (id1 < id2)
				return -1;
			else
				return 1;
		}
	}
}
int main(void)
{
	int num, count;
	int dayins[DAYSPERMONTH];
	scanf_s("%d", &num);
	for (int i = 0; i < DAYSPERMONTH; i++) {
		scanf_s("%d", dayins + i);
	}
	Staff* staff = (Staff*)malloc(sizeof(Staff) * num);
	InitializeStaff(staff, num);

	for (int i = 0; i < DAYSPERMONTH; i++) {
		for (int j = 0; j < dayins[i]; j++) {
			scanf_s("%d", &count);
			staff[count].insnum++;
			if (staff[count].est == 0)
				staff[count].est = i + 1;
		}
	}
	qsort((void*)staff, num, sizeof(Staff), compare);
	if (num < 5)
		for (int i = 0; i < num; i++) {
			printf("%d ", staff[i].id);
			if (i == num - 1)
				printf("\n");
		}
	else
		for (int j = 0; j < 5; j++) {
			printf("%d ", staff[j].id);
			if (j == 4)
				printf("\n");
		}
	free(staff);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int rl, rw, sl, need;
	int really = 0;
	int count = 0;
	scanf_s("%d %d %d %d", &rl, &rw, &sl, &need);
	int** powerec = (int**)malloc(rl * sizeof(int*));
	for (int i = 0; i < rl; i++)
		powerec[i] = (int*)malloc(rw * sizeof(int));
	for (int i = 0; i < rl; i++)
		for (int j = 0; j < rw; j++)
			scanf_s("%d", &powerec[i][j]);

	for (int i = 0; i <= rl - sl; i++) {
		for (int j = 0; j <= rw - sl; j++) {
			really = 0;
			for (int k = i; k - i < sl; k++) {
				for (int s = j; s - j < sl; s++) {
					really += powerec[k][s];
				}
			}
			if (really >= need)
				count++;
		}
	}
	for (int i = 0; i < rl; i++)
		free(powerec[i]);
	free(powerec);
	printf("%d\n", count);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 99
#define LETTERSNUM 26

int compare_strings(const void* a, const void* b)
{
	char* str1 = (char*)a;
	char* str2 = (char*)b;
	return strcmp(str1, str2);
}

void collect_words(char** destination, char* source, int* count)
{
	char* start = source;
	char* end = source;
	while (*end != '\0') {
		if (*end == ' ') {
			*end = '\0';
			destination[(*count)++] = start;
			start = end + 1;
		}
		end++;
	}
	destination[(*count)++] = start;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}
int main(void)
{
	char* newspaper[N];
	char* anonymousLetter[N];
	char newspapers[N * LETTERSNUM],anonymousLetters[N * LETTERSNUM];
	int count1 = 0, count2 = 0;
	int found = 0;

	s_gets(newspapers, N * LETTERSNUM);
	s_gets(anonymousLetters, N * LETTERSNUM);
	collect_words(newspaper, newspapers, &count1);
	collect_words(anonymousLetter, anonymousLetters, &count2);

	for (int i = 0; i < count1; i++) {
		qsort((void*)newspaper[i], strlen(newspaper[i]), sizeof(char), compare_strings);
	}
	for (int j = 0; j < count2; j++) {
		qsort((void*)anonymousLetter[j], strlen(anonymousLetter[j]), sizeof(char), compare_strings);
	}

	for (int i = 0; i < count2; i++) {
		for (int j = 0; j < count1; j++) {
			if (!strcmp(anonymousLetter[i], newspaper[j])) {
				found++;
				break;
			}
		}
	}
	
	if (found == count2)
		printf("true\n");
	else
		printf("false\n");

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define N 100

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char reverse_str[N];
	char posive_str[N] = { 0 };
	char* start = s_gets(reverse_str, N);
	char* end = start;
	char* p = posive_str;

	while (*end != '\0') {
		if (!isalpha(*end)) {
			for (char* temp = end - 1; temp >= start; temp--) {
				*p++ = *temp;
			}
			if (isalpha(*(end + 1))) {
				*p++ = *end;
				start = end + 1;
				end += 2;
			}
			else
			{
				*p++ = *end;
				*p++ = *(end + 1);
				*p++ = *(end + 2);
				if (*(end + 2) == '\0')
					break;
				end += 3;
				start = end;
			}
		}
		else
			end++;
	}
	printf("%s\n", posive_str);
	return 0;
}
#endif

/*TSP!!!*/
#if 0
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 20
#define INF 1000000000

int n;
int dist[MAXN][MAXN];
int dp[1 << MAXN][MAXN];

int tsp() {
	int full = (1 << n);

	// 初始化 DP
	for (int i = 0; i < full; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INF;

	dp[1][0] = 0; // 从顶点0出发，只访问0

	// 状态压缩DP
	for (int mask = 1; mask < full; mask++) {
		for (int u = 0; u < n; u++) {
			if (!(mask & (1 << u))) continue;      // u 不在集合里
			if (dp[mask][u] == INF) continue;

			for (int v = 0; v < n; v++) {
				if (mask & (1 << v)) continue;    // v 已经访问过
				int next = mask | (1 << v);
				if (dp[next][v] > dp[mask][u] + dist[u][v])
					dp[next][v] = dp[mask][u] + dist[u][v];
			}
		}
	}

	// 回到起点 0
	int ans = INF;
	int final_mask = full - 1;  // 所有点都访问完

	for (int u = 1; u < n; u++) {
		if (dp[final_mask][u] < INF) {
			int cost = dp[final_mask][u] + dist[u][0];
			if (cost < ans)
				ans = cost;
		}
	}

	return ans;
}

int main() {
	printf("输入节点数 n（≤20）:\n");
	scanf("%d", &n);

	printf("输入邻接矩阵 dist[i][j]:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &dist[i][j]);

	int ans = tsp();
	printf("最短回路长度 = %d\n", ans);
	return 0;
}
#endif

/*day 4*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXSTRINGS 100
char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	int i, j, k, start, length, maxlength;
	char text1[MAXSTRINGS], text2[MAXSTRINGS];

	s_gets(text1, MAXSTRINGS);
	s_gets(text2, MAXSTRINGS);
	k = j = start = 0;
	i = k;
	length = maxlength = 0;
	while (text1[k] != '\0') {
		while (text1[i++] == text2[j++]) {
			length++;
			if (text1[i] == '\0' || text2[j] == '\0')
				break;
		}
		if (text1[i] == '\0' || text2[j] == '\0') {
			if (length > maxlength) {
				maxlength = length;
				start = j - length;
			}
			i = ++k;
			j = 0;
		}
		else {
			if (length > maxlength) {
				maxlength = length;
				start = j - length - 1;
			}
		}
		length = 0;
	}
	
	for (int n = 0; n < maxlength; n++)
		putchar(text2[start + n]);

	printf("\n");
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAXFIRSTSTR 100000
#define MAXSECONDSTR 500

int compare_str(const void* a, const void* b)
{
	char* ch1 = (char*)a;
	char* ch2 = (char*)b;

	return (*ch1 - *ch2);
}

int findiffwords(char* increastr)
{
	int count = 0;
	char prev = '\0';
	char* end = increastr;
	while (*end != '\0') {
		if (*end != prev) {
			count++;
			prev = *end;
		}
		end++;
	}

	return count;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	int strnum = 0;
	char firststr[MAXFIRSTSTR], secondstr[MAXSECONDSTR];
	char* strset[MAXFIRSTSTR / 2];

	char* end = s_gets(firststr, MAXFIRSTSTR);
	s_gets(secondstr, MAXSECONDSTR);
	char* start = end;

	while (*end != '\0') {
		if (strchr("abcdef", *end) || isdigit(*end)) {
			*end = '\0';
			if (*start != '\0') {
				strset[strnum++] = start;
				start = end + 1;
			}
			else
				start = end + 1;
		}
		end++;
	}
	strset[strnum++] = start;

	char* temp = (char*)malloc(MAXFIRSTSTR * sizeof(char));
	int* countstr = (int*)calloc(strnum, sizeof(int));
	int* idset = (int*)calloc(strnum, sizeof(int));

	for (int i = 0; i < strnum; i++) {
		if (!strcpy(temp, strset[i]))
			continue;
		qsort((void*)temp, strlen(temp), sizeof(char), compare_str);
		countstr[i] = findiffwords(temp);
	}
	qsort((void*)secondstr, strlen(secondstr), sizeof(char), compare_str);
	int con = findiffwords(secondstr);
	int dismin = INT_MAX, dis = 0, num = 0;
	for (int i = 0; i < strnum; i++) {
		if ((dis = con - countstr[i]) >= 0) {
			if (dis <= dismin) {
				dismin = dis;
				idset[num++] = i;
			}
		}
	}
	if (num > 0) {
		char* result = strset[idset[0]];
		for (int j = 1; j < num; j++) {
			if (strcmp(strset[idset[j]], result))
				result = strset[idset[j]];
		}
		printf("%s\n", result);
	}
	else
		printf("Not Found\n");
	free(idset);
	free(countstr);
	free(temp);

	return 0;
}
#endif

/*day 5*/
#if 0
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

int findBR(int n, uint64_t k)
{
	uint64_t numofrows = 1ULL << (n - 1);
	if (numofrows == 1)
		return 0;
	else {
		if (k < numofrows / 2) {
			if (findBR(n - 1, k))
				return 0;
			else
				return 1;
		}
		else {
			if (findBR(n - 1, k - numofrows / 2))
				return 1;
			else
				return 0;
		}
	}
}

int main(void)
{
	int T;
	scanf_s("%d", &T);

	int* n = (int*)malloc(T * sizeof(int));
	uint64_t* k = (uint64_t*)malloc(T * sizeof(uint64_t));
	for (int i = 0; i < T; i++) {
		scanf_s("%d %llud", &n[i], &k[i]);
	}
	for (int i = 0; i < T; i++) {
		
		if (findBR(n[i], k[i]))
			printf("blue\n");
		else
			printf("red\n");
	}
	free(k);
	free(n);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define	N 10000
#define MAXLEN 50
#define ALPHAKINDS 26

char* OrganizeStr(char* source)
{
	char* end = source;
	while (*end != '\0' && !isalpha(*end))
		end++;
	char* start = end;
	int notstrnum = 0;
	while (*end != '\0') {
		if (isalpha(*end)) {
			*end = tolower(*end);
			if (notstrnum > 0) {
				strcat(start, end);
				end = end - notstrnum;
				notstrnum = 0;
			}
		}
		else {
			*end = '\0';
			notstrnum++;
		}
		end++;
	}
	return start;
}

int compare_str(const void* a, const void* b)
{
	char* ch1 = (char*)a;
	char* ch2 = (char*)b;

	return *ch1 - *ch2;
}

int main(void)
{
	char key[ALPHAKINDS];
	int boxes = 0, id = -1;
	char** strset = (char**)malloc(N * sizeof(char*));
	for (int i = 0; i < N; i++)
		strset[i] = (char*)malloc(MAXLEN * sizeof(char));

	scanf_s("%s", key, ALPHAKINDS);
	for (int i = 0; i < N; i++) {
		scanf_s("%s", strset[i], MAXLEN);
		boxes++;
		if (getchar() == ' ')
			continue;
		else
			break;
	}

	char** temp = (char**)malloc(boxes * sizeof(char*));

	for (int j = 0; j < boxes; j++) {
		temp[j] = OrganizeStr(strset[j]);
		qsort((void*)temp[j], strlen(temp[j]), sizeof(char), compare_str);
	}

	for (int i = 0; i < boxes; i++) {
		if (!strcmp(temp[i], key)) {
			id = i + 1;
			break;
		}
	}

	printf("%d\n", id);

	free(temp);
	for (int i = 0; i < N; i++)
		free(strset[i]);
	free(strset);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXPAGENUM 105
#define MAXPASSWORDLEN 105

typedef struct {
	char* str;
	int len;
}Password;

int compare_password(const void* a, const void* b)
{
	Password* password1 = (Password*)a;
	Password* password2 = (Password*)b;
	if (password1->len < password2->len)
		return 1;
	else if (password1->len > password2->len)
		return -1;
	else
		return strcmp(password2->str, password1->str);
}
int main(void)
{
	int count, curlen, templen;
	char** string = (char**)malloc(MAXPAGENUM * sizeof(char*));
	for (int i = 0; i < MAXPAGENUM; i++)
		string[i] = (char*)calloc(MAXPASSWORDLEN, sizeof(char));
	count = curlen = templen = 0;

	for (int j = 0; j < MAXPAGENUM; j++) {
		scanf_s("%s", string[j], MAXPASSWORDLEN);
		count++;
		if (getchar() == ' ')
			continue;
		else
			break;
	}

	Password* passwords = (Password*)malloc(count * sizeof(Password));
	for (int i = 0; i < count; i++) {
		passwords[i].str = string[i];
		passwords[i].len = (int)strlen(string[i]);
	}

	qsort((void*)passwords, count, sizeof(Password), compare_password);

	int match;

	for (int i = 0; i < count; i++) {
		curlen = passwords[i].len;
		match = 0;
		for (int j = i + 1; j < count; j++) {
			templen = passwords[j].len;
			if (templen == curlen)
				continue;
			if (templen < curlen-1)
				break;
			if (!strncmp(passwords[i].str, passwords[j].str, curlen - 1)) {
				match++;
				curlen--;
			}
		}
		if (match > 0 && match == passwords[i].len - 1) {
			printf("%s", passwords[i].str);
			break;
		}
	}
	printf("\n");

	free(passwords);
	for (int i = 0; i < MAXPAGENUM; i++)
		free(string[i]);
	free(string);

	return 0;
}
#endif

/*day 6*/
#if 0
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int head, nodenum;
	int next, visited, size;
	scanf_s("%d %d", &head, &nodenum);
	int* list = (int*)malloc(nodenum * sizeof(int));
	int** listdata = (int**)malloc(nodenum * sizeof(int*));
	for (int i = 0; i < nodenum; i++)
		listdata[i] = (int*)malloc(3 * sizeof(int));

	for (int j = 0; j < nodenum; j++) {
		scanf_s("%d %d %d", listdata[j], listdata[j] + 1, listdata[j] + 2);
	}

	next = head;
	size = 0;
	visited = -1;
	for (int i = 0; i != visited; i = (i + 1) % nodenum) {
		if (listdata[i][0] == next) {
			visited = i;
			list[size++] = listdata[i][1];
			next = listdata[i][2];
			if (next == -1)
				break;
		}
	}
	if (size > 0)
		printf("%d\n", list[size / 2]);
	for (int i = 0; i < nodenum; i++)
		free(listdata[i]);
	free(listdata);
	free(list);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXN 100
#define MAXM 100

short matrix[MAXN][MAXM];

void dfs(int n, int m)
{
	int row, col;
	if (n - 1 < 0)
		row = n;
	else
		row = n - 1;
	if (m - 1 < 0)
		col = m;
	else
		col = m - 1;
	matrix[n][m] = (short)0;
	for (int i = row; i < 2 + n; i++) {
		for (int j = col; j < 2 + m; j++) {
			if (matrix[i][j])
				dfs(i, j);
		}
	}
}

int main(void)
{
	int clicks = 0;
	int N, M;

	scanf_s("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf_s("%hd", &matrix[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (matrix[i][j]) {
				dfs(i, j);
				clicks++;
			}
		}
	}

	printf("%d\n", clicks);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
	int id;
	int time;
	int distance;
	char actualDeviceNumber[5];
	char registeredDeviceNumber[5];
}ClockRecords;

int main(void)
{
	int N, currid;
	int samerecords;
	int maxidx = -1;
	scanf_s("%d", &N);
	ClockRecords* clockrecords = (ClockRecords*)malloc(N * sizeof(ClockRecords));
	bool* vaild = (bool*)malloc(N * sizeof(bool));
	int* staffid = (int*)malloc(N * sizeof(int));
	int* visited = (int*)calloc(N, sizeof(int));

	for (int i = 0; i < N; i++) {
		scanf_s("%d ,%d ,%d ,%4s ,%4s", &clockrecords[i].id, &clockrecords[i].time, &clockrecords[i].distance,
			clockrecords[i].actualDeviceNumber, 5, clockrecords[i].registeredDeviceNumber, 5);
		vaild[i] = true;
	}
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			samerecords = 0;
			staffid[samerecords++] = i;
			currid = clockrecords[i].id;
			for (int j = i + 1; j < N; j++) {
				if (!visited[j]) {
					if (clockrecords[j].id == currid) {
						staffid[samerecords++] = j;
						visited[j] = 1;
					}
				}
			}
			for (int k = 0; k < samerecords; k++) {
				if (strcmp(clockrecords[staffid[k]].actualDeviceNumber, clockrecords[staffid[k]].registeredDeviceNumber)) {
					vaild[staffid[k]] = false;
					maxidx = (staffid[k] > maxidx) ? staffid[k] : maxidx;
				}
				for (int s = k + 1; s < samerecords; s++) {
					if (abs(clockrecords[staffid[k]].time - clockrecords[staffid[s]].time) < 60 &&
						abs(clockrecords[staffid[k]].distance - clockrecords[staffid[s]].distance) > 5) {
						if (vaild[staffid[k]]) {
							vaild[staffid[k]] = false;
							maxidx = (staffid[k] > maxidx) ? staffid[k] : maxidx;
						}
						if (vaild[staffid[s]]) {
							vaild[staffid[s]] = false;
							maxidx = (staffid[s] > maxidx) ? staffid[s] : maxidx;
						}
					}
				}
			}
			visited[i] = 1;
		}
	}

	if (maxidx < 0)
		printf("null\n");
	else {
		for (int i = 0; i <= maxidx; i++) {
			if (!vaild[i])
				printf("%d,%d,%d,%s,%s", clockrecords[i].id, clockrecords[i].time, clockrecords[i].distance,
					clockrecords[i].actualDeviceNumber, clockrecords[i].registeredDeviceNumber);
			if (i == maxidx)
				printf("\n");
			else
				printf(";");
		}
	}
	free(visited);
	free(staffid);
	free(vaild);
	free(clockrecords);
	return 0;
}
#endif

/*day 7*/
#if 0
#include<stdio.h>
#include<stdlib.h>

int dfs(int** usetime, int n, int k)
{
	int maxtime = 0;
	for (int i = 0; i < n; i++) {
		if (i != k && usetime[k][i] == 1) {
			int time = dfs(usetime, n, i);
			if (time > maxtime)
				maxtime = time;
		}
	}

	return maxtime + usetime[k][k];
}
int main(void)
{
	int n, k;
	int leastime;
	scanf_s("%d", &n);

	int** useTime = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		useTime[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			scanf_s("%d", useTime[i] + j);
		}
	}
	scanf_s("%d", &k);

	leastime = dfs(useTime, n, k - 1);

	printf("%d\n", leastime);

	for (int i = 0; i < n; i++)
		free(useTime[i]);
	free(useTime);

	return 0;
}
#endif

# if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAXFILES 1000
#define MAXPRINTERS 5
#define MAXSTRS 20

typedef struct {
	int num;
	int priority;
}File;

typedef struct {
	int size;
	File file[MAXFILES];
}Printer;

int compare_file(const void* a, const void* b)
{
	File* f1 = (File*)a;
	File* f2 = (File*)b;
	if (f1->priority > f2->priority)
		return 1;
	else if (f1->priority < f2->priority)
		return -1;
	else
		return (f2->num - f1->num);
}
char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	int N, pid;
	int count = 0;
	char* end;
	Printer* printer = (Printer*)calloc(MAXPRINTERS , sizeof(Printer));

	scanf_s("%d", &N);
	while (getchar() != '\n')
		continue;

	char** event = (char**)malloc(N * sizeof(char*));
	for (int i = 0; i < N; i++) {
		event[i] = (char*)malloc(MAXSTRS * sizeof(char));
		s_gets(event[i], MAXSTRS);
	}

	for (int i = 0; i < N; i++) {
		end = event[i];
		while (!isdigit(*end))
			end++;
		pid = (int)strtol(end, &end, 10);

		if (strncmp(event[i], "IN", 2)) {
			if (printer[pid - 1].size > 0) {
				qsort((void*)printer[pid - 1].file, printer[pid - 1].size, sizeof(File), compare_file);
				printf("%d\n", printer[pid - 1].file[--printer[pid - 1].size].num);
			}
			else
				printf("NULL\n");
		}
		else {
			printer[pid - 1].file[printer[pid - 1].size].num = ++count;
			while (!isdigit(*end))
				end++;
			printer[pid - 1].file[printer[pid - 1].size].priority = strtol(end, &end, 10);
			printer[pid - 1].size++;
		}
	}

	for (int j = 0; j < N; j++)
		free(event[j]);
	free(event);
	free(printer);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<string.h>
#define MAXCARS 100000
#define COLORKINDS 3

int main(void)
{
	int cars[MAXCARS];
	int freq[COLORKINDS] = { 0 };
	int count = 0, maxfreq = 0;
	int time_windows;
	while (1) {
		scanf_s("%d", cars + count);
		count++;
		if (getchar() == ' ')
			continue;
		else
			break;
	}
	scanf_s("%d", &time_windows);
	if (count < time_windows) {
		memset(freq, 0, sizeof(freq));
		for (int i = 0; i < count; i++)
			freq[cars[i]]++;
		for (int j = 0; j < count; j++) {
			if (freq[cars[j]] > maxfreq)
				maxfreq = freq[cars[j]];
		}
	}
	else {
		for (int i = time_windows - 1; i < count; i++) {
			memset(freq, 0, sizeof(freq));
			int start = i + 1 - time_windows;
			for (int j = start; j <= i; j++) {
				freq[cars[j]]++;
			}
			for (int k = start; k <= i; k++)
				if (freq[cars[k]] > maxfreq)
					maxfreq = freq[cars[k]];
		}
	}
	printf("%d\n", maxfreq);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
	int n, m, mindis;
	scanf_s("%d %d", &n, &m);
	int** nums = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		nums[i] = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++) {
			scanf_s("%d", nums[i]+j);
		}
	}
	int** dis = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		dis[i] = (int*)malloc(m * sizeof(int));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mindis = INT_MAX;
			for (int k = 0; k < n; k++) {
				for (int s = 0; s < m; s++) {
					if (k == i && s == j)
						continue;
					if (nums[k][s] == nums[i][j]) {
						mindis = min((abs(k - i) + abs(s - j)), mindis);
					}
				}
			}
			if (mindis == INT_MAX)
				dis[i][j] = -1;
			else
				dis[i][j] = mindis;
		}
	}
	printf("[");
	for (int i = 0; i < n; i++) {
		printf("[");
		for (int j = 0; j < m; j++) {
			printf("%d", dis[i][j]);
			if (j == m - 1)
				printf("]");
			else
				printf(",");
		}
		if (i == n - 1)
			printf("]\n");
		else
			printf(",");
	}
	for (int j = 0; j < n; j++)
		free(dis[j]);
	free(dis);
	for (int j = 0; j < n; j++)
		free(nums[j]);
	free(nums);

	return 0;
}
#endif

/*day 8*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXRECORDS 1000

typedef struct {
	int size;
	short data[MAXRECORDS];
}Stack;

bool Push(Stack* stack, int digit)
{
	if (stack->size == MAXRECORDS) {
		fprintf(stderr, "Stack is full!\n");
		return false;
	}
	stack->data[stack->size++] = (short)digit;
	return true;
}

bool Pop(Stack* stack)
{
	if (stack->size == 0) {
		fprintf(stderr, "Stack is null!\n");
		return false;
	}
	stack->size--;
	return true;
}

void InitStack(Stack* stack)
{
	stack->size = 0;
}

int DataSum(Stack* stack)
{
	int sum = 0;
	for (int i = 0; i < stack->size; i++) {
		sum += (int)stack->data[i];
	}
	return sum;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char ops[MAXRECORDS];
	Stack digitstack;
	int nextdata;
	s_gets(ops, MAXRECORDS + 1);

	char* end = ops;
	InitStack(&digitstack);

	while (*end != '\0') {
		switch (*end) {
		case 'C':
			if (digitstack.size < 1) {
				printf("-1\n");
				return -1;
			}
			if (!Pop(&digitstack)) {
				printf("-1\n");
				return -1;
			}
			end++;
			break;

		case 'D':
			if (digitstack.size < 1) {
				printf("-1\n");
				return -1;
			}
			nextdata = 2 * digitstack.data[digitstack.size - 1];
			if (nextdata < -312 || nextdata>312) {
				printf("-1\n");
				return -1;
			}
			if (!Push(&digitstack, nextdata)) {
				printf("-1\n");
				return -1;
			}
			end++;
			break;

		case '+':
			if (digitstack.size < 2) {
				printf("-1\n");
				return -1;
			}
			nextdata = digitstack.data[digitstack.size - 1] + digitstack.data[digitstack.size - 2];
			if (nextdata < -312 || nextdata>312) {
				printf("-1\n");
				return -1;
			}
			if (!Push(&digitstack, nextdata)) {
				printf("-1\n");
				return -1;
			}
			end++;
			break;

		case ' ':
			end++;
			break;

		default:
			nextdata = strtol(end, &end, 10);
			if (nextdata < -312 || nextdata>312) {
				printf("-1\n");
				return -1;
			}
			if (!Push(&digitstack, nextdata)) {
				printf("-1\n");
				return -1;
			}
		}
	}
	int sum = DataSum(&digitstack);
	printf("%d\n", sum);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#define MAXNUMS 1024

int findmidpos(unsigned int nums[], int n)
{
	int i = 0;
	int j = n - 1;
	unsigned int prevleft, prevright;
	prevleft = prevright = 1U;
	while (j - i >= 2) {
		if (nums[i] * prevleft > nums[j] * prevright) {
			prevright = nums[j] * prevright;
			j--;
		}
		else if (nums[i] * prevleft < nums[j] * prevright) {
			prevleft = nums[i] * prevleft;
			i++;
		}
		else {
			if (j - i == 2)
				return i + 1;
			else {
				prevright = nums[j] * prevright;
				j--;
			}
		}
	}
	return -1;
}

int main(void)
{
	unsigned int nums[MAXNUMS];
	int n = 0;
	for (int i = 0; i < MAXNUMS; i++) {
		scanf_s("%d", nums + i);
		n++;
		if (getchar() == ' ')
			continue;
		else
			break;
	}
	printf("%d\n", findmidpos(nums, n));

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXCARDS 1000
#define KARDKINDS 13

typedef struct {
	int id;
	int nums;
}Kards;

void InitKards(Kards* kards, int n)
{
	for (int i = 0; i < n; i++) {
		kards[i].id = 0;
		kards[i].nums = 0;
	}
}

int compare_kards(const void* a, const void* b)
{
	Kards* kard1 = (Kards*)a;
	Kards* kard2 = (Kards*)b;
	if (kard1->nums > kard2->nums)
		return -1;
	else if (kard1->nums < kard2->nums)
		return 1;
	else
		return kard2->id - kard1->id;
}

int compare_single(const void* a, const void* b)
{
	int* kard1 = (int*)a;
	int* kard2 = (int*)b;
	return *kard2 - *kard1;
}

int main(void)
{
	int kardid;
	int isthree = 0;
	int  nums = 0;
	int single[MAXCARDS] = { 0 };
	Kards kards[KARDKINDS];

	InitKards(kards, KARDKINDS);

	while (1) {
		scanf_s("%d", &kardid);
		kards[kardid - 1].id = kardid;
		kards[kardid - 1].nums++;
		if (getchar() == ' ')
			continue;
		else
			break;
	}

	qsort((void*)kards, KARDKINDS, sizeof(Kards), compare_kards);

	for (int i = 0; i < KARDKINDS; i++) {
		if (!kards[i].id)
			break;
		if (kards[i].nums == 3) {
			isthree ^= 1;
			if (!isthree) {
				kards[i].nums--;
				single[nums++] = kards[i].id;
			}
		}
		if(kards[i].nums==1)
			single[nums++] = kards[i].id;
	}

	qsort((void*)single, nums, sizeof(int), compare_single);

	for (int i = 0; i < KARDKINDS; i++) {
		if (kards[i].nums > 1) {
			for (int j = 0; j < kards[i].nums; j++)
				printf("%d ", kards[i].id);
		}
		else
			break;
	}
	for (int i = 0; i < nums; i++) {
		printf("%d", single[i]);
		if (i == nums - 1)
			printf("\n");
		else
			printf(" ");
	}

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXSTATIONS 100000

int main(void)
{
	int* stations = (int*)malloc(MAXSTATIONS * sizeof(int));
	int size = 0;
	int i, j, l_friendliness, r_friendliness;
	int max_friendliness = 0;

	while (1) {
		scanf_s("%d", &stations[size++]);
		if (getchar() == ' ')
			continue;
		else
			break;
	}
	stations[size++] = 2;//when end is 0,conut maxfriendliness

	i = l_friendliness = r_friendliness = 0;

	while (i < size - 1) {
		if (stations[i] == 0) {
			for (j = i + 1; j < size; j++) {
				if (stations[j] != 1) {
					max_friendliness = max(l_friendliness + r_friendliness, max_friendliness);
					if (stations[j] == 0) {
						l_friendliness = r_friendliness;
						r_friendliness = 0;
						i = j;
					}
					else {
						l_friendliness = r_friendliness = 0;
						i = j + 1;
					}
					break;
				}
				else
					r_friendliness++;
			}
			continue;
		}
		else if (stations[i] == 1) {
			l_friendliness++;
		}
		else {
			l_friendliness = 0;
		}
		i++;
	}

	printf("%d\n", max_friendliness);

	free(stations);
	return 0;
}
#endif

/*day 9*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXLOGS 1000

int main(void)
{
	int logs[MAXLOGS];
	int nums = 0;
	int maxpoint = 0;
	int allogs = 0;
	int negativepoint;

	while (1) {
		scanf_s("%d", &logs[nums++]);
		if (getchar() == ' ')
			continue;
		else
			break;
	}

	for (int i = 0; i < nums; i++) {
		negativepoint = 0;
		unsigned int k = 1;
		for (int j = i - 2; j >= 0; j--) {
			negativepoint += (++k) * logs[j];
		}
		if (allogs + logs[i] >= 100) {
			maxpoint = max(100 - allogs - negativepoint, maxpoint);
			break;
		}
		else {
			allogs += logs[i];
			maxpoint = max(logs[i] - negativepoint, maxpoint);
		}
	}

	printf("%d\n", maxpoint);

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

bool IsBisected(int score[], int n, int gpa)
{
	int count = 0;
	int reminder = 0;
	int* todie = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		if (score[i] == INT_MIN)
			continue;
		if (score[i] > gpa) {
			free(todie);
			return false;
		}
		reminder = gpa - score[i];
		if (reminder != 0) {
			for (int j = i + 1; j < n; j++) {
				if (score[j] != INT_MIN && score[j] <= reminder) {
					reminder -= score[j];
					todie[count++] = j;
					if (reminder != 0) {
						for (int k = j + 1; k < n; k++) {
							if (score[k] != INT_MIN && score[k] <= reminder) {
								reminder -= score[k];
								todie[count++] = k;
								if (reminder == 0)
									break;
							}
						}
						if (reminder == 0) {
							for (int m = 0; m < count; m++)
								score[todie[m]] = INT_MIN;
							count = 0;
							break;
						}
						else {
							reminder = gpa - score[i];
							count = 0;
						}
					}
					else {
						for (int m = 0; m < count; m++)
							score[todie[m]] = INT_MIN;
						count = 0;
						break;
					}
				}
			}
			if (reminder != 0)
				break;
		}
	}
	free(todie);
	if (reminder == 0)
		return true;
	else
		return false;
}

int compare(const void* a, const void* b)
{
	int* digit1 = (int*)a;
	int* digit2 = (int*)b;

	return *digit2 - *digit1;
}
int main(void)
{
	unsigned int minutes;
	int totalscore = 0;
	scanf_s("%u", &minutes);
	int* score = (int*)malloc(minutes * sizeof(int));

	for (unsigned int i = 0; i < minutes; i++) {
		scanf_s("%d", score + i);
		totalscore += score[i];
	}

	int* temp = (int*)malloc(minutes * sizeof(int));
	memcpy(temp, score, minutes * sizeof(int));

	qsort((void*)temp, minutes, sizeof(int), compare);

	for (int i = minutes; i > 0; i--) {
		if (totalscore % i == 0) {
			if (IsBisected(temp, minutes, totalscore / i)) {
				printf("%d\n", totalscore / i);
				break;
			}
		}
	}

	free(temp);
	free(score);

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int arr_global[50];
int used[50];
int n;

/*
 * 尝试是否能凑出目标值 num
 */
bool dfs(int target, int current, int start) {
	if (current == target) { // 找到一组
		return true;
	}
	for (int i = start; i < n; i++) {
		if (used[i]) continue;

		int v = arr_global[i];
		if (current + v > target) continue;  // 剪枝

		used[i] = 1;
		if (dfs(target, current + v, i + 1)) {
			return true;
		}
		used[i] = 0;

		// 如果这个值失败，第一个值就失败，则无需再尝试相同值
		while (i + 1 < n && arr_global[i + 1] == v)
			i++;
	}
	return false;
}

/*
 * 检查是否能分成 k 组，每组和为 target
 */
bool can_split(int target) {
	for (int i = 0; i < n; i++) used[i] = 0;

	int need_groups = 0;
	int sum = 0;
	for (int i = 0; i < n; i++) sum += arr_global[i];

	need_groups = sum / target;

	// 每次寻找一组
	for (int g = 1; g < need_groups; g++) {
		if (!dfs(target, 0, 0)) return false;
	}

	return true;
}

int solve_method(int* arr, int len) {
	n = len;
	for (int i = 0; i < len; i++) arr_global[i] = arr[i];

	// 降序排序（重要剪枝）
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr_global[j] > arr_global[i]) {
				int t = arr_global[i];
				arr_global[i] = arr_global[j];
				arr_global[j] = t;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < len; i++) sum += arr_global[i];

	for (int groups = len; groups >= 1; groups--) {
		if (sum % groups == 0) {
			int target = sum / groups;
			if (can_split(target))
				return target;
		}
	}

	return sum;
}

int main() {
	int arr[] = { 8, 7 ,6, 5 ,4, 3 };
	int len = sizeof(arr) / sizeof(arr[0]);

	int result = solve_method(arr, len);
	printf("result = %d\n", result);

	return 0;
}
#endif

/*day 10*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAXLENA 100
#define MAXLENB 10
int* prevpos;

bool searchsubstr(char* str_A, char* str_B, int len_A, int len_B)
{
	int i, j;
	for (i = 0; i < len_B ; i++) {
		for (j = prevpos[i] + 1; j < len_A; j++) {
			if (str_A[j] == str_B[i]) {
				prevpos[i] = j;
				if (i != len_B - 1 && i > prevpos[i + 1])
					prevpos[i + 1] = j;
				break;
			}
		}
		if (j == len_A)
			return false;
	}
	return true;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char str_A[MAXLENA];
	char str_B[MAXLENB];

	s_gets(str_A, MAXLENA);
	s_gets(str_B, MAXLENB);

	int len_A = (int)strlen(str_A);
	int len_B = (int)strlen(str_B);
	int nums = 0;

	prevpos = (int*)malloc(len_B * sizeof(int));
	memset(prevpos, -1, len_B * sizeof(int));

	while (1) {
		if (searchsubstr(str_A, str_B, len_A, len_B))
			nums++;
		else
			break;
	}

	printf("%d\n", nums);

	free(prevpos);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int totalweight, num;

	scanf_s("%d %d", &totalweight, &num);

	int* weight = (int*)malloc(num * sizeof(int));
	int* value = (int*)malloc(num * sizeof(int));
	int* dp = (int*)calloc(totalweight + 1, sizeof(int));

	for (int i = 0; i < num; i++) {
		scanf_s("%d %d", weight + i, value + i);
	}

	for (int i = 0; i < num; i++) {
		for (int w = totalweight; w >= weight[i]; w--) {
			dp[w] = max(dp[w - weight[i]] + value[i], dp[w]);
			if (i == num - 1)
				break;
		}
	}

	printf("%d\n", dp[totalweight]);

	free(dp);
	free(value);
	free(weight);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int statdays(int fields[], int size, int ee)
{
	int days = 0;
	for (int i = 0; i < size; i++) {
		days += fields[i] / ee;
		if (fields[i] % ee != 0)
			days++;
	}
	return days;
}

int findminee(int fields[], int size, int limit, int left, int right)
{
	int mid = (left + right) / 2;
	int days = statdays(fields, size, mid);
	if (days > limit) {
		if (mid == right)
			return -1;
		return findminee(fields, size, limit, mid + 1, right);
	}
	else {
		if (mid == left)
			return left;
		return findminee(fields, size, limit, left, mid - 1);
	}
}

int main(void)
{
	int m, n;
	int maxfield = 0;
	scanf_s("%d %d", &m, &n);

	int* fields = (int*)malloc(m * sizeof(int));

	for (int i = 0; i < m; i++) {
		scanf_s("%d", fields + i);
		if (fields[i] > maxfield)
			maxfield = fields[i];
	}

	printf("%d\n", findminee(fields, m, n, 1, maxfield));

	free(fields);

	return 0;
}
#endif

/*day 11*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define ALPHAKINDS 26
#define MAXSTR1 50
#define MAXSTR2 100
typedef struct {
	char ch;
	int nums;
}Alpha;

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int compare_ch(const void* a, const void* b)
{
	char* ch1 = (char*)a;
	char* ch2 = (char*)b;
	return *ch1 - *ch2;
}

bool findsubstr(Alpha* alpha, int size, char* temp, int len)
{
	int i, j;
	int count = 0;
	j = 0;
	for (i = 0; i < len; i++) {
		if (temp[i] == alpha[j].ch)
			count++;
		else {
			if (count < alpha[j].nums)
				return false;
			else {
				count = 1;
				j++;
			}
		}
	}
	if (j == size)
		return true;
	else
		return false;
}
int main(void)
{
	int k, n1, n2;
	int size = 0;
	char s1[MAXSTR1];
	char s2[MAXSTR2];
	Alpha alpha[ALPHAKINDS] = { 0 };

	s_gets(s1, MAXSTR1);
	s_gets(s2, MAXSTR2);
	scanf_s("%d", &k);

	n1 = (int)strlen(s1);
	n2 = (int)strlen(s2);

	qsort((void*)s1, n1, sizeof(char), compare_ch);

	
	char prev = s1[0];
	int count = 1;

	for (int i = 1; i < n1; i++) {
		if (s1[i] == prev)
			count++;
		else {
			alpha[size].ch = prev;
			alpha[size].nums = count;
			size++;
			prev = s1[i];
			count = 1;
		}
	}
	alpha[size].ch = prev;
	alpha[size].nums = count;
	size++;

	char* temp = (char*)malloc((n1 + k + 1) * sizeof(char));
	for (int i = 0; i < n2; i++) {
		if (n2 - i < n1 + k) {
			printf("-1\n");
			break;
		}
		else {
			memcpy(temp, s2 + i, n1 + k);
			qsort((void*)temp, n1 + k, sizeof(char), compare_ch);
			temp[n1 + k] = '\0';
			if (findsubstr(alpha, size, temp, n1 + k + 1)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	free(temp);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int findshortest(int boards[], int shortboards[],int wood, int n)
{
	static int i,count, boardsum, avg;
	count = boardsum = 0;
	for (i = 0; i < n; i++)
		boardsum += boards[shortboards[i]];
	avg = (boardsum + wood) / n;

	for (i = 0; i < n; i++) {
		if (boards[shortboards[i]] <= avg)
			shortboards[count++] = i;
	}
	if (count == n)
		return avg;
	else
		return findshortest(boards, shortboards, wood, count);
}

int main(void)
{
	int nums, wood;
	scanf_s("%d %d", &nums, &wood);

	int* boards = (int*)malloc(nums * sizeof(int));
	int* shortboards = (int*)malloc(nums * sizeof(int));

	for (int i = 0; i < nums; i++) {
		scanf_s("%d", boards + i);
		shortboards[i] = i;
	}

	printf("%d\n", findshortest(boards, shortboards,wood, nums));

	free(shortboards);
	free(boards);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int n, p_max;
	scanf_s("%d", &n);
	int* powers = (int*)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		scanf_s("%d", powers + i);
	}
	scanf_s("%d", &p_max);

	int* dp = (int*)calloc(p_max + 1, sizeof(int));

	for (int i = 0; i < n; i++) {
		for (int p = p_max; p >= powers[i]; p--) {
			if (dp[p - powers[i]] + powers[i] == p_max) {
				dp[p_max] = p_max;
				break;
			}
			dp[p] = max(dp[p - powers[i]] + powers[i], dp[p]);
		}
		if (dp[p_max] == p_max)
			break;
	}

	printf("%d\n", dp[p_max]);
	free(dp);
	free(powers);

	return 0;
}
#endif

/*day 12*/
#if 0
#include<stdio.h>
#include<stdlib.h>

int m, n;

typedef struct {
	int row;
	int col;
	int size;
}Validdistrict;

void dfs(Validdistrict* validistrict, int** spared, int* edges, int x, int y)
{
	if (spared[x][y]) {
		if (x == 0 || y == 0 || x == m - 1 || y == n - 1) {
			validistrict->row = x;
			validistrict->col = y;
			(*edges)++;
		}
		spared[x][y] = 0;
		validistrict->size++;
		if (x != 0)
			dfs(validistrict, spared, edges, x - 1, y);
		if (y != n - 1)
			dfs(validistrict, spared, edges, x, y + 1);
		if (x != m - 1)
			dfs(validistrict, spared, edges, x + 1, y);
		if (y != 0)
			dfs(validistrict, spared, edges, x, y - 1);
	}
}

int compare_validistrict(const void* a, const void* b)
{
	Validdistrict* district1 = (Validdistrict*)a;
	Validdistrict* district2 = (Validdistrict*)b;
	return district2->size - district1->size;
}

void freemem(void** arr, int n)
{
	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

int main(void)
{
	int count = 0;
	int edges;

	scanf_s("%d %d", &m, &n);

	Validdistrict* validistrict = (Validdistrict*)calloc((m + n) , sizeof(Validdistrict));

	int** spared = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		spared[i] = (int*)calloc(n, sizeof(int));
	}

	char** matrix = (char**)malloc(m * sizeof(char*));
	for (int i = 0; i < m; i++) {
		matrix[i] = (char*)malloc(n * sizeof(char));
		for (int j = 0; j < n; j++) {
			scanf_s(" %c", matrix[i] + j);
			if (matrix[i][j] == 'O')
				spared[i][j] = 1;
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			edges = 0;
			if (spared[i][j]) {
				dfs(&validistrict[count], spared, &edges, i, j);
				if (edges != 1) {
					validistrict[count].size = 0;
				}
				else
					count++;
			}
		}
	}

	qsort((void*)validistrict, count, sizeof(Validdistrict), compare_validistrict);

	if (validistrict[0].size == 0)
		printf("NULL\n");
	else if (validistrict[0].size == validistrict[1].size)
		printf("%d\n", validistrict[0].size);
	else
		printf("%d %d %d\n", validistrict[0].row, validistrict[0].col, validistrict[0].size);

	freemem(matrix, m);
	freemem(spared, m);
	free(validistrict);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MAXQUEUE 300000
#define MAXSTRLEN 20

typedef struct node {
	int item;
	struct node* next;
}Node;

typedef struct {
	Node* head;
	Node* tail;
	int size;
}Queue;

void InitQueue(Queue* pq)
{
	pq->head = NULL;
	pq->tail = NULL;
	pq->size = 0;
}

bool EnQueue(Queue* pq, int item, bool istail)
{
	if (pq->size == MAXQUEUE)
		return false;
	Node* pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		exit(1);
	pnew->item = item;
	pnew->next = NULL;

	if (pq->size == 0) {
		pq->head = pq->tail = pnew;
		pq->head->next = pq->tail;
	}
	else if (istail) {
		pq->tail->next = pnew;
		pq->tail = pnew;
	}
	else {
		pnew->next = pq->head->next;
		pq->head = pnew;
	}
	pq->size++;
	return true;
}

bool DeQueue(Queue* pq, int* item)
{
	if (pq->size == 0)
		return false;
	*item = pq->head->item;
	Node* pt = pq->head;
	pq->head = pq->head->next;
	free(pt);
	pq->size--;
	if (pq->size == 0)
		pq->head = pq->tail = NULL;
	return true;
}

void  EmptyTheQueue(Queue* pq)
{
	int dummy;
	while (!(pq->size == 0))
		DeQueue(pq, &dummy);
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	int n, item;
	int out = 1;
	int adjusts = 0;
	char command[MAXSTRLEN];
	char* end;
	Queue queue;

	scanf_s("%d", &n);
	while (getchar() != '\n')
		continue;

	InitQueue(&queue);
	for (int i = 0; i < 2 * n; i++) {
		s_gets(command, MAXSTRLEN);
		end = command;
		while (*end != '\0' && !isdigit(*end))
			end++;
		if (!strncmp(command, "head", 4)) {
			item = strtol(end, &end, 10);
			if (!EnQueue(&queue, item, false))
				return -1;
		}
		else if (!strncmp(command, "tail", 4)) {
			item = strtol(end, &end, 10);
			if (!EnQueue(&queue, item, true))
				return -1;
		}
		else {
			if (queue.size == 0)
				return -1;
			int count = 0;
			while (queue.head->item != out) {
				DeQueue(&queue, &item);
				EnQueue(&queue, item, true);
				count++;
				if (count == queue.size)
					return -1;
			}
			DeQueue(&queue, &item);
			adjusts += count;
			out++;
		}
	}

	EmptyTheQueue(&queue);
	printf("%d\n", adjusts);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define N 1000
#define M 1000
#define MAXLEN 20

int compare_ch(const void* a, const void* b)
{
	char* ch1 = (char*)a;
	char* ch2 = (char*)b;
	return *ch1 - *ch2;
}

void cleardup(char* word, int len)
{
	int count = 0;
	char* temp = (char*)malloc(len * sizeof(char));
	char prev = '\0';
	for (int i = 0; i < len; i++) {
		if (word[i] == prev)
			continue;
		else {
			prev = word[i];
			temp[count++] = prev;
		}
	}
	memcpy(word, temp, count);
	word[count] = '\0';

	free(temp);
}

void OrganizeWords(char* pwords[], int nums)
{
	for (int i = 0; i < nums; i++) {
		qsort((void*)pwords[i], strlen(pwords[i]), sizeof(char), compare_ch);
		cleardup(pwords[i], (int)strlen(pwords[i]));
	}
}

void freemem(void** arr, int n)
{
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	int num1 = 0;
	int num2 = 0;
	bool isfound;
	char* str1 = (char*)malloc(N * MAXLEN * sizeof(char));
	char* str2 = (char*)malloc(M * MAXLEN * sizeof(char));
	if (str1 == NULL)
		return -1;

	char* end;

	end = s_gets(str1, N * MAXLEN);
	
	while (end = strchr(end, ',')) {
		*end = '\0';
		num1++;
		end++;
	}
	num1++;

	end = str1;
	char** words = (char**)malloc(num1 * sizeof(char*));
	if (!words)
		return -1;
	for (int i = 0; i < num1; i++) {
		words[i] = end;
		end = strchr(end, '\0') + 1;
	}

	end = s_gets(str2, M * MAXLEN);

	while (end = strchr(end, ',')) {
		*end = '\0';
		num2++;
		end++;
	}
	num2++;

	end = str2;
	char** wordlists = (char**)malloc(num2 * sizeof(char*));
	if (!wordlists)
		return -1;
	for (int i = 0; i < num2; i++) {
		wordlists[i] = end;
		end = strchr(end, '\0') + 1;
	}

	char** pwords = (char**)malloc(num1 * sizeof(char*));
	if (!pwords)
		return -1;
	for (int i = 0; i < num1; i++) {
		pwords[i] = (char*)malloc(MAXLEN * sizeof(char));
		if (!pwords[i])
			return -1;
		strcpy(pwords[i], words[i]);
	}

	char** pwordlists = (char**)malloc(num2 * sizeof(char*));
	if (!pwordlists)
		return -1;
	for (int i = 0; i < num2; i++) {
		pwordlists[i] = (char*)malloc(MAXLEN * sizeof(char));
		if (!pwordlists[i])
			return -1;
		strcpy(pwordlists[i], wordlists[i]);
	}

	int* result = (int*)malloc(num1 * sizeof(int));
	if (!result)
		return -1;
	int count = 0;

	OrganizeWords(pwords, num1);
	OrganizeWords(pwordlists, num2);

	for (int i = 0; i < num1; i++) {
		isfound = false;
		for (int j = 0; j < num2; j++) {
			if (!strcmp(pwords[i], pwordlists[j])) {
				result[count++] = j;
				isfound = true;
				break;
			}
		}
		if (!isfound) {
			break;
		}
	}
	if (count < num1)
		printf("not found\n");
	else {
		for (int i = 0; i < count; i++) {
			printf("%s", wordlists[result[i]]);
			if (i == count - 1)
				printf("\n");
			else
				printf(",");
		}
	}

	free(result);
	freemem(pwordlists, num2);
	freemem(pwords, num1);
	free(wordlists);
	free(words);
	free(str2);
	free(str1);

	return 0;
}
#endif

/*day 13*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

int main(void)
{
	int length;
	int maxdis = -1;
	scanf_s("%d", &length);

	uint32_t* lego = (uint32_t*)malloc(length * sizeof(uint32_t));
	bool* visited = (bool*)malloc(length * sizeof(bool));

	for (int i = 0; i < length; i++) {
		scanf_s("%u", lego + i);
		visited[i] = false;
	}

	for (int i = 0; i < length; i++) {
		if (!visited[i]) {
			visited[i] = true;
		}
		for (int j = i + 1; j < length; j++) {
			if (!visited[j]) {
				if (lego[j] == lego[i]) {
					maxdis = max(j - i, maxdis);
					visited[j] = true;
				}
			}
		}
	}

	printf("%d\n", maxdis);

	free(visited);
	free(lego);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXCONTENTS 10000000
#define MAXWORDS 2000

int compare_ch(const void* a, const void* b)
{
	char* ch1 = (char*)a;
	char* ch2 = (char*)b;
	return *ch1 - *ch2;
}

char* copy_sortext(char* dst, const char* src, int len)
{
	if (dst) {
		memcpy(dst, src, len);
		dst[len] = '\0';
		qsort((void*)dst, len, sizeof(char), compare_ch);
	}
	return dst;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char* content = (char*)malloc(MAXCONTENTS * sizeof(char));
	char* word = (char*)malloc(MAXWORDS * sizeof(char));
	s_gets(content, MAXCONTENTS);
	s_gets(word, MAXWORDS);

	int count = 0;
	int len = (int)strlen(word);
	char* temp = (char*)malloc((len + 1) * sizeof(char));
	int stop = (int)strlen(content) - len;

	qsort((void*)word, len, sizeof(char), compare_ch);

	for (int i = 0; i <= stop; i++) {
		copy_sortext(temp, content + i, len);
		if (!strcmp(temp, word)) {
			count++;
		}
	}

	printf("%d\n", count);

	free(temp);
	free(word);
	free(content);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int compare_w(const void* a, const void* b)
{
	int* digit1 = (int*)a;
	int* digit2 = (int*)b;
	return *digit1 - *digit2;
}

int main(void)
{
	int m, n;
	scanf_s("%d %d", &m, &n);

	int* weight = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++)
		scanf_s("%d", weight + i);

	qsort((void*)weight, n, sizeof(int), compare_w);

	int i = 0, j = n - 1;
	int count = 0;
	while (i <= j) {
		if (weight[i] + weight[j] <= m) {
			count++;
			i++;
			j--;
		}
		else {
			count++;
			j--;
		}
	}

	printf("%d\n", count);

	free(weight);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAXPORTS 100

typedef enum {
	INITIAL, SINGLE, MERGED, ZOOMBIE
}Status;

void cleardup(int* ports, int* len)
{
	int k = 1;
	for (int i = 1; i < *len; i++) {
		if (ports[i] != ports[k - 1])
			ports[k++] = ports[i];
	}
	*len = k;
}

int compare_digit(const void* a, const void* b)
{
	int* digit1 = (int*)a;
	int* digit2 = (int*)b;
	return *digit1 - *digit2;
}

bool merge(int* dst, int* src, int* dlen, int* slen)
{
	bool found;
	int count = 0;
	int* temp = (int*)malloc(*slen * sizeof(int));
	for (int i = 0; i < *slen; i++) {
		found = false;
		for (int j = 0; j < *dlen; j++) {
			if (dst[j] == src[i]) {
				found = true;
				break;
			}
			else if (dst[j] > src[i])
				break;
		}
		if (!found)
			temp[count++] = src[i];
	}
	if (*slen-count < 2) {
		free(temp);
		return false;
	}
	for (int i = 0; i < count; i++)
		dst[*dlen + i] = temp[i];
	*dlen += count;
	qsort((void*)dst, *dlen, sizeof(int), compare_digit);
	free(temp);
	return true;
}

int main(void)
{
	int m;
	int i, start, prev;
	scanf_s("%d", &m);
	Status* state = (Status*)malloc(m * sizeof(Status));
	int* len = (int*)calloc(m, sizeof(int));
	int** portset = (int**)malloc(m * sizeof(int*));

	for (i = 0; i < m; i++) {
		state[i] = INITIAL;
		portset[i] = (int*)malloc(MAXPORTS * sizeof(int));
		while (1) {
			scanf_s("%d", portset[i] + len[i]);
			len[i]++;
			if (getchar() != '\n')
				continue;
			else
				break;
		}
		qsort((void*)portset[i], len[i], sizeof(int), compare_digit);
		cleardup(portset[i], &len[i]);
	}

	prev = 0;
	while (len[prev] <= 1) {
		state[prev] = SINGLE;
		prev++;
	}
	start = prev;
	i = prev + 1;
	while (i < m) {
		if (i != prev && (state[i] == INITIAL || state[i] == MERGED)) {
			if (len[i] <= 1) {
				state[i] = SINGLE;
			}
			else {

				if (merge(portset[prev], portset[i], len + prev, len + i)) {
					if (i < prev) {
						int* temp = portset[prev];
						portset[prev] = portset[i];
						portset[i] = temp;
						len[i] = len[prev];
						state[prev] = ZOOMBIE;
						state[i] = MERGED;
						prev = i;
					}
					else {
						state[prev] = MERGED;
						state[i] = ZOOMBIE;
					}
					i = start;
					continue;
				}
			}
		}
		if (i == m - 1) {
			if (prev != m - 2) {
				while (++prev < m && (state[prev] == ZOOMBIE || state[prev] == SINGLE))
					continue;
				i = prev + 1;
			}
			else
				break;
		}
		else
			i++;
	}

	prev = 0;
	printf("[");
	while (prev < m && state[prev] == ZOOMBIE) {
		prev++;
	}
	for (i = prev; i < m; i++) {
		if (state[i] != ZOOMBIE) {
			if (i != prev)
				printf(",");
			printf("[");
			for (start = 0; start < len[i]; start++) {
				printf("%d", portset[i][start]);
				if (start == len[i] - 1)
					printf("]");
				else
					printf(",");
			}
		}
	}
	printf("]\n");

	for (i = 0; i < m; i++)
		free(portset[i]);
	free(portset);
	free(len);
	free(state);

	return 0;
}
#endif

/*day 14*/

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAXSTRS 1000

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char str[MAXSTRS];
	int n, i, j;
	bool ToDown;
	s_gets(str, MAXSTRS);
	char* end = strchr(str, ' ');
	if (end)
		*end = '\0';
	else
		return -1;
	n = strtol(end + 1, &end, 10);

	int len = (int)strlen(str);
	for (i = 0; i < n; i++) {
		ToDown = true;
		j = i;
		while (j < len) {
			printf("%c", str[j]);
			if (ToDown) {
				j += (n - i) * 2 - 1;
				ToDown = false;
			}
			else {
				j += i * 2 + 1;
				ToDown = true;
			}
		}
		if (i != n - 1)
			printf("\n");
	}

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int minprice;
	int nums;
}Solution;

Solution findmincost(int price, int fdics, int discounts, int nothds)
{
	int  lowerlimit = 100 * fdics;
	int upperlimit = fdics * 100 / 0.92;
	Solution sol;
	if (discounts < 1) {
		if (price <= lowerlimit) {
			int fd = price / 100;
			sol.minprice = price - fd * 10 - nothds * 5;
			sol.nums = fd + nothds;
		}
		else {
			sol.minprice = price - fdics * 10 - nothds * 5;
			sol.nums = fdics + nothds;
		}
		return sol;
	}
	else {
		if (price <= lowerlimit) {
			int fd = price / 100;
			int disfst = 0.92 * price;
			int price1 = 0.92 * (price - fd * 10);
			int price2 = disfst - disfst / 100 * 10;
			if (price1 < price2) {
				sol.minprice = price1;
				sol.nums = fd + 1;
			}
			else {
				sol.minprice = price2;
				sol.nums = 1 + disfst / 100;
			}
		}
		else if (price > upperlimit) {
			int price1 = 0.92 * (price - 10 * fdics);
			int disfst = 0.92 * price;
			int price2 = disfst - 10 * fdics;
			sol.minprice = min(price1, price2);
			sol.nums = fdics + 1;
		}
		else {
			int price1 = 0.92 * (price - 10 * fdics);
			int disfst = 0.92 * price;
			int price2 = disfst - disfst / 100 * 10;
			if (price1 < price2) {
				sol.minprice = price1;
				sol.nums = 1 + fdics;
			}
			else {
				sol.minprice = price2;
				sol.nums = 1 + disfst / 100;
			}
		}
	}
	sol.minprice -= 5 * nothds;
	sol.nums += nothds;

	return sol;
}
int main(void)
{
	int fdics, discounts, nothds, nums;
	scanf_s("%d %d %d %d", &fdics, &discounts, &nothds, &nums);

	int price;
	Solution* sol = (Solution*)malloc(nums * sizeof(Solution));
	for (int i = 0; i < nums; i++) {
		scanf_s("%d", &price);
		sol[i] = findmincost(price, fdics, discounts, nothds);
	}

	for (int i = 0; i < nums; i++) {
		printf("%d %d\n", sol[i].minprice, sol[i].nums);
	}

	free(sol);
	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 100
#define MIDVALUE 128
#define UPPER 255
#define LOWER 0

int round_int(double x)
{
	return (int)(x >= 0 ? x + 0.5 : x - 0.5);
}

int threshold(int img[], bool visited[], int n, int k,int* distribute)
{
	int tsd = 0;
	if (k > 0) {
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				if (img[i] + k >= UPPER) {
					*distribute -= UPPER - img[i];
					tsd++;
					visited[i] = true;
				}
			}
		}
	}
	else if(k < 0) {
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				if (img[i] + k <= LOWER) {
					*distribute += img[i] - LOWER;
					tsd++;
					visited[i] = true;
				}
			}
		}
	}

	return tsd;
}
int main(void)
{
	int img[N];
	int count = 0, sum = 0;
	int totsd = -1;
	int valids, k, prev_k, distribute;

	while (1) {
		scanf_s("%d", img + count);
		count++;
		if (getchar() != '\n')
			continue;
		else
			break;
	}

	bool* visited = (bool*)malloc(count * sizeof(bool));
	for (int i = 0; i < count; i++) {
		visited[i] = false;
		sum += img[i];
	}

	valids = count;
	k = 0;
	distribute = MIDVALUE * count - sum;

	while (totsd != 0 && valids > 0) {
		prev_k = k;
		k = round_int((double)distribute / valids);

		if (k == prev_k)
			break;   // 已收敛

		totsd = threshold(img, visited, count, k, &distribute);
		valids -= totsd;
	}

	printf("%d\n", k);
	free(visited);

	return 0;
}
#endif

/*day 15*/
#if 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 50

typedef struct {
	int major;
	int minor;
	int incremental;
	char* milestone;
}Version;

void InitialVersion(Version* v, const char* maven)
{
	if (maven == NULL)
		exit(1);
	char* end = maven;
	v->major = strtol(end, &end, 10);
	v->minor = strtol(end + 1, &end, 10);
	if (strchr(end, '.'))
		v->incremental = strtol(end + 1, &end, 10);
	else
		v->incremental = -1;
	if (strchr(end, '-'))
		v->milestone = end + 1;
	else
		v->milestone = "\0";
}

int versioncmp(const Version* v1, const Version* v2)
{
	if (v1->major > v2->major)
		return 0;
	else if (v1->major < v2->major)
		return 1;
	else {
		if (v1->minor > v2->minor)
			return 0;
		else if (v1->minor < v2->minor)
			return 1;
		else {
			if (v1->incremental > v2->incremental)
				return 0;
			else if (v1->incremental < v2->incremental)
				return 1;
			else {
				if (strcmp(v1->milestone, v2->milestone) < 0)
					return 1;
				else
					return 0;
			}
		}
	}
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char maven1[MAXLEN], maven2[MAXLEN];
	Version version[2];
	s_gets(maven1, MAXLEN);
	s_gets(maven2, MAXLEN);

	InitialVersion(&version[0], maven1);
	InitialVersion(&version[1], maven2);

	int num = versioncmp(&version[0], &version[1]);
	if (num)
		printf("%s\n", maven2);
	else
		printf("%s\n", maven1);

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <string.h>
#define MAXLEN 10

int idx(char c)
{
	if (c == 'A')return 0;
	if (c == 'S')return 1;
	if (c == 'D')return 2;
	else
		return 3;//'W'
}

int minReplaceLength(char* s)
{
	int n = (int)strlen(s);
	int cnt[4] = { 0 };
	int target = n / 4;
	int left = 0;
	int ans = n;

	for (int i = 0; i < n; i++) {
		cnt[idx(s[i])]++;
	}

	if (cnt[0] <= target && cnt[1] <= target &&
		cnt[2] <= target && cnt[3] <= target)
		return 0;

	int len;
	for (int right = 0; right < n; right++) {
		cnt[idx(s[right])]--;
		while (left <= right && cnt[0] <= target && cnt[1] <= target &&
			cnt[2] <= target && cnt[3] <= target) {
			len = right - left + 1;
			if (len < ans)
				ans = len;
			cnt[idx(s[left])]++;
			left++;
		}
	}

	return ans;
}

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

int main(void)
{
	char move[MAXLEN];
	s_gets(move, MAXLEN);
	int minreplen = minReplaceLength(move);
	printf("%d\n", minreplen);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdint.h>

#define FENPERYUAN 100
#define FENPERHKD (100/123.0)
#define FENPERJPY (100/1825.0)
#define FENPEREUR (100/14.0)
#define FENPERGBP (100/12.0)
#define MAXSIZE 100

char* s_gets(char* str, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(str, n, stdin);
	if (ret_val) {
		while (ret_val[i] != '\n' && ret_val[i] != '\0')
			i++;
		if (ret_val[i] == '\n')
			ret_val[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}

double MoneytoFen(char* s)
{
	if (!isdigit(*s))
		exit(1);
	char* end = s;
	uint64_t money = strtol(end, &end, 10);
	uint64_t re = 0;
	if (isdigit(*(end + 3))) {
		re = strtol(end + 3, NULL, 10);
	}
	switch (*end) {
	case 'C':
		return (double)(money * FENPERYUAN + re);
	case 'f':
		return (double)money;
	case 'H':
		return ((money * FENPERYUAN) + re) * FENPERHKD;
	case 'c':
		return money * FENPERHKD;
	case 'J':
		return ((money * FENPERYUAN) + re) * FENPERJPY;
	case 's':
		return money * FENPERJPY;
	case 'E':
		return ((money * FENPERYUAN) + re) * FENPEREUR;
	case 'e':
		return money * FENPEREUR;
	case 'G':
		return ((money * FENPERYUAN) + re) * FENPERGBP;
	case 'p':
		return money * FENPERGBP;
	default:
		exit(1);
	}
}
int main(void)
{
	char money[MAXSIZE];
	int N;
	double tatalfens = 0.0;

	scanf_s("%d", &N);
	while (getchar() != '\n')
		continue;

	for (int i = 0; i < N; i++) {
		s_gets(money, MAXSIZE);
		tatalfens += MoneytoFen(money);
	}

	printf("%llu\n", (uint64_t)tatalfens);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>

int maxprofits(int** item_price,int* item, int items, int days)
{
	if (days < 2)
		return 0;
	int profits = 0;
	for (int i = 0; i < days - 1; i++) {
		for (int j = 0; j < items; j++) {
			if (item_price[j][i] < item_price[j][i + 1])
				profits += item[j] * (item_price[j][i + 1] - item_price[j][i]);
		}
	}

	return profits;
}

int main(void)
{
	int items, days;
	scanf_s("%d %d", &items, &days);

	int* item = (int*)malloc(items * sizeof(int));
	for (int i = 0; i < items; i++)
		scanf_s("%d", item + i);

	int** item_price = (int**)malloc(items * sizeof(int*));
	for (int i = 0; i < items; i++) {
		item_price[i] = (int*)malloc(days * sizeof(int));
		for (int j = 0; j < days; j++)
			scanf_s("%d", item_price[i] + j);
	}

	int profits = maxprofits(item_price, item, items, days);

	printf("%d\n", profits);
	for (int i = 0; i < items; i++) {
		free(item_price[i]);
	}
	free(item_price);
	free(item);

	return 0;
}
#endif

/*day 16*/
#if 0
#include<stdio.h>
#include<stdlib.h>

int compare_d(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int cleardup(int* arr, int* freq, int n)
{
	if (n <= 0)
		return 0;

	qsort((void*)arr, n, sizeof(int), compare_d);
	int k = 1;
	freq[k - 1] = 1;
	for (int i = 1; i < n; i++) {
		if (arr[i] == arr[k - 1])
			freq[k - 1]++;
		else {
			arr[k] = arr[i];
			freq[k] = 1;
			k++;
		}
	}

	return k;
}

int main(void)
{
	int n;
	scanf_s("%d", &n);

	int* errors = (int*)malloc(n * sizeof(int));
	int* temp = (int*)malloc(n * sizeof(int));
	int* freq = (int*)calloc(n, sizeof(int));
	int* idx = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf_s("%d", errors + i);
		temp[i] = errors[i];
	}

	int alones = cleardup(temp, freq, n);
	int maxfreq = 0;
	int nums = 0;

	for (int i = 0; i < alones; i++) {
		if (freq[i] > maxfreq)
			maxfreq = freq[i];
	}

	for (int i = 0; i < alones; i++) {
		if (freq[i] == maxfreq)
			idx[nums++] = i;
	}

	int* len = (int*)malloc(nums * sizeof(int));
	int* stat = (int*)calloc(nums, sizeof(int));

	for (int i = 0; i < nums; i++)
		len[i] = -1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < nums; j++) {
			if (errors[i] == temp[idx[j]]) {
				stat[j]++;
				if (len[j] == -1)
					len[j] = i;
				if (stat[j] == maxfreq)
					len[j] = i - len[j] + 1;
				break;
			}
		}
	}

	int minlen = INT_MAX;
	for (int i = 0; i < nums; i++) {
		if (len[i] < minlen)
			minlen = len[i];
	}

	printf("%d\n", minlen);

	free(stat);
	free(len);
	free(idx);
	free(freq);
	free(temp);
	free(errors);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#define MAXFILES 10000

int compare_d(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int cleardup(int* arr, int* freq, int n)
{
	if (n <= 0)
		return 0;

	qsort((void*)arr, n, sizeof(int), compare_d);
	int k = 1;
	freq[k - 1] = 1;
	for (int i = 1; i < n; i++) {
		if (arr[i] == arr[k - 1])
			freq[k - 1]++;
		else {
			arr[k] = arr[i];
			freq[k] = 1;
			k++;
		}
	}

	return k;
}

int findsize(int* filesize, int* files, int n, int flag)
{
	for (int i = 0; i < n; i++) {
		if (files[i] == flag)
			return filesize[i];
	}
	return 0;
}

int main(void)
{
	int cache_cost, num;
	int fn = 0;
	int* files = (int*)malloc(MAXFILES * sizeof(int));
	scanf_s("%d", &cache_cost);

	while (1) {
		scanf_s("%d", files + fn);
		fn++;
		if (getchar() != '\n')
			continue;
		else
			break;
	}

	int* temp = (int*)malloc(fn * sizeof(int));
	int* freq = (int*)calloc(fn, sizeof(int));
	int* filesize = (int*)malloc(fn * sizeof(int));

	for (int i = 0; i < fn; i++) {
		scanf_s("%d", filesize + i);
		temp[i] = files[i];
	}

	int alones = cleardup(temp, freq, fn);
	int leastcost = 0;

	for (int i = 0; i < alones; i++) {
		num = findsize(filesize, files, fn, temp[i]);
		leastcost += min(num * freq[i], num + cache_cost);
	}

	printf("%d\n", leastcost);

	free(filesize);
	free(freq);
	free(temp);
	free(files);

	return 0;
}
#endif

#if 0
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
	int price;
	int difference;
}Hotel;

int compare_hotel(const void* a, const void* b)
{
	Hotel* hotel1 = (Hotel*)a;
	Hotel* hotel2 = (Hotel*)b;

	if (hotel1->difference < hotel2->difference)
		return -1;
	else if (hotel1->difference > hotel2->difference)
		return 1;
	else
		return hotel1->price - hotel2->price;
}

int compare_price(const void* a, const void* b)
{
	Hotel* hotel1 = (Hotel*)a;
	Hotel* hotel2 = (Hotel*)b;
	return hotel1->price - hotel2->price;
}

int main(void)
{
	int n, k, x;
	scanf_s("%d %d %d", &n, &k, &x);

	Hotel* hotels = (Hotel*)malloc(n * sizeof(Hotel));
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &hotels[i].price);
		hotels[i].difference = abs(hotels[i].price - x);
	}

	qsort((void*)hotels, n, sizeof(Hotel), compare_hotel);
	qsort((void*)hotels, k, sizeof(Hotel), compare_price);

	for (int i = 0; i < k; i++) {
		printf("%d", hotels[i].price);
		if (i == k - 1)
			printf("\n");
		else
			printf(" ");
	}

	free(hotels);

	return 0;
}
#endif