#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#define size 6

void erase();
void print_start();
int check_position(int* r1, int* c1, int* r2, int* c2);
int btxt(int ary[][size]);
int enter();
int check(int a[size][size], int score);
void print_board(int a[size][size]);
void print_result(int* turn, int* r1, int* c1, int* r2, int* c2, int score, int b[size][size]);
void gamestart();
void turnnum(int* turn);
void scoretot(int score);
void swap(int* a, int* b);
void whatswap1(int* r1, int* c1);
void whatswap2(int* r2, int* c2);
void randnum(int a[][size]);
void redboard(int a[size][size], int r1, int c1, int r2, int c2);
void zero(int a[size][size], int b[size][size]);
void red(int x);
void blankboard(int a[size][size]);
void redboard2(int a[size][size]);

//main 함수 
int main()
{
	srand((unsigned int)time(NULL));
	gamestart();
	return 0;
}

//화면 지우기
void erase()
{
	system("cls");
}

//게임 시작 화면 출력
void print_start()
{
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assingment 2\n\n");
	printf("[[ Match-3 Game ]]\n\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
}

//match 게임 body
void gamestart()
{
	//변수 선언
	int n, score, turn, r1, c1, r2, c2, z;
	r1 = 0;
	c1 = 0;
	r2 = 0;
	c2 = 0;
	score = 0;
	turn = 5;
	print_start();

	//ENTER 입력 받기
	n = enter();
	if (n == 1)
		erase();
	else
		return;     

	int board[size][size];  //메인 보드
	int board2[size][size]; //서브 보드로서 메인 보드 출력 보조
	if (btxt(board) == 0)   //board.txt 불러오기
	{
		erase();
		printf("error!");
		return;
	}
	else;	

	while (turn > 0)          //turn 시작!
	{
		
		erase();
		scoretot(score);
		print_board(board);
		printf("====================\n\n");

		print_result(&turn, &r1, &c1, &r2, &c2, score, board);
		swap(&board[r1][c1], &board[r2][c2]);
		erase();

		scoretot(score);
		redboard(board, r1, c1, r2, c2);   //swap한 블록 2개 빨갛게 출력
		Sleep(1000);
		check(board, score);
		z = check(board, score);
		if (z==0)              
			continue;
		else                        //match 3 있을 경우
		{
			for (; z != 0;)    
			{
				
				erase();               //연속된 블록들 빨갛게 출력
				scoretot(score);
				redboard2(board);
				Sleep(1000);

				erase();               //연속된 블록들 제거 후 점수 계산해 출력
				zero(board, board2);
				score += check(board, score);;
				scoretot(score);
				blankboard(board);
				Sleep(1000);

				erase();                //빈칸에 새로운 랜덤한 블록들 넣고 출력
				randnum(board2);
				scoretot(score);
				print_board(board2);
				Sleep(1000);
				z=check(board2, score);
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						board[i][j] = board2[i][j];
					}
				}
			} 
		}			
	}
	erase();                                //5턴 종료 후
	scoretot(score);
	print_board(board);
	printf("====================\n\n");
	printf("**You've earned %d points**", score);
}

/*가로 또는 세로로 3개 이상의 블록이 같은지 확인하기!
없으면 0을 반환, 있으면 점수 계산해서 늘어난 만큼을 반환*/
int check(int a[size][size], int score)
{
	int ch = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])      //가로 확인
				ch += a[i][j];
			else if (j <= 3 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])
				ch += a[i][j];
			else if (j >= 2 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2])
				ch += a[i][j];
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j]) // 세로 확인
				ch += a[i][j];
			else if (i <= 3 && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
				ch += a[i][j];
			else if (i >= 2 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j])
				ch += a[i][j];
			else;
		}
	}
	if (ch == 0)
		return 0;
	else
		return ch;
}

//가로나 세로로 3개이상 연속된 블록이 있으면 빨갛게 칠해서 보드 출력
void redboard2(int a[size][size])
{
	int k = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])  //가로 빨강
			{
				red(a[i][j]);
				continue;
			}
			else if (j <= 3 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])
			{
				red(a[i][j]);
				continue;
			}
			else if (j >= 2 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2])
			{
				red(a[i][j]);
				continue;
			}
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j])  //세로 빨강
			{
				red(a[i][j]);
				continue;
			}
			else if (i <= 3 && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
			{
				red(a[i][j]);
				continue;
			}
			else if (i >= 2 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j])
			{
				red(a[i][j]);
				continue;
			}
			else                          //그 외에는 그대로
			{
				printf("%d ", a[i][j]);
				continue;
			}
		}
		printf("| %d\n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5\n");
}

//블록을 빨강으로 바꿔 칠하고 다시 검은색으로 바꾸기
void red(int x)
{
	printf("\033[1;31m");
	printf("%d ", x);
	printf("\033[0m");
}

//연속된 블록을 제거한 빈칸이 있는 보드 출력하기
void blankboard(int a[size][size])
{
	int k = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])  //가로 빈칸
			{
				printf("  ");
				continue;
			}
			else if (j <= 3 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])
			{
				printf("  ");
				continue;
			}
			else if (j >= 2 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2])
			{
				printf("  ");
				continue;
			}
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j])  //세로 빈칸
			{
				printf("  ");
				continue;
			}
			else if (i <= 3 && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
			{
				printf("  ");
				continue;
			}
			else if (i > 1 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j])
			{
				printf("  ");
				continue;
			}
			else                   // 그 외에는 그대로
			{
				printf("%d ", a[i][j]);
				continue;
			}
		}
		printf("| %d\n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5\n");
}

