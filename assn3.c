#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_FILE_NAME 30

void mainmenu();
int checksame(char cmd[], char* word);
void erase();
void command();
int mystrlen(char* str);
int mystrcmp(char* str1, char* str2);
char* mystrcpy(char* toStr, char* fromStr);
char* mystrlower(char* str);
int training(int* judg);
int test(int* judg);
void printerror();
void printerror2();
char* mystrblank(char* str);
void swap(int* a, int* b);

int main()
{
	command();
	return 0;
}

//test �ܰ� 
int test(int* judg)
{
	FILE* openf=fopen("stats.txt", "r");
	/*stats.txt������ ���� ��� 
	���� �޽��� ��� �� ���� �޴��� ���ư���*/
	if (openf == NULL)
	{
		erase();
		mainmenu();
		printerror2();
		Sleep(1000);
		erase();
		return 0;
	}
	/*stats.txt ������ �����ϴ� ���*/
	else
	{
		char text[1000];
		char line[100];
		char text2[1000];
		char** words;
		char** textw;
		char* token;
		char* token2;
		int* sfreq;
		int* hfreq;
		int ham, spam, i, j;
		char h, s;
		float pham, pspam, totph, totps;
		int num = 0;
		int z = 5;
		int* ywn;
		char* temp;
		words = (char**)calloc(5, sizeof(char*));
		textw = (char**)calloc(5, sizeof(char*));
		sfreq = (int*)calloc(5, sizeof(int));
		hfreq = (int*)calloc(5, sizeof(int));
		ywn = (int*)calloc(5, sizeof(int));
		//�������� �ƴ��� Ȯ���� ���� �Է¹ޱ�
		printf("Enter a message: ");
		gets(text);
		strcpy(text2, text);
		mystrlower(text);	
		mystrblank(text);

		//stats.txt ���Ͽ��� ���� �ҷ�����
		fscanf(openf, "Ham: %d, Spam: %d\n", &ham, &spam);
		while (1)
		{
			fgets(line, sizeof(line), openf);
			if (feof(openf))
				break;
			//stats.txt ���� ,�� �������� �߶� �б�
			temp = strtok(line, ",");
			words[num] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
			strcpy(words[num], temp);
			temp = strtok(NULL, ",");
			hfreq[num] = atoi(temp);
			temp = strtok(NULL, ",");
			sfreq[num] = atoi(temp);
			num++;
			//�޸� ���Ҵ�
			if (num != 0 && num == z - 1)
			{
				z = 2 * z;
				words = (char**)realloc(words, z * sizeof(char*));
				hfreq = (int*)realloc(hfreq, z * sizeof(int));
				sfreq = (int*)realloc(sfreq, z * sizeof(int));
			}
			else;
		}
		const int filen = num;
		j = 0;
		num = 0;
		z = 5;

		//�Էµ� ���� ���� ������ �ڸ���1
		token = strtok(text, " ");    
		if (token == NULL);
		else if (strcmp(token, " ") == 0 || strcmp(token, "") == 0);
		else
		{
			textw[num] = (char*)calloc(mystrlen(token) + 1, sizeof(char));
			textw[num] = token;
			num++;
		}

		//�Էµ� ���� ���� ������ �ڸ���2
		j = 0;
		while (1)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			else if (strcmp(token, " ") == 0 || strcmp(token, "") == 0)
				continue;
			textw[num] = (char*)calloc(mystrlen(token) + 1, sizeof(char));
			textw[num] = token;
			
			//������ ������ �ܾ �ִ��� �˻��ϱ�
			j = 0;
			while (j < num)
			{
				if (mystrcmp(textw[j], textw[num]) == 0)
				{
					num--;
					break;
				}
				j++;
			}
			num++;
			//�޹��� ���Ҵ�
			if (num != 0 && num == z - 1)
			{
				z = 2 * z;
				textw = (char**)realloc(textw, z * sizeof(char*));
				ywn = (int*)realloc(ywn, z * sizeof(int));
			}
			else;
		}
		
		const int textn = num;
	
		//���� �� �ܾ ��迡 ���ԵǴ��� Ȯ���ϱ�
		for (i = 0; i<textn ; i++)
		{
			ywn[i] = -1;
			for (j = 0; j < filen; j++)
			{
				if (mystrcmp(textw[i], words[j]) == 0)
				{
					ywn[i] = j;
					break;
				}
				else;
			}
		}

		//������ Ȯ��, �ƴ� Ȯ�� ���
		pham = (float)ham / (float)(ham + spam);
		pspam = (float)spam / (float)(ham + spam);
		printf("\n\nP(Ham) = %.3f, P(Spam)=%.3f\n\n", pham, pspam);

		totph = (float)pham;
		totps = (float)pspam;
		for (i = 0; i < textn; i++)
		{
			if (ywn[i] == -1)
				continue;
			else
			{
				if (hfreq[ywn[i]] == 0)
					pham =(float) 0.1 / (float)ham;
				else
					pham = (float)hfreq[ywn[i]] / (float)ham;
				if (sfreq[ywn[i]] == 0)
					pspam = (float)0.1 / (float)spam;
				else
					pspam = (float)sfreq[ywn[i]] / (float)spam;
				totph = totph * pham;
				totps = totps * pspam;
				printf("P(%s | Ham) = %.3f, P(%s | Spam) = %.3f\n", textw[i], pham, textw[i], pspam);
			}
		}
		printf("\nP(Ham | '%s') : %.3f\n", text2, totph);
		printf("P(Spam | '%s') : %.3f\n\n", text2, totps);
		
		if (totph > totps)
			printf("This message is HAM\n");
		else if (totph < totps)
			printf("This message is SPAM\n");
		else if (totph == totps)
			printf("This message is called SPAM as a HAM\n Help yourself\n");

		//�޸� ���� �Ҵ� ����
		free(sfreq);
		free(hfreq);
		free(ywn);
		for (i = 0; i < textn; i++)
		{
			textw[i] = NULL;
			free(textw[i]);
		}
		free(textw);
		for (i = 0; i < filen; i++)
		{
			words[i] = NULL;
			free(words[i]);
		}
		free(words);


		return 1;
	}	


}

