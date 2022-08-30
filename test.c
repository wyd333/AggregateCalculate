#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NUM 100000
#include<stdio.h>
#include<stdlib.h>

//�˵�
void menu() {
	printf("*******************************************\n");
	printf("      1.Intersection       2.Union\n");
	printf("      3.Difference         4.enter again\n");
	printf("     -1.�������⸺���˳�...     \n");
	printf("*******************************************\n");
}

//���غ���
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

//����
int* Inter(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) {
	qsort(arrA, len_A, sizeof(arrA[0]), cmp_int); // ����AԪ����������
	qsort(arrB, len_B, sizeof(arrB[0]), cmp_int); // ����BԪ����������
	int* ret = (int*)malloc(sizeof(int) * (*returnSize));
	if (ret == NULL) {
		printf("malloc failed!\n");
		exit(-1);
	}
	int i = 0, j = 0, k = 0;

	while (i < len_A && j < len_B) {
		if (arrA[i] == arrB[j]) { // ��i, j��ָ��ָ��Ԫ�����
			ret[k++] = arrA[i]; // Ԫ�ؽ�����
			i++;
			j++; // ��ָ����ƶ�
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

//����-��ϣ��
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

//����-��ʵ
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


//�
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
	//ѭ�����غ�ģʽѡ��
	int input = 0;
	//��˳�����ʾ����
	int arrA[MAX_NUM] = { 0 };
	int arrB[MAX_NUM] = { 0 };
	//��������
	int size = 10;
	int* ret = NULL;
	//ת�Ʊ�
	int* (*p[4])(int* arrA, int len_A, int* arrB, int len_B, int* returnSize) = { 0, Inter, Uni, Dif };

	menu();

again:	//����ģʽ4-�������뼯��
	printf("�����뼯�ϡ�\n");
	//���뼯��A
	printf("�����뼯��A��Ԫ�ظ���:>");
	int len_A = 0;
	scanf("%d", &len_A);

	printf("�����뼯��A:>");
	int i = 0;
	int cnt = 0;
	//���벢����
	while (i < len_A) {
		scanf(" %d", &arrA[i]);
		if (toFind(arrA, i, arrA[i])) {
			cnt++;
			printf("�� %d ��Ԫ�������ظ��������������ظ�ֵ:>\n", cnt);
			continue;
		}
		i++;
	}

	//����B
	printf("�����뼯��B��Ԫ�ظ���:>");
	int len_B = 0;
	scanf("%d", &len_B);
	printf("�����뼯��B:>");
	i = 0;
	cnt = 0;
	//���벢����
	while (i < len_B) {
		scanf(" %d", &arrB[i]);
		if (toFind(arrB, i, arrB[i])) {
			cnt++;
			printf("�� %d ��Ԫ�������ظ��������������ظ�ֵ:>\n", cnt);
			continue;
		}
		i++;
	}

	//չʾ�����ļ���A��B
	printf("����AΪ��");
	for (int i = 0; i < len_A; i++) {
		printf("%d ", arrA[i]);
	}
	printf("����BΪ��");
	for (int i = 0; i < len_B; i++) {
		printf("%d ", arrB[i]);
	}
	printf("\n");

	//ģʽѡ��
	do {
		printf("����ѡ������ģʽ��:>\n");
		scanf(" %d", &input);

		//��Чģʽ
		if ((input >= 1) && (input <= 4))
		{
			//ģʽ4-�������뼯�ϣ�����again
			if (input == 4) {
				goto again;
			}

			//���������ת�Ʊ��ȡ��������ֵ
			ret = (*p[input])(arrA, len_A, arrB, len_B, &size);

			//������
			printf("������Ϊ��> ");
			for (int i = 0; i < size; i++) {
				printf("%d ", ret[i]);
			}
			printf("\n");
		}
		else if (input < 0) 	//�˳�
		{
			printf("�˳�����\n");
		}
		else	//��ʾ���벻��ȷ
		{
			printf("��������ȷ��ѡ�\n");
		}
	} while (input >= 0);

	return 0;
}