#ifndef  __H_CHECK_
#define  __H_CHECK_

const char* CHECK_FLOAT;//ƥ����
const char* CHECK_INT;//ƥ������
const char* CHECK_Y_N;//ƥ��y��n  �ǻ��߷�
const char* CHECK_OPTION;
const char* CHECK_NUM;
int check(char *string, char *pattern);//ƥ������
void error_gets(char* s, char* regex, char* error_massage);
#endif 
//����������ͣ����������
