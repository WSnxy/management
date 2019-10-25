#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>
#include "check.h"
#include"dyArray.h"
#include"treeMap.h"
#pragma warning(disable:4996)
static const char* PASSWORD = "123456";  //����
#define ID_SORT 0						//��Ų��� ����������
#define PRICE_SORT 1					//�۸���� ������
#define SALE_SORT 2                     //���۶���� ϣ������
#define BST_SEARCH_ID 0                 //��Ų��� ����������
#define BINARY_SEARCH_ID 1              //��Ų��� ���ֲ���
int c = 0;
int count = 1;
TreeMap* products = NULL;				//������Ϣ

//��Ʒ
typedef struct
{
	char name[100];  //������
	char num[100]; //���ȱ��
	float price;    //����
	int count;      //������
	float sale;     //���۶�
} Product;
//������
void maxHeap(DynamicArray* arr, int size, int index) {
	//���ӽǱ�
	int leftNode = 2 * index + 1;
	//�Һ��ӽǱ�
	int rightNode = 2 * index + 2;
	//�������ֵ�ýǱ�
	int max = index;
	if (leftNode<size && ((Product*)arr->p[leftNode])->price >((Product*)arr->p[max])->price)
		max = leftNode;
	if (rightNode<size && ((Product*)arr->p[rightNode])->price >((Product*)arr->p[max])->price)
		max = rightNode;
	if (max != index) {
		void* temp = arr->p[max];
		arr->p[max] = arr->p[index];
		arr->p[index] = temp;
		maxHeap(arr, size, max);
	}
}
void heapSort(DynamicArray* arr) {
	int start = (arr->amount - 1) / 2;
	//����Ϊ�󶥶�
	for (int i = start; i >= 0; i--)
	{
		maxHeap(arr, arr->amount, i);
	}
	for (int i = arr->amount - 1; i > 0; i--)
	{
		void* temp = (void*)arr->p[0];
		arr->p[0] = arr->p[i];
		arr->p[i] = temp;
		maxHeap(arr, i, 0);
	}
}
//ϣ������
void shellSort(DynamicArray* arr) {

	for (int gap=arr->amount/2; gap>0;gap/=2)
	{
		for (int i = gap; i <arr->amount; i++)
		{
			Product* temp = ((Product*)arr->p[i]);
			int j;
			for (j=i;j>= gap &&((Product*)temp)->sale<((Product*)arr->p[j- gap])->sale;j-= gap)
			{
				((Product*)arr->p[j]) = ((Product*)arr->p[j- gap]);
			}
			((Product*)arr->p[j]) = temp;
		}
	}
}

//���ֲ���
int binarySearch(DynamicArray* arr, char* key) {
	int low = 0;
	int high = arr->amount - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (strcmp(((Product*)arr->p[mid])->num, key) == 0)
			return mid;
		if (strcmp(((Product*)arr->p[mid])->num, key) == 1)
			high = mid - 1;
		if (strcmp(((Product*)arr->p[mid])->num, key) == -1)
			low = mid + 1;
	}
	return -1;

}


//��ӭ����
void welcome()
{
	if (system("cls") != 0)exit(0);
	char password[60] = "\0";
	printf("%10s %s\n\n", "", "----------------------------------------");
	printf("%15s %s\n\n", "", "��ӭ����329С����ϵͳ��ϵͳ������");
	printf("%10s %s\n\n", "", "----------------------------------------");
	printf("%11s %s", "", "��������λ���룺");
	for (size_t i = 0; i < sizeof(password) / sizeof(password[0]); i++)
	{
		char ch = getch();
		if (ch == '\r')break;
		if (ch == '\b'&&i > 0) {
			password[--i] = '\0';
			i--;
		}
		else
		{
			password[i] = ch;
			if (password[0] == '\b')i--;
		}
	}
	//�ж������Ƿ���ȷ
	if (strcmp(password, PASSWORD) == 0)
	{
		printf("\n\n\n%25s %s\n", "", "����ɹ�!");
		printf("%10s %s\n\n", "", "----------------------------------------");
		printf("\n\n%s", "���¡������������ �������˵���");
		getch();
	}
	else
	{
		if (count++ == 4) {
			printf("\n\n%30s %s  ", "", "���������������,�˳�ϵͳ...");
			Sleep(1500);
			if (system("cls") != 0)exit(0);
			exit(0);
		}
		if (strlen(password) > 6)
			printf("\n\n%30s %s  ", "", "�����������");
		else
			printf("\n\n%30s %s ", "", "���������");
		Sleep(1500);
		welcome();
	}
}
//¼����Ϣ
Product *input() //����product
{
	char string[100];
	Product *product = (Product *)malloc(sizeof(Product));
	printf("���ȵı�ţ�");
	gets(&(product->num));
	//У����Ʒ��Ÿ�ʽ
	error_gets(product->num, CHECK_NUM, "A-Z��ͷ,����4λ���ֽ�β >>");

	printf("���ȵ����ƣ�");
	gets(&(product->name));
	//У�����Ƶĳ���
	while (strlen(product->name) > 10)
	{
		printf("\n�����10λ�������� >> ");
		gets(&(product->name));
	}
	//���Ʋ���10λ,�ո���
	int len = 10 - strlen(product->name);
	while (len--)strcat(product->name, " ");
	printf("���ȵļ۸�");
	gets(string);
	//У�� price
	error_gets(string, CHECK_FLOAT, " ���͡����� >> ");
	while (strlen(string) > 11)
	{
		printf("\n �۸��11λ�������� >> ");
		gets(string);
	}
	product->price = atof(string);
	printf("���ոò�����������");
	gets(string);
	//У����Ʒ����
	error_gets(string, CHECK_INT, "����ֵ������ ��>> ");
	while (strlen(string) > 10)
	{
		printf("\n ����ֵ�10λ�������� >> ");
		gets(string);
	}
	product->count = atoi(string);
	product->sale = product->price * product->count;
	return product;
}

/*����<1>-->��ʾ�˵���Ϣ �������
products �˵��б�
sortMark ����ʽ
*/
void show_products(TreeMap* products, int sortMark) {
	if (NULL == products) 
		printf("\n  %s  ", "û���κ���Ʒ��Ϣ");
	else
	{
		printf("%s        %s          %s            %s       %s", "���", "����", "����", "��������", "���۶�");
		DynamicArray* values = getValues_TreeMap(products);
		//�ж�����ʽ
		if (sortMark == PRICE_SORT) heapSort(values);
		if (sortMark == SALE_SORT) shellSort(values);
		for (size_t i = 0; i < values->amount; i++)
		{
			//���²����Ǳ�֤��ӡ��ʽ������
			char* name = ((Product*)values->p[i])->name;
			char* num = ((Product*)values->p[i])->num;
			float price = ((Product*)values->p[i])->price;
			int count = ((Product*)values->p[i])->count;
			float sale = ((Product*)values->p[i])->sale;
			char sprice[100];
			char scount[100];
			sprintf(sprice, "%.2f", price);
			sprintf(scount, "%d", count);
			int pi = 11 - strlen(sprice);
			while (pi--)strcat(sprice, " ");
			int ci = 10 - strlen(scount);
			while (ci--)strcat(scount, " ");
			printf("\n%s       %s    %s     %s     %.2f", num, name, sprice, scount, sale);
			printf("\n");
		}
		printf("\n\n��Ʒ����:%d", values->amount);
		free_DynamicArray(values);
	}
}

/*
����<2>-->��Ӳ���
*/
void add_product(TreeMap** products)
{
	int count = 1;
	printf("\n\n");
	while (count)
	{
		char is[100];
		Product *product = input();
		printf("\n");
		if (NULL == *products) {
			//fuck �������ݴ���,������һ��Сʱ��bug
			*products = creat_TreeMap(product->num, product);
		}
		else
		{
			insert_TreeMap(*products, product, product->num);
		}
		printf("    ����¼�룿[y/n]: "); gets(is);
		//У���Ƿ��������
		error_gets(is, CHECK_Y_N, "  ��y|n��?__? >> ");
		printf("\n");
		count = strcmp(is, "n");
	}

}

/*
����<3>-->ɾ������
*/
void remove_product(TreeMap** products) {
	char num[100];
	printf("\nҪɾ�����ȵı�� : ");
	gets(num);
	int status = delete_TreeMap(products, num);
	if (status == 0)
		printf("\nɾ���ɹ�!\n");
	else
		printf("\nû�ж�Ӧ�Ĳ���,�޷�ɾ��!\n");
}

/*
����<4>-->�޸Ĳ���
*/
void update_product(TreeMap** products) {
	char key[100];
	printf("\nҪ�޸Ĳ��ȵı�� : ");
	gets(key);
	TreeMap* up = search_TreeMap(*products, key);
	if (NULL == up)
	{
		printf("\nû�ж�Ӧ�Ĳ���,�޷��޸�!\n");
	}
	else
	{
		char string[100];
		Product *product = (Product*)up->value;

		printf("\n���ȵ����ƣ�");
		gets(&(product->name));
		//У�����Ƶĳ���
		while (strlen(product->name) > 10)
		{
			printf("\n�����10λ�������� >> ");
			gets(&(product->name));
		}
		//����10λ �ո�ȫ
		int len = 10 - strlen(product->name);
		while (len--)strcat(product->name, " ");
		printf("���ȵļ۸�");
		gets(string);
		//У�� price
		error_gets(string, CHECK_FLOAT, " ���͡����� >> ");
		while (strlen(string) > 11)
		{
			printf("\n �۸��11λ�������� >> ");
			gets(string);
		}
		product->price = atof(string);

		printf("���ոò��ȵ���������");
		gets(string);
		//У��count
		error_gets(string, CHECK_INT, "����ֵ������ ��>> ");
		while (strlen(string) > 10)
		{
			printf("\n ����ֵ�10λ�������� >> ");
			gets(string);
		}
		product->count = atoi(string);
		product->sale = product->price * product->count;
	}
}

