#include "str_lb.h"



int str_len(char* txt)
{
	int i;

	for (i = 0; (*txt) != '\0'; i++)
	{
		txt++;
	}
	return i;
}





char* str_str(char* txt, const char* w)
{
	int i;
	int j;
	int flag;
	char* c;
	flag = 0;
	i = 0;
	j = 0;
	
		while (*(txt + i) != '\0')
		{
			if (flag) break;
			while ((*(txt + i) == *(w + j)) && (*(w + j) != '\0'))
			{

				i++;
				j++;
				if (*(w + j) == '\0') flag++;
			}
			i++;
		}
	
	

	
	c = txt + i - j - 1;
	if (flag) return c;
	else
	{
		return NULL;
	}
}
