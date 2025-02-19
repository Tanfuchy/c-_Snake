#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include<stdio.h>
#define Height 600  // ��Ϸ����ߴ�
#define Width 1000
#define N 50
#define K 20
#define S 200000000

//���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

// ȫ�ֱ���
IMAGE img_menu;    //����˵�����
int gameStatus; // ��Ϸ״̬��0Ϊ�˵���1Ϊ������Ϸ��2Ϊ˫��ģʽ��3Ϊ����,4Ϊ��ͣ,5Ϊ���˽�����6Ϊ˫�˽���

IMAGE img_help;   //�����������
IMAGE img_over;   //�����������
IMAGE img_bk;    //����IMAGE����

int minute;
int second;			//ʱ��
int l;

int m;     //�浵������Ҫ

//����
IMAGE img_9;
IMAGE img_10;

int score;   //��Ϸ�÷�

int temp;     //�л���ͬ��Ϸ

int location_x, location_y;    //��ͼ����
int head_x, head_y;   //��ͷ����
float radius_head;   //��ͷ�뾶
int moveDirection;    //��ͷ�ƶ�����
int moveSpeed;    //��ͷ�ƶ��ٶ�

int body_x[S], body_y[S];  //����
float radius_body;    //����뾶
int k;    //�������йصı�������
int n;    //���峤��

int eyeb_x1, eyeb_y1;   //�۰�1
int eyeb_x2, eyeb_y2;   //�۰�2
float radius_eyeb;   //�۰װ뾶

int eyez_x1, eyez_y1;   //����1
int eyez_x2, eyez_y2;   //����2
float radius_eyez;   //����뾶

int ball_x1[N], ball_y1[N]; // С����npc1������
int ball_x2[N], ball_y2[N]; // С����npc2������
int ball_x3[N], ball_y3[N]; // С����npc3������
float radius1, radius2, radius3;    //npc�İ뾶
//˫��
IMAGE img_1;
IMAGE img_2;
IMAGE img_3;
IMAGE img_4;
IMAGE img_5;
IMAGE img_6;
IMAGE img_7;
IMAGE img_8;

const double pi = 4.0 * atan(1.0);

int score1;        //���1�ķ���
int score2;			//���2�ķ���
int win_player;

int head1_x, head1_y;   //1��ͷ����
int head2_x, head2_y;   //2��ͷ����
int moveDirection1;    //1��ͷ�ƶ�����
int moveDirection2;	//2��ͷ�ƶ�����
int moveSpeed1;    //1��ͷ�ƶ��ٶ�
int moveSpeed2;    //2��ͷ�ƶ��ٶ�


int eyeb1_x1, eyeb1_y1;   //1���۰�1
int eyeb2_x1, eyeb2_y1;   //2���۰�1
int eyeb1_x2, eyeb1_y2;   //1���۰�2
int eyeb2_x2, eyeb2_y2;   //2���۰�2
float radius1_eyeb;   //1���۰װ뾶
float radius2_eyeb;   //2���۰װ뾶

int eyez1_x1, eyez1_y1;   //1������1
int eyez1_x2, eyez1_y2;   //1������2
int eyez2_x1, eyez2_y1;   //2������1
int eyez2_x2, eyez2_y2;   //2������2

float radius1_eyez;   //1������뾶
float radius2_eyez;   //2������뾶

int body1_x[50000], body1_y[50000];	//1������
int body2_x[50000], body2_y[50000];	//2������
float radius1_body;		//1������뾶
float radius2_body;		//2������뾶
int i;				 //�������йصı�������
float length1;				//1������ĳ���
float length2;				//2������ĳ���

//������װ
void startup();   //���ݳ�ʼ��
void menu();    //�˵�
void help();    //����
void playoperation();   //ִ�в���
void gameover();
void time();    //����ʱ
void stop();    //��Ϸ��ͣ

void playgame1();   //������Ϸ
void startup1();  // ����ģʽ��ʼ��
void clean1();   // ��������
void show1();    // ��ʾ����
void over1();    // ��������
void updateWithoutInput1();  // ���û������޹صĸ���
void updateWithInput1();  // ���û������йصĸ���

void playgame2();   //˫����Ϸ
void startup2();  // ˫��ģʽ��ʼ��
void clean2();  // ��������
void show2();  // ��ʾ����
void over2();    // ��������
void control1_body();   //����С��1�������ƶ�
void control2_body();   //����С��2�������ƶ�
void control1_eyez();   //����С��1���۾��ƶ�
void control2_eyez();   //����С��2���۾��ƶ�
void updateWithoutInput2();  // ���û������޹صĸ���
void updateWithInput2();  // ���û������йصĸ���

//�浵����
void readRecordFile1();  //��ȡ��Ϸ�����ļ��浵
void writeRecordFile1();  //�洢��Ϸ�����ļ��浵

void readRecordFile2();  //��ȡ��Ϸ�����ļ��浵
void writeRecordFile2();  //�洢��Ϸ�����ļ��浵

//
void startup()   //���ݳ�ʼ��
{
	initgraph(Width, Height);    //��ʼ��������С������һ���ߴ�Ϊ1000x600�Ļ�ͼ����

//��ȡͼƬ��img������
	loadimage(&img_menu, _T(".\\̰���߲˵�����.jpg"));  
	/*����Դ�ļ���ȡͼ��
	void loadimage(
		IMAGE * pDstImg, // ����ͼ��� IMAGE ����ָ��
		LPCTSTR pResType, // ��Դ����
		LPCTSTR pResName, // ��Դ����
		int nWidth = 0, // ͼƬ��������
		int nHeight = 0, // ͼƬ������߶�
		bool bResize = false // �Ƿ���� IMAGE �Ĵ�С����ӦͼƬ
	);
	*/
	loadimage(&img_help, _T(".\\��������ͼ.jpg"));
	loadimage(&img_over, _T(".\\��������ͼ.jpg"));

	BeginBatchDraw();/* ��������Ҫ���������Ķ���ʱ��һֱˢ����Ļ��������������ǿ��������������������⡣    
	����BeginBatchDraw�����еĻ�ͼ��������ʾ����Ļ�ϣ��������ڴ��н���,ֱ������EndBatchDraw��֮ǰ�������ڴ��л�ͼ�ĳ�Ʒ��һ��չʾ����Ļ��*/

	while (gameStatus == 0)   //��Ϸ״̬��0Ϊ�˵���1Ϊ��ʼ��Ϸ��2Ϊ˫��ģʽ��3Ϊ����,4Ϊ��ͣ,5Ϊ���˽�����6Ϊ˫�˽���
		menu();		//����  �˵� ����
}

