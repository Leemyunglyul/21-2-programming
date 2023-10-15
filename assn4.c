#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_FILE_NAME 30

//USER ����ü ����
typedef struct User {
	char name[21];
	char email[41];
	struct User* next;
}USER;

//PARTCIPANT ����ü ����
typedef struct Participant {
	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;
}PARTICIPANT;

//CONFERENCE ����ü ����
typedef struct Conference {
	char roomName[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participants;
	PARTICIPANT* parttail;
}CONFERENCE;

//U_LIST ����ü ����
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

//main �Լ�
int main()
{
	start_p();
	return 0;
}

//���α׷��� main
void start_p()
{
	int i, j, z, x;
	char line[100], * filename, ** name, ** email, * temp, temp2[21], temp3[21], temp4[41], a;
	filename = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	CONFERENCE conf;
	z = 10;

	//���� �̸� �Է¹ޱ�
	printf("���� ����Ʈ ���� �̸��� �Է����ֽʽÿ�. >> ");
	gets(filename, MAX_FILE_NAME, stdin);
	FILE* data = fopen(filename, "r");
	while (1) //��ȿ�� ���� �Է� ���� ������ �Է¹ޱ�
	{
		if (data == NULL)
		{
			printf("��ȿ���� ���� �Է��Դϴ�. ���� ����Ʈ ���� �̸��� �Է����ּ��� >> ");
			gets(filename, MAX_FILE_NAME, stdin);
			data = fopen(filename, "r");
			continue;
		}
		else
			break;
	}
	for (i = 0; fgets(line, sizeof line, data) != NULL; i++); //������ �� ������ �˻�
	const int f_end = i;
	name = (char**)calloc(f_end, sizeof(char*));
	email = (char**)calloc(f_end, sizeof(char*));
	fclose(data);
	data = fopen(filename, "r");

	//���Ͽ��� �������� �о�ͼ� name�� email �κ��� �߶� �����ϱ�
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

	//���� ����Ʈ�� ���ĺ� ������ �����ϱ�
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

	//���� ����Ʈ�� ȸ�� ������ ����Ʈ ����ü ���� �� �ʱ�ȭ
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

	//��� ���
	printf("\n[INFO] %s���� �� %d���� ������ �ҷ��Խ��ϴ�.\n", filename, f_end);
	printf("\nȸ�ǽ� �̸��� �Է����ּ���. >> ");
	scanf("%s", &conf.roomName);
	printf("�ִ� ����� ���� �Է����ּ���. >> ");
	scanf("%d", &conf.maxParticipant);
	printf("[INFO] %s ȸ�ǽ��� �����Ǿ����ϴ�!\n\n", conf.roomName);

	//name�� email, filename ������ �Ҵ� ����
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

	//��ɾ� �Է¹ޱ�
	char cmd[25];
	printf("��ɾ �Է����ּ���. >> ");
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
			printf("��ȿ���� ���� �Է��Դϴ�. ");
		printf("��ɾ �Է����ּ���. >> ");
	}
}

//���� ���Ḯ��Ʈ�� �� ���� ���� �߰��ϱ�
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

//user list ����-��� ������ ������ ����ϱ�
void user_list(U_LIST* ulist)
{
	int i = 1;
	char a;
	USER* temp;
	printf("==============================================================\n");
	printf("��ȣ             �̸�				�̸���\n");
	printf("--------------------------------------------------------------\n");
	for (temp = ulist->head; temp != NULL; temp = temp->next, i++) //������ ������ ����ϴ� �κ�
		printf("%d %20s%40s\n", i, temp->name, temp->email);
	printf("==============================================================\n\n");
}

//user add ����
void user_add(U_LIST* ulist)
{
	int i;
	USER *temp, *pre;
	USER* temp2 = (USER*)malloc(sizeof(USER));
	char tword1[21], tword2[21];
	char* name=(char*)calloc(21, sizeof(char));
	char* email = (char*)calloc(41, sizeof(char));
	printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", name);
	
	for (i=0,temp = ulist->head, pre = temp; temp != NULL; pre = temp, temp = temp->next, i++)
	{
		strcpy(tword1, temp->name);
		strcpy(tword2, name);
		if (strcmp(tword1, tword2) == 0) //��������Ʈ�� �ش� ������ �����ϴ� ���
		{
			printf("[INFO] %s, %s ������ �̹� ���� ����Ʈ�� �ֽ��ϴ�.\n\n", temp->name, temp->email);
			return;
		}
		else if (i == 0 && strcmp(tword1, tword2) > 0) //user ���Ḯ��Ʈ�� head �κп� ����Ǵ� ���
		{
			printf("�߰��� ������ �̸����� �Է����ּ���. >> ");
			scanf("%s", email);
			ulist->head = temp2;
			ulist->head->next = temp;
			strcpy(temp2->name, name);
			strcpy(temp2->email, email);
			temp2->next = temp;
			printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n\n", name, email);
			ulist->count++;
			return;
		}
		else if (strcmp(tword1, tword2) > 0)  //user ���Ḯ��Ʈ�� �߰��� ����Ǵ� ���
		{
			printf("�߰��� ������ �̸����� �Է����ּ���. >> ");
			scanf("%s", email);
			pre->next = temp2;
			temp2->next = temp;
			strcpy(temp2->name, name);
			strcpy(temp2->email, email);
			printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n\n", name, email);
			ulist->count++;
			return;
		}
		else;
	}
	//user ���Ḯ��Ʈ�� ���� ����Ǵ� ���
	printf("�߰��� ������ �̸����� �Է����ּ���. >> ");
	scanf("%s", email);
	insert(ulist, name, email);
	printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n\n", name, email);
	ulist->count++;
	fflush(stdin);
	free(name);
	free(email);
}

