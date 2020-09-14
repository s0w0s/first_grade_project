#pragma warning (disable:4996) //���� ���ſ�
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>	//Ű���� �Է� �Լ� ����� ���� [���ͳ� ����]
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")


#define true 1	//�� ���� �� ��ũ��
#define FALSE 0

#define LEFT 75	 /*Ű���� �Է� ����(�ƽ�Ű)*/
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

#define BY 2	/*�� ������ ���� ����*/
#define BX 3		
#define BH 24		
#define BW 10		
#define MX 44 //��Ƽ ��ġ�� ���� ��ũ�� ��
#define max(a,b) (((a)>(b))?(a):(b))	//���� ū�� ��ȯ ��ũ��


	void gotoxy(int x, int y) { //gotoxy�Լ� [���ͳ� ����]
		COORD pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };//Ŀ�� ������ ����ü [���ͳ� ����]

	void coursor_N() {			//Ŀ�� ����� �Լ�[���ͳ� ����]
		cursorInfo.bVisible = FALSE;
		cursorInfo.dwSize = 100;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
	


	int loginDesign();//�α��� ȭ�� ������

	int signUp();//ȸ������
	int titleDesign(); //���ӽ���ȭ�� ������

	void controlsPresent(void);// ��Ʈ������Ű ����
	void drawSquare(int left, int top, int right, int bottom);//�簢���׸��� ��/��/��/��


	void comboPrint(int x); // ��� �ı��� �޺� ������ ȭ�鿡 ����Լ� 
	void showBlock(int show);	// ��� 				/*http://yk209.tistory.com/entry/c%EC%96%B8%EC%96%B4-%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4-%EA%B2%8C%EC%9E%84-%EC%86%8C%EC%8A%A4 */
	void showNBlock(int show);	// ���� ���			/*http://kkikkodev.tistory.com/71 */
	void showShadow(int show);	// �׸���				//��� ������ ���� ���ظ� ���� ������
	int movedown(); // ����� ��ĭ ������ �Լ�
	int checkAround(int x, int y, int z, int r); // �ֺ� �˻� �Լ�		
	int checkLine(); // ��� �� �˻� �� �Ǵ��Ͽ� ���� [+������ �ټ��� ��ȯ �ϴ� �Լ�]	
	int inputKey(); // Ű �Է� �Լ�		
	int gameOver();	//��������� ȭ�� ����
	void pause(); // �Ͻ� ���� 
	void levelupBonus(); // ���� ���� ���޽� �̺�Ʈ �߻� �Լ�	
	void gamePage();	// ���� ȭ�� 
	void boardPage(); //  �� ���� ��� ��Ȳ ȭ�鿡 ���		
	void gameScore(int x, int y); // ���� ������ ȭ�鿡 �����ִ� �Լ� 
	void gamelevel(); // ���� [����+ ������ ����] ȭ�鿡 �����ִ� �Լ�
	
	void arrBlock(int show);	//�迭 (���� / ����) �Լ�
	int MultiMain(int,int); //��Ƽ�� �Լ�
	void addLine(int atk);		//���� �߰�       
		

	enum { EMPTY, BLOCK, NBLOCK, WALL, SHADOW, LV, ATK };	//�����, �����̴º��, �̵��Ϸ���, ��, �׸���,�̺�Ʈ,����
	
	const char *Tiles[7] = { "  ","��","��","��","��" ,"��", "��" };	//�� �������� ���� ����

	int blocks[7][4][8] = { { { 0,-1,1,-1,-1,0,0,0 },{ -1,-1,-1,0,0,0,0,1 },{ 0,-1,1,-1,-1,0,0,0 },{ -1,-1,-1,0,0,0,0,1 } },

	{ { 0,0,1,0,0,-1,-1,-1 },{ -1,1,-1,0,0,0,0,-1 },{ 0,0,1,0,0,-1,-1,-1 },{ -1,1,-1,0,0,0,0,-1 } },

	{ { -2,1,-1,1,0,1,1,1 },{ -1,2,-1,1,-1,0,-1,-1 },{ -2,1,-1,1,0,1,1,1 },{ -1,2,-1,1,-1,0,-1,-1 } }, // �� 

	{ { -1,1,0,1,1,1,-1,0 },{ -1,1,0,1,0,0,0,-1 },{ 0,1,0,0,-1,0,-2,0 },{ -1,2,-1,1,-1,0,0,0 } }, // �� 

	{ { -1,1,0,1,-1,0,0,0 },{ -1,1,0,1,-1,0,0,0 },{ -1,1,0,1,-1,0,0,0 },{ -1,1,0,1,-1,0,0,0 } }, // �� 

	{ { -2,1,-1,1,0,1,0,0 },{ 0,2,0,1,0,0,-1,0 },{ -1,1,-1,0,0,0,1,0 },{ -1,1,0,1,-1,0,-1,-1 } },

	{ { 0,1,-1,0,0,0,1,0 },{ 0,1,0,0,1,0,0,-1 },{ -1,0,0,0,1,0,0,-1 },{ 0,1,0,0,-1,0,0,-1 } } }; // �� 

	int SingleBoard[BW + 2][BH + 2];			//�̱���ü[�� x,y]
	int MultiBoard[BW + 2][BH + 2];				//��Ƽ��ü[�� x y]
	int Block, Shape, nextBlock, nextShape; // ��� ����, ��� 
	int nx, ny; // ��ǥ�� 
	int Frame = 20, Stay; // ��� �������� �ӵ�
	int score = 0, bestScore=0;		//������ ,�ְ��� ����
	int level = 1,BreakBlocks = 0; // ����, �μ��� ��ϼ� ������ ����
	
	int main() {

		coursor_N();	//Ŀ�� ����� �Լ�
		char ch;
		int i, j;
		int Mod;
		srand((unsigned)time(NULL)); //����ǥ���� 

		while (loginDesign() != 1) {}

		Mod = titleDesign();
		switch (Mod)
		{
		case 1:
			
			srand((unsigned)time(NULL));
			system("cls");		//�ʱ�ȭ

			for (i = 0;i<BW + 2;i++) {	//�� ������ ���� �迭�� ���� �ִ� 2�� �ݺ���
				
				for (j = 0;j < BH + 2;j++){

					SingleBoard[i][j] = (i == 0 || i == BW + 1 || j == BH + 1)? WALL : EMPTY;
				}
			}
			
			gamePage();	//[��+��ȭ�� ex)���ھ� ] ȭ�鿡 ���� �Լ�
			Block = rand() % 7;		//��� ��������
			Shape = rand() % 4;		// ��� ��� ���� ����

			sndPlaySoundA("A.wav", SND_ASYNC | SND_LOOP);
			
			while (true) 
			{
				nextBlock = rand() % 7;
				nextShape = rand() % 4; // �״��� �� 

				nx = BW / 2;	//5 �߾ӿ� �����ϱ� ���ؼ�
				ny = 1;

				showNBlock(TRUE);
				showShadow(TRUE);//�׸��� ����
				showBlock(TRUE);//��� ����

				if (checkAround(nx, ny, Block, Shape) != 0) {
					arrBlock(true);
					Sleep(1000);//�ǹ� �ִ����� �𸣰���..
					PlaySound(NULL, NULL, NULL);
					gameOver();
					break;
				}//���� ��������

				Stay = Frame;
				arrBlock(true);
				
				while(true) {			//��� �̵� �ϴ� �ݺ��� [����� ���� ������ ��������]	
					
					if (--Stay == 0) {		//�������� �ӵ��� ���� if��

						Stay = Frame;
						arrBlock(FALSE);	//�˻�⸦ ��������� �迭�� ��� �����ֱ� ����
						if (movedown()) {
							break;	//����� ���� ������ �ݺ��� ��������
						}
						
					}

					if (inputKey())break;
					arrBlock(true);
					Sleep(50);
				}

				showNBlock(FALSE);
				Block = nextBlock;
				Shape = nextShape;
			}
			
			break;

		case 2:

			srand((unsigned)time(NULL));
			system("cls");		//�ʱ�ȭ

			for (i = 0;i<BW + 2;i++) {	//�� ������ ���� �迭�� ���� �ִ� 2�� �ݺ���

				for (j = 0;j < BH + 2;j++) {

					SingleBoard[i][j] = (i == 0 || i == BW + 1 || j == BH + 1) ? WALL : EMPTY;
				}
			}


			gamePage();	//[��+��ȭ�� ex)���ھ� ] ȭ�鿡 ���� �Լ�
			Block = rand() % 7;		//��� ��������
			Shape = rand() % 4;		// ��� ��� ���� ����
			PlaySound(TEXT("tg.wav"),NULL, SND_ASYNC | SND_LOOP);
			while (true)
			{
				nextBlock = rand() % 7;
				nextShape = rand() % 4; // �״��� �� 

				nx = BW / 2;	//5 �߾ӿ� �����ϱ� ���ؼ�
				ny = 1;

				showNBlock(TRUE);
				showShadow(TRUE);//�׸��� ����
				showBlock(TRUE);//��� ����

				if (checkAround(nx, ny, Block, Shape) != 0) {
					arrBlock(true);
					Sleep(1000);//�ǹ� �ִ����� �𸣰���..
					PlaySound(NULL, NULL, NULL);
					gameOver();
					break;
				}//���� ��������

				Stay = Frame;
				arrBlock(true);
				

				while (true) {			//��� �̵� �ϴ� �ݺ��� [����� ���� ������ ��������]
					MultiMain(66, 30);
					if (--Stay == 0) {

						Stay = Frame;
						
						arrBlock(FALSE);	//�˻�⸦ ��������� �迭�� ��� �����ֱ� ����
						
						if (movedown()) {
							//*��κп� ��Ƽ ������ �� ȭ�鿡 ����ϴ� �Լ�*//
							

							break;	//����� ���� ������ �ݺ��� ��������
						}
					}

					if (inputKey())break;
					arrBlock(true);
					Sleep(50);
				}

				showNBlock(FALSE);
				Block = nextBlock;
				Shape = nextShape;
			}
			//��Ƽ
		default:
			break;
		}
}
	
	
	int loginDesign(void) {

		int x = 10; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
		int y = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
		char Choose;


		while (true) {
			system("cls");
			gotoxy(x, y + 0);printf("�������  �������  �������  �������  ���  �������     \n");Sleep(100);
			gotoxy(x, y + 1);printf("    ���      ���              ���      ���      ��  ���  ���      ���   \n");Sleep(100);
			gotoxy(x, y + 2);printf("    ���      ���              ���      ���    ���  ���    ���           \n");Sleep(100);
			gotoxy(x, y + 3);printf("    ���      �������      ���      ���  ���    ���      ���         \n");Sleep(100);
			gotoxy(x, y + 4);printf("    ���      ���              ���      ����        ���         ���      \n");Sleep(100);
			gotoxy(x, y + 5);printf("    ���      ���              ���      ���  ���    ���  ���      ���   \n");Sleep(100);
			gotoxy(x, y + 6);printf("    ���      �������      ���      ���    ���  ���    �������   \n");Sleep(100);
			gotoxy(x + 10, y + 13);printf("Connection complete Welcome...");//���ӿϷ� ȯ���մϴ�.
			gotoxy(x + 10, y + 20);printf("[1] ȸ�� ���� [2] �α��� [3]����\n\t");

			Choose = getch();
			if (Choose == '1') {
				//SignUp();
			}//ȸ������
			else if (Choose == '2') { return 1; }//�α���
			else if (Choose == '3') { exit(-1); }//����
			else { gotoxy(x + 10, y + 30); printf("�߸��Է��Ͽ����ϴ� �ٽ� �Է����ּ���."); Sleep(1400); }
		}
	}

	int titleDesign(void) {

		int x = 10; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
		int y = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
		int Choose;//���ѷ��� Ż�� ���ǹ�

		while (true)
		{
			system("cls");
			gotoxy(x, y + 0);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 1);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 2);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 3);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 4);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 5);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x, y + 6);printf("����������������������������������������� \n");Sleep(100);
			gotoxy(x + 10, y + 8);printf("Please Enter want Key to Start..");
			gotoxy(x + 20, y + 13);printf("                                                        "); //welcom�۾� ���������

			gotoxy(x + 10, y + 10); printf("��1.SinglePlay ��    ");
			gotoxy(x + 10, y + 13); printf("��2.Multi Play ��    ");
			gotoxy(x + 10, y + 16); printf("��3. Controls  ��    ");
			gotoxy(x + 10, y + 19); printf("��4.   EXIT    ��\n\n");
			Sleep(10); // 00.1�� ������  
			Choose = getch();
			if (Choose == '1') return 1; //Ű�Է��� ������ ���ѷ��� ����
			else if (Choose == '2')return 2;
			else if (Choose == '3') {
				//����Ű �Լ�
				controlsPresent();
			}
			else if (Choose == '4') { exit(-1); }
			else { printf("\n\t �߸��Է��Ͽ����ϴ� �ٽ� �Է����ּ��� : ");Sleep(1400); }
		}
	}

	
	void controlsPresent(void) {
		system("cls");
		int x = 25, y = 9;
		char ch;

		drawSquare(x - 1, y - 1, x + 30, y + 7);
		gotoxy(x + 10, y - 1);
		printf("%c", 22);
		gotoxy(x + 10, y + 7);
		printf("%c", 21);
		
		gotoxy(x, y);
		printf(" ��       %c Move Left     ", 5);
		gotoxy(x, y + 1);
		printf(" ��       %c Move Right     ", 5);
		gotoxy(x, y + 2);
		printf(" ��       %c Soft Drop      ", 5);
		gotoxy(x, y + 3);
		printf(" ��       %c Rotate Right   ", 5);
		gotoxy(x, y + 4);
		printf(" Space    %c Hard Drop      ", 5);
		gotoxy(x, y + 5);
		printf(" s        %c Pause          ", 5);
		gotoxy(x, y + 6);
		printf("          %c            \n\n", 5);
				
		Sleep(2000);	//2�� ���
		ch = getch();		//Ű�Է½� �Լ���������
		return;

	}


	void drawSquare(int left, int top, int right, int bottom) {
		int i, j;
		for (i = 0; i <= bottom - top; i++) {
			if (i == 0) {
				gotoxy(left, top + i);
				printf("%c", 1);
				for (j = 0; j <= right - left - 2; j++)
					printf("%c", 6);
					printf("%c", 2);
			}
			else if (i == bottom - top) {
				gotoxy(left, top + i);
				printf("%c", 3);
				for (j = 0; j <= right - left - 2; j++)
				printf("%c", 6);
				printf("%c", 4);
			}
			else {
				gotoxy(left, top + i);
				printf("%c", 5);
				gotoxy(right, top + i);
				printf("%c", 5);
			}
		}
		return;
	}

	int signUp(void) {
		char ID[20];

		system("cls");
		printf("ȸ������ ��û��..");
		while (true) {
			printf("ID�� �Է��ϼ��� : ");
			scanf("%s", ID);
			//if ()//���̵� �̹� ���� ���� printf("�̹� �����ϴ� ���̵� �Դϴ�.");
			//ID[0]=NULL;
		}
	}

		
	void showBlock(int show) {

		int i;
		
		for (i = 0;i<8;i += 2) {

			gotoxy(BX + (blocks[Block][Shape][i] + nx) * 2, BY + blocks[Block][Shape][i + 1] + ny);
			puts(Tiles[show ? BLOCK : EMPTY]); // show���� ���̸� ��, �����̸� ���� 
		}
	}


	void gamePage() {  // ����ȭ�� ��� 

		int i, j;

		for (i = 0;i<BW + 2;i++) {			//����ȭ�� �� �׸��� �ݺ���

			for (j = 0;j<BH + 2;j++) {
				gotoxy(BX + i * 2, BY + j);
				puts(Tiles[SingleBoard[i][j]]);
			}
		}

		gotoxy(28, 2);printf("������ Next Block ������\n");
		gotoxy(28, 3);printf("��                    ��\n");
		gotoxy(28, 4);printf("��                    ��\n");
		gotoxy(28, 5);printf("��                    ��\n");
		gotoxy(28, 6);printf("��                    ��\n");
		gotoxy(28, 7);printf("��                    ��\n");
		gotoxy(28, 8);printf("��                    ��\n");
		gotoxy(28, 9);printf("������������������������\n");

		gameScore(0, 0);
		gamelevel();//���� ������ ���� ��� Ŭ���� ��

	}


	int inputKey() { // Ű ������ 

		int ch;
		arrBlock(FALSE);	//������ �������� �迭 ��� ����

		if (kbhit()) {

			ch = getch();

			switch (ch) {

			case 'S':

			case 's':

				pause();

				break;

			case LEFT:

				if (checkAround(nx - 1, ny, Block, Shape) == EMPTY) {

					showBlock(FALSE);
					showShadow(FALSE);

					nx--;

					showShadow(TRUE);
					showBlock(TRUE);
					//addLine(2);
				}

				break;

			case RIGHT:

				if (checkAround(nx + 1, ny, Block, Shape) == EMPTY) {

					
					showBlock(FALSE);
					showShadow(FALSE);

					nx++;
					//addLine(2);
					showShadow(TRUE);
					showBlock(TRUE);
				}

				break;

			case UP:
				for (int i = 0; i < 2; i++)
				{
					if (checkAround(nx, ny, Block, (Shape + 1) % 4) == WALL) {
						if (nx < 3) {
							showBlock(FALSE);
							showShadow(FALSE);
							nx++;
						}

						else if (nx > 9) {

							showBlock(FALSE);
							showShadow(FALSE);
							nx--;
						}
					}
				}
				
		
				if (checkAround(nx, ny, Block, (Shape + 1) % 4) == EMPTY) {
					
						showBlock(FALSE);
						showShadow(FALSE);

						Shape = (Shape + 1) % 4;	//��� ������
						
						showShadow(TRUE);
						showBlock(TRUE);
					
				}

				break;

			case DOWN:

				if (movedown()) {	//������ �������� ����

					return TRUE;
				}

				break;

			case SPACE:		//�����̽�
				
				while (movedown() == FALSE) {}		//�ٳ����������� �ݺ�

				return TRUE;

			}
		}

		return FALSE;
	}


	int checkAround(int x, int y, int z, int r) { // �ֺ� �� �˻� 

		int i, k = EMPTY;

		for (i = 0;i<8;i += 2) {

			k = max(k, SingleBoard[x + blocks[z][r][i]][y + blocks[z][r][i + 1]]); // �ΰ��� ���Ͽ� �����ִٸ� ����� ��ȯ 
																			 //a�� b�� ���Ͽ� ū�� ��ȯ
		}
		return k; // 0�̸� ���� �׿ܰ��̸� �� 
	}


	int movedown() { // �Ʒ��� ��ĭ ������ 

		if (checkAround(nx, ny + 1, Block, Shape) != EMPTY) {	//��ĭ ������ ������ ����

			checkLine();

			return TRUE;

		}

		showBlock(FALSE);

		ny++;

		showBlock(TRUE);

		return FALSE;
	}


	int checkLine() { // �� �˻� + ��� ó��[ȭ��,�迭]

		int i, j, x, y, combo = 0, Line=0;

		for (i = 0;i<8;i += 2) {		//���,�迭 nBLOCKó��
			gotoxy(BX + (blocks[Block][Shape][i] + nx) * 2, BY + blocks[Block][Shape][i + 1] + ny);
			SingleBoard[nx + blocks[Block][Shape][i]][ny + blocks[Block][Shape][i + 1]] = NBLOCK;
			puts(Tiles[NBLOCK]);
		}

		for (i = 1;i<BH + 1;i++) {		//����

			for (j = 1;j<BW + 1;j++) {		//����

				if (SingleBoard[j][i] != NBLOCK && SingleBoard[j][i] != ATK)break;

			} // �� �˻� 


			if (j == BW + 1) {	//���� ��á���� 

				comboPrint(++combo);
				Line++;		//�μ��� ���� ����
				
				for (y = i;y>1;y--) {		//�迭 ���� ������ 2�� �ݺ���

					for (x = 1;x<BW + 1;x++) {

						SingleBoard[x][y] = SingleBoard[x][y - 1];	//���� �迭 ������
					}
				}

				BreakBlocks++;
				gamelevel();	//���� ȭ�� 
				Sleep(500);
				boardPage();	//���� �ڽ��� ����
			}
		}
		combo = 0;
		levelupBonus();//������ ���� + ���ʽ�
		if (Line > 2) { Line *= 2; }
		return Line;
	}

	
	void boardPage() { // ���� �ڽ� �� ������� 

		int i, j;
		
		for (i = 1;i<BW + 1;i++) {	//�� ���� ������ 2�߹ݺ���

			for (j = 1;j<BH + 1;j++) {

				gotoxy(BX + i * 2, BY + j);	puts(Tiles[SingleBoard[i][j]]);
				
			}
		}
	}

	
	void showNBlock(int show) { // ���� �� ��� 

		int i;

		for (i = 0;i<8;i += 2) {

			gotoxy(40 + blocks[nextBlock][nextShape][i] * 2, 5 + blocks[nextBlock][nextShape][i + 1]);	//������ġ�� ��� ���
			//x*2�� ȭ��� ���� [���� 2ĭ ���� 1ĭ���� �������⶧����]
			puts(Tiles[show ? BLOCK : EMPTY]); // show���� ���̸� ��, �����̸� ���� 
		}
	}

	
	void gameScore(int a, int b) { // ���� ���� 

		score += a;
		score += b;
		if (score > bestScore) { bestScore = score; }
		gotoxy(30, 24);printf("Score : %d", score);
		gotoxy(30, 22);printf("bsetScore : %d", bestScore);
	}
	

	void showShadow(int show) {
		int i;
		int yy;

		for (yy = ny;checkAround(nx, yy, Block, Shape) == EMPTY;yy++);		//���� ��� empty�� �ƴҶ����� �ݺ�

		for (i = 0;i<8;i += 2) {

			gotoxy(BX + (blocks[Block][Shape][i] + nx) * 2, BY + blocks[Block][Shape][i + 1] + yy - 1);//empty���·� �����ֱ����� [yy-1]
			
			puts(Tiles[show ? SHADOW : EMPTY]);

		}
	}
	

	void levelupBonus() {

		int i, j,Check=0;
		
		if (BreakBlocks >= 5) {
						
			if (level < 5) { BreakBlocks %= 5;	//�ѹ��� 7~8���Ǵ� ��Ȳ�� ����
			gotoxy(BX + 8, 8);printf("Leve up!!");
			Check = true;
			}
			
			if (level >= 5) {if (BreakBlocks >= 10){		//������ �����̻� �ö󰡸� �̺�Ʈ �߻�	3ĭ �����
				BreakBlocks %= 10;	
				Check = true;
				gotoxy(BX + 8, 8);	printf("Leve up!!");

					for (i = BH;i > BH - 3;i--) {

						for (j = 1;j < BW + 1;j++) {

							gotoxy(BX + j * 2, BY + i);
							puts(Tiles[LV]);
							SingleBoard[j][i] = LV;
							Sleep(40);
						}
					}

				Sleep(100);

				for (i = BH;i > 3 - 1;i--) {

					for (j = 1;j < BW + 1;j++) {
						SingleBoard[j][i] = SingleBoard[j][i - 3];
					}
				}
			}//����	
			}//���

			Sleep(300);
			boardPage(); //��Ͼ� ��Ȳ ȭ�鿡 ���
			
			if (Check==true)//������ Ȯ��
			{
				if (Frame > 4)Frame -= 3;

				else Frame = 4;
				level++;
			}
						
		}
		gamelevel();
		
	}

	void comboPrint(int x) {

		gotoxy(BX + 6, 8);printf("%d combo!", x); // �޺�
		gotoxy(BX + 16, 9);printf("+%d", x*x * 100);
		gotoxy(BX + 16, 10);printf("+%d", level*x * 100);
		
		gameScore(x*x * 100, level*x * 100);
	}
	

	void gamelevel() {	//���� + ������ ��� ǥ��
		
		gotoxy(30, 26);	printf("Lv : %d", level);
		if (level >= 5) { gotoxy(30, 27); printf("Break block :%2d/10", BreakBlocks); }
		else { gotoxy(30, 27); printf("Break block :%d/5", BreakBlocks); }

	}

	
	void pause() {
		char pause;

		gotoxy(BX + BW , BY + 7);	printf("�ââââââââââââââââ�");
		gotoxy(BX + BW , BY + 8);	printf("��                              ��");
		gotoxy(BX + BW , BY + 9);	printf("��         P  A  U  S  E        ��");
		gotoxy(BX + BW , BY + 10);	printf("��                              ��");
		gotoxy(BX + BW , BY + 11);	printf("��      �ƹ� Ű�� ��������      ��");
		gotoxy(BX + BW , BY + 12);	printf("��                              ��");
		gotoxy(BX + BW , BY + 13);	printf("�ââââââââââââââââ�");
		Sleep(1000);
		pause = getch();
		system("cls");
		boardPage();
		gamePage();

		showNBlock(TRUE);
		showBlock(TRUE);
		showShadow(TRUE);
	}


	int gameOver() {
		char over;

		gotoxy(BX + BW , BY + 7);	printf("�ââââââââââââââââ�");
		gotoxy(BX + BW , BY + 8);	printf("��                              ��");
		gotoxy(BX + BW , BY + 9);	printf("��                              ��");
		gotoxy(BX + BW , BY + 10);	printf("��      G A M E    O V E R      ��");
		gotoxy(BX + BW , BY + 11);	printf("��                              ��");
		gotoxy(BX + BW , BY + 12);	printf("��                              ��");
		gotoxy(BX + BW , BY + 13);	printf("�ââââââââââââââââ�");
		over = getch();
		gotoxy(1, 28);
		return bestScore;
	}
		
	void arrBlock(int show) {

		for (int i = 0;i<8;i += 2) {		

			SingleBoard[nx + blocks[Block][Shape][i]][ny + blocks[Block][Shape][i + 1]] = (show ? BLOCK : EMPTY);

		}
	}
	
	
	int MultiMain(int Mx,int score) {
		
		int i, j;
		//system("cls");		//�ʱ�ȭ
		
		for (i = 0;i<BW + 2;i++) {	//�� ������ ���� �迭�� ���� �ִ� 2�� �ݺ���

			for (j = 0;j < BH + 2;j++) {

				MultiBoard[i][j] = SingleBoard[i][j];
			}
		}
		
		for (i = 0;i<BW + 2;i++) {	//�� ������ ���� �迭�� ���� �ִ� 2�� �ݺ���

			
			for (j = 0;j<BH + 2;j++) {
				
				gotoxy(Mx +BX + i * 2, BY + j);	puts(Tiles[MultiBoard[i][j]]);
				
			}
		}

	
		
		return 1; //����
	}

	void addLine(int atk)
	{
		int i, j;
		int AT = (rand() % 9) + 1;//�������� ���ڸ��� ����α�����

		for (i = atk;i < BH + 1;i++) {
			for (j = 0;j < BW + 1;j++) {
				SingleBoard[j][i - atk] = SingleBoard[j][i];
			}
		}

		for (i = BH;i > BH - atk;i--) {

			for (j = 1;j < BW + 1;j++) {

				gotoxy(BX + j * 2, BY + i);
				if (AT == j)
				{
					SingleBoard[j][i] = EMPTY;	//��ĭ�� ����ֱ�����
				}
				else {
					SingleBoard[j][i] = ATK;
					Sleep(40);
				}
			}
			AT = (rand() % 9) + 1;	//����
		}

		Sleep(100);
		boardPage(); //��Ͼ� ��Ȳ ȭ�鿡 ���
		showNBlock(TRUE);
		showBlock(TRUE);	//��� show
		showShadow(TRUE);	//�׸��� show
	}