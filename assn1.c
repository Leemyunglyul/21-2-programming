#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>

int print_menu();
void game_info();
void erase();
void initial_menu();
void game_start();
void print_drink(int drinkcap);
void print_map(int user_pos);
char set_position(int user_pos, int pos);
int dice_go(int option);
void play_juru(int user_pos, int* USERcap, int* COMcap);
void play_normal(int* drinkcap);
void play_mission(int* USERcap, int* COMcap);
void play_chance(int* USERcap);
void finish();

int game1();
int game2();

int main()
{

	print_menu();
	return 0;


}

/*ȭ�� ����� �Լ�*/
void erase()
{
	system("cls");
	return ;
}

/*�ʱ� �޴� ���*/
void initial_menu()
{
	printf("[�ַ縶��]\n");
	printf("========================================\n");
	printf("	1.  ���� ����\n");
	printf("	2.  ���� ����\n");
	printf("	3.  ���� ����\n");
	printf("========================================\n");
	printf("�Է�: ");
	
}


/*�ʱ� ���� �޴��� ����ϰ�, ����ڷκ���
�޴� ��ȣ�� �޾� �� ��ȣ�� ��ȯ*/
int print_menu()
{
	erase();
	int menu_num=0;
	initial_menu();
	scanf_s(" %d", &menu_num);

	switch (menu_num)                               //�Է¹��� �޴� ��ȣ�� ���� ó��
	{
		case 1:
			erase();
			game_info();
			break;
		case 2:
			game_start();
			break;
		case 3:
			printf("���α׷��� �����մϴ�...");
			break;

		default:
			/* 1,2,3�̿��� ���� ���� �� ȭ�� ����� �޴� �ٽ� ����! */
			erase();

			printf("�޴��� �ٽ� �Է��ϼ���.\n"); 
			print_menu();
			break;

	}

	return 0;

}

/* ���Ӽ��� ��� ��, ������� (-1)�Է� �� ���� ȭ������ ���ư�*/
void game_info()
{
	int main_menu;
	printf("================================�ַ縶���� ���� ����================================\n\n");
	printf("1. USER�� ���� �ֻ����� ������. �ֻ����� ���� �� �ֻ����� ���� �÷��̾ �����Ѵ�.\n\n");
	printf("2. COMPUTER�� �ֻ����� ������ ������ ���� 1���� ���� ���Ŵ�.\n\n");
	printf("3. USER�� COMPUTER�� �ַ��� ���� 2��(14��)�̸�, 14���� ���� ���� ���� �й��Ѵ�.\n\n");
	printf("4. ���� ĭ�� 5���� ĭ���� �̷���������� USER�� �� ĭ�� �䱸������ �������Ѿ� �Ѵ�.\n\n");
	printf("====================================================================================\n");
	printf("���� �޴��� ���ư���(-1):");
	scanf_s("%d", &main_menu);

	if (main_menu == -1)
	{
		erase();
		print_menu();
	}
	else
	{
		erase();
		printf("�ٽ� �Է��� �ֽñ� �ٶ��ϴ�.\n");
		game_info();
	}
	

}

