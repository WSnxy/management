#ifndef  __H_CHECK_
#define  __H_CHECK_

const char* CHECK_FLOAT;//匹浮点
const char* CHECK_INT;//匹配整形
const char* CHECK_Y_N;//匹配y或n  是或者否
const char* CHECK_OPTION;
const char* CHECK_NUM;
int check(char *string, char *pattern);//匹配正则
void error_gets(char* s, char* regex, char* error_massage);
#endif 
//检验各种类型，检验操作。
