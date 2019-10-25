#ifndef  __H_DYNAMICARRAY_
#define  __H_DYNAMICARRAY_
/*
动态数组 2倍扩容
*/
typedef struct
{
	int len;
	int amount;
	void **p;
} DynamicArray;
//初始化数组
DynamicArray *init_DynamicArray(int len);
//向数组中添加元素
int insert_DynamicArray(DynamicArray *array, void *en, int pos);
//释放数组
void free_DynamicArray(DynamicArray* dya);

#endif 