/*������ �����ϰ� �ʿ��� ����(�ַ�, ��ġ)���� �ʱ�ȭ�Ѵ�. �� ���帶�� 
USER�� �ֻ����� ������ ���� ���⸦ �� �������� �����ϵ��� �ϸ�, 
COMPUTER�� �̼� ĭ�� �����ϰ� �� �ϸ��� 1���� ���õ��� �Ѵ�. �̴� ���� ������� �ݺ��ȴ�.*/
void game_start()
{
	erase();
	int user_pos = 0;
	int USERcap = 0;
	int COMcap = 0;
	int option;
	int dice_result;

	printf("[�ַ縶�� ����]\n");                                 //���� ���� �ʱ� ȭ��
	printf("==================================\n");
	print_map(user_pos);
	printf("==================================\n");
	printf("[USER - %d] (0/14)\n",user_pos);
	print_drink(USERcap);
	printf("[COMPUTER - 0] (0/14)\n");
	print_drink(COMcap);
	printf("==================================\n\n");
	printf("�ֻ����� �����ðڽ��ϱ�? (0-����, -1-��������):");
	scanf_s("%d", &option);
	if (option == -1)    //���� ����
	{
		erase();
		print_menu();
		return;
	}
	else;
	dice_go(option);
	dice_result=dice_go(option);
	user_pos += dice_result;


	erase();
	int roundnum = 1;
	while (USERcap < 14 || COMcap < 14)                              //���� ����
	{
		printf("==================================\n");
		printf(">>>>Round %d >>>>>>>>>>>>>>>>>>>>>>\n", roundnum);
		printf("==================================\n");
		printf("[USER's Turn]\n");
		printf("----------------------------------\n");
		printf("�ֻ��� ��: %d\n", dice_result);
		print_map(user_pos);
		play_juru(user_pos,&USERcap,&COMcap);
		if (USERcap < 14 )                  //���� �Ͽ� 14���� �Ѿ�� �� ��� ����
		{
			if (COMcap >= 14)
			{
				COMcap = 14;
			}
			else
			{
				printf("\n\n[COMPUTER's Turn]\n");
				printf("----------------------------------\n\n");
				if (user_pos == 3 || user_pos == 9)                         //�̼� ĭ ������ ��ǻ�ʹ� �̹� ���忡 �� 1��X
				{
					printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n\n");
				}
				else
				{
					printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n\n");
					COMcap = COMcap + 1;
				}
			}
			
		}
		else
		{
			USERcap = 14;
		}

		if (COMcap >= 14 || USERcap>=14)                      //������ ��ǻ�Ͱ� 14���� �Ѿ�� ���� �޽��� ���
		{
	
			printf("\n������ ����Ǿ����ϴ�.\n");
		}
		else;
		printf("==================================\n");      //�ַ� Ȯ��
		printf("[USER - %d] (%d/14)\n", user_pos, USERcap);
		print_drink(USERcap);
		printf("[COMPUTER - 0] (%d/14)\n",COMcap);
		print_drink(COMcap);
		printf("==================================\n\n");
		if (COMcap >= 14)                                   //�¸� ��� ���
		{
			printf("*��� USER�� �¸��Ͽ����ϴ�.\n");
			break;
		}
		else if (USERcap >= 14)
		{
			printf("*��� COMPUTER�� �¸��Ͽ����ϴ�.\n");
			break;
		}
		else;
		printf("�ֻ����� �����ðڽ��ϱ�? (0-����, -1-��������):");
		scanf_s("%d", &option);
		if (option == -1)              //���� ����
		{
			erase();
			print_menu();
			return;
		}
		else;
		dice_go(option);
		dice_result = dice_go(option);
		user_pos += dice_result;
		if (user_pos >= 12)            //�� ���� ���� user_pos �ʱ�ȭ
		{
			user_pos = user_pos - 12;
		}
		else;
		roundnum += 1;
		erase();
	
	}
	finish();
}

/*���� ������. -1���� �Է¹޵���*/
void finish()
{
	int fin;
	printf("\n\n���� �޴��� ���ư���(-1): ");
	scanf_s("%d", &fin);
	if (fin == -1)
	{
		erase();
		print_menu();
	}
	else
	{
		printf("\n�ٽ� �Է��� �ֽñ� �ٶ��ϴ�.\n");
		finish();
	}
}



/*USER�� ������ ����ĭ�� ��Ģ�� ���� ������ �ൿ��
�����Ѵ�. switch - case���� �̿��Ͽ� �� ���� ĭ���� �䱸�ϴ� ����� �����Ѵ�*/
void play_juru(int user_pos,int* USERcap, int* COMcap)
{
	switch (user_pos)
	{
		case 0:
			printf("���� ĭ�� �����Ͽ����ϴ�.\n");
			printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
			break;
		case 6:
			printf("�޽� ĭ�� �����Ͽ����ϴ�.\n");
			printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
			break;
		case 1:
		case 4:
		case 5:
		case 7:
		case 10:
		case 11:
			printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
			printf("USER�� 1�� ���ð� �Ǿ����ϴ�.\n");
			play_normal(USERcap);
			break;
		case 3:
		case 9:
			printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
			play_mission(USERcap, COMcap);
			break;
		case 2:
		case 8:
			printf("���� ĭ�� �����Ͽ����ϴ�.\n");
			play_chance(USERcap);
			break;

	}
}

/*�Ϲ� ĭ ������ �ؾ��� �ൿ!*/
void play_normal(int* drinkcap)
{
	*drinkcap= *drinkcap + 1;
	return;
}

