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

//test 단계 
int test(int* judg)
{
	FILE* openf=fopen("stats.txt", "r");
	/*stats.txt파일이 없는 경우 
	에러 메시지 출력 후 메인 메뉴로 돌아가기*/
	if (openf == NULL)
	{
		erase();
		mainmenu();
		printerror2();
		Sleep(1000);
		erase();
		return 0;
	}
	/*stats.txt 파일이 존재하는 경우*/
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
		//스팸인지 아닌지 확인할 문장 입력받기
		printf("Enter a message: ");
		gets(text);
		strcpy(text2, text);
		mystrlower(text);	
		mystrblank(text);

		//stats.txt 파일에서 정보 불러오기
		fscanf(openf, "Ham: %d, Spam: %d\n", &ham, &spam);
		while (1)
		{
			fgets(line, sizeof(line), openf);
			if (feof(openf))
				break;
			//stats.txt 파일 ,을 기준으로 잘라서 읽기
			temp = strtok(line, ",");
			words[num] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
			strcpy(words[num], temp);
			temp = strtok(NULL, ",");
			hfreq[num] = atoi(temp);
			temp = strtok(NULL, ",");
			sfreq[num] = atoi(temp);
			num++;
			//메모리 재할당
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

		//입력된 문장 띄어쓰기 단위로 자르기1
		token = strtok(text, " ");    
		if (token == NULL);
		else if (strcmp(token, " ") == 0 || strcmp(token, "") == 0);
		else
		{
			textw[num] = (char*)calloc(mystrlen(token) + 1, sizeof(char));
			textw[num] = token;
			num++;
		}

		//입력된 문장 띄어쓰기 단위로 자르기2
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
			
			//이전에 동일한 단어가 있는지 검사하기
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
			//메무리 재할당
			if (num != 0 && num == z - 1)
			{
				z = 2 * z;
				textw = (char**)realloc(textw, z * sizeof(char*));
				ywn = (int*)realloc(ywn, z * sizeof(int));
			}
			else;
		}
		
		const int textn = num;
	
		//문장 내 단어가 통계에 포함되는지 확인하기
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

		//스팸일 확률, 아닐 확률 계산
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

		//메모리 동적 할당 해제
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

//메인 메뉴 출력하기
void mainmenu()
{
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED101\n");
	printf("Assignemnt 3\n\n");
	printf("Naive Bayesian Classifier for Spam Filtering\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

//메인메뉴에서 사용자의 입력 받기
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
		if (checksame(cmd, "train") == 1) //train 입력시
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
		else if (checksame(cmd, "test") == 1) //test 입력시
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
		else if (checksame(cmd, "exit") == 1) //exit 입력시
		{
			return;
		}
		else //그 외 단어 입력시
		{
			printf("Error: Invalid input");
			Sleep(1000);
			erase();
			judg = 1;
			command();
		}
	}
}

//화면 지우는 함수
void erase()
{
	system("cls");
}

//입력된 단어가 대소문자 구분없이 동일한지 확인
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

//train 실행
int training(int* judg)
{
	//파일 이름 입력 받기
	char filename[MAX_FILE_NAME] = {0};
	printf("File name: ");
	gets(filename, MAX_FILE_NAME, stdin);
	int i,j,x,y,spam,ham, z, num, idx1, idx2, idx3;
	FILE* dataset= fopen(filename, "r");
	/*해당 파일이 없을 경우*/
	if (dataset == NULL)
	{
		erase();
		mainmenu();
		printerror();
		Sleep(1000);
		erase();
		return 0;
	}
	else //파일이 존재하는 경우
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
		for (i = 0; fgets(line, sizeof line, dataset) != NULL; i++); //파일이 몇 줄인지 검사
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
			//파일에서 한 줄 읽어오기
			token1 = NULL;
			fgets(line, sizeof line, dataset);
			mystrlower(line);
			mystrblank(line);
			// \t을 기준으로 왼쪽의 label 읽어오기
			token = strtok(line, "\t");
			label[i] = (char*)calloc(strlen(token)+1, sizeof(char));
			idx3++;
			mystrcpy(label[i], token);
			// \t을 기준으로 오른쪽의 label 읽어오기
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
			
			//그 줄에서 첫 번째 단어 읽어오고 ham, spam 횟수 수정
			token2 = strtok(text[i], " ");
			if (strlen(token2) == 1 || strlen(token2) > 20);  //단어 길이가 1이거나 20이상일 경우 제외
			else
			{
				words[num] = (char*)calloc(strlen(token2) + 1, sizeof(char));
				mystrcpy(words[num], token2);
				y = num;
				x = 0;
				sfreq[num] = 0;
				hfreq[num] = 0;
				//이전에 동일한 단어가 있는지 검사하기
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
				//ham, spam 빈도수 수정하기
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
				//메모리 부족할 경우 재할당
				if (num != 0 && num == z - 1)
				{
					z = 2 * z;
					words = (char**)realloc(words, z * sizeof(char*));
					hfreq = (int*)realloc(hfreq, z * sizeof(int));
					sfreq = (int*)realloc(sfreq, z * sizeof(int));

				}
				else;	
			}

			
			// 그 줄에서 첫 번째 이후 단어들 읽어오고 ham,spam 횟수 수정
			for(;token2 != NULL;)
			{
				token2 = NULL;

				token2 = strtok(NULL, " ");
				if (token2 == NULL)  //더 이상 읽을 단어가 없을 경우 다음 줄 읽기
					break;
				else if (strcmp(token2, " ") == 0 || strcmp(token2, "") == 0)// 띄어쓰기 건너뛰기
					continue;
				else if (strlen(token2) == 1 || strlen(token2) > 20)
					continue;
				else;

				words[num] = (char*)malloc((strlen(token2) + 1)*sizeof(char));
				mystrcpy(words[num], token2);
				y = num;
				sfreq[num] = 0;
				hfreq[num] = 0;
				//이전에 동일한 단어가 있는지 검사하기
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
				//ham, spam 빈도수 수정하기
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
				//메모리 부족할 경우 재할당
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
		//알파벳 순으로 정렬하기
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
		//ham, spam 횟수 계산하기
		for (i = 0; i < n; i++)
		{
			if (strcmp(label[i],"spam")==0)
				spam++;
			else if (strcmp(label[i], "ham")==0)
				ham++;
		}

		//통계 출력하기
		printf("\n\nAfter training...\nHam: %d, Spam: %d\n", ham, spam);
		for (i = 0; i < num; i++)
		{
			printf("%s,%d,%d\n", words[i], hfreq[i], sfreq[i]);
		}
		fclose(dataset);

		//통계를 바탕으로 stats.txt 파일 작성하기
		FILE* stats;
		stats = fopen("stats.txt", "w");
		fprintf(stats, "Ham: %d, Spam: %d\n", ham, spam);
		for (i = 0; i < num; i++)
		{
			fprintf(stats,"%s,%d,%d\n", words[i], hfreq[i], sfreq[i]);
		}
		fclose(stats);

		//메모리 동적할당 해제
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
//값 바꾸기
void swap(int* a, int* b)
{
	int tem;
	tem = *a;
	*a = *b;
	*b = tem;
}
//enter 입력 받기
int enter()
{
	char s, n;
	n = scanf("%c", &s);

	if (n == 1)
		return 1;
	else
		return 0;
}
//txt파일이 존재하지 않을 경우 error 출력
void printerror()
{
	printf("Command: train\n");
	printf("Error: File does not exist\n");
}
//stats.txt파일이 존재하지 않을 경우 error 출력
void printerror2()
{
	printf("Command: test\n");
	printf("Error: File does not exist\n");
}
//문자열 길이 계산
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
//아스키를 기준으로 두 문자열 대소관계 비교
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
//문자열 복사하기
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
//알파벳 소문자로 바꾸기
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

//알파벳 외의 문자는 빈칸 처리하기
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