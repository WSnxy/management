#include<stdio.h>
#include<regex.h>

/*
 *对传入的正则进行匹配
 *param1 原字符串
 *param2 正则字符串
 *编译失败返回1
 *匹配失败返回2
 *匹配成功返回0
 检验输入录入的信息
 * */
const char* CHECK_FLOAT = "^[0-9]{1,8}(\\.)?[0-9]{0,}$";
const char* CHECK_INT = "^[0-9]{1,}$";
const char* CHECK_Y_N = "^(y|n){1}$";
const char* CHECK_OPTION = "^[0-5]{1}$";
const char* CHECK_NUM= "^[A-Z]{1}[0-9]{4}$";
int check(char *string, char *pattern)
{
	regex_t preg;
	size_t nmatch = 1;
	regmatch_t pmatch[1024];
	int comp = regcomp(&preg, pattern, REG_EXTENDED);
	if (comp != 0)
	{
		return 1;
	}
	int ec = regexec(&preg, string, nmatch, pmatch, 0);
	if (ec != 0)
	{
		return 2;
	}
	regfree(&preg);
	return 0;
}

void error_gets(char* s,char* regex,char* error_massage) {
	while (check(s, regex) == 2)
	{
		printf(error_massage);
		gets(s);
	}

}