/*�̼� ĭ ������ �ؾ��� �ൿ!*/
void play_mission(int* USERcap, int* COMcap)
{
	int whatgame;
	srand((int)time(NULL));
	whatgame = rand() % 2;
	int gameresult;
	if (whatgame == 0)
	{
		printf("----------------------------------\n");
		printf("*****        369����         *****\n");
		printf("----------------------------------\n");
		gameresult=game1();
		if (gameresult == 0)
		{
			*USERcap += 4;
			printf("----------------------------------\n");
			printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
			printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
		}
		else
		{
			*COMcap += 4;
			printf("----------------------------------\n");
			printf("USER�� �¸��Ͽ����ϴ�.\n");
			printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
		}
	}
	else
	{
		printf("----------------------------------\n");
		printf("*****   ����Ų��� ����    *****\n");
		printf("----------------------------------\n");
		gameresult=game2();
		if (gameresult == 0)
		{
			*USERcap += 4;
			printf("----------------------------------\n");
			printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
			printf("USER�� 4�� ���ð� �Ǿ����ϴ�.\n");
		}
		else
		{
			*COMcap += 4;
			printf("----------------------------------\n");
			printf("USER�� �¸��Ͽ����ϴ�.\n");
			printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
		}

	}
}
/*���� ĭ ������ �ؾ��� �ൿ*/
void play_chance(int* USERcap)
{
	int whatchance = 0;
	srand((int)time(NULL));
	whatchance = rand() % 2;
	if (whatchance == 0)
	{
		printf("'���� ��!'ī�带 �̾ҽ��ϴ�.\n");
		printf("USER�� 3�� ���ð� �Ǿ����ϴ�.\n");
		*USERcap = *USERcap + 3;
	}
	else
	{
		printf("'���� 808'ī�带 �̾ҽ��ϴ�.\n");
		printf("USER�� -2���� ���ð� �Ǿ����ϴ�.\n");
		if (*USERcap >= 2)
		{
			*USERcap = *USERcap + 2;
		}
		else
		{
			*USERcap = 0;
		}
	}
	return;
}

/*�ֻ��� ������*/
int dice_go(int option)
{
	srand((int)time(NULL));
	int dice;
	switch (option)
	{
	case 0:						//�������� �ֻ��� ������
		srand((int)time(NULL));
		dice = rand() % 6 + 1;
		return dice;
	case 1:                      //Ư�� �ֻ��� �� �����ϱ�(1~6)
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	default:
		printf("\n�ٽ� �Է��Ͻʽÿ�:");
		scanf_s("%d", &option);
		dice_go(option);
		return 0;
	}
}

/* USER�� COMPUTER�� ���� ����� �� ������ �ַ��� ����Ѵ�.*/
void print_drink(int drinkcap)
{
	int a=1;
	int b=0;
	if (drinkcap > 14)
	{
		drinkcap = 14;
	}
	else;
	
	while (b < drinkcap)
	{
		printf("��");
		b++;
	}
	for (a = a + b; a < 15; a++)
	{
		printf("��");
	}
	printf("\n\n");

}

/*USER ���� ��ġ�� ���Ե� �ַ縶�� ���带 ����Ѵ�.*/
void print_map(int user_pos)
{
	char a, b, c, d, e, f, g, h, i, j, k, l;
	a = set_position(user_pos, 0);
	b = set_position(user_pos, 1);
	c = set_position(user_pos, 2);
	d = set_position(user_pos, 3);
	e = set_position(user_pos, 4);
	f = set_position(user_pos, 5);
	g = set_position(user_pos, 6);
	h = set_position(user_pos, 7);
	i = set_position(user_pos, 8);
	j = set_position(user_pos, 9);
	k = set_position(user_pos, 10);
	l = set_position(user_pos, 11);

	printf("+-------+-------+-------+-------+\n");
	printf("| �̼�%c | ����%c | �Ϲ�%c | �޽�%c |\n",j,i,h,g);
	printf("+-------+-------+-------+-------+\n");
	printf("| �Ϲ�%c |               | �Ϲ�%c |\n",k,f);
	printf("+-------+               +-------+\n");
	printf("| �Ϲ�%c |               | �Ϲ�%c |\n",l,e);
	printf("+-------+-------+-------+-------+\n");
	printf("| ���� %c| �Ϲ�%c | ����%c | �̼�%c |\n",a,b,c,d);
	printf("+-------+-------+-------+-------+\n");

}

/*���忡���� USER ���� ��ġ�� ���� ������ ��ġ�� ���� �޾�, 
USER ���� ��ġ�� ���� ������ ��ġ�� ������ �빮�� ��O���� ��ȯ�ϰ�, 
���� ������ �����̽� �� ĭ(�� ��)�� ��ȯ�Ѵ�. ���� ���, set_position(0, 0);��
���ؼ� �빮�� ��O���� ��ȯ. print_map() �Լ����� ȣ��ǵ��� �����Ѵ�.*/
char set_position(int user_pos, int pos)
{
	if (user_pos != pos)
	{
		return ' ';
	}
	else
	{
		return '0';
	}

 }

/*369 ����
- 369 ������ 1���� ���ڸ� �ϳ��� ��鼭, 3, 6, 9�� ���� ���ڴ� ���ڸ� ���ϴ�
��� �ڼ��� ġ�� �����̴�.
- �� ���������� COMPUTER�� USER�� �����ư��鼭 1���� ���ڸ� �ϳ��� ��鼭, 369��
���� ���ڿ� 10�� ������� �ڼ��� ģ��. �ڼ��� �ľ� �ϴ� ���ڿ����� 0�� ��
�ڸ� �뵵�� �Ѵ�.
- ������ USER�� COMPUTER �� �ϳ��� �����ϰ� ���õǾ� ���� �����ϵ��� �Ѵ�. �Ʒ�
���ô� COMPUTER�� ���� �����ϴ� ���� 1�� ���ڸ� ���� ����ϸ�, ���� USER��
�Է��� ��ٸ��� USER�� ������ �´� ���ڸ� �Է��ϸ� COMPUTER�� ������ �Ѿ��.
- COMPUTER�� �ڱ� �������� �׻� �ùٸ� ���ڸ� ���Ѵ�(����Ѵ�). 21�� ���ڱ���
USER�� �ùٸ� ���ڸ� ����(�Է���) ���, USER�� �¸��ϰ� �ȴ�.
*/
int game1()
{
	int game1_result=0;
	int game1_turn;
	int game1_num;
	int usergamenum;
	int stg2;
	int stg3;
	int stg4;

	srand((int)time(NULL));
	game1_turn = rand() % 2;                   //���� �İ� �̱�

	if (game1_turn == 0)                   //��ǻ�� ����
	{
		for (game1_num = 1; game1_num < 22; game1_num += 2)
		{
			usergamenum = game1_num + 1;
			stg2 = game1_num;
			stg3 = usergamenum;

			if (stg2 == 3 || stg2 == 9 || stg2 == 13 || stg2 == 19)    //0�� ���ľ� �Ǵ� ����
			{
				stg2 = 0;
			}
			else;

			if (stg3 == 6 || stg3 == 10 || stg3 == 16 || stg3 == 20)  //0�� ���ľ� �Ǵ� ����
			{
				stg3 = 0;
			}
			else;

			printf("COMP >> %d\n", stg2);
			if (stg2== 21)             //21 ���޽� ����
			{
				break;
			}
			else;
			printf("USER >> ");
			scanf_s("%d", &stg4);

			if (stg3 != stg4)       //������ �Է��� ���� Ʋ�� ��� ���� ����
			{
				game1_result = 0;
				break;
			}
			else
			{
				game1_result = 1;
				}

		}

		return game1_result;
	}

	else                 //���� ����
	{
		for (usergamenum = 1; usergamenum < 22; usergamenum += 2)
		{
			game1_num = usergamenum + 1;
			stg2 = game1_num;
			stg3 = usergamenum;

			if (stg2 == 3 || stg2 == 9 || stg2 == 13 || stg2 == 19)  
			{
				stg2 = 0;
			}
			else;

			if (stg3 == 6 || stg3 == 10 || stg3 == 16 || stg3 == 20)
			{
				stg3 = 0;
			}
			else;

			printf("USER >> ");            
			scanf_s("%d", &stg4);
			if (stg4 == 21)           //21 ���޽� ����
			{
				break;
			}
			else;
			printf("COMP >> %d\n", stg3);

			if (stg2 != stg4)       //������ �Է��� ���� Ʋ�� ��� ����
			{
				game1_result = 0;
				break;
			}
			else
			{
				game1_result = 1;
			}
		}

		return game1_result;

	}

}