//���� �޴� ����ϱ�
void mainmenu()
{
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED101\n");
	printf("Assignemnt 3\n\n");
	printf("Naive Bayesian Classifier for Spam Filtering\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

//���θ޴����� ������� �Է� �ޱ�
void command()
{
	mainmenu();
	char cmd[10];
	int i, judg, ccs;
	judg = 0;
	printf("Command: ");
	gets(cmd, sizeof cmd, stdin);

	while (judg==0)
	{
		if (checksame(cmd, "train") == 1) //train �Է½�
		{
			ccs=training(&judg);
			if (ccs == 1)
			{
				i = enter();
				if (i == 1)
				{
					erase();
					judg = 1;
					command();
				}
				else;
			}
			else if (ccs == 0)
			{
				judg = 1;
				command();
			}
		}
		else if (checksame(cmd, "test") == 1) //test �Է½�
		{
			ccs=test(&judg);
			if (ccs == 1)
			{
				i = enter();
				if (i == 1)
				{
					erase();
					judg = 1;
					command();
				}
				else;
			}
			else if (ccs == 0)
			{
				judg = 1;
				command();
			}
		}
		else if (checksame(cmd, "exit") == 1) //exit �Է½�
		{
			return;
		}
		else //�� �� �ܾ� �Է½�
		{
			printf("Error: Invalid input");
			Sleep(1000);
			erase();
			judg = 1;
			command();
		}
	}
}

//ȭ�� ����� �Լ�
void erase()
{
	system("cls");
}

//�Էµ� �ܾ ��ҹ��� ���о��� �������� Ȯ��
int checksame(char* cmd, char* word)
{
	for (int i = 0;; i++)
	{
		if (cmd[i] == '\0')
			break;
		else if (word[i] == cmd[i] || word[i]==cmd[i]+32 || word[i]==cmd[i]-32)
			continue;
		else
			return 0;
	}
	return 1;
}

//train ����
int training(int* judg)
{
	//���� �̸� �Է� �ޱ�
	char filename[MAX_FILE_NAME] = {0};
	printf("File name: ");
	gets(filename, MAX_FILE_NAME, stdin);
	int i,j,x,y,spam,ham, z, num, idx1, idx2, idx3;
	FILE* dataset= fopen(filename, "r");
	/*�ش� ������ ���� ���*/
	if (dataset == NULL)
	{
		erase();
		mainmenu();
		printerror();
		Sleep(1000);
		erase();
		return 0;
	}
	else //������ �����ϴ� ���
	{
		char line[1010];
		char** label;
		char** text;
		char* token;
		char* token1;
		char* token2;
		char** words;
		char** tmp;
		char* twords;
		int tfreq;
		int* tmp1;
		int* tmp2;
		int* hfreq;
		int* sfreq;
		for (i = 0; fgets(line, sizeof line, dataset) != NULL; i++); //������ �� ������ �˻�
		const int n = i;
		label = (char**)malloc(n*sizeof(char*));
		text = (char**)malloc(n * sizeof(char*));
		words = (char**)malloc(5 * sizeof(char*));
		twords = (char*)calloc(30, sizeof(char));
		hfreq = (int*)calloc(5, sizeof(int));
		sfreq = (int*)calloc(5, sizeof(int));
		num = 0;
		z = 5;
		idx1 = 0;
		idx2 = 0;
		idx3 = 0;
		fclose(dataset);
		dataset= fopen(filename, "r");
		for (i=0; i<n;i++)
		{
			//���Ͽ��� �� �� �о����
			token1 = NULL;
			fgets(line, sizeof line, dataset);
			mystrlower(line);
			mystrblank(line);
			// \t�� �������� ������ label �о����
			token = strtok(line, "\t");
			label[i] = (char*)calloc(strlen(token)+1, sizeof(char));
			idx3++;
			mystrcpy(label[i], token);
			// \t�� �������� �������� label �о����
			token = NULL;
			token = strtok(NULL, "\t");
			for (x = 0;i<n-1; x++)
			{
				if (token[x] == '\n')
				{
					token[x] = '\0';
					token1 = (char*)calloc(x, sizeof(char));
					mystrcpy(token1, token);
					break;
				}
				else;
			}
			if (i == n - 1)
			{
				text[i] = (char*)calloc(strlen(token) + 1, sizeof(char));
				mystrcpy(text[i], token);
			}
			else
			{
				text[i] = (char*)calloc(strlen(token1) + 1, sizeof(char));
				mystrcpy(text[i], token1);
			}
			idx2++;
			
			//�� �ٿ��� ù ��° �ܾ� �о���� ham, spam Ƚ�� ����
			token2 = strtok(text[i], " ");
			if (strlen(token2) == 1 || strlen(token2) > 20);  //�ܾ� ���̰� 1�̰ų� 20�̻��� ��� ����
			else
			{
				words[num] = (char*)calloc(strlen(token2) + 1, sizeof(char));
				mystrcpy(words[num], token2);
				y = num;
				x = 0;
				sfreq[num] = 0;
				hfreq[num] = 0;
				//������ ������ �ܾ �ִ��� �˻��ϱ�
				while (x < num)
				{
					if (strcmp(words[x], words[num]) == 0)
					{
						y = x;
						idx1--;
						num--;
						break;
					}
					else;
					x++;
				}
				//ham, spam �󵵼� �����ϱ�
				if (strcmp(label[i], "spam") == 0)
				{
					if (sfreq[y] == 0)
						sfreq[y] = 1;
					else
						sfreq[y] += 1;
				}
				else if (strcmp(label[i], "ham") == 0)
				{
					if (hfreq[y] == 0)
						hfreq[y] = 1;
					else
						hfreq[y] += 1;
				}
				num++;
				idx1++;
				//�޸� ������ ��� ���Ҵ�
				if (num != 0 && num == z - 1)
				{
					z = 2 * z;
					words = (char**)realloc(words, z * sizeof(char*));
					hfreq = (int*)realloc(hfreq, z * sizeof(int));
					sfreq = (int*)realloc(sfreq, z * sizeof(int));

				}
				else;	
			}

			
			// �� �ٿ��� ù ��° ���� �ܾ�� �о���� ham,spam Ƚ�� ����
			for(;token2 != NULL;)
			{
				token2 = NULL;

				token2 = strtok(NULL, " ");
				if (token2 == NULL)  //�� �̻� ���� �ܾ ���� ��� ���� �� �б�
					break;
				else if (strcmp(token2, " ") == 0 || strcmp(token2, "") == 0)// ���� �ǳʶٱ�
					continue;
				else if (strlen(token2) == 1 || strlen(token2) > 20)
					continue;
				else;

				words[num] = (char*)malloc((strlen(token2) + 1)*sizeof(char));
				mystrcpy(words[num], token2);
				y = num;
				sfreq[num] = 0;
				hfreq[num] = 0;
				//������ ������ �ܾ �ִ��� �˻��ϱ�
				for(x=0;x< num;x++)
				{
					if (strcmp(words[x], words[num]) == 0)
					{
						y = x;
						num--;
						idx1--;
						break;
					}
					else;
				}
				//ham, spam �󵵼� �����ϱ�
				if (strcmp(label[i], "spam") == 0)
				{
					if (sfreq[y] == 0)
					{
						sfreq[y] = 1;
					}
					else
						sfreq[y] += 1;
				}
				else if (strcmp(label[i], "ham") == 0)
				{
					if (hfreq[y] == 0)
					{
						hfreq[y] = 1;
					}	
					else
						hfreq[y] += 1;
				}
				num++;
				idx1++;
				//�޸� ������ ��� ���Ҵ�
				if (num !=0 && num==z-1)
				{
					z = 2 * z;
					words=(char**)realloc(words, z * sizeof(char*));
					hfreq = (int*)realloc(hfreq, z * sizeof(int));
					sfreq = (int*)realloc(sfreq, z * sizeof(int));
				
				}
				else;
			}
		}
		//���ĺ� ������ �����ϱ�
		for (i = 0; i < num-1; i++)
		{
			for (j = num-1; j > i; j--)
			{
				if (mystrcmp(words[j-1], words[j]) == 1)
				{
					strcpy(twords, words[j - 1]);
					strcpy(words[j - 1], words[j]);
					strcpy(words[j], twords);
					swap(&tfreq, &hfreq[j - 1]);
					swap(&hfreq[j - 1], &hfreq[j]);
					swap(&hfreq[j], &tfreq);
					swap(&tfreq, &sfreq[j - 1]);
					swap(&sfreq[j - 1], &sfreq[j]);
					swap(&sfreq[j], &tfreq);
				}
				else;
			}
		}
		ham = 0;
		spam = 0;
		//ham, spam Ƚ�� ����ϱ�
		for (i = 0; i < n; i++)
		{
			if (strcmp(label[i],"spam")==0)
				spam++;
			else if (strcmp(label[i], "ham")==0)
				ham++;
		}

		//��� ����ϱ�
		printf("\n\nAfter training...\nHam: %d, Spam: %d\n", ham, spam);
		for (i = 0; i < num; i++)
		{
			printf("%s,%d,%d\n", words[i], hfreq[i], sfreq[i]);
		}
		fclose(dataset);

		//��踦 �������� stats.txt ���� �ۼ��ϱ�
		FILE* stats;
		stats = fopen("stats.txt", "w");
		fprintf(stats, "Ham: %d, Spam: %d\n", ham, spam);
		for (i = 0; i < num; i++)
		{
			fprintf(stats,"%s,%d,%d\n", words[i], hfreq[i], sfreq[i]);
		}
		fclose(stats);

		//�޸� �����Ҵ� ����
		token1 = NULL;
		free(sfreq);
		free(hfreq);
		free(twords);
		free(token1);
		for (i = idx2 - 1; i >= 0; i--)
			free(text[i]);
		free(text);
		
		for (i = 0; i <n; i++)
		{
			label[i] = NULL;
			free(label[i]);
		}
		
		for (idx1 = 0; idx1 < z; idx1++)
			words[idx1] = NULL;
		free(label);

		for (i = 0; i < idx1; i++)
			free(words[i]);
		free(words);
		
		return 1;
		
	}
	
}
//�� �ٲٱ�
void swap(int* a, int* b)
{
	int tem;
	tem = *a;
	*a = *b;
	*b = tem;
}
//enter �Է� �ޱ�
int enter()
{
	char s, n;
	n = scanf("%c", &s);

	if (n == 1)
		return 1;
	else
		return 0;
}
//txt������ �������� ���� ��� error ���
void printerror()
{
	printf("Command: train\n");
	printf("Error: File does not exist\n");
}
//stats.txt������ �������� ���� ��� error ���
void printerror2()
{
	printf("Command: test\n");
	printf("Error: File does not exist\n");
}
//���ڿ� ���� ���
int mystrlen(char* str)
{
	int i = 0;
	while (1)
	{
		if (str[0] == '\0')
			return 0;
		else if (str[i] == '\0')
			break;
		else
			i++;
	}
	return i;
}
//�ƽ�Ű�� �������� �� ���ڿ� ��Ұ��� ��
int mystrcmp(char* str1, char* str2) 
{
	int i;
	for (i = 0;; i++)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return 0;
		else if (str1[i] < str2[i] || str1[i] == '\0')
			return -1;
		else if (str1[i] > str2[i] || str2[i] == '\0')
			return 1;
		else if (str1[i] == str2[i])
			continue;
		
	}
}
//���ڿ� �����ϱ�
char* mystrcpy(char* toStr, char* fromStr)
{
	int i;
	for (i=0;i<strlen(fromStr);i++)
	{
		toStr[i] = fromStr[i];
	}
	toStr[i] = '\0';
	return toStr;
}
//���ĺ� �ҹ��ڷ� �ٲٱ�
char* mystrlower(char* str)
{
	int i = 0;
	while (1)
	{
		if (str[i] == '\0' || str[i] == '\n')
			break;
		else if (str[i] == '\t')
		{
			i++;
			continue;
		}
		else if (str[i] == ' ')
			i++;
		else if (str[i] > 96 && str[i] < 123)
			i++;
		else if (str[i] < 91 && str[i]>64)
		{
			str[i] += 32;
			i++;
		}
		else
			i++;
	}
	return str;
}

//���ĺ� ���� ���ڴ� ��ĭ ó���ϱ�
char* mystrblank(char* str)
{
	int i = 0;
	while (1)
	{
		if (str[i] == '\n' || str[i]=='\0')
			break;
		else if (str[i] == '\t')
		{
			i++;
			continue;
		}
		else if (!((str[i] > 96 && str[i] < 123) || (str[i] > 64 && str[i] < 91)))
			str[i] = ' ';
		else;
		i++;
	}
	return str;
}