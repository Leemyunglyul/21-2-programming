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

//main �Լ� 
int main()
{
	srand((unsigned int)time(NULL));
	gamestart();
	return 0;
}

//ȭ�� �����
void erase()
{
	system("cls");
}

//���� ���� ȭ�� ���
void print_start()
{
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assingment 2\n\n");
	printf("[[ Match-3 Game ]]\n\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
}

//match ���� body
void gamestart()
{
	//���� ����
	int n, score, turn, r1, c1, r2, c2, z;
	r1 = 0;
	c1 = 0;
	r2 = 0;
	c2 = 0;
	score = 0;
	turn = 5;
	print_start();

	//ENTER �Է� �ޱ�
	n = enter();
	if (n == 1)
		erase();
	else
		return;     

	int board[size][size];  //���� ����
	int board2[size][size]; //���� ����μ� ���� ���� ��� ����
	if (btxt(board) == 0)   //board.txt �ҷ�����
	{
		erase();
		printf("error!");
		return;
	}
	else;	

	while (turn > 0)          //turn ����!
	{
		
		erase();
		scoretot(score);
		print_board(board);
		printf("====================\n\n");

		print_result(&turn, &r1, &c1, &r2, &c2, score, board);
		swap(&board[r1][c1], &board[r2][c2]);
		erase();

		scoretot(score);
		redboard(board, r1, c1, r2, c2);   //swap�� ��� 2�� ������ ���
		Sleep(1000);
		check(board, score);
		z = check(board, score);
		if (z==0)              
			continue;
		else                        //match 3 ���� ���
		{
			for (; z != 0;)    
			{
				
				erase();               //���ӵ� ��ϵ� ������ ���
				scoretot(score);
				redboard2(board);
				Sleep(1000);

				erase();               //���ӵ� ��ϵ� ���� �� ���� ����� ���
				zero(board, board2);
				score += check(board, score);;
				scoretot(score);
				blankboard(board);
				Sleep(1000);

				erase();                //��ĭ�� ���ο� ������ ��ϵ� �ְ� ���
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
	erase();                                //5�� ���� ��
	scoretot(score);
	print_board(board);
	printf("====================\n\n");
	printf("**You've earned %d points**", score);
}

/*���� �Ǵ� ���η� 3�� �̻��� ����� ������ Ȯ���ϱ�!
������ 0�� ��ȯ, ������ ���� ����ؼ� �þ ��ŭ�� ��ȯ*/
int check(int a[size][size], int score)
{
	int ch = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])      //���� Ȯ��
				ch += a[i][j];
			else if (j <= 3 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])
				ch += a[i][j];
			else if (j >= 2 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2])
				ch += a[i][j];
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j]) // ���� Ȯ��
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

//���γ� ���η� 3���̻� ���ӵ� ����� ������ ������ ĥ�ؼ� ���� ���
void redboard2(int a[size][size])
{
	int k = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])  //���� ����
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
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j])  //���� ����
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
			else                          //�� �ܿ��� �״��
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

//����� �������� �ٲ� ĥ�ϰ� �ٽ� ���������� �ٲٱ�
void red(int x)
{
	printf("\033[1;31m");
	printf("%d ", x);
	printf("\033[0m");
}

//���ӵ� ����� ������ ��ĭ�� �ִ� ���� ����ϱ�
void blankboard(int a[size][size])
{
	int k = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j >= 1 && j < 5 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1])  //���� ��ĭ
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
			else if (i >= 1 && i < 5 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j])  //���� ��ĭ
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
			else                   // �� �ܿ��� �״��
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

//���ӵ� ��� ���ڵ� ��� 0���� ��ȯ
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

//0�� ��ϵ��� ��� ������ ���ڷ� �ٽ� ä���ֱ�
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

//swap�� 2���� ��ϸ� ������ ���
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

//������ ����ϱ�
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

//�Է¹��� �Է��� ��ȿ���� Ȯ���� ����ϱ�
void print_result(int* turn, int* r1, int* c1, int* r2, int* c2, int score, int b[size][size])
{
	int a;
	turnnum(turn);
	printf("Swap...\n");
	whatswap1(r1, c1);
	whatswap2(r2, c2);

	a=check_position(r1, c1, r2, c2);
	if (a == 0)            //��� �� ������ �Ѿ �Է�
	{
		erase();
		scoretot(score);
		print_board(b);
		printf("====================\n\n");
		printf("*** Out of range! ***");
		*turn = *turn + 1;
		print_result(turn, r1, c1, r2, c2, score, b);
	}
	else if (a == 2)   //������ �� ����� �ƴ� ���
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

//ENTER �Է� �ޱ�
int enter()
{
	char s, n;
	n = scanf("%c", &s);

	if (n == 1)
		return 1;
	else
		return 0;
}

//board.txt ���� �о����
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

//���� �� ���
void turnnum(int* turn)
{
	printf("\n* Remaining turns: %d\n", *turn);
	*turn = *turn - 1;
}

//���� ���
void scoretot(int score)
{
	printf("Score: %d\n", score);
}

//swap �Լ�
void swap(int* a, int* b)
{
	int tem;
	tem = *a;
	*a = *b;
	*b = tem;
}

//������� �Է��� ��ȿ���� Ȯ���ϱ�
// ������ �Ѿ�� 0�� ��ȯ, �������� ������ 2�� ��ȯ, ��ȿ�ϸ� 1�� ��ȯ
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

//Block 1 �Է� �ޱ�
void whatswap1(int* r1, int* c1)
{
	printf("Block 1: ");
	scanf_s("%d %d", r1, c1);
}

//Block 2 �Է� �ޱ�
void whatswap2(int* r2, int* c2)
{
	printf("Block 2: ");
	scanf_s("%d %d", r2, c2);
}