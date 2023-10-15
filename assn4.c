#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_FILE_NAME 30

//USER 구조체 선언
typedef struct User {
	char name[21];
	char email[41];
	struct User* next;
}USER;

//PARTCIPANT 구조체 선언
typedef struct Participant {
	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;
}PARTICIPANT;

//CONFERENCE 구조체 선언
typedef struct Conference {
	char roomName[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participants;
	PARTICIPANT* parttail;
}CONFERENCE;

//U_LIST 구조체 선언
typedef struct
{ 
	int count;
	USER* head;
	USER* tail;
}U_LIST;

void start_p();
void user_list(U_LIST* ulist);
void insert(U_LIST* ulist, char* str1, char* str2);
void user_add(U_LIST* ulist);
void user_delete(U_LIST* ulist);
void conf_info(CONFERENCE* conf);
void conf_join(CONFERENCE* conf, U_LIST* ulist);
void insert2(CONFERENCE* conf, bool cam, bool mic);
void conf_hangup(CONFERENCE* conf);
void conf_toggle_camera(CONFERENCE* conf);
void conf_toggle_mic(CONFERENCE* conf);
void quit(CONFERENCE* conf, U_LIST* ulist);

//main 함수
int main()
{
	start_p();
	return 0;
}

//프로그램의 main
void start_p()
{
	int i, j, z, x;
	char line[100], * filename, ** name, ** email, * temp, temp2[21], temp3[21], temp4[41], a;
	filename = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	CONFERENCE conf;
	z = 10;

	//파일 이름 입력받기
	printf("유저 리스트 파일 이름을 입력해주십시오. >> ");
	gets(filename, MAX_FILE_NAME, stdin);
	FILE* data = fopen(filename, "r");
	while (1) //유효한 파일 입력 받을 때까지 입력받기
	{
		if (data == NULL)
		{
			printf("유효하지 않은 입력입니다. 유저 리스트 파일 이름을 입력해주세요 >> ");
			gets(filename, MAX_FILE_NAME, stdin);
			data = fopen(filename, "r");
			continue;
		}
		else
			break;
	}
	for (i = 0; fgets(line, sizeof line, data) != NULL; i++); //파일이 몇 줄인지 검사
	const int f_end = i;
	name = (char**)calloc(f_end, sizeof(char*));
	email = (char**)calloc(f_end, sizeof(char*));
	fclose(data);
	data = fopen(filename, "r");

	//파일에서 한줄한줄 읽어와서 name과 email 부분을 잘라서 저장하기
	for (i = 0; i < f_end; i++)
	{
		temp = NULL;
		fgets(line, sizeof line, data);
		temp = strtok(line, "\t");
		name[i] = (char*)calloc(strlen(temp), sizeof(char));
		strcpy(name[i], temp);
		temp = NULL;
		temp = strtok(NULL, "\t");
		for (x = 0;; x++)
		{
			if (temp[x] == '\n')
			{
				temp[x] = '\0';
				break;
			}
			else if (temp[x] == '\0')
				break;
		}		
		email[i] = (char*)calloc(strlen(temp), sizeof(char));
		strcpy(email[i], temp);
		
		if (i != 0 && i == z - 1)
		{
			z = 2 * z;
			name = (char**)realloc(name, z * sizeof(char*));
			email = (char**)realloc(email, z * sizeof(char*));
		}
		else;
	}
	fclose(data);

	//유저 리스트를 알파벳 순으로 정렬하기
	for (i = 0; i < f_end - 1; i++)
	{
		for (j = f_end - 1; j > i; j--)
		{
			strcpy(temp2, name[j - 1]);
			strcpy(temp3, name[j]);
			if (strcmp(name[j - 1], name[j]) == 1)
			{
				strcpy(name[j - 1], temp3);
				strcpy(name[j], temp2);
				strcpy(temp4, email[j - 1]);
				strcpy(email[j - 1], email[j]);
				strcpy(email[j], temp4);
			}
			else
			{
				strcpy(name[j - 1], temp2);
				strcpy(name[j], temp3);
			}
		}
	}

	//유저 리스트와 회의 참여자 리스트 구조체 선언 및 초기화
	U_LIST ulist;
	ulist.count = f_end;
	ulist.head = NULL;
	ulist.tail = NULL;
	for (i = 0; i < f_end; i++)
		insert(&ulist, name[i], email[i]);
	conf.numParticipant = 0;
	conf.maxParticipant = 0;
	conf.participants = NULL;
	conf.parttail = NULL;

	//결과 출력
	printf("\n[INFO] %s에서 총 %d명의 유저를 불러왔습니다.\n", filename, f_end);
	printf("\n회의실 이름을 입력해주세요. >> ");
	scanf("%s", &conf.roomName);
	printf("최대 사용자 수를 입력해주세요. >> ");
	scanf("%d", &conf.maxParticipant);
	printf("[INFO] %s 회의실이 생성되었습니다!\n\n", conf.roomName);

	//name과 email, filename 포인터 할당 해제
	for (i = 0; i < f_end; i++)
	{
		name[i] = NULL;
		free(name[i]);
		email[i] = NULL;
		free(email[i]);
	}
	free(name);
	free(email);
	free(filename);

	//명령어 입력받기
	char cmd[25];
	printf("명령어를 입력해주세요. >> ");
	gets(cmd, sizeof cmd, stdin);
	while(1)
	{
		gets(cmd, sizeof cmd, stdin);
		if (strcmp(cmd, "user list") == 0)
			user_list(&ulist);
		else if (strcmp(cmd, "user add") == 0)
		{
			user_add(&ulist);
			a = getchar();
			fflush(stdin);
		}
		else if (strcmp(cmd, "user delete") == 0)
			user_delete(&ulist);
		else if (strcmp(cmd, "conf info") == 0)
			conf_info(&conf);
		else if (strcmp(cmd, "conf join") == 0)
		{
			conf_join(&conf, &ulist);
		}
		else if (strcmp(cmd, "conf hangup") == 0)
			conf_hangup(&conf);
		else if (strcmp(cmd, "conf toggle camera") == 0)
			conf_toggle_camera(&conf);
		else if (strcmp(cmd, "conf toggle mic") == 0)
			conf_toggle_mic(&conf);
		else if (strcmp(cmd, "quit") == 0)
		{
			quit(&conf, &ulist);
			return;
		}
		else
			printf("유효하지 않은 입력입니다. ");
		printf("명령어를 입력해주세요. >> ");
	}
}

//유저 연결리스트의 맨 끝에 유저 추가하기
void insert(U_LIST* ulist, char* str1, char* str2)
{
	USER* user = (USER*)malloc(sizeof(USER));
	
	if (ulist->head == NULL)
		ulist->head = user;
	else
		ulist->tail->next= user;
	ulist->tail = user;
	strcpy(user->name, str1);
	strcpy(user->email, str2);
	user->next = NULL;
}

//user list 실행-모든 유저의 정보를 출력하기
void user_list(U_LIST* ulist)
{
	int i = 1;
	char a;
	USER* temp;
	printf("==============================================================\n");
	printf("번호             이름				이메일\n");
	printf("--------------------------------------------------------------\n");
	for (temp = ulist->head; temp != NULL; temp = temp->next, i++) //유저의 정보를 출력하는 부분
		printf("%d %20s%40s\n", i, temp->name, temp->email);
	printf("==============================================================\n\n");
}

//user add 실행
void user_add(U_LIST* ulist)
{
	int i;
	USER *temp, *pre;
	USER* temp2 = (USER*)malloc(sizeof(USER));
	char tword1[21], tword2[21];
	char* name=(char*)calloc(21, sizeof(char));
	char* email = (char*)calloc(41, sizeof(char));
	printf("추가할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", name);
	
	for (i=0,temp = ulist->head, pre = temp; temp != NULL; pre = temp, temp = temp->next, i++)
	{
		strcpy(tword1, temp->name);
		strcpy(tword2, name);
		if (strcmp(tword1, tword2) == 0) //유저리스트에 해당 유저가 존재하는 경우
		{
			printf("[INFO] %s, %s 유저가 이미 유저 리스트에 있습니다.\n\n", temp->name, temp->email);
			return;
		}
		else if (i == 0 && strcmp(tword1, tword2) > 0) //user 연결리스트의 head 부분에 연결되는 경우
		{
			printf("추가할 유저의 이메일을 입력해주세요. >> ");
			scanf("%s", email);
			ulist->head = temp2;
			ulist->head->next = temp;
			strcpy(temp2->name, name);
			strcpy(temp2->email, email);
			temp2->next = temp;
			printf("[INFO] %s, %s 유저가 추가되었습니다.\n\n", name, email);
			ulist->count++;
			return;
		}
		else if (strcmp(tword1, tword2) > 0)  //user 연결리스트의 중간에 연결되는 경우
		{
			printf("추가할 유저의 이메일을 입력해주세요. >> ");
			scanf("%s", email);
			pre->next = temp2;
			temp2->next = temp;
			strcpy(temp2->name, name);
			strcpy(temp2->email, email);
			printf("[INFO] %s, %s 유저가 추가되었습니다.\n\n", name, email);
			ulist->count++;
			return;
		}
		else;
	}
	//user 연결리스트의 끝에 연결되는 경우
	printf("추가할 유저의 이메일을 입력해주세요. >> ");
	scanf("%s", email);
	insert(ulist, name, email);
	printf("[INFO] %s, %s 유저가 추가되었습니다.\n\n", name, email);
	ulist->count++;
	fflush(stdin);
	free(name);
	free(email);
}

//user delete 실행
void user_delete(U_LIST* ulist)
{
	char answer;
	USER* temp, *pre;
	char* name = (char*)calloc(21, sizeof(char));
	if (ulist->count == 0) //유저리스트가 비어 있는 경우
	{
		printf("[INFO] 유저 리스트가 비어 있습니다!\n\n");
		return;
	}
	else;
	printf("제거할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", name);

	//유저 리스트에서 해당 유저 찾기
	for (temp = ulist->head, pre = temp; temp != NULL; pre = temp, temp = temp->next) 
	{
		if (strcmp(temp->name, name) == 0) //해당 유저가 존재할 때
		{
			printf("%s, %s 유저를 제거하시겠습니까? (y/n) >> ", temp->name, temp->email);
			answer = getchar();
			fflush(stdin);
			answer = getchar();
			if (answer == 'n') // n 입력시
			{
				printf("\n");
				answer = getchar();
				fflush(stdin);
				return;
			}
			else if (answer == 'y') //y 입력시
			{
				if (pre == temp)
					ulist->head = temp->next;
				else
					pre->next = temp->next;
				free(temp);
				answer = getchar();
				fflush(stdin);
				printf("\n");
				ulist->count--;
				return;
			}
		}
	}
	//해당 유저가 존재하지 않는 경우
	printf("[INFO] 해당 유저는 존재하지 않습니다!\n\n");
	answer = getchar();
	fflush(stdin);
	free(name);
}

//conf info 실행
void conf_info(CONFERENCE* conf)
{
	char a;
	char* w1 = (char*)malloc(4 * sizeof(char));
	char* w2 = (char*)malloc(4 * sizeof(char));
	char str1[] = "on";
	char str2[] = "off";

	PARTICIPANT* temp;
	printf("\n회의실 이름: %s\n최대 사용자 수: %d\n참여자 목록:\n", conf->roomName, conf->maxParticipant);
	printf("============================================================================\n");
	printf("               이름				     이메일  카메라  마이크\n");
	printf("----------------------------------------------------------------------------\n");
	for (temp = conf->participants; temp != NULL; temp = temp->next) //참여자 목록 출력하는 부분
	{
		if (temp->camera == true)
			strcpy(w1, str1);
		else if (temp->camera == false)
			strcpy(w1, str2);
		else;
		if (temp->microphone == true)
			strcpy(w2, str1);
		else if (temp->microphone == false)
			strcpy(w2, str2);
		else;
		printf("%20s%40s%6s%6s\n", temp->user->name, temp->user->email, w1, w2);
	}
	printf("============================================================================\n\n");
	free(w1);
	free(w2);
}

//conf join 실행
void conf_join(CONFERENCE* conf, U_LIST* ulist)
{
	char name[21], c, m, a;
	int b;
	bool cam, mic;
	PARTICIPANT* pre;
	USER* temp=(USER*)malloc(sizeof(USER));
	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	if (conf->maxParticipant == conf->numParticipant) //최대 인원이 참여하는 경우
	{
		printf("[INFO] 회의에 최대 인원 %d 명이 참여하고 있습니다!\n\n", conf->maxParticipant);
		return;
	}
	printf("추가할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", name);

	//해당 유저가 이미 참여한 경우
	for (part = conf->participants; part != NULL; part = part->next) 
	{
		if (strcmp(part->user->name, name) == 0)
		{
			printf("[INFO] %s 이(가) 회의에 이미 참여하였습니다!\n\n", name);
			a = getchar();
			fflush(stdin);
			return;
		}
	}
	a = getchar();
	fflush(stdin);

	//해당 유저가 유저 리스트에 존재하지 않는 경우
	for (temp = ulist->head, b=0; temp != NULL; temp = temp->next) 
	{
		if (strcmp(temp->name, name) == 0)
		{
			b = 1;
			break;
		}
		else;
	}
	if (b == 0)
	{
		printf("[INFO] 해당 유저는 존재하지 않습니다.\n\n");
		return;
	}
	else;

	//카메라와 마이크 on/off 여부 입력받기
	printf("카메라를 켠 상태로 시작하시겠습니까? (y/n) >> ");
	scanf("%c", &c);
	if (c=='y')
		cam = true;
	else if (c=='n')
		cam = false;
	a = getchar();
	fflush(stdin);
	printf("마이크를 켠 상태로 시작하시겠습니까? (y/n) >> ");
	scanf("%c", &m);
	if (m=='y')
		mic = true;
	else if (m=='n')
		mic = false;
	part = NULL;

	//참여자 리스트에 참여자 연결하기
	for (temp = ulist->head; temp != NULL;temp = temp->next)
	{
		if (conf->numParticipant == 0 && strcmp(temp->name, name) == 0) //참여자 리스트에 아무도 없는 경우
		{
			insert2(conf, cam, mic);
			conf->participants->user = temp;
			printf("[INFO] %s 이(가) 회의에 참여하였습니다.\n\n", name);
			conf->numParticipant++;
			a = getchar();
			fflush(stdin);
			return;
		}
		else if (strcmp(temp->name, name) == 0) //참여자 리스트에 최소 1명이상 있을 경우
		{
			insert2(conf, cam, mic);
			conf->parttail->user = temp;
			printf("[INFO] %s 이(가) 회의에 참여하였습니다.\n\n", name);
			conf->numParticipant++;
			a = getchar();
			fflush(stdin);
			return;
		}
	}
}

//참여자 리스트에 참여자 연결하기
void insert2(CONFERENCE* conf, bool cam, bool mic)
{
	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	if (conf->participants== NULL)
		conf->participants= part;
	else
		conf->parttail->next = part;
	conf->parttail= part;
	part->camera = cam;
	part->microphone = mic;
	part->next = NULL;
}

//conf hangup 실행
void conf_hangup(CONFERENCE* conf)
{
	int result = 0;
	char name[21], a;
	PARTICIPANT* pre;
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//참여자 리스트에 아무도 없는 경우
	if (conf->numParticipant == 0)
	{
		printf("[INFO] 회의 참석자가 없습니다.\n\n");
		return;
	}
	else;
	printf("제외할 유저 이름을 입력해주세요. >> ");
	scanf("%s", name);

	//회의에 존재하는지 확인하기
	for (temp = conf->participants, pre = temp; temp != NULL; pre = temp, temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}

	//회의에 존재하지 않는 경우
	if (result == 0)
	{
		printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	a = getchar();
	fflush(stdin);
	printf("정말로 회의에서 내보내시겠습니까? (y/n) >> ");
	scanf("%c", &a);
	if (a == 'y') //y 입력시
	{
		if (pre == temp)
			conf->participants = temp->next;
		else
			pre->next = temp->next;
		free(temp);
		printf("[INFO] %s 이(가) 회의에서 나갔습니다!\n\n", name);
		conf->numParticipant--;
		a = getchar();
		fflush(stdin);
	}
	else if (a == 'n') //n 입력시
	{
		printf("\n");
		a = getchar();
		fflush(stdin);
		return;
	}
}

//conf toggle camera 실행
void conf_toggle_camera(CONFERENCE* conf)
{
	char a;
	int result = 0;
	char name[21], msg[3];
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//회의에 아무도 없는 경우
	if (conf->numParticipant == 0)
	{
		printf("[INFO] 회의 참석자가 없습니다.\n\n");
		return;
	}
	else;
	printf("카메라 상태를 변경할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", name);

	//회의에 해당 참여자가 있는지 확인하기
	for (temp = conf->participants; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}
	if (result == 0) //존재하지 않는 경우
	{
		printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	if (temp->camera == true) //cam이 on인 경우
	{
		printf("[INFO] %s 의 카메라가 on -> off 되었습니다!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->camera = false;
	}
	else if (temp->camera == false) //cam이 off인 경우
	{
		printf("[INFO] %s 의 카메라가 off -> on 되었습니다!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->camera = true;
	}
}

//conf toggle mic 실행
void conf_toggle_mic(CONFERENCE* conf)
{
	char a;
	int result = 0;
	char name[21], msg[3];
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//회의에 아무도 없는 경우
	if (conf->numParticipant == 0)
	{
		printf("[INFO] 회의 참석자가 없습니다.\n\n");
		return;
	}
	else;
	printf("마이크 상태를 변경할 유저의 이름을 입력해주세요. >> ");
	scanf("%s", name);

	//회의에 해당 참여자가 존재하는지 확인하기
	for (temp = conf->participants; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}
	if (result == 0) //존재하지 않는 경우
	{
		printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	if (temp->microphone == true) //mic가 on인 경우
	{
		printf("[INFO] %s 의 마이크가 on -> off 되었습니다!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->microphone = false;
	}
	else if (temp->microphone == false) //mic가 off인 경우
	{
		printf("[INFO] %s 의 마이크가 off -> on 되었습니다!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->microphone = true;
	}
}

//quit 실행
void quit(CONFERENCE* conf, U_LIST* ulist)
{
	PARTICIPANT* temp1, *temp4;
	USER* temp2, *temp3;
	printf("[INFO] 회의를 종료합니다!\n\n");

	//할당 해제
	for (temp2 = ulist->head;temp2!=NULL; temp2 = temp3)
	{
		temp3 = temp2->next;
		temp2 = NULL;
		free(temp2);
	}
	for (temp1 = conf->participants; temp1 != NULL; temp1 = temp4)
	{
		temp4 = temp1->next;
		temp1 = NULL;
		free(temp1);
	}
}