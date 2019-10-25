#include<stdio.h>
#include<regex.h>

/*
 *�Դ�����������ƥ��
 *param1 ԭ�ַ���
 *param2 �����ַ���
 *����ʧ�ܷ���1
 *ƥ��ʧ�ܷ���2
 *ƥ��ɹ�����0
 ��������¼�����Ϣ
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