/*
����<5>-->���Ҳ���
*/
void search_product(TreeMap** products, int searchMark) {
	char key[100];
	printf("\n\nҪ������Ʒ�ı�� : ");
	gets(key);
	printf("\n");

	if (BINARY_SEARCH_ID == searchMark) { //���ֲ���
		TreeMap* search = NULL;
		DynamicArray* arr = getValues_TreeMap(*products);
		int stu = binarySearch(arr, key);
		if (stu != -1) {
			search = creat_TreeMap(((Product*)arr->p[stu])->num, arr->p[stu]);
			show_products(search, ID_SORT);
			free(search);
		}
		else show_products(search, ID_SORT);
		free_DynamicArray(arr);
	}
	else if (BST_SEARCH_ID == searchMark) {//�������
		TreeMap* se = NULL;
		TreeMap* search = search_TreeMap(*products, key);
		if (NULL != search)
			se = creat_TreeMap(search->key, search->value);
		show_products(se, ID_SORT);
		free(se);
	}
}
	


//�����˵�
void option_menu() {
	system("cls");
	printf("\t%s  \n", "*************************************");
	printf("%s\n", "\t*            1 �� ������Ϣ          *");
	printf("%s\n", "\t*            2 �� ��Ӳ���          *");
	printf("%s\n", "\t*            3 �� ɾ������          *");
	printf("%s\n", "\t*            4 �� �޸Ĳ���          *");
	printf("%s\n", "\t*            5 �� ���Ҳ���          *");
	printf("%s\n", "\t*            0 �� �˳�ϵͳ          *");
	printf("\t%s  \n\n","*************************************");
	printf("%s", "���������<0-5> :");
	char option[100];
	gets(option);
	while (check(option, CHECK_OPTION) == 2) {
		printf("\n%s", "������<0-5> :");
		gets(option);
	}
	int i = atoi(option);
	switch (i)
	{
	case 1://�鿴������Ϣ
	{
		printf("\n%s   %s   %s %s\n", "ѡ������ʽ:", "s �������(BST)", "p �۸�����(������)", "j ���۶�����(ϣ������)");
		char* sort = getch();
		while ( 's'!=sort&& 'p'!=sort && 'j' != sort) {
			sort = getch();
		}
		if ( 's'==sort) {
			system("cls");
			show_products(products, ID_SORT);//����������
		}
		if ('p'==sort) {
			system("cls");
			show_products(products, PRICE_SORT);
		}
		if ('j' == sort) {
			system("cls");
			show_products(products, SALE_SORT);
		}
		printf("\n\n%s", "���¡������������ �������˵���");
		getch();
		option_menu();
	}
	break;
	case 2://��Ӳ���
	{
		add_product(&products);
		system("cls");
		option_menu();
	}
	break;
	case 3://ɾ������
	{
		char num[100];
		int count = 1;
		while (count) {
			remove_product(&products);
			printf("\n����ɾ���� [y/n]: "); gets(num);
			error_gets(num, CHECK_Y_N, "��y|n�� >> ");
			printf("\n");
			count = strcmp(num, "n");
		}
		option_menu();
	}
	break;
	case 4://�޸Ĳ�����Ϣ
	{
		char num[100];
		int count = 1;
		while (count) {
			update_product(&products);//����������
			printf("\n�����޸ģ� [y/n]: "); gets(num);
			error_gets(num, CHECK_Y_N, "��y|n�� >> ");
			printf("\n");
			count = strcmp(num, "n");
		}
		option_menu();
	}
	break;
	case 5://���Ҳ�����Ϣ
	{
		printf("\n%s   %s   %s\n", "ѡ�����:", "s ���(����������)", "   p ���(���ֲ���)");
		char* search = getch();
		while ('s' != search && 'p' != search) {
			search = getch();
		}
		if ('s'== search) {
			search_product(&products,BST_SEARCH_ID);//��������������
		}
		if ('p' == search) {
			search_product(&products, BINARY_SEARCH_ID);
		}
		printf("\n\n%s", "���¡������������ �������˵���");
		getch();
		option_menu();
	}
	break;
	case 0://�˳�ϵͳ
	{
		DynamicArray* arr = getValues_TreeMap(products);
		for (size_t i = 0; i < arr->amount; i++)
		{
			free(arr->p[i]);
		}
		free_DynamicArray(arr); 
		free_TreeMap(products);
		printf("\n�˳�ϵͳ,��ӭ�ٴ�ʹ��!");
		Sleep(1000);
		exit(0);
	}
		break;
	}
}


int main()
{
	welcome();
	option_menu();
	return 0;
}