void menu()    //�˵�
{
	m = 0;

	putimage(0, 0, &img_menu);    
	/*��ʾ�˵�����ͼƬ���˺������÷�ʽΪvoid putimage(int left,int top,void *buf,int ops);
	����(left,top)Ϊ�����Ļͼ������Ͻǣ������ͼ�����ʼλ�á�bufָ��Ҫ������ڴ���ͼ�񡣲���ops����ͼ���Ժ��ַ�ʽ�������Ļ�ϡ�*/
	setbkmode(TRANSPARENT);
	/* ʹ��SetBkMode����������DrawText�����������ʽ����ʾ�豸�������������ʽ��OPAQUE��TRANSPARENT��
	OPAQUE�ķ�ʽ���õ�ǰ�����Ļ�ˢ����ɫ�����ʾ���ֵı�������TRANSPARENT��ʹ��͸���������Ҳ�������ֵı����ǲ��ı�ġ�*/
	//settextcolor(RGB(205, 92, 92));
	//settextstyle(100, 0, _T("�����鷨�������"));
	/* ����settextstyle() ����ͼ���ı���ǰ���塢�ı���ʾ����ˮƽ��ʾ��ֱ��ʾ���Լ��ַ���С��
	�÷������˺������÷�ʽΪvoid settextstyle(int font,int direction,int charsize);
	˵���������������У�fontΪ�ı����������directionΪ�ı���ʾ����charsizeΪ�ַ���С������

	_T("")��һ����,��������������ĳ���֧��Unicode���롣������У�T��Transformation��ת��������˼��
	��ΪWindowsʹ�������ַ���ANSI��UNICODE��ǰ�߾���ͨ��ʹ�õĵ��ֽڷ�ʽ�������ַ�ʽ����������������˫�ֽ��ַ������㣬
	���׳��ְ�����ֵ��������������˫�ֽڷ�ʽ�����㴦��˫�ֽ��ַ���*/
	//outtextxy(Width * 0.2, Height * 0.15, "̰���ߴ���ս"); 
	//��������� settextcolor settextstyle outtextxy�Ǳ������ʾ

	settextcolor(RGB(85, 107, 47));
	settextstyle(50, 0, _T("����"));
	outtextxy(Width * 0.4, Height * 0.5, "����ģʽ");
	outtextxy(Width * 0.4, Height * 0.6, "˫��ģʽ");
	outtextxy(Width * 0.45, Height * 0.7, "����");

	settextcolor(RGB(102, 139, 139));
	settextstyle(20, 0, _T("����"));
	outtextxy(Width * 0.8, Height * 0.85, "���������ѡ��");

	
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.495, Width * 0.61, Height * 0.585);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.595, Width * 0.61, Height * 0.685);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.695, Width * 0.61, Height * 0.785);

	FlushBatchDraw();
	Sleep(2);

	MOUSEMSG m;		 //���������Ϣ
	while (MouseHit())    //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.495 && m.y <= Height * 0.585)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������������ģʽ
				gameStatus = 1;
		}
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.595 && m.y <= Height * 0.685)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //���������˫��ģʽ
				gameStatus = 2;
		}
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.695 && m.y <= Height * 0.785)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������������
				gameStatus = 3;
		}
	}
}

void help()   //������ʼ��
{
	putimage(0, 0, &img_help);    //��ʾ��������ͼƬ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(30, 0, _T("����"));
	outtextxy(Width * 0.1, Height * 0.2, "����Ϸ��2��ģʽ");
	outtextxy(Width * 0.1, Height * 0.3, "��ģʽ1Ϊ������ʱģʽ");
	outtextxy(Width * 0.1, Height * 0.4, "  ��ģʽָ���޶�ʱ������ҿ���̰���߶��ʳ���ȡ�÷�");
	outtextxy(Width * 0.1, Height * 0.5, "��ģʽ2Ϊ˫�˶�սģʽ");
	outtextxy(Width * 0.1, Height * 0.6, "  ��ģʽָ��ս��ҿ����Լ���̰���߶��ʳ�ɱ���Է���");
	outtextxy(Width * 0.1, Height * 0.7, "  ʱ���ֹʱ�����϶�����ʤ��");


	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));
	outtextxy(Width * 0.85, Height * 0.1, "�˳�");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.09, Width * 0.93, Height * 0.15);

	FlushBatchDraw();
	/* ��ʹ��Easy���ʱ������ÿ�ζ�������ʱ����Ʊ�����������˸������������������ͼ���������л�ͼһ������ʾ�������Խ����˸�����⡣
	BeginBatchDraw����������ڿ�ʼ������ͼ��ִ�к��κλ�ͼ����������ʱ���������Ļ�ϣ�ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ�����*/
	Sleep(5);

	char input;
	if (_kbhit())    //�ж��Ƿ�������
	{
		input = _getch();   //�����û��Ĳ�ͬ������ѡ�񣬲�������س�
		if (input == 27)    //Esc�˳���������
			gameStatus = 0;
	}

	MOUSEMSG m;		 //���������Ϣ
	while (MouseHit())    //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.09 && m.y <= Height * 0.15)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������
				gameStatus = 0;
		}
	}

	playoperation();
}

void playoperation()   //ִ�в���
{
	while (gameStatus == 0)   //����˵�����
		menu();
	while (gameStatus == 1)   //���뵥��ģʽ����
		playgame1();
	while (gameStatus == 2)   //����˫��ģʽ����
		playgame2();
	while (gameStatus == 3)   //�����������
		help();
	while (gameStatus == 4)   //������ͣ����
		stop();
	while (gameStatus == 5)   //���뵥�˽�������
		over1();
	while (gameStatus == 6)   //����˫�˽�������
		over2();
}

void gameover()
{
	EndBatchDraw();
	closegraph();
}

void time()
{
	TCHAR str1[10];
	TCHAR str2[10];
	TCHAR str3[10];
	int k = 0;
	setbkcolor(WHITE);
	settextcolor(RGB(200, 150, 0));
	settextstyle(28, 0, _T("����"));
	sprintf_s(str1, _T("%d"), minute);
	outtextxy(Width / 2 - 23, 5, str1);
	outtextxy(Width / 2 - 10, 5, ":");
	sprintf_s(str2, _T("%d"), (second - minute * 60) / 10);
	outtextxy(Width / 2, 5, str2);
	sprintf_s(str3, _T("%d"), second - minute * 60 - ((second - minute * 60) / 10) * 10);
	outtextxy(Width / 2 + 15, 5, str3);

	setcolor(RGB(200, 150, 0));
	rectangle(Width / 2 - 30, 3, Width / 2 + 33, 33);

	if (minute == 0 && second == 0)
	{
		if (gameStatus == 1)
			gameStatus = 5;
		else if (gameStatus == 2)
			gameStatus = 6;
	}
}

