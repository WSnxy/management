#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int len;
	int amount;
	void **p;
} DynamicArray;

DynamicArray *init_DynamicArray(int len)
{
	if (len < 0)
	{
		return NULL;
	}
	DynamicArray *array = (DynamicArray *)malloc(sizeof(DynamicArray));
	if (array == NULL)
	{
		return NULL;
	}
	array->len = len;
	array->amount = 0;
	array->p = (void **)malloc(sizeof(void *) * len);
	return array;
}

int insert_DynamicArray(DynamicArray *array, void *en, int pos)
{

	if (array->amount >= array->len)
	{
		int len2 = array->len * 2;
		void **pp = malloc(sizeof(void *) * len2);
		memcpy(pp, array->p, sizeof(void *) * array->len);
		free(array->p);
		array->p = pp;
		array->len = len2;
	}
	if (pos < 0 || pos > array->len)
	{
		return 1;
	}

	array->p[pos] = en;
	array->amount++;
	return 0;
}
void free_DynamicArray(DynamicArray* dya) {
	free(dya->p);
	free(dya);
}
//开辟了一片内存，自动扩展，两倍扩展。
