#ifndef  __H_DYNAMICARRAY_
#define  __H_DYNAMICARRAY_
/*
��̬���� 2������
*/
typedef struct
{
	int len;
	int amount;
	void **p;
} DynamicArray;
//��ʼ������
DynamicArray *init_DynamicArray(int len);
//�����������Ԫ��
int insert_DynamicArray(DynamicArray *array, void *en, int pos);
//�ͷ�����
void free_DynamicArray(DynamicArray* dya);

#endif 
