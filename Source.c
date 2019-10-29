#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>
//#include <string.h>
#include "str_lb.h"

void tk_arg(char arr0[],char file[],char w0[],char  w1[],char com[]);
void car_op(char com,char w0[],char w1[],char file[] );

/*--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/
int main(void)
{
	char arr0[278];		//the command entered
	char file[65];	    //the file name
	char w0[65];		//the first word
	char w1[65];		//the last word
	char com[8];		//the operations
	char s;				//showing help(switch arg.)
	int com_num;		//number of the elements in the operation array
	int i;				//counter index
	
	printf("Enter 'q' for help or 'c' to enter a command\n");
	scanf("%c", &s);
	while (getchar() != '\n');
	switch (s)
	{
	case 'q':
		printf("To use replace : ");
		printf("enter the command as follows : \n");
		printf("replace opt <from><to>--<filename>\n");
		printf("opt : -b --> backup\n");
		printf("	In case of choosing back up:\n replace -b <><new_file_name>--<original_file_name>\n\n");
		printf("opt : -f --> replace first match\n");
		printf("opt : -l --> replace last match\n");
		printf("opt : -i --> replace all matches\n");

		printf("Inaccurate results for 1 character\n type is as ( c)\n");


	case 'c':
		printf("Enter the freaking command\n");
		fgets(arr0, sizeof(arr0), stdin);
		tk_arg(arr0, file, w0, w1, com);//determine the first , the last words and the file name

		/*
		printf("%s\n", arr0);
		printf("%s\n", w0);
		printf("%s\n", w1);
		printf("%s\n", com);
		printf("%s\n", file);
		*/

		com_num = str_len(com);
		for (i = 0;i < com_num;i++)
		{
			car_op(com[i],w0,w1,file);
		}
		

		break;
	}
	getchar();
	return 0;
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
void tk_arg(char arr0[], char file[], char w0[], char  w1[],char com[])
{
	int ct;//'<' counter
	int i;
	int j;//counter indices

	
	
	ct = 0;
	j = 0;


	for (i = 0;ct <= 2;i++)
	{
		if ((arr0[i] == '-')&&(arr0[i+1]!='-')&&(arr0[i+1]!='<'))
		{
			i++;
			while (arr0[i] != '<')
			{
				com[j] = arr0[i];
				i += 2;
				j++;
			}
			com[j] = '\0';
			j = 0;
			i--;
		}


		else if (arr0[i] == '<' && ct == 0)
		{
			i++;
			while (arr0[i] != '>')
			{
				w0[j] = arr0[i];
				j++;
				i++;
			}
			w0[j] = '\0';
			ct++;
			j = 0;
		}


		else if (arr0[i] == '<' && ct == 1)
		{
			i++;
			while (arr0[i] != '>')
			{
				w1[j] = arr0[i];
				j++;
				i++;
			}
			w1[j] = '\0';
			ct++;
			j = 0;
		}

		else if (arr0[i] == '<' && ct == 2)
		{
			i++;
			while (arr0[i] != '>')
			{
				file[j] = arr0[i];
				j++;
				i++;
			}
			file[j] = '\0';
			ct++;
		}
	}
}
/*---------------------------------------------------------------------*/
void car_op(char com, char w0[], char w1[], char file[])
{
	FILE* pf;
	char* c_1;			//the first character of the searched word
	//char* c_2;			//sub c_1
	char* txt;
	char* rem_txt;		//remainder of the original text
	int size;
	int count;			//the number of repitions os the searched word
	int diff;			//the difference in the lengthes of the two strings
	int dis;			//the distance between two pointerse

	size= 0;

	pf = fopen(file, "rb");
	fseek(pf, 0, SEEK_END);
	size = ftell(pf);
	txt = (char*)malloc(size);
	*(txt + size + 1) = '\0';
	rem_txt = (char*)malloc(size);
	rewind(pf);
	fread(txt,size,1,pf);
	
	switch (com)
	{
		case 'f':
			
			c_1=str_str(txt, w0);//the first character of the word to be changed
			dis = c_1 - txt;//the number of the characters before the word to be changed
			if (c_1 == NULL)
			{
				printf("Specified word not found\n");
			}
			else
			{	
				freopen(file, "w", pf);
				//if (str_len(w0) > str_len(w1)) size = size-(str_len(w1)-str_len(w0));
				//else if (str_len(w1) > str_len(w0)) size -= (dis + str_len(w0));
				size -= (dis + str_len(w0));
				rem_txt = txt + dis+str_len(w0);
				fwrite(txt, dis, 1, pf);
				fwrite(w1, str_len(w1), 1, pf);
				fwrite(rem_txt, size, 1, pf);
				fclose(pf);
				free(txt);
			}
			break;

		case 'i':
			freopen(file, "w", pf);
			c_1 = str_str(txt,w0);
			if (c_1 == NULL)
			{
				printf("Specified word not found\n");
				exit(1);
			}
			
			else
			{
				while (c_1 != NULL)
				{
					dis = c_1 - txt;
					rem_txt = txt + dis + str_len(w0);
					fwrite(txt, dis, 1, pf);
					fwrite(w1, str_len(w1), 1, pf);
					diff = str_len(txt) - str_len(rem_txt);
					size -= diff;
					txt = rem_txt;
					c_1 = str_str(txt, w0);
				}
				fwrite(txt, size, 1, pf);
				
			}
				break;

		case'l':
			freopen(file, "w", pf);
			c_1 = str_str(txt, w0);
			if (c_1 == NULL) printf("Specified word not found\n");
			else
			{
				//rem_txt is the sector of the last repeated word
				count = 0;
				while (c_1 != NULL)
				{
					dis = c_1 - txt;
					rem_txt = txt + dis;
					c_1 = str_str(rem_txt+str_len(w0), w0);
				}
				fwrite(txt, str_len(txt) - str_len(rem_txt), 1, pf);
				fwrite(w1, str_len(w1), 1, pf);
				diff = str_len(txt) - str_len(rem_txt);
				size -= (diff+str_len(w0));
				fwrite(rem_txt + str_len(w0),size, 1, pf);
				
			}
			break;

		case 'b':
			fclose(pf);
			pf=fopen(w1, "w");
			fwrite(txt,str_len(txt)-1,1,pf);
	}
}