void stop()
{
	putimage(0, 0, &img_help);    //��ʾ��������ͼƬ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("����"));
	outtextxy(Width * 0.42, Height * 0.25, "��Ϸ��ͣ");
	outtextxy(Width * 0.3, Height * 0.5, "������Ϸ");
	outtextxy(Width * 0.55, Height * 0.5, "�˳���Ϸ");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.28, Height * 0.48, Width * 0.52, Height * 0.59);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.53, Height * 0.48, Width * 0.77, Height * 0.59);

	FlushBatchDraw();
	Sleep(5);

	MOUSEMSG m;		 //���������Ϣ
	while (MouseHit())    //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.28 && m.x <= Width * 0.52 && m.y >= Height * 0.48 && m.y <= Height * 0.59)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������
			{
				if (temp == 1)
					gameStatus = 1;
				else if (temp == 2)
					gameStatus = 2;
			}
		}
		if (m.x >= Width * 0.53 && m.x <= Width * 0.77 && m.y >= Height * 0.48 && m.y <= Height * 0.59)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������
				gameStatus = 0;
		}
	}
	playoperation();
}

void readRecordFile1()  //��ȡ��Ϸ�����ļ��浵
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf_s(fp, "%d %d %d %d %d %f %d %d", &score, &location_x, &location_y, &head_x, &head_y, &radius_head, &moveDirection, &moveSpeed);
	fclose(fp);
}

void writeRecordFile1()  //�洢��Ϸ�����ļ��浵
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf_s(fp, "%d %d %d %d %d %f %d %d", score, location_x, location_y, head_x, head_y, radius_head, moveDirection, moveSpeed);
	fclose(fp);
}

void readRecordFile2()  //��ȡ��Ϸ�����ļ��浵
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf_s(fp, "%d %d %d %d %d %d %f %d %d %d %d", &score1, &head1_x, &head1_y, &score2, &head2_x, &head2_y, &radius_head, &moveDirection1, &moveDirection2, &moveSpeed1, &moveSpeed2);
	fclose(fp);
}

void writeRecordFile2()  //�洢��Ϸ�����ļ��浵
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf_s(fp, "%d %d %d %d %d %d %f %d %d %d %d", score1, head1_x, head1_y, score2, head2_x, head2_y, radius_head, moveDirection1, moveDirection2, moveSpeed1, moveSpeed2);
	fclose(fp);
}


void playgame1()    //������Ϸ
{
	startup1();  // ������Ϸ�����ʼ��
	while (gameStatus == 1)  //  ��Ϸѭ��ִ��
	{
		clean1();  // ��֮ǰ���Ƶ�����ȡ��
		updateWithoutInput1();  // ���û������޹صĸ���
		updateWithInput1();     // ���û������йصĸ���
		show1();  // ��ʾ�»���
		writeRecordFile1();  //�洢��Ϸ�����ļ��浵
		char input;
		if (_kbhit())    //�ж��Ƿ�������
		{
			input = _getch();   //�����û��Ĳ�ͬ������ѡ�񣬲�������س�
			if (input == 27)
			{
				gameStatus = 4;
				m++;
			}
		}
	}
	playoperation();
	gameover();     // ��Ϸ��������������
}

void startup1()  // ����ģʽ��ʼ��
{
	mciSendString("open .\\У��.mp3 alias bkmusic", NULL, 0, NULL);   //��������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);   //ѭ������

	initgraph(Width, Height);    ////��ʼ��������С

	//��ȡͼƬ��img������
	loadimage(&img_bk, _T(".\\̰���߱���ͼ.jpg"));
	loadimage(&img_9, _T(".\\p6.jpg"));
	loadimage(&img_10, _T(".\\ͼ6.jpg"));

	if (m == 0)
	{
		//��ʼ����ͼλ��
		location_x = 0;
		location_y = 0;

		temp = 1;

		//��ʼ��ʱ��
		minute = 3;
		second = 180;
		l = 0;

		//��ʼ���÷�
		score = 0;

		//��ʼ����ͷ�ƶ���������
		moveDirection = 4;

		//��ʼ����ͷλ��
		head_x = Width / 3;
		head_y = Height / 3;
		radius_head = 10;

		//��ʼ������λ��
		radius_body = radius_head;
		n = 20;
		body_x[0] = head_x;
		body_y[0] = head_y - 2 * radius_body;
		for (k = 1; k < n; k++)
		{
			body_x[k] = body_x[k - 1];
			body_y[k] = body_y[k - 1] - 2 * radius_body;
		}

		//��ʼ���۰�λ��
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;
		radius_eyeb = 5;

		//��ʼ������λ��
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
		radius_eyez = 2;

		//��ʼ��С����npc��λ��
		int i;
		for (i = 0; i < N; i++)
		{
			ball_x1[i] = rand() % 1500;
			ball_y1[i] = rand() % 1000;
			ball_x2[i] = rand() % 1500;
			ball_y2[i] = rand() % 1000;
			ball_x3[i] = rand() % 1500;
			ball_y3[i] = rand() % 1000;
		}
		radius1 = 3;
		radius2 = 5;
		radius3 = 7;
	}

	else
		readRecordFile1();  //��ȡ��Ϸ�����ļ��浵

	BeginBatchDraw();
}

void clean1()  // ��������
{
	setcolor(BLACK);
	setfillcolor(BLACK);

	fillcircle(head_x, head_y, radius_head);   //������ͷ

	for (k = 0; k < n; k++)
		fillcircle(body_x[k], body_y[k], radius_body);   //��������

	//�����۾�
	fillcircle(eyeb_x1, eyeb_y1, radius_eyeb);   //�����۰�1
	fillcircle(eyeb_x2, eyeb_y2, radius_eyeb);   //�����۰�2
	fillcircle(eyez_x1, eyez_y1, radius_eyez);   //��������1
	fillcircle(eyez_x2, eyez_y2, radius_eyez);   //��������2
}

void show1()  // ��ʾ����
{
	putimage(location_x, location_y, &img_bk);  //������(location_x,location_y)λ����ʾ����

	//���Ƶ÷�
	settextcolor(RGB(200, 150, 0));
	setbkcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	putimage(Width - 300, -20, &img_9, NOTSRCERASE);
	putimage(Width - 300, -20, &img_10, SRCINVERT);
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), score);
	outtextxy(Width - 70, 75, s);

	//���Ʊ߿�
	setcolor(RGB(200, 150, 0));
	rectangle(Width - 257, 3, Width - 2, 110);

	//���ƻ�ɫ��ͷ
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(head_x, head_y, radius_head);

	//���ƻ�ɫ����
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	for (k = 0; k < n; k++)
		fillcircle(body_x[k], body_y[k], radius_body);

	//�����۰�
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(eyeb_x1, eyeb_y1, radius_eyeb);
	fillcircle(eyeb_x2, eyeb_y2, radius_eyeb);

	//��������
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(eyez_x1, eyez_y1, radius_eyez);
	fillcircle(eyez_x2, eyez_y2, radius_eyez);

	//����С����npc
	int i;
	for (i = 0; i < N; i++)
	{
		setcolor(RGB(10, 20, 50));
		setfillcolor(RGB(10, 20, 50));
		fillcircle(ball_x1[i], ball_y1[i], radius1);	// ��������Բ	1��
		setcolor(RGB(34, 139, 34));
		setfillcolor(RGB(34, 139, 34));
		fillcircle(ball_x2[i], ball_y2[i], radius2);	// ������Բ   2��
		setcolor(RGB(255, 192, 203));
		setfillcolor(RGB(255, 192, 203));
		fillcircle(ball_x3[i], ball_y3[i], radius3);	// ���Ʒ�Բ  3��
	}

	time();    //ʱ��

	FlushBatchDraw();
	// ��ʱ
	Sleep(3);
}

