#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NUM 100000
#include<stdio.h>
#include<stdlib.h>

//菜单
void menu() {
	printf("*******************************************\n");
	printf("      1.Intersection       2.Union\n");
	printf("      3.Difference         4.enter again\n");
	printf("     -1.输入任意负数退出...     \n");
	printf("*******************************************\n");
}

//查重函数
int toFind(int* arrA, int len, int x) {
	for (int i = 0; i < len; i++) {
		if (arrA[i] == x) {
			return 1;
		}
	}
	return 0;
}

int cmp_int(const void* e1, const void* e2) {
	return *(int*)e1 - *(int*)e2;
}

//交集
int* Inter(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) {
	qsort(arrA, len_A, sizeof(arrA[0]), cmp_int); // 集合A元素升序排列
	qsort(arrB, len_B, sizeof(arrB[0]), cmp_int); // 集合B元素升序排列
	int* ret = (int*)malloc(sizeof(int) * (*returnSize));
	if (ret == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}
	int i = 0, j = 0, k = 0;

	while (i < len_A && j < len_B) {
		if (arrA[i] == arrB[j]) { // 当i, j两指针指向元素相等
			ret[k++] = arrA[i]; // 元素进交集
			i++;
			j++; // 两指针均移动
		}
		else {
			if (len_A > len_B) {
				i++;
			}
			else {
				j++;
			}
		}
	}
	*returnSize = k;
	return ret;
}

//并集-哈希表
/*
int* Uni(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) {
	int* ret = (int*)malloc(sizeof(int) * (*returnSize));
	if (ret == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}
	int* tmp = (int*)malloc(sizeof(int) * MAX_NUM);
	if (tmp == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}

	for (int i = 0; i < MAX_NUM; i++) {
		tmp[i] = 0;
	}

	for (int i = 0; i < len_A; i++) {
		tmp[arrA[i]] = 1;
	}
	for (int i = 0; i < len_B; i++) {
		tmp[arrB[i]] = 1;
	}

	int k = 0;
	for (int i = 0; i < MAX_NUM; i++) {
		if (tmp[i]) {
			ret[k++] = i;
		}
	}
	*returnSize = k;
	return ret;
}*/

//并集-朴实
int* Uni(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) {
	int* ret = (int*)malloc(sizeof(int) * (*returnSize));
	if (ret == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}

	int k = 0;
	for (int i = 0; i < len_A; i++) {
		ret[k++] = arrA[i];
	}
	for (int i = 0; i < len_B; i++) {
		if (!toFind(ret, k, arrB[i])) {
			ret[k++] = arrB[i];
		}
	}
	*returnSize = k;
	return ret;
}


//差集
int* Dif(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) {
	int* ret = (int*)malloc(sizeof(int) * MAX_NUM);
	if (ret == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}

	int k = 0;
	for (int i = 0; i < len_A; i++) {
		if (!toFind(arrB, len_B, arrA[i])) {
			ret[k++] = arrA[i];
		}
	}
	*returnSize = k;
	return ret;
}


int main() {
	//循环开关和模式选择
	int input = 0;
	//用顺数组表示集合
	int arrA[MAX_NUM] = { 0 };
	int arrB[MAX_NUM] = { 0 };
	//返回数组
	int size = 10;
	int* ret = NULL;
	//转移表
	int* (*p[4])(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) = { 0, Inter, Uni, Dif };

	menu();

again:	//用于模式4-重新输入集合
	printf("【输入集合】\n");
	//输入集合A
	printf("请输入集合A的元素个数:>");
	int len_A = 0;
	scanf("%d", &len_A);

	printf("请输入集合A:>");
	int i = 0;
	int cnt = 0;
	//输入并查重
	while (i < len_A) {
		scanf(" %d", &arrA[i]);
		if (toFind(arrA, i, arrA[i])) {
			cnt++;
			printf("有 %d 个元素输入重复！请重新输入重复值:>\n", cnt);
			continue;
		}
		i++;
	}

	//集合B
	printf("请输入集合B的元素个数:>");
	int len_B = 0;
	scanf("%d", &len_B);
	printf("请输入集合B:>");
	i = 0;
	cnt = 0;
	//输入并查重
	while (i < len_B) {
		scanf(" %d", &arrB[i]);
		if (toFind(arrB, i, arrB[i])) {
			cnt++;
			printf("有 %d 个元素输入重复！请重新输入重复值:>\n", cnt);
			continue;
		}
		i++;
	}

	//展示输入后的集合A与B
	printf("集合A为：");
	for (int i = 0; i < len_A; i++) {
		printf("%d ", arrA[i]);
	}
	printf("集合B为：");
	for (int i = 0; i < len_B; i++) {
		printf("%d ", arrB[i]);
	}
	printf("\n");

	//模式选择
	do {
		printf("【请选择运算模式】:>\n");
		scanf(" %d", &input);

		//有效模式
		if ((input >= 1) && (input <= 4))
		{
			//模式4-重新输入集合，返回again
			if (input == 4) {
				goto again;
			}

			//返回数组从转移表获取函数返回值
			ret = (*p[input])(arrA, len_A, arrB, len_B, &size);

			//结果输出
			printf("计算结果为：> ");
			for (int i = 0; i < size; i++) {
				printf("%d ", ret[i]);
			}
			printf("\n");
		}
		else if (input < 0) 	//退出
		{
			printf("退出程序！\n");
		}
		else	//提示输入不正确
		{
			printf("请输入正确的选项！\n");
		}
	} while (input >= 0);

	return 0;
}