//연속된 블록 숫자들 모두 0으로 변환
void zero(int a[size][size], int b[size][size])
{   
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j > 1 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])
				b[i][j] = 0;
			else if (a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])
				b[i][j] = 0;
			else if (j > 2 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2])
				b[i][j] = 0;
			else if (i > 1 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j])
				b[i][j] = 0;
			else if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j])
				b[i][j] = 0;
			else if (i > 2 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j])
				b[i][j] = 0;
			else
				b[i][j] = a[i][j];
		}
	}
}

//0인 블록들은 모두 랜덤한 숫자로 다시 채워주기
void randnum(int a[][size])
{
	int x;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (a[i][j] == 0)
			{
				x = rand() % 5 + 1;
				a[i][j] = x;
			}
			else;
		}
	}
}

//swap한 2개의 블록만 빨갛게 출력
void redboard(int a[size][size], int r1, int c1, int r2, int c2)
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{

			if ((r == r1 && c == c1) || (r == r2 && c == c2))
			{
				red(a[r][c]);
				continue;
			}
			else
				printf("%d ", a[r][c]);
		}
		printf("| %d\n", r);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5\n");
}

//보드판 출력하기
void print_board(int a[size][size])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (a[i][j] == 0)
				printf("   ");
			else;
				printf("%d ", a[i][j]);
		}
		printf("| %d\n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5\n");
	
}	

//입력받은 입력이 유효한지 확인해 출력하기
void print_result(int* turn, int* r1, int* c1, int* r2, int* c2, int score, int b[size][size])
{
	int a;
	turnnum(turn);
	printf("Swap...\n");
	whatswap1(r1, c1);
	whatswap2(r2, c2);

	a=check_position(r1, c1, r2, c2);
	if (a == 0)            //행과 열 범위를 넘어간 입력
	{
		erase();
		scoretot(score);
		print_board(b);
		printf("====================\n\n");
		printf("*** Out of range! ***");
		*turn = *turn + 1;
		print_result(turn, r1, c1, r2, c2, score, b);
	}
	else if (a == 2)   //인접한 두 블록이 아닐 경우
	{
		erase();
		scoretot(score);
		print_board(b);
		printf("====================\n\n");
		printf("*** They are not adjacent! ***");
		*turn = *turn + 1;
		print_result(turn, r1, c1, r2, c2, score, b);
	}
	else;
}

//ENTER 입력 받기
int enter()
{
	char s, n;
	n = scanf("%c", &s);

	if (n == 1)
		return 1;
	else
		return 0;
}

//board.txt 파일 읽어오기
int btxt(int ary[][size])
{
	FILE* ini;
	ini = fopen("board.txt", "r");

	if (ini == 0)
		return 0;
	else
	{
		for (int i = 0; i < 6; i++)
		{
			fscanf_s(ini, "%d %d %d %d %d %d", &ary[i][0], &ary[i][1], \
				&ary[i][2], &ary[i][3], &ary[i][4], &ary[i][5]);
		}
		return 1;
	}
}

//남은 턴 출력
void turnnum(int* turn)
{
	printf("\n* Remaining turns: %d\n", *turn);
	*turn = *turn - 1;
}

//점수 출력
void scoretot(int score)
{
	printf("Score: %d\n", score);
}

//swap 함수
void swap(int* a, int* b)
{
	int tem;
	tem = *a;
	*a = *b;
	*b = tem;
}

//사용자의 입력이 유효한지 확인하기
// 범위를 넘어가면 0을 반환, 인접하지 않으면 2를 반환, 유효하면 1을 반환
int check_position(int* r1, int* c1, int* r2, int* c2)
{
	if (!(*r1 == 0 || *r1 == 1 || *r1 == 2 || *r1 == 3 || *r1 == 4 || *r1 == 5))
		return 0;
	else if (!(*c1 == 0 || *c1 == 1 || *c1 == 2 || *c1 == 3 || *c1 == 4 || *c1 == 5))
		return 0;
	else if (!(*r2 == 0 || *r2 == 1 || *r2 == 2 || *r2 == 3 || *r2 == 4 || *r2 == 5))
		return 0;
	else if (!(*c2 == 0 || *c2 == 1 || *c2 == 2 || *c2 == 3 || *c2 == 4 || *c2 == 5))
		return 0;
	else if (*r1 == *r2 && *c1 == *c2)
		return 2;
	else if (!((*r1 == *r2 && (*c1 == *c2 + 1 || *c2 == *c1 + 1)) \
		|| (*c1 == *c2 && (*r1 == *r2 + 1 || *r2 == *r1 + 1))))
		return 2;
	else
		return 1;
}

//Block 1 입력 받기
void whatswap1(int* r1, int* c1)
{
	printf("Block 1: ");
	scanf_s("%d %d", r1, c1);
}

//Block 2 입력 받기
void whatswap2(int* r2, int* c2)
{
	printf("Block 2: ");
	scanf_s("%d %d", r2, c2);
}