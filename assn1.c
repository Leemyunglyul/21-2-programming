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

/*화면 지우는 함수*/
void erase()
{
	system("cls");
	return ;
}

/*초기 메뉴 출력*/
void initial_menu()
{
	printf("[주루마블]\n");
	printf("========================================\n");
	printf("	1.  게임 설명\n");
	printf("	2.  게임 시작\n");
	printf("	3.  게임 종료\n");
	printf("========================================\n");
	printf("입력: ");
	
}


/*초기 선택 메뉴를 출력하고, 사용자로부터
메뉴 번호를 받아 그 번호를 반환*/
int print_menu()
{
	erase();
	int menu_num=0;
	initial_menu();
	scanf_s(" %d", &menu_num);

	switch (menu_num)                               //입력받은 메뉴 번호에 따라 처리
	{
		case 1:
			erase();
			game_info();
			break;
		case 2:
			game_start();
			break;
		case 3:
			printf("프로그램을 종료합니다...");
			break;

		default:
			/* 1,2,3이외의 숫자 나올 시 화면 지우고 메뉴 다시 선택! */
			erase();

			printf("메뉴를 다시 입력하세요.\n"); 
			print_menu();
			break;

	}

	return 0;

}

/* 게임설명 출력 후, 사용자의 (-1)입력 시 메인 화면으로 돌아감*/
void game_info()
{
	int main_menu;
	printf("================================주루마블의 게임 설명================================\n\n");
	printf("1. USER는 매턴 주사위를 던진다. 주사위를 던질 때 주사위의 눈은 플레이어가 결정한다.\n\n");
	printf("2. COMPUTER는 주사위를 던지지 않으며 매턴 1잔의 술을 마신다.\n\n");
	printf("3. USER와 COMPUTER의 주량은 소주 2병(14잔)이며, 14잔을 먼저 마신 쪽이 패배한다.\n\n");
	printf("4. 보드 칸은 5가지 칸으로 이루어져있으며 USER는 각 칸의 요구사항을 만족시켜야 한다.\n\n");
	printf("====================================================================================\n");
	printf("메인 메뉴로 돌아가기(-1):");
	scanf_s("%d", &main_menu);

	if (main_menu == -1)
	{
		erase();
		print_menu();
	}
	else
	{
		erase();
		printf("다시 입력해 주시기 바랍니다.\n");
		game_info();
	}
	

}

/*게임을 시작하고 필요한 변수(주량, 위치)들을 초기화한다. 매 라운드마다 
USER는 주사위를 굴릴지 게임 포기를 할 것인지를 선택하도록 하며, 
COMPUTER는 미션 칸을 제외하고 매 턴마다 1잔을 마시도록 한다. 이는 게임 종료까지 반복된다.*/
void game_start()
{
	erase();
	int user_pos = 0;
	int USERcap = 0;
	int COMcap = 0;
	int option;
	int dice_result;

	printf("[주루마블 게임]\n");                                 //게임 시작 초기 화면
	printf("==================================\n");
	print_map(user_pos);
	printf("==================================\n");
	printf("[USER - %d] (0/14)\n",user_pos);
	print_drink(USERcap);
	printf("[COMPUTER - 0] (0/14)\n");
	print_drink(COMcap);
	printf("==================================\n\n");
	printf("주사위를 굴리시겠습니까? (0-굴림, -1-게임포기):");
	scanf_s("%d", &option);
	if (option == -1)    //게임 포기
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
	while (USERcap < 14 || COMcap < 14)                              //라운드 시작
	{
		printf("==================================\n");
		printf(">>>>Round %d >>>>>>>>>>>>>>>>>>>>>>\n", roundnum);
		printf("==================================\n");
		printf("[USER's Turn]\n");
		printf("----------------------------------\n");
		printf("주사위 눈: %d\n", dice_result);
		print_map(user_pos);
		play_juru(user_pos,&USERcap,&COMcap);
		if (USERcap < 14 )                  //유저 턴에 14잔이 넘어가면 그 즉시 종료
		{
			if (COMcap >= 14)
			{
				COMcap = 14;
			}
			else
			{
				printf("\n\n[COMPUTER's Turn]\n");
				printf("----------------------------------\n\n");
				if (user_pos == 3 || user_pos == 9)                         //미션 칸 도착시 컴퓨터는 이번 라운드에 술 1잔X
				{
					printf("COMPUTER가 0잔 마시게 되었습니다.\n\n");
				}
				else
				{
					printf("COMPUTER가 1잔 마시게 되었습니다.\n\n");
					COMcap = COMcap + 1;
				}
			}
			
		}
		else
		{
			USERcap = 14;
		}

		if (COMcap >= 14 || USERcap>=14)                      //유저나 컴퓨터가 14잔이 넘어가면 종료 메시지 출력
		{
	
			printf("\n게임이 종료되었습니다.\n");
		}
		else;
		printf("==================================\n");      //주량 확인
		printf("[USER - %d] (%d/14)\n", user_pos, USERcap);
		print_drink(USERcap);
		printf("[COMPUTER - 0] (%d/14)\n",COMcap);
		print_drink(COMcap);
		printf("==================================\n\n");
		if (COMcap >= 14)                                   //승리 결과 출력
		{
			printf("*결과 USER가 승리하였습니다.\n");
			break;
		}
		else if (USERcap >= 14)
		{
			printf("*결과 COMPUTER가 승리하였습니다.\n");
			break;
		}
		else;
		printf("주사위를 굴리시겠습니까? (0-굴림, -1-게임포기):");
		scanf_s("%d", &option);
		if (option == -1)              //게임 포기
		{
			erase();
			print_menu();
			return;
		}
		else;
		dice_go(option);
		dice_result = dice_go(option);
		user_pos += dice_result;
		if (user_pos >= 12)            //한 바퀴 돌면 user_pos 초기화
		{
			user_pos = user_pos - 12;
		}
		else;
		roundnum += 1;
		erase();
	
	}
	finish();
}

/*게임 끝내기. -1만을 입력받도록*/
void finish()
{
	int fin;
	printf("\n\n메인 메뉴로 돌아가기(-1): ");
	scanf_s("%d", &fin);
	if (fin == -1)
	{
		erase();
		print_menu();
	}
	else
	{
		printf("\n다시 입력해 주시기 바랍니다.\n");
		finish();
	}
}



/*USER가 도착한 보드칸의 규칙에 따라 적절한 행동을
수행한다. switch - case문을 이용하여 각 보드 칸에서 요구하는 기능을 구현한다*/
void play_juru(int user_pos,int* USERcap, int* COMcap)
{
	switch (user_pos)
	{
		case 0:
			printf("시작 칸에 도착하였습니다.\n");
			printf("이번 턴은 아무것도 하지 않습니다.\n");
			break;
		case 6:
			printf("휴식 칸에 도착하였습니다.\n");
			printf("이번 턴은 아무것도 하지 않습니다.\n");
			break;
		case 1:
		case 4:
		case 5:
		case 7:
		case 10:
		case 11:
			printf("일반 칸에 도착하였습니다.\n");
			printf("USER가 1잔 마시게 되었습니다.\n");
			play_normal(USERcap);
			break;
		case 3:
		case 9:
			printf("미션 칸에 도착하였습니다.\n");
			play_mission(USERcap, COMcap);
			break;
		case 2:
		case 8:
			printf("찬스 칸에 도착하였습니다.\n");
			play_chance(USERcap);
			break;

	}
}

/*일반 칸 도착시 해야할 행동!*/
void play_normal(int* drinkcap)
{
	*drinkcap= *drinkcap + 1;
	return;
}

/*미션 칸 도착시 해야할 행동!*/
void play_mission(int* USERcap, int* COMcap)
{
	int whatgame;
	srand((int)time(NULL));
	whatgame = rand() % 2;
	int gameresult;
	if (whatgame == 0)
	{
		printf("----------------------------------\n");
		printf("*****        369게임         *****\n");
		printf("----------------------------------\n");
		gameresult=game1();
		if (gameresult == 0)
		{
			*USERcap += 4;
			printf("----------------------------------\n");
			printf("COMPUTER가 승리하였습니다.\n");
			printf("USER가 4잔 마시게 되었습니다.\n");
		}
		else
		{
			*COMcap += 4;
			printf("----------------------------------\n");
			printf("USER가 승리하였습니다.\n");
			printf("COMPUTER가 4잔 마시게 되었습니다.\n");
		}
	}
	else
	{
		printf("----------------------------------\n");
		printf("*****   베스킨라빈스 게임    *****\n");
		printf("----------------------------------\n");
		gameresult=game2();
		if (gameresult == 0)
		{
			*USERcap += 4;
			printf("----------------------------------\n");
			printf("COMPUTER가 승리하였습니다.\n");
			printf("USER가 4잔 마시게 되었습니다.\n");
		}
		else
		{
			*COMcap += 4;
			printf("----------------------------------\n");
			printf("USER가 승리하였습니다.\n");
			printf("COMPUTER가 4잔 마시게 되었습니다.\n");
		}

	}
}
/*찬스 칸 도착시 해야할 행동*/
void play_chance(int* USERcap)
{
	int whatchance = 0;
	srand((int)time(NULL));
	whatchance = rand() % 2;
	if (whatchance == 0)
	{
		printf("'세잔 더!'카드를 뽑았습니다.\n");
		printf("USER가 3잔 마시게 되었습니다.\n");
		*USERcap = *USERcap + 3;
	}
	else
	{
		printf("'여명 808'카드를 뽑았습니다.\n");
		printf("USER가 -2잔을 마시게 되었습니다.\n");
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

/*주사위 굴리기*/
int dice_go(int option)
{
	srand((int)time(NULL));
	int dice;
	switch (option)
	{
	case 0:						//랜덤으로 주사위 굴리기
		srand((int)time(NULL));
		dice = rand() % 6 + 1;
		return dice;
	case 1:                      //특정 주사위 눈 선택하기(1~6)
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
		printf("\n다시 입력하십시오:");
		scanf_s("%d", &option);
		dice_go(option);
		return 0;
	}
}

/* USER와 COMPUTER의 턴이 종료된 후 각자의 주량을 출력한다.*/
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
		printf("■");
		b++;
	}
	for (a = a + b; a < 15; a++)
	{
		printf("□");
	}
	printf("\n\n");

}

/*USER 말의 위치가 포함된 주루마불 보드를 출력한다.*/
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
	printf("| 미션%c | 찬스%c | 일반%c | 휴식%c |\n",j,i,h,g);
	printf("+-------+-------+-------+-------+\n");
	printf("| 일반%c |               | 일반%c |\n",k,f);
	printf("+-------+               +-------+\n");
	printf("| 일반%c |               | 일반%c |\n",l,e);
	printf("+-------+-------+-------+-------+\n");
	printf("| 시작 %c| 일반%c | 찬스%c | 미션%c |\n",a,b,c,d);
	printf("+-------+-------+-------+-------+\n");

}

/*보드에서의 USER 말의 위치와 현재 보드의 위치를 전달 받아, 
USER 말의 위치와 현재 보드의 위치가 같으면 대문자 ‘O’를 반환하고, 
같지 않으면 스페이스 한 칸(‘ ’)을 반환한다. 예를 들면, set_position(0, 0);에
대해서 대문자 ‘O’를 반환. print_map() 함수에서 호출되도록 구현한다.*/
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

/*369 게임
- 369 게임은 1부터 숫자를 하나씩 대면서, 3, 6, 9가 들어가는 숫자는 숫자를 말하는
대신 박수를 치는 게임이다.
- 본 과제에서는 COMPUTER와 USER가 번갈아가면서 1부터 숫자를 하나씩 대면서, 369가
들어가는 숫자와 10의 배수에서 박수를 친다. 박수를 쳐야 하는 숫자에서는 0의 숫
자를 대도록 한다.
- 게임은 USER와 COMPUTER 중 하나가 랜덤하게 선택되어 먼저 시작하도록 한다. 아래
예시는 COMPUTER가 먼저 시작하는 경우로 1의 숫자를 먼저 출력하며, 다음 USER의
입력을 기다리며 USER가 순서에 맞는 숫자를 입력하면 COMPUTER의 순서로 넘어간다.
- COMPUTER는 자기 순서에서 항상 올바른 숫자를 말한다(출력한다). 21의 숫자까지
USER가 올바른 숫자를 말한(입력한) 경우, USER가 승리하게 된다.
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
	game1_turn = rand() % 2;                   //선공 후공 뽑기

	if (game1_turn == 0)                   //컴퓨터 먼저
	{
		for (game1_num = 1; game1_num < 22; game1_num += 2)
		{
			usergamenum = game1_num + 1;
			stg2 = game1_num;
			stg3 = usergamenum;

			if (stg2 == 3 || stg2 == 9 || stg2 == 13 || stg2 == 19)    //0을 외쳐야 되는 숫자
			{
				stg2 = 0;
			}
			else;

			if (stg3 == 6 || stg3 == 10 || stg3 == 16 || stg3 == 20)  //0을 외쳐야 되는 숫자
			{
				stg3 = 0;
			}
			else;

			printf("COMP >> %d\n", stg2);
			if (stg2== 21)             //21 도달시 종료
			{
				break;
			}
			else;
			printf("USER >> ");
			scanf_s("%d", &stg4);

			if (stg3 != stg4)       //유저가 입력한 값이 틀릴 경우 게임 종료
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

	else                 //유저 선공
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
			if (stg4 == 21)           //21 도달시 종료
			{
				break;
			}
			else;
			printf("COMP >> %d\n", stg3);

			if (stg2 != stg4)       //유저가 입력한 값이 틀릴 경우 종료
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

/*베스킨라빈스 게임
- 베스킨라빈스 게임은 1부터 31까지의 수를 순서대로 불러서 마지막 31을 말하는 사
람이 지는 게임으로, 게임 참여자들은 각자의 순서에 1~3개까지의 숫자를 연속하여
11
말할 수 있다.
- COMPUTER와 USER가 번갈아가면서 게임을 진행하는데, USER는 자신의
순서에 연속하여 부를 숫자의 개수를 입력하며, COMPUTER는 자신의 순서에 연속하여
부를 숫자의 개수를 랜덤하게 선택한다. 각자의 순서에 1~3 범위 내의 숫자를 선택
하도록 한다. (부를 숫자가 3개 미만으로 남은 경우에도 1~3 범위 내의 숫자를 선택
하도록 구현한다.)
- 만약 USER가 1~3 이외에 값을 입력하게 되면 해당 값을 무시하고 다시 입력 받는다.
- 게임 시작은 랜덤하게 플레이어(COMPUTER 또는 USER)를 선택하여 시작하도록 한다.
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

	if (game2_turn == 0)                      //컴퓨터 먼저 시작
	{
		while (a <32 && c<32)
		{
			srand((int)time(NULL));
			rannum = rand() % 3 + 1;               //컴퓨터가 외칠 값을 랜덤으로
			printf("COMP >> %d\n", rannum);        

			if (rannum == 1)                //1일 때
			{
				a += 1;
				printf("%d\n", a);
				if (a >= 31)
					break;
				else;
			}

			else if (rannum == 2)   //2일 때
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

			else                    //3일 때
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
			printf("USER >> ");                   //유저의 차례!
			scanf_s("%d", &b);

			while (b != 1 && b != 2 && b != 3)   //1,2,3 이외의 값을 입력했을 때 잘못되었음을 알려주기
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf_s("%d", &b);

			}
			if (b == 1)              //1일 때
			{
				c += 1;
				printf("%d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 2)           //2일 때
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

			else if (b == 3)          //3일 때
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

		if (a >= 31)                 //승패 결정
			game2_result = 1;
		else
			game2_result = 0;
		
		return game2_result;

	}

	else                                          //user 먼저 시작
	{

		while (a < 32 && c < 32)
		{
			printf("USER >> ");
			scanf_s("%d", &b);

			while (b != 1 && b != 2 && b != 3)      //1,2,3이외이 값을 입력받았을 때 잘못되었음을 표시
			{
				printf("WRONG INPUT!\n");
				printf("USER >> ");
				scanf_s("%d", &b);
			}

			if (b == 1)        //1일 때
			{
				c += 1;
				printf("%d\n", c);
				if (c >= 31)
					break;
				else;
			}

			else if (b == 2)    //2일 때
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

			else if (b == 3)          //3일 때
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
			rannum = rand() % 3 + 1;              //컴퓨터가 입력할 숫자 랜덤으로 정하기
			printf("COMP >> %d\n", rannum);
			
			if (rannum == 1)        //1일 때
			{
				a += 1;
				printf("%d\n", a);
				if (a >= 31)
					break;
				else;
			}

			else if (rannum == 2)   //2일 때
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

			else                        //3일 때
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
		if (a >= 31)           //승패 결정
			game2_result = 1;
		else
			game2_result = 0;

		return game2_result;
	}
}