/*����Ų��� ����
- ����Ų��� ������ 1���� 31������ ���� ������� �ҷ��� ������ 31�� ���ϴ� ��
���� ���� ��������, ���� �����ڵ��� ������ ������ 1~3�������� ���ڸ� �����Ͽ�
11
���� �� �ִ�.
- COMPUTER�� USER�� �����ư��鼭 ������ �����ϴµ�, USER�� �ڽ���
������ �����Ͽ� �θ� ������ ������ �Է��ϸ�, COMPUTER�� �ڽ��� ������ �����Ͽ�
�θ� ������ ������ �����ϰ� �����Ѵ�. ������ ������ 1~3 ���� ���� ���ڸ� ����
�ϵ��� �Ѵ�. (�θ� ���ڰ� 3�� �̸����� ���� ��쿡�� 1~3 ���� ���� ���ڸ� ����
�ϵ��� �����Ѵ�.)
- ���� USER�� 1~3 �̿ܿ� ���� �Է��ϰ� �Ǹ� �ش� ���� �����ϰ� �ٽ� �Է� �޴´�.
- ���� ������ �����ϰ� �÷��̾�(COMPUTER �Ǵ� USER)�� �����Ͽ� �����ϵ��� �Ѵ�.
*/
int	game2()
{
	int game2_result;
	int game2_turn;
	int rannum;
	int a;
	a = 0;
	int b;
	int c;
	c = 0;
	srand((int)time(NULL));
	game2_turn = rand() % 2;

	if (game2_turn == 0)                      //��ǻ�� ���� ����
	{
		while (a <32 && c<32)
		{
			srand((int)time(NULL));
			rannum = rand() % 3 + 1;               //��ǻ�Ͱ� ��ĥ ���� ��������
			printf("COMP >> %d\n", rannum);        

			if (rannum == 1)                //1�� ��
			{
				a += 1;
				printf("%d\n", a);
				if (a >= 31)
					break;
				else;
			}

			else if (rannum == 2)   //2�� ��
			{
				a += 1;
				printf("%d", a);
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				a += 1;
				printf(" %d\n", a);
				if (a >= 31)
					break;
				else;
			}

			else                    //3�� ��
			{
				a += 1;
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				printf("%d", a);
				a += 1;
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				printf(" %d", a);
				a += 1;
				if (a >= 31)
					break;
				else;
				printf(" %d\n", a);
			}

			c = a;
			printf("USER >> ");                   //������ ����!
			scanf_s("%d", &b);

			while (b != 1 && b != 2 && b != 3)   //1,2,3 �̿��� ���� �Է����� �� �߸��Ǿ����� �˷��ֱ�
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf_s("%d", &b);

			}
			if (b == 1)              //1�� ��
			{
				c += 1;
				printf("%d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 2)           //2�� ��
			{
				c += 1;
				printf("%d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 3)          //3�� ��
			{
				c += 1;
				printf("%d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d\n", c);
				if (c >= 31)
					break;
				else;
			}
			else;
			c = a;
		}

		if (a >= 31)                 //���� ����
			game2_result = 1;
		else
			game2_result = 0;
		
		return game2_result;

	}

	else                                          //user ���� ����
	{

		while (a < 32 && c < 32)
		{
			printf("USER >> ");
			scanf_s("%d", &b);

			while (b != 1 && b != 2 && b != 3)      //1,2,3�̿��� ���� �Է¹޾��� �� �߸��Ǿ����� ǥ��
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf_s("%d", &b);
			}

			if (b == 1)        //1�� ��
			{
				c += 1;
				printf("%d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 2)    //2�� ��
			{
				c += 1;
				printf("%d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 3)          //3�� ��
			{
				c += 1;
				printf("%d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d", c);
				if (c >= 31)
				{
					printf("\n");
					break;
				}
				else;
				c += 1;
				printf(" %d\n", c);
				if (c >= 31)
					break;
				else;
			}
			else;

			a = c;
			srand((int)time(NULL));
			rannum = rand() % 3 + 1;              //��ǻ�Ͱ� �Է��� ���� �������� ���ϱ�
			printf("COMP >> %d\n", rannum);
			
			if (rannum == 1)        //1�� ��
			{
				a += 1;
				printf("%d\n", a);
				if (a >= 31)
					break;
				else;
			}

			else if (rannum == 2)   //2�� ��
			{
				a += 1;
				printf("%d", a);
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				a += 1;
				printf(" %d\n", a);
				if (a >= 31)
				{
					break;
				}
				else;
			}

			else                        //3�� ��
			{
				a += 1;
				printf("%d", a);
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				a += 1;
				printf(" %d", a);
				if (a >= 31)
				{
					printf("\n");
					break;
				}
				else;
				a += 1;
				printf(" %d\n", a);
				if (a >= 31)
					break;
				else;
			}
			c = a;
		}
		if (a >= 31)           //���� ����
			game2_result = 1;
		else
			game2_result = 0;

		return game2_result;
	}
}