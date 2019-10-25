#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>
#include "check.h"
#include"dyArray.h"
#include"treeMap.h"
#pragma warning(disable:4996)
static const char* PASSWORD = "123456";  //密码
#define ID_SORT 0						//编号查找 二叉排序树
#define PRICE_SORT 1					//价格查找 堆排序
#define SALE_SORT 2                     //销售额查找 希尔排序
#define BST_SEARCH_ID 0                 //编号查找 二叉排序树
#define BINARY_SEARCH_ID 1              //编号查找 二分查找
int c = 0;
int count = 1;
TreeMap* products = NULL;				//菜谱信息

//商品
typedef struct
{
	char name[100];  //菜肴名
	char num[100]; //菜肴编号
	float price;    //单价
	int count;      //销售量
	float sale;     //销售额
} Product;
//堆排序
void maxHeap(DynamicArray* arr, int size, int index) {
	//左孩子角标
	int leftNode = 2 * index + 1;
	//右孩子角标
	int rightNode = 2 * index + 2;
	//计算最大值得角标
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
	//调整为大顶堆
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
//希尔排序
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

//二分查找
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


//欢迎界面
void welcome()
{
	if (system("cls") != 0)exit(0);
	char password[60] = "\0";
	printf("%10s %s\n\n", "", "----------------------------------------");
	printf("%15s %s\n\n", "", "欢迎来到329小饭桌系统，系统启动！");
	printf("%10s %s\n\n", "", "----------------------------------------");
	printf("%11s %s", "", "请输入六位密码：");
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
	//判断密码是否正确
	if (strcmp(password, PASSWORD) == 0)
	{
		printf("\n\n\n%25s %s\n", "", "登入成功!");
		printf("%10s %s\n\n", "", "----------------------------------------");
		printf("\n\n%s", "按下【任意键】进入 【操作菜单】");
		getch();
	}
	else
	{
		if (count++ == 4) {
			printf("\n\n%30s %s  ", "", "尝试密码次数过多,退出系统...");
			Sleep(1500);
			if (system("cls") != 0)exit(0);
			exit(0);
		}
		if (strlen(password) > 6)
			printf("\n\n%30s %s  ", "", "【密码过长】");
		else
			printf("\n\n%30s %s ", "", "【密码错误】");
		Sleep(1500);
		welcome();
	}
}
//录入信息
Product *input() //放在product
{
	char string[100];
	Product *product = (Product *)malloc(sizeof(Product));
	printf("菜肴的编号：");
	gets(&(product->num));
	//校验商品编号格式
	error_gets(product->num, CHECK_NUM, "A-Z开头,任意4位数字结尾 >>");

	printf("菜肴的名称：");
	gets(&(product->name));
	//校验名称的长度
	while (strlen(product->name) > 10)
	{
		printf("\n名称最长10位【过长】 >> ");
		gets(&(product->name));
	}
	//名称不足10位,空格补齐
	int len = 10 - strlen(product->name);
	while (len--)strcat(product->name, " ");
	printf("菜肴的价格：");
	gets(string);
	//校验 price
	error_gets(string, CHECK_FLOAT, " 类型【有误】 >> ");
	while (strlen(string) > 11)
	{
		printf("\n 价格最长11位【过长】 >> ");
		gets(string);
	}
	product->price = atof(string);
	printf("今日该菜肴销售量：");
	gets(string);
	//校验商品数量
	error_gets(string, CHECK_INT, "数量值【有误 】>> ");
	while (strlen(string) > 10)
	{
		printf("\n 数量值最长10位【过长】 >> ");
		gets(string);
	}
	product->count = atoi(string);
	product->sale = product->price * product->count;
	return product;
}

/*操作<1>-->显示菜单信息 编号排序
products 菜单列表
sortMark 排序方式
*/
void show_products(TreeMap* products, int sortMark) {
	if (NULL == products) 
		printf("\n  %s  ", "没有任何商品信息");
	else
	{
		printf("%s        %s          %s            %s       %s", "编号", "名称", "单价", "销售数量", "销售额");
		DynamicArray* values = getValues_TreeMap(products);
		//判断排序方式
		if (sortMark == PRICE_SORT) heapSort(values);
		if (sortMark == SALE_SORT) shellSort(values);
		for (size_t i = 0; i < values->amount; i++)
		{
			//以下操作是保证打印格式不乱套
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
		printf("\n\n商品总数:%d", values->amount);
		free_DynamicArray(values);
	}
}

/*
操作<2>-->添加菜肴
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
			//fuck 参数传递错误,我找了一个小时的bug
			*products = creat_TreeMap(product->num, product);
		}
		else
		{
			insert_TreeMap(*products, product, product->num);
		}
		printf("    继续录入？[y/n]: "); gets(is);
		//校验是否继续输入
		error_gets(is, CHECK_Y_N, "  【y|n】?__? >> ");
		printf("\n");
		count = strcmp(is, "n");
	}

}

/*
操作<3>-->删除菜肴
*/
void remove_product(TreeMap** products) {
	char num[100];
	printf("\n要删除菜肴的编号 : ");
	gets(num);
	int status = delete_TreeMap(products, num);
	if (status == 0)
		printf("\n删除成功!\n");
	else
		printf("\n没有对应的菜肴,无法删除!\n");
}

/*
操作<4>-->修改菜肴
*/
void update_product(TreeMap** products) {
	char key[100];
	printf("\n要修改菜肴的编号 : ");
	gets(key);
	TreeMap* up = search_TreeMap(*products, key);
	if (NULL == up)
	{
		printf("\n没有对应的菜肴,无法修改!\n");
	}
	else
	{
		char string[100];
		Product *product = (Product*)up->value;

		printf("\n菜肴的名称：");
		gets(&(product->name));
		//校验名称的长度
		while (strlen(product->name) > 10)
		{
			printf("\n名称最长10位【过长】 >> ");
			gets(&(product->name));
		}
		//不足10位 空格补全
		int len = 10 - strlen(product->name);
		while (len--)strcat(product->name, " ");
		printf("菜肴的价格：");
		gets(string);
		//校验 price
		error_gets(string, CHECK_FLOAT, " 类型【有误】 >> ");
		while (strlen(string) > 11)
		{
			printf("\n 价格最长11位【过长】 >> ");
			gets(string);
		}
		product->price = atof(string);

		printf("今日该菜肴的销售量：");
		gets(string);
		//校验count
		error_gets(string, CHECK_INT, "数量值【有误 】>> ");
		while (strlen(string) > 10)
		{
			printf("\n 数量值最长10位【过长】 >> ");
			gets(string);
		}
		product->count = atoi(string);
		product->sale = product->price * product->count;
	}
}

/*
操作<5>-->查找菜肴
*/
void search_product(TreeMap** products, int searchMark) {
	char key[100];
	printf("\n\n要查找商品的编号 : ");
	gets(key);
	printf("\n");

	if (BINARY_SEARCH_ID == searchMark) { //二分查找
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
	else if (BST_SEARCH_ID == searchMark) {//二叉查找
		TreeMap* se = NULL;
		TreeMap* search = search_TreeMap(*products, key);
		if (NULL != search)
			se = creat_TreeMap(search->key, search->value);
		show_products(se, ID_SORT);
		free(se);
	}
}
	


//操作菜单
void option_menu() {
	system("cls");
	printf("\t%s  \n", "*************************************");
	printf("%s\n", "\t*            1 — 菜肴信息          *");
	printf("%s\n", "\t*            2 — 添加菜肴          *");
	printf("%s\n", "\t*            3 — 删除菜肴          *");
	printf("%s\n", "\t*            4 — 修改菜肴          *");
	printf("%s\n", "\t*            5 — 查找菜肴          *");
	printf("%s\n", "\t*            0 — 退出系统          *");
	printf("\t%s  \n\n","*************************************");
	printf("%s", "输入操作项<0-5> :");
	char option[100];
	gets(option);
	while (check(option, CHECK_OPTION) == 2) {
		printf("\n%s", "请输入<0-5> :");
		gets(option);
	}
	int i = atoi(option);
	switch (i)
	{
	case 1://查看菜肴信息
	{
		printf("\n%s   %s   %s %s\n", "选择排序方式:", "s 编号排序(BST)", "p 价格排序(堆排序)", "j 销售额排序(希尔排序)");
		char* sort = getch();
		while ( 's'!=sort&& 'p'!=sort && 'j' != sort) {
			sort = getch();
		}
		if ( 's'==sort) {
			system("cls");
			show_products(products, ID_SORT);//二叉排序树
		}
		if ('p'==sort) {
			system("cls");
			show_products(products, PRICE_SORT);
		}
		if ('j' == sort) {
			system("cls");
			show_products(products, SALE_SORT);
		}
		printf("\n\n%s", "按下【任意键】返回 【操作菜单】");
		getch();
		option_menu();
	}
	break;
	case 2://添加菜肴
	{
		add_product(&products);
		system("cls");
		option_menu();
	}
	break;
	case 3://删除菜肴
	{
		char num[100];
		int count = 1;
		while (count) {
			remove_product(&products);
			printf("\n继续删除？ [y/n]: "); gets(num);
			error_gets(num, CHECK_Y_N, "【y|n】 >> ");
			printf("\n");
			count = strcmp(num, "n");
		}
		option_menu();
	}
	break;
	case 4://修改菜肴信息
	{
		char num[100];
		int count = 1;
		while (count) {
			update_product(&products);//二叉排序树
			printf("\n继续修改？ [y/n]: "); gets(num);
			error_gets(num, CHECK_Y_N, "【y|n】 >> ");
			printf("\n");
			count = strcmp(num, "n");
		}
		option_menu();
	}
	break;
	case 5://查找菜肴信息
	{
		printf("\n%s   %s   %s\n", "选择查找:", "s 编号(二叉排序树)", "   p 编号(二分查找)");
		char* search = getch();
		while ('s' != search && 'p' != search) {
			search = getch();
		}
		if ('s'== search) {
			search_product(&products,BST_SEARCH_ID);//二叉排序树查找
		}
		if ('p' == search) {
			search_product(&products, BINARY_SEARCH_ID);
		}
		printf("\n\n%s", "按下【任意键】返回 【操作菜单】");
		getch();
		option_menu();
	}
	break;
	case 0://退出系统
	{
		DynamicArray* arr = getValues_TreeMap(products);
		for (size_t i = 0; i < arr->amount; i++)
		{
			free(arr->p[i]);
		}
		free_DynamicArray(arr); 
		free_TreeMap(products);
		printf("\n退出系统,欢迎再次使用!");
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