void over1()     //��������
{
	putimage(0, 0, &img_over);    //��ʾ��������ͼƬ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("����"));
	outtextxy(Width * 0.42, Height * 0.4, "��Ϸ����");

	settextcolor(BLACK);
	settextstyle(40, 0, _T("����"));
	outtextxy(Width * 0.45, Height * 0.55, "�÷֣�");
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), score);
	outtextxy(Width * 0.55, Height * 0.55, s);

	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));
	outtextxy(Width * 0.85, Height * 0.85, "�˳�");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.84, Width * 0.93, Height * 0.90);

	FlushBatchDraw();
	Sleep(5);

	char input;
	if (_kbhit())    //�ж��Ƿ�������
	{
		input = _getch();   //�����û��Ĳ�ͬ������ѡ�񣬲�������س�
		if (input == 27)    //Esc�˳���������
			gameStatus = 0;
	}

	MOUSEMSG m;		 //���������Ϣ
	while (MouseHit())    //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.84 && m.y <= Height * 0.90)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������
				gameStatus = 0;
		}
	}

	playoperation();
}

void updateWithoutInput1()  // ���û������޹صĸ���
{
	//����ʱ��
	if (l >= 59)
	{
		second = second - 1;
		minute = second / 60;
		l = 0;
	}
	else
		l++;

	//�����ƶ�
	for (k = n - 1; k > 0; k--)
	{
		body_x[k] = body_x[k - 1];
		body_y[k] = body_y[k - 1];
	}
	body_x[0] = head_x;
	body_y[0] = head_y;

	//��ͷ�ƶ�
	if (moveDirection == 1)   //a
	{
		head_x -= moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y - radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 2)   //d
	{
		head_x += moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x + radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x + radius_head / 2;
		eyeb_y2 = head_y - radius_head / 2;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 3)   //w
	{
		head_y -= moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x + radius_head / 2;
		eyeb_y1 = head_y - radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y - radius_head / 2;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 4)   //s
	{
		head_y += moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x + radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 5)   //a,w
	{
		head_x -= moveSpeed;
		head_y -= moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x + radius_head / 2 - radius_head / 3;
		eyeb_y1 = head_y - radius_head / 3 - radius_head / 3;
		eyeb_x2 = head_x - radius_head / 2 - radius_head / 3;
		eyeb_y2 = head_y + radius_head / 3 - radius_head / 3;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 6)   //a,s
	{
		head_x -= moveSpeed;
		head_y += moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x - radius_head / 2 - radius_head / 3;
		eyeb_y1 = head_y - radius_head / 3 + radius_head / 3;
		eyeb_x2 = head_x + radius_head / 2 - radius_head / 3;
		eyeb_y2 = head_y + radius_head / 3 + radius_head / 3;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 7)   //d,s
	{
		head_x += moveSpeed;
		head_y += moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x - radius_head / 2 + radius_head / 3;
		eyeb_y1 = head_y + radius_head / 3 + radius_head / 3;
		eyeb_x2 = head_x + radius_head / 2 + radius_head / 3;
		eyeb_y2 = head_y - radius_head / 3 + radius_head / 3;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 8)   //d,w
	{
		head_x += moveSpeed;
		head_y -= moveSpeed;

		//�۰��ƶ�
		eyeb_x1 = head_x + radius_head / 2 + radius_head / 3;
		eyeb_y1 = head_y + radius_head / 3 - radius_head / 3;
		eyeb_x2 = head_x - radius_head / 2 + radius_head / 3;
		eyeb_y2 = head_y - radius_head / 3 - radius_head / 3;

		//�����ƶ�
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	int i;
	for (i = 0; i < N; i++)
	{
		//�ж��Ƿ�Ե�����
		if ((head_x >= ball_x1[i] - radius_head - radius1) && (head_x <= ball_x1[i] + radius_head + radius1) && (head_y >= ball_y1[i] - radius_head - radius1) && (head_y <= ball_y1[i] + radius_head + radius1))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x1[i], ball_y1[i], radius1);
			ball_x1[i] = rand() % 1500;
			ball_y1[i] = rand() % 1000;
			radius_head += 0.02;
			radius_body = radius_head;
			radius_eyeb += 0.02;
			radius_eyez = radius_eyeb / 2;
			n++;
			score += 1;
		}
		if ((head_x >= ball_x2[i] - radius_head - radius2) && (head_x <= ball_x2[i] + radius_head + radius2) && (head_y >= ball_y2[i] - radius_head - radius2) && (head_y <= ball_y2[i] + radius_head + radius2))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x2[i], ball_y2[i], radius2);
			ball_x2[i] = rand() % 1500;
			ball_y2[i] = rand() % 1000;
			radius_head += 0.04;
			radius_body = radius_head;
			radius_eyeb += 0.04;
			radius_eyez = radius_eyeb / 2;
			n++;
			score += 2;
		}
		if ((head_x >= ball_x3[i] - radius_head - radius3) && (head_x <= ball_x3[i] + radius_head + radius3) && (head_y >= ball_y3[i] - radius_head - radius3) && (head_y <= ball_y3[i] + radius_head + radius3))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x3[i], ball_y3[i], radius3);
			ball_x3[i] = rand() % 1500;
			ball_y3[i] = rand() % 1000;
			radius_head += 0.06;
			radius_body = radius_head;
			radius_eyeb += 0.06;
			radius_eyez = radius_eyeb / 2;
			n++;
			score += 3;
		}
	}

	//�жϵ�ͼ�ƶ�
	/*if (head_x <= Width / 4)
	{
		head_x += moveSpeed;
		int i;
		for (i = 0; i < n; i++)
			body_x[i] += moveSpeed;
		location_x += moveSpeed;
		int j;
		for (j = 0; j < N; j++)
		{
			ball_x1[j] += moveSpeed;
			ball_x2[j] += moveSpeed;
			ball_x3[j] += moveSpeed;
		}
	}
	//if (head_x >= 3 * Width / 4)
	{
		head_x -= moveSpeed;
		int i;
		for (i = 0; i < n; i++)
			body_x[i] -= moveSpeed;
		location_x -= moveSpeed;
		int j;
		for (j = 0; j < N; j++)
		{
			ball_x1[j] -= moveSpeed;
			ball_x2[j] -= moveSpeed;
			ball_x3[j] -= moveSpeed;
		}
	}
	//if (head_y <= Height / 4)
	{
		head_y += moveSpeed;
		int i;
		for (i = 0; i < n; i++)
			body_y[i] += moveSpeed;
		location_y += moveSpeed;
		int j;
		for (j = 0; j < N; j++)
		{
			ball_y1[j] += moveSpeed;
			ball_y2[j] += moveSpeed;
			ball_y3[j] += moveSpeed;
		}
	}
	//if (head_y >= 3 * Height / 4)
	{
		head_y -= moveSpeed;
		int i;
		for (i = 0; i < n; i++)
			body_y[i] -= moveSpeed;
		location_y -= moveSpeed;
		int j;
		for (j = 0; j < N; j++)
		{
			ball_y1[j] -= moveSpeed;
			ball_y2[j] -= moveSpeed;
			ball_y3[j] -= moveSpeed;
		}
	}
	*/
	if (head_x <= location_x + 10 || head_x >= location_x + 1000 - 10 || head_y <= location_y + 10 || head_y >= location_y + 600 - 10)//2362  1417
		gameStatus = 5;
}

void updateWithInput1()  // ���û������йصĸ���
{
	//��ͷ�ƶ�
	if ((GetAsyncKeyState(0x41) & 0x8000))  // a 
		moveDirection = 1;
	if ((GetAsyncKeyState(0x44) & 0x8000))  // d
		moveDirection = 2;
	if (GetAsyncKeyState(0x57) & 0x8000)  // w
		moveDirection = 3;
	if ((GetAsyncKeyState(0x53) & 0x8000))  // s
		moveDirection = 4;
	if ((GetKeyState(0x41) & 0x8000) && (GetKeyState(0x57) & 0x8000))   // a,w
		moveDirection = 5;
	if ((GetKeyState(0x41) & 0x8000) && (GetKeyState(0x53) & 0x8000))   // a,s
		moveDirection = 6;
	if ((GetKeyState(0x53) & 0x8000) && (GetKeyState(0x44) & 0x8000))	// s,d
		moveDirection = 7;
	if ((GetKeyState(0x57) & 0x8000) && (GetKeyState(0x44) & 0x8000))	// d,w
		moveDirection = 8;

	//ʵ�ּ���
	if ((GetAsyncKeyState(0x20) & 0x8000))  // �ո�
		moveSpeed = 4;
	else
		moveSpeed = 2;
}


void playgame2()   //˫��ģʽ
{
	startup2();  // ˫����Ϸ�����ʼ��	
	while (gameStatus == 2)  //  ��Ϸѭ��ִ��
	{
		clean2();  // ��֮ǰ���Ƶ�����ȡ��
		updateWithoutInput2();  // ���û������޹صĸ���
		updateWithInput2();     // ���û������йصĸ���
		show2();  // ��ʾ�»���
		writeRecordFile2();    //�洢��Ϸ�����ļ��浵
		char input;
		if (_kbhit())    //�ж��Ƿ�������
		{
			input = _getch();   //�����û��Ĳ�ͬ������ѡ�񣬲�������س�
			if (input == 27)
			{
				gameStatus = 4;
				m++;
			}
		}
	}
	playoperation();
	gameover();     // ��Ϸ��������������
}

void startup2()   //˫��ģʽ��ʼ��
{
	mciSendString("open .\\��������.mp3 alias bkmusic", NULL, 0, NULL);   //��������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);   //ѭ������

	initgraph(Width, Height);    ////��ʼ��������С
	win_player = 0;
	//��ȡͼƬ��img������
	loadimage(&img_bk, ".\\̰���ߴ��ͼ3.jpg");
	loadimage(&img_1, _T(".\\p3.jpg"));
	loadimage(&img_2, _T(".\\p1.jpg"));
	loadimage(&img_3, _T(".\\p2.jpg"));
	loadimage(&img_4, _T(".\\p4.jpg"));
	loadimage(&img_5, _T(".\\ͼ1.jpg"));
	loadimage(&img_6, _T(".\\ͼ2.jpg"));
	loadimage(&img_7, _T(".\\ͼ3.jpg"));
	loadimage(&img_8, _T(".\\ͼ4.jpg"));

	if (m == 0)
	{
		temp = 2;

		//��ʼ��ʱ��
		minute = 3;
		second = 180;
		l = 0;
		//��ʼ����ͼλ��
		location_x =0;
		location_y =0;

		//��ʼ���÷�
		score1 = 0;
		score2 = 0;

		//��ʼ��1��ͷ�ƶ���������
		moveDirection1 = 4;

		//��ʼ��2��ͷ�ƶ���������
		moveDirection2 = 3;

		//��ʼ��1��ͷλ��
		head1_x = Width / 4;
		head1_y = Height / 4;
		//��ʼ��2��ͷλ��
		head2_x = 3 * Width / 4;
		head2_y = 3 * Height / 4;
		radius_head = 10;//��ʼ���뾶

		//��ʼ��1���۰�λ��
		eyeb1_x1 = head1_x - radius_head / 2;
		eyeb1_y1 = head1_y + radius_head / 2;
		eyeb1_x2 = head1_x - radius_head / 2;
		eyeb1_y2 = head1_y + radius_head / 2;
		//��ʼ��2���۰�λ��
		eyeb2_x1 = head2_x - radius_head / 2;
		eyeb2_y1 = head2_y + radius_head / 2;
		eyeb2_x2 = head2_x - radius_head / 2;
		eyeb2_y2 = head2_y + radius_head / 2;
		radius1_eyeb = 6;
		radius2_eyeb = 6;

		//��ʼ��1������λ��
		eyez1_x1 = eyeb1_x1;
		eyez1_y1 = eyeb1_y1;
		eyez1_x2 = eyeb1_x2;
		eyez1_y2 = eyeb1_y2;
		//��ʼ��2������λ��
		eyez2_x1 = eyeb2_x1;
		eyez2_y1 = eyeb2_y1;
		eyez2_x2 = eyeb2_x2;
		eyez2_y2 = eyeb2_y2;
		radius1_eyez = 3;
		radius2_eyez = 3;

		//��ʼ��1�������λ��
		radius1_body = radius_head;
		length1 = 30;			//��ʼ����
		body1_x[0] = head1_x;
		body1_y[0] = head1_y - 2 * radius1_body;
		for (i = 1; i <= length1; i++)
		{
			body1_x[i] = body1_x[i - 1];
			body1_x[i] = body1_y[i - 1] - 2 * radius1_body;
		}

		//��ʼ��2�������λ��
		radius2_body = radius_head;
		length2 = 30;			//��ʼ����
		body2_x[0] = head2_x;
		body2_y[0] = head2_y - 2 * radius2_body;
		for (i = 1; i <= length2; i++)
		{
			body2_x[i] = body2_x[i - 1];
			body2_x[i] = body2_y[i - 1] - 2 * radius2_body;
		}

		//��ʼ��С����npc��λ��

		for (i = 0; i < K; i++)
		{
			ball_x1[i] = rand() % (Width - 50);
			ball_y1[i] = rand() % (Height - 50);
			ball_x2[i] = rand() % (Width - 50);
			ball_y2[i] = rand() % (Height - 50);
			ball_x3[i] = rand() % (Width - 50);
			ball_y3[i] = rand() % (Height - 50);
		}
		radius1 = 3;
		radius2 = 5;
		radius3 = 7;
	}

	else
		readRecordFile2();

	BeginBatchDraw();
}

void clean2()  // ��������
{
	setcolor(BLACK);
	setfillcolor(BLACK);

	fillcircle(head1_x, head1_y, radius_head);   //����1��ͷ
	fillcircle(head2_x, head2_y, radius_head);   //����2��ͷ

	//����1���۾�
	fillcircle(eyeb1_x1, eyeb1_y1, radius1_eyeb);   //�����۰�1
	fillcircle(eyeb1_x2, eyeb1_y2, radius1_eyeb);   //�����۰�2
	fillcircle(eyez1_x1, eyez1_y1, radius1_eyez);   //��������1
	fillcircle(eyez1_x2, eyez1_y2, radius1_eyez);   //��������2
	//����2���۾�
	fillcircle(eyeb2_x1, eyeb2_y1, radius2_eyeb);   //�����۰�1
	fillcircle(eyeb2_x2, eyeb2_y2, radius2_eyeb);   //�����۰�2
	fillcircle(eyez2_x1, eyez2_y1, radius2_eyez);   //��������1
	fillcircle(eyez2_x2, eyez2_y2, radius2_eyez);   //��������2

	//�������
	for (i = 0; i <= length1; i++)
	{
		fillcircle(body1_x[i], body1_y[i], radius1_body);
	}
	for (i = 0; i <= length2; i++)
	{
		fillcircle(body2_x[i], body2_y[i], radius2_body);
	}
}

void show2()  // ��ʾ����
{
	TCHAR s[80];
	putimage(location_x, location_y, &img_bk);  //������(0,0)λ����ʾ����
	settextcolor(RGB(200, 150, 0));
	setbkcolor(WHITE);
	settextstyle(30, 0, _T("����"));
	putimage(Width - 250, -10, &img_8, NOTSRCERASE);
	putimage(Width - 250, -10, &img_5, SRCINVERT);
	putimage(Width - 250, 90, &img_7, NOTSRCERASE);
	putimage(Width - 250, 90, &img_6, SRCINVERT);

	TCHAR s1[5];
	_stprintf_s(s1, _T("%d"), score1);
	outtextxy(Width - 50, 60, s1);
	TCHAR s2[5];
	_stprintf_s(s2, _T("%d"), score2);
	outtextxy(Width - 50, 160, s2);

	//���Ʊ߿�
	setcolor(RGB(200, 150, 0));
	rectangle(Width - 222, 7, Width - 5, 192);

	//����1������
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	for (i = 0; i <= length1; i++)
	{
		fillcircle(body1_x[i], body1_y[i], radius1_body);
	}
	//����2������
	setcolor(RED);
	setfillcolor(RED);
	for (i = 0; i <= length2; i++)
	{
		fillcircle(body2_x[i], body2_y[i], radius2_body);
	}

	//����1��ͷ
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(head1_x, head1_y, radius_head);
	//����2��ͷ
	setcolor(RED);
	setfillcolor(RED);
	fillcircle(head2_x, head2_y, radius_head);

	//�����۰�
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(eyeb1_x1, eyeb1_y1, radius1_eyeb);
	fillcircle(eyeb1_x2, eyeb1_y2, radius1_eyeb);
	fillcircle(eyeb2_x1, eyeb2_y1, radius2_eyeb);
	fillcircle(eyeb2_x2, eyeb2_y2, radius2_eyeb);

	//��������
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(eyez1_x1, eyez1_y1, radius1_eyez);
	fillcircle(eyez1_x2, eyez1_y2, radius1_eyez);
	fillcircle(eyez2_x1, eyez2_y1, radius2_eyez);
	fillcircle(eyez2_x2, eyez2_y2, radius2_eyez);

	//����С����npc
	int i;
	for (i = 0; i < K; i++)
	{
		setcolor(RGB(10, 20, 50));
		setfillcolor(RGB(10, 20, 50));
		fillcircle(ball_x1[i], ball_y1[i], radius1);	// ��������Բ	
		setcolor(RGB(34, 139, 34));
		setfillcolor(RGB(34, 139, 34));
		fillcircle(ball_x2[i], ball_y2[i], radius2);	// ������Բ
		setcolor(RGB(255, 192, 203));
		setfillcolor(RGB(255, 192, 203));
		fillcircle(ball_x3[i], ball_y3[i], radius3);	// ���Ʒ�Բ
	}

	time();												//����ʱ

	FlushBatchDraw();
	// ��ʱ
	Sleep(3);
}

void over2()     //��������
{
	putimage(0, 0, &img_over);    //��ʾ��������ͼƬ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("����"));
	outtextxy(Width * 0.42, Height * 0.3, "��Ϸ����");

	settextcolor(BLACK);
	settextstyle(40, 0, _T("����"));
	TCHAR s1[5];
	TCHAR s2[5];
	outtextxy(Width * 0.35, Height * 0.45, "���1�÷֣�");
	_stprintf_s(s1, _T("%d"), score1);
	outtextxy(Width * 0.6, Height * 0.45, s1);
	outtextxy(Width * 0.35, Height * 0.55, "���2�÷֣�");
	_stprintf_s(s2, _T("%d"), score2);
	outtextxy(Width * 0.6, Height * 0.55, s2);

	if (win_player == 0)
	{
		if (score1 > score2)
			win_player == 1;
		if (score1 < score2)
			win_player == 2;
		if (score1 == score2)
			win_player == 0;
	}
	if (win_player == 1)
	{
		settextcolor(RED);
		settextstyle(50, 0, _T("����"));
		outtextxy(Width * 0.35, Height * 0.18, "һ����һ�ʤ��");
	}
	if (win_player == 2)
	{
		settextcolor(RED);
		settextstyle(50, 0, _T("����"));
		outtextxy(Width * 0.35, Height * 0.18, "������һ�ʤ��");
	}
	if (win_player == 0)
	{
		settextcolor(RED);
		settextstyle(50, 0, _T("����"));
		outtextxy(Width * 0.47, Height * 0.18, "ƽ�֣�");
	}

	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));
	outtextxy(Width * 0.85, Height * 0.85, "�˳�");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.84, Width * 0.93, Height * 0.90);

	FlushBatchDraw();
	Sleep(5);

	char input;
	if (_kbhit())    //�ж��Ƿ�������
	{
		input = _getch();   //�����û��Ĳ�ͬ������ѡ�񣬲�������س�
		if (input == 27)    //Esc�˳���������
			gameStatus = 0;
	}

	MOUSEMSG m;		 //���������Ϣ
	while (MouseHit())    //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.84 && m.y <= Height * 0.90)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //�������
				gameStatus = 0;
		}
	}

	playoperation();
}

void control1_body()
{
	//�����ƶ�
	body1_x[0] = head1_x;
	body1_y[0] = head1_y;
	for (i = length1; i >= 1; i--)
	{
		body1_x[i] = body1_x[i - 1];
		body1_y[i] = body1_y[i - 1];
	}
}

void control2_body()
{
	//�����ƶ�
	body2_x[0] = head2_x;
	body2_y[0] = head2_y;
	for (i = length2; i >= 1; i--)
	{
		body2_x[i] = body2_x[i - 1];
		body2_y[i] = body2_y[i - 1];
	}
}

void control1_eyez()
{
	//�����ƶ�
	eyez1_x1 = eyeb1_x1;
	eyez1_y1 = eyeb1_y1;
	eyez1_x2 = eyeb1_x2;
	eyez1_y2 = eyeb1_y2;
}

void control2_eyez()
{
	eyez2_x1 = eyeb2_x1;
	eyez2_y1 = eyeb2_y1;
	eyez2_x2 = eyeb2_x2;
	eyez2_y2 = eyeb2_y2;
}

void updateWithoutInput2()  // ���û������޹صĸ���
{
	//����ʱ��
	if (l >= 49)
	{
		second = second - 1;
		minute = second / 60;
		l = 0;
	}
	else
		l++;

	//1��ͷ�ƶ�
	if (moveDirection1 == 1)   //a
	{
		//�����ƶ�
		control1_body();

		head1_x -= moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x - radius_head;
		eyeb1_y1 = head1_y - radius_head;
		eyeb1_x2 = head1_x - radius_head;
		eyeb1_y2 = head1_y + radius_head;

		//�����ƶ�
		control1_eyez();
	}

	if (moveDirection1 == 2)   //d
	{
		//�����ƶ�
		control1_body();

		head1_x += moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x + radius_head;
		eyeb1_y1 = head1_y + radius_head;
		eyeb1_x2 = head1_x + radius_head;
		eyeb1_y2 = head1_y - radius_head;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 3)   //w
	{
		//�����ƶ�
		control1_body();

		head1_y -= moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x + radius_head;
		eyeb1_y1 = head1_y - radius_head;
		eyeb1_x2 = head1_x - radius_head;
		eyeb1_y2 = head1_y - radius_head;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 4)   //s
	{
		//�����ƶ�
		control1_body();

		head1_y += moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x - radius_head;
		eyeb1_y1 = head1_y + radius_head;
		eyeb1_x2 = head1_x + radius_head;
		eyeb1_y2 = head1_y + radius_head;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 5)	//a,w;
	{

		//�����ƶ�
		control1_body();

		head1_x -= moveSpeed1;
		head1_y -= moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y - radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x - radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 6)	//a,s;
	{

		//�����ƶ�
		control1_body();

		head1_x -= moveSpeed1;
		head1_y += moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y + radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x - radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 7)	//s,d;
	{

		//�����ƶ�
		control1_body();

		head1_x += moveSpeed1;
		head1_y += moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y + radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x + radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//�����ƶ�
		control1_eyez();
	}
	if (moveDirection1 == 8)	//w,d;
	{

		//�����ƶ�
		control1_body();

		head1_x += moveSpeed1;
		head1_y -= moveSpeed1;

		//�۰��ƶ�
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y - radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x + radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//�����ƶ�
		control1_eyez();
	}
	//2��ͷ�ƶ�
	if (moveDirection2 == 1)   //left
	{
		//�����ƶ�
		control2_body();

		head2_x -= moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x - radius_head;
		eyeb2_y1 = head2_y - radius_head;
		eyeb2_x2 = head2_x - radius_head;
		eyeb2_y2 = head2_y + radius_head;

		//�����ƶ�
		control2_eyez();

	}
	if (moveDirection2 == 2)   //right
	{
		//�����ƶ�
		control2_body();

		head2_x += moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x + radius_head;
		eyeb2_y1 = head2_y + radius_head;
		eyeb2_x2 = head2_x + radius_head;
		eyeb2_y2 = head2_y - radius_head;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 3)   //up
	{
		//�����ƶ�
		control2_body();

		head2_y -= moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x + radius_head;
		eyeb2_y1 = head2_y - radius_head;
		eyeb2_x2 = head2_x - radius_head;
		eyeb2_y2 = head2_y - radius_head;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 4)   //down
	{
		//�����ƶ�
		control2_body();

		head2_y += moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x - radius_head;
		eyeb2_y1 = head2_y + radius_head;
		eyeb2_x2 = head2_x + radius_head;
		eyeb2_y2 = head2_y + radius_head;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 5)	//left&&up
	{

		//�����ƶ�
		control2_body();

		head2_x -= moveSpeed2;
		head2_y -= moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y - radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x - radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 6)	//left&&down
	{

		//�����ƶ�
		control2_body();

		head2_x -= moveSpeed2;
		head2_y += moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y + radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x - radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 7)	//down&&right
	{

		//�����ƶ�
		control2_body();

		head2_x += moveSpeed2;
		head2_y += moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y + radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x + radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//�����ƶ�
		control2_eyez();
	}
	if (moveDirection2 == 8)	//up&&right
	{

		//�����ƶ�
		control2_body();

		head2_x += moveSpeed2;
		head2_y -= moveSpeed2;

		//�۰��ƶ�
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y - radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x + radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//�����ƶ�
		control2_eyez();
	}
	for (i = 0; i < K; i++)
	{
		//�ж�1���Ƿ�Ե�����
		if ((head1_x >= ball_x1[i] - radius_head - radius1) && (head1_x <= ball_x1[i] + radius_head + radius1) && (head1_y >= ball_y1[i] - radius_head - radius1) && (head1_y <= ball_y1[i] + radius_head + radius1))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x1[i], ball_y1[i], radius1);
			score1 = score1 + 1;
			ball_x1[i] = rand() % (Width - 50);
			ball_y1[i] = rand() % (Height - 50);
			radius_head += 0.02;
			radius1_body += 0.02;
			radius1_eyeb += 0.02;
			radius1_eyez = radius1_eyeb / 2;
			length1 = length1 + 1;
		}
		if ((head1_x >= ball_x2[i] - radius_head - radius2) && (head1_x <= ball_x2[i] + radius_head + radius2) && (head1_y >= ball_y2[i] - radius_head - radius2) && (head1_y <= ball_y2[i] + radius_head + radius2))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x2[i], ball_y2[i], radius2);
			score1 = score1 + 2;
			ball_x2[i] = rand() % (Width - 50);
			ball_y2[i] = rand() % (Height - 50);
			radius_head += 0.04;
			radius1_body += 0.04;
			radius1_eyeb += 0.04;
			radius1_eyez = radius1_eyeb / 2;
			length1 = length1 + 2;
		}
		if ((head1_x >= ball_x3[i] - radius_head - radius3) && (head1_x <= ball_x3[i] + radius_head + radius3) && (head1_y >= ball_y3[i] - radius_head - radius3) && (head1_y <= ball_y3[i] + radius_head + radius3))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x3[i], ball_y3[i], radius3);
			score1 = score1 + 3;
			ball_x3[i] = rand() % (Width - 50);
			ball_y3[i] = rand() % (Height - 50);
			radius_head += 0.06;
			radius1_body += 0.06;
			radius1_eyeb += 0.06;
			radius1_eyez = radius1_eyeb / 2;
			length1 = length1 + 3.5;
		}
		//�ж�2���Ƿ�Ե�����
		if ((head2_x >= ball_x1[i] - radius_head - radius1) && (head2_x <= ball_x1[i] + radius_head + radius1) && (head2_y >= ball_y1[i] - radius_head - radius1) && (head2_y <= ball_y1[i] + radius_head + radius1))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x1[i], ball_y1[i], radius1);
			score2 = score2 + 1;
			ball_x1[i] = rand() % (Width - 50);
			ball_y1[i] = rand() % (Height - 50);
			radius_head += 0.02;
			radius2_body += 0.02;
			radius2_eyeb += 0.02;
			radius2_eyez = radius2_eyeb / 2;
			length2 = length2 + 1;
		}
		if ((head2_x >= ball_x2[i] - radius_head - radius2) && (head2_x <= ball_x2[i] + radius_head + radius2) && (head2_y >= ball_y2[i] - radius_head - radius2) && (head2_y <= ball_y2[i] + radius_head + radius2))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x2[i], ball_y2[i], radius2);
			score2 = score2 + 2;
			ball_x2[i] = rand() % (Width - 50);
			ball_y2[i] = rand() % (Height - 50);
			radius_head += 0.04;
			radius2_body += 0.04;
			radius2_eyeb += 0.04;
			radius2_eyez = radius2_eyeb / 2;
			length2 = length2 + 2;
		}
		if ((head2_x >= ball_x3[i] - radius_head - radius3) && (head2_x <= ball_x3[i] + radius_head + radius3) && (head2_y >= ball_y3[i] - radius_head - radius3) && (head2_y <= ball_y3[i] + radius_head + radius3))
		{
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(ball_x3[i], ball_y3[i], radius3);
			score2 = score2 + 3;
			ball_x3[i] = rand() % (Width - 50);
			ball_y3[i] = rand() % (Height - 50);
			radius_head += 0.06;
			radius2_body += 0.06;
			radius2_eyeb += 0.06;
			radius2_eyez = radius2_eyeb / 2;
			length2 = length2 + 3.5;
		}
	}
	//�ж�С���Ƿ���ײ
	//1��ײ��2��
	for (i = 0; i < length2; i++)
	{
		int k;
		if ((head1_x == body2_x[i] && abs(head1_y - body2_y[i]) < 2 * radius2_body) || (head1_y == body2_y[i] && abs(head1_x - body2_x[i]) < 2 * radius2_body))
		{
			win_player = 2;
			gameStatus = 6;
		}
	}
	//2��ײ��1��
	for (i = 0; i < length1; i++)
	{
		int k;
		if ((head2_x == body1_x[i] && abs(head2_y - body1_y[i]) < 2 * radius1_body) || (head2_y == body1_y[i] && abs(head2_x - body1_x[i]) < 2 * radius1_body))
		{
			win_player = 1;
			gameStatus = 6;
		}
	}
	//1�߳���
	if (head1_x <= location_x + 10 || head1_x >= location_x + 1000 - 10 || head1_y <= location_y + 10 || head1_y >= location_y + 600 - 10)//2362  1417
	{
		gameStatus = 6;
		win_player = 2;
	}
	//2�߳���
	if (head2_x <= location_x + 10 || head2_x >= location_x + 1000 - 10 || head2_y <= location_y + 10 || head2_y >= location_y + 600 - 10)
	{
		gameStatus = 6;
		win_player = 1;
	}

		
}

void updateWithInput2()  // ���û������йصĸ���
{
	//1��ͷ�ƶ�
	if ((GetAsyncKeyState(0x41) & 0x8000))  // a 
		moveDirection1 = 1;
	if ((GetAsyncKeyState(0x44) & 0x8000))  // d
		moveDirection1 = 2;
	if ((GetAsyncKeyState(0x57) & 0x8000))  // w
		moveDirection1 = 3;
	if ((GetAsyncKeyState(0x53) & 0x8000))  // s
		moveDirection1 = 4;
	if ((GetKeyState(0x41) & 0x8000) && (GetKeyState(0x57) & 0x8000)) // a,w;
		moveDirection1 = 5;
	if ((GetKeyState(0x41) & 0x8000) && (GetKeyState(0x53) & 0x8000)) // a ,s
		moveDirection1 = 6;
	if ((GetKeyState(0x53) & 0x8000) && (GetKeyState(0x44) & 0x8000))	//s,d
		moveDirection1 = 7;
	if ((GetKeyState(0x57) & 0x8000) && (GetKeyState(0x44) & 0x8000))	//d,w
		moveDirection1 = 8;
	//2��ͷ�ƶ�
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000))  // left
		moveDirection2 = 1;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))  // right
		moveDirection2 = 2;
	if (GetAsyncKeyState(VK_UP) & 0x8000)  // up
		moveDirection2 = 3;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))  // down
		moveDirection2 = 4;
	if ((GetKeyState(VK_LEFT) & 0x8000) && (GetKeyState(VK_UP) & 0x8000))  // left&&up
		moveDirection2 = 5;
	if ((GetKeyState(VK_LEFT) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000))  // left&&down
		moveDirection2 = 6;
	if ((GetKeyState(VK_RIGHT) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000))  // right&&down
		moveDirection2 = 7;
	if ((GetKeyState(VK_RIGHT) & 0x8000) && (GetKeyState(VK_UP) & 0x8000))  // right&&up
		moveDirection2 = 8;
	//1��ʵ�ּ���
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))  // ���¿ո�
		moveSpeed1 = 4;
	else
		moveSpeed1 = 2;
	//2��ʵ�ּ���
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000))  // ���»س�
		moveSpeed2 = 4;
	else
		moveSpeed2 = 2;
}


int main()
{
	startup();  // ���ݲ˵�����
	while (gameStatus != 1 && gameStatus != 2)
		playoperation();
	if (gameStatus == 1)    //���е���ģʽ
		playgame1();
	else if (gameStatus == 2)   //����˫��ģʽ
		playgame2();
	return 0;
}