//user delete ����
void user_delete(U_LIST* ulist)
{
	char answer;
	USER* temp, *pre;
	char* name = (char*)calloc(21, sizeof(char));
	if (ulist->count == 0) //��������Ʈ�� ��� �ִ� ���
	{
		printf("[INFO] ���� ����Ʈ�� ��� �ֽ��ϴ�!\n\n");
		return;
	}
	else;
	printf("������ ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", name);

	//���� ����Ʈ���� �ش� ���� ã��
	for (temp = ulist->head, pre = temp; temp != NULL; pre = temp, temp = temp->next) 
	{
		if (strcmp(temp->name, name) == 0) //�ش� ������ ������ ��
		{
			printf("%s, %s ������ �����Ͻðڽ��ϱ�? (y/n) >> ", temp->name, temp->email);
			answer = getchar();
			fflush(stdin);
			answer = getchar();
			if (answer == 'n') // n �Է½�
			{
				printf("\n");
				answer = getchar();
				fflush(stdin);
				return;
			}
			else if (answer == 'y') //y �Է½�
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
	//�ش� ������ �������� �ʴ� ���
	printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n\n");
	answer = getchar();
	fflush(stdin);
	free(name);
}

//conf info ����
void conf_info(CONFERENCE* conf)
{
	char a;
	char* w1 = (char*)malloc(4 * sizeof(char));
	char* w2 = (char*)malloc(4 * sizeof(char));
	char str1[] = "on";
	char str2[] = "off";

	PARTICIPANT* temp;
	printf("\nȸ�ǽ� �̸�: %s\n�ִ� ����� ��: %d\n������ ���:\n", conf->roomName, conf->maxParticipant);
	printf("============================================================================\n");
	printf("               �̸�				     �̸���  ī�޶�  ����ũ\n");
	printf("----------------------------------------------------------------------------\n");
	for (temp = conf->participants; temp != NULL; temp = temp->next) //������ ��� ����ϴ� �κ�
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

//conf join ����
void conf_join(CONFERENCE* conf, U_LIST* ulist)
{
	char name[21], c, m, a;
	int b;
	bool cam, mic;
	PARTICIPANT* pre;
	USER* temp=(USER*)malloc(sizeof(USER));
	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));
	if (conf->maxParticipant == conf->numParticipant) //�ִ� �ο��� �����ϴ� ���
	{
		printf("[INFO] ȸ�ǿ� �ִ� �ο� %d ���� �����ϰ� �ֽ��ϴ�!\n\n", conf->maxParticipant);
		return;
	}
	printf("�߰��� ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", name);

	//�ش� ������ �̹� ������ ���
	for (part = conf->participants; part != NULL; part = part->next) 
	{
		if (strcmp(part->user->name, name) == 0)
		{
			printf("[INFO] %s ��(��) ȸ�ǿ� �̹� �����Ͽ����ϴ�!\n\n", name);
			a = getchar();
			fflush(stdin);
			return;
		}
	}
	a = getchar();
	fflush(stdin);

	//�ش� ������ ���� ����Ʈ�� �������� �ʴ� ���
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
		printf("[INFO] �ش� ������ �������� �ʽ��ϴ�.\n\n");
		return;
	}
	else;

	//ī�޶�� ����ũ on/off ���� �Է¹ޱ�
	printf("ī�޶� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
	scanf("%c", &c);
	if (c=='y')
		cam = true;
	else if (c=='n')
		cam = false;
	a = getchar();
	fflush(stdin);
	printf("����ũ�� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >> ");
	scanf("%c", &m);
	if (m=='y')
		mic = true;
	else if (m=='n')
		mic = false;
	part = NULL;

	//������ ����Ʈ�� ������ �����ϱ�
	for (temp = ulist->head; temp != NULL;temp = temp->next)
	{
		if (conf->numParticipant == 0 && strcmp(temp->name, name) == 0) //������ ����Ʈ�� �ƹ��� ���� ���
		{
			insert2(conf, cam, mic);
			conf->participants->user = temp;
			printf("[INFO] %s ��(��) ȸ�ǿ� �����Ͽ����ϴ�.\n\n", name);
			conf->numParticipant++;
			a = getchar();
			fflush(stdin);
			return;
		}
		else if (strcmp(temp->name, name) == 0) //������ ����Ʈ�� �ּ� 1���̻� ���� ���
		{
			insert2(conf, cam, mic);
			conf->parttail->user = temp;
			printf("[INFO] %s ��(��) ȸ�ǿ� �����Ͽ����ϴ�.\n\n", name);
			conf->numParticipant++;
			a = getchar();
			fflush(stdin);
			return;
		}
	}
}

//������ ����Ʈ�� ������ �����ϱ�
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

//conf hangup ����
void conf_hangup(CONFERENCE* conf)
{
	int result = 0;
	char name[21], a;
	PARTICIPANT* pre;
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//������ ����Ʈ�� �ƹ��� ���� ���
	if (conf->numParticipant == 0)
	{
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n\n");
		return;
	}
	else;
	printf("������ ���� �̸��� �Է����ּ���. >> ");
	scanf("%s", name);

	//ȸ�ǿ� �����ϴ��� Ȯ���ϱ�
	for (temp = conf->participants, pre = temp; temp != NULL; pre = temp, temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}

	//ȸ�ǿ� �������� �ʴ� ���
	if (result == 0)
	{
		printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	a = getchar();
	fflush(stdin);
	printf("������ ȸ�ǿ��� �������ðڽ��ϱ�? (y/n) >> ");
	scanf("%c", &a);
	if (a == 'y') //y �Է½�
	{
		if (pre == temp)
			conf->participants = temp->next;
		else
			pre->next = temp->next;
		free(temp);
		printf("[INFO] %s ��(��) ȸ�ǿ��� �������ϴ�!\n\n", name);
		conf->numParticipant--;
		a = getchar();
		fflush(stdin);
	}
	else if (a == 'n') //n �Է½�
	{
		printf("\n");
		a = getchar();
		fflush(stdin);
		return;
	}
}

//conf toggle camera ����
void conf_toggle_camera(CONFERENCE* conf)
{
	char a;
	int result = 0;
	char name[21], msg[3];
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//ȸ�ǿ� �ƹ��� ���� ���
	if (conf->numParticipant == 0)
	{
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n\n");
		return;
	}
	else;
	printf("ī�޶� ���¸� ������ ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", name);

	//ȸ�ǿ� �ش� �����ڰ� �ִ��� Ȯ���ϱ�
	for (temp = conf->participants; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}
	if (result == 0) //�������� �ʴ� ���
	{
		printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	if (temp->camera == true) //cam�� on�� ���
	{
		printf("[INFO] %s �� ī�޶� on -> off �Ǿ����ϴ�!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->camera = false;
	}
	else if (temp->camera == false) //cam�� off�� ���
	{
		printf("[INFO] %s �� ī�޶� off -> on �Ǿ����ϴ�!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->camera = true;
	}
}

//conf toggle mic ����
void conf_toggle_mic(CONFERENCE* conf)
{
	char a;
	int result = 0;
	char name[21], msg[3];
	PARTICIPANT* temp = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));

	//ȸ�ǿ� �ƹ��� ���� ���
	if (conf->numParticipant == 0)
	{
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�.\n\n");
		return;
	}
	else;
	printf("����ũ ���¸� ������ ������ �̸��� �Է����ּ���. >> ");
	scanf("%s", name);

	//ȸ�ǿ� �ش� �����ڰ� �����ϴ��� Ȯ���ϱ�
	for (temp = conf->participants; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->user->name, name) == 0)
		{
			result = 1;
			break;
		}
		else;
	}
	if (result == 0) //�������� �ʴ� ���
	{
		printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n\n");
		a = getchar();
		fflush(stdin);
		return;
	}
	else;
	if (temp->microphone == true) //mic�� on�� ���
	{
		printf("[INFO] %s �� ����ũ�� on -> off �Ǿ����ϴ�!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->microphone = false;
	}
	else if (temp->microphone == false) //mic�� off�� ���
	{
		printf("[INFO] %s �� ����ũ�� off -> on �Ǿ����ϴ�!\n\n", name);
		a = getchar();
		fflush(stdin);
		temp->microphone = true;
	}
}

//quit ����
void quit(CONFERENCE* conf, U_LIST* ulist)
{
	PARTICIPANT* temp1, *temp4;
	USER* temp2, *temp3;
	printf("[INFO] ȸ�Ǹ� �����մϴ�!\n\n");

	//�Ҵ� ����
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