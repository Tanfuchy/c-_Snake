#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include<stdio.h>
#define Height 600  // 游戏画面尺寸
#define Width 1000
#define N 50
#define K 20
#define S 200000000

//引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

// 全局变量
IMAGE img_menu;    //定义菜单背景
int gameStatus; // 游戏状态，0为菜单，1为单人游戏，2为双人模式，3为帮助,4为暂停,5为单人结束，6为双人结束

IMAGE img_help;   //定义帮助背景
IMAGE img_over;   //定义结束背景
IMAGE img_bk;    //定义IMAGE对象

int minute;
int second;			//时间
int l;

int m;     //存档读档需要

//单蛇
IMAGE img_9;
IMAGE img_10;

int score;   //游戏得分

int temp;     //切换不同游戏

int location_x, location_y;    //地图坐标
int head_x, head_y;   //蛇头坐标
float radius_head;   //蛇头半径
int moveDirection;    //蛇头移动方向
int moveSpeed;    //蛇头移动速度

int body_x[S], body_y[S];  //身体
float radius_body;    //身体半径
int k;    //与身体有关的遍历变量
int n;    //身体长度

int eyeb_x1, eyeb_y1;   //眼白1
int eyeb_x2, eyeb_y2;   //眼白2
float radius_eyeb;   //眼白半径

int eyez_x1, eyez_y1;   //眼珠1
int eyez_x2, eyez_y2;   //眼珠2
float radius_eyez;   //眼珠半径

int ball_x1[N], ball_y1[N]; // 小豆豆npc1的坐标
int ball_x2[N], ball_y2[N]; // 小豆豆npc2的坐标
int ball_x3[N], ball_y3[N]; // 小豆豆npc3的坐标
float radius1, radius2, radius3;    //npc的半径
//双蛇
IMAGE img_1;
IMAGE img_2;
IMAGE img_3;
IMAGE img_4;
IMAGE img_5;
IMAGE img_6;
IMAGE img_7;
IMAGE img_8;

const double pi = 4.0 * atan(1.0);

int score1;        //玩家1的分数
int score2;			//玩家2的分数
int win_player;

int head1_x, head1_y;   //1蛇头坐标
int head2_x, head2_y;   //2蛇头坐标
int moveDirection1;    //1蛇头移动方向
int moveDirection2;	//2蛇头移动方向
int moveSpeed1;    //1蛇头移动速度
int moveSpeed2;    //2蛇头移动速度


int eyeb1_x1, eyeb1_y1;   //1蛇眼白1
int eyeb2_x1, eyeb2_y1;   //2蛇眼白1
int eyeb1_x2, eyeb1_y2;   //1蛇眼白2
int eyeb2_x2, eyeb2_y2;   //2蛇眼白2
float radius1_eyeb;   //1蛇眼白半径
float radius2_eyeb;   //2蛇眼白半径

int eyez1_x1, eyez1_y1;   //1蛇眼珠1
int eyez1_x2, eyez1_y2;   //1蛇眼珠2
int eyez2_x1, eyez2_y1;   //2蛇眼珠1
int eyez2_x2, eyez2_y2;   //2蛇眼珠2

float radius1_eyez;   //1蛇眼珠半径
float radius2_eyez;   //2蛇眼珠半径

int body1_x[50000], body1_y[50000];	//1蛇身体
int body2_x[50000], body2_y[50000];	//2蛇身体
float radius1_body;		//1蛇身体半径
float radius2_body;		//2蛇身体半径
int i;				 //与身体有关的遍历变量
float length1;				//1蛇身体的长度
float length2;				//2蛇身体的长度

//函数封装
void startup();   //数据初始化
void menu();    //菜单
void help();    //帮助
void playoperation();   //执行操作
void gameover();
void time();    //倒计时
void stop();    //游戏暂停

void playgame1();   //单人游戏
void startup1();  // 单人模式初始化
void clean1();   // 消除画面
void show1();    // 显示画面
void over1();    // 结束画面
void updateWithoutInput1();  // 与用户输入无关的更新
void updateWithInput1();  // 与用户输入有关的更新

void playgame2();   //双人游戏
void startup2();  // 双人模式初始化
void clean2();  // 消除画面
void show2();  // 显示画面
void over2();    // 结束画面
void control1_body();   //控制小蛇1的身体移动
void control2_body();   //控制小蛇2的身体移动
void control1_eyez();   //控制小蛇1的眼睛移动
void control2_eyez();   //控制小蛇2的眼睛移动
void updateWithoutInput2();  // 与用户输入无关的更新
void updateWithInput2();  // 与用户输入有关的更新

//存档读档
void readRecordFile1();  //读取游戏数据文件存档
void writeRecordFile1();  //存储游戏数据文件存档

void readRecordFile2();  //读取游戏数据文件存档
void writeRecordFile2();  //存储游戏数据文件存档

//
void startup()   //数据初始化
{
	initgraph(Width, Height);    //初始化画布大小，创建一个尺寸为1000x600的绘图环境

//读取图片到img对象中
	loadimage(&img_menu, _T(".\\贪吃蛇菜单背景.jpg"));  
	/*从资源文件获取图像
	void loadimage(
		IMAGE * pDstImg, // 保存图像的 IMAGE 对象指针
		LPCTSTR pResType, // 资源类型
		LPCTSTR pResName, // 资源名称
		int nWidth = 0, // 图片的拉伸宽度
		int nHeight = 0, // 图片的拉伸高度
		bool bResize = false // 是否调整 IMAGE 的大小以适应图片
	);
	*/
	loadimage(&img_help, _T(".\\帮助背景图.jpg"));
	loadimage(&img_over, _T(".\\结束背景图.jpg"));

	BeginBatchDraw();/* 当我们需要绘制连续的动画时，一直刷新屏幕会产生闪屏，我们可以用他们来解决这个问题。    
	运行BeginBatchDraw后，所有的绘图都不再显示在屏幕上，而是在内存中进行,直到碰到EndBatchDraw，之前所有在内存中绘图的成品将一并展示在屏幕中*/

	while (gameStatus == 0)   //游戏状态，0为菜单，1为开始游戏，2为双人模式，3为帮助,4为暂停,5为单人结束，6为双人结束
		menu();		//进入  菜单 函数
}

void menu()    //菜单
{
	m = 0;

	putimage(0, 0, &img_menu);    
	/*显示菜单背景图片，此函数调用方式为void putimage(int left,int top,void *buf,int ops);
	参数(left,top)为输出屏幕图像的左上角，即输出图像的起始位置。buf指向要输出的内存中图像。参数ops控制图像以何种方式输出到屏幕上。*/
	setbkmode(TRANSPARENT);
	/* 使用SetBkMode函数来设置DrawText函数的输出方式，显示设备共有两种输出方式：OPAQUE和TRANSPARENT。
	OPAQUE的方式是用当前背景的画刷的颜色输出显示文字的背景，而TRANSPARENT是使用透明的输出，也就是文字的背景是不改变的。*/
	//settextcolor(RGB(205, 92, 92));
	//settextstyle(100, 0, _T("禹卫书法行书简体"));
	/* 函数settextstyle() 设置图形文本当前字体、文本显示方向（水平显示或垂直显示）以及字符大小。
	用法：　此函数调用方式为void settextstyle(int font,int direction,int charsize);
	说明：　函数括号中，font为文本字体参数，direction为文本显示方向，charsize为字符大小参数。

	_T("")是一个宏,他的作用是让你的程序支持Unicode编码。我理解中，T是Transformation（转换）的意思。
	因为Windows使用两种字符集ANSI和UNICODE，前者就是通常使用的单字节方式，但这种方式处理象中文这样的双字节字符不方便，
	容易出现半个汉字的情况。而后者是双字节方式，方便处理双字节字符。*/
	//outtextxy(Width * 0.2, Height * 0.15, "贪吃蛇大作战"); 
	//上面的三句 settextcolor settextstyle outtextxy是标题的显示

	settextcolor(RGB(85, 107, 47));
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.4, Height * 0.5, "单人模式");
	outtextxy(Width * 0.4, Height * 0.6, "双人模式");
	outtextxy(Width * 0.45, Height * 0.7, "帮助");

	settextcolor(RGB(102, 139, 139));
	settextstyle(20, 0, _T("黑体"));
	outtextxy(Width * 0.8, Height * 0.85, "鼠标点击进行选择");

	
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.495, Width * 0.61, Height * 0.585);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.595, Width * 0.61, Height * 0.685);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.39, Height * 0.695, Width * 0.61, Height * 0.785);

	FlushBatchDraw();
	Sleep(2);

	MOUSEMSG m;		 //定义鼠标消息
	while (MouseHit())    //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.495 && m.y <= Height * 0.585)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键，单人模式
				gameStatus = 1;
		}
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.595 && m.y <= Height * 0.685)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键，双人模式
				gameStatus = 2;
		}
		if (m.x >= Width * 0.39 && m.x <= Width * 0.61 && m.y >= Height * 0.695 && m.y <= Height * 0.785)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键，帮助
				gameStatus = 3;
		}
	}
}

void help()   //帮助初始化
{
	putimage(0, 0, &img_help);    //显示帮助背景图片
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(Width * 0.1, Height * 0.2, "本游戏共2种模式");
	outtextxy(Width * 0.1, Height * 0.3, "·模式1为单人限时模式");
	outtextxy(Width * 0.1, Height * 0.4, "  该模式指在限定时间内玩家控制贪吃蛇多吃食物，获取得分");
	outtextxy(Width * 0.1, Height * 0.5, "·模式2为双人对战模式");
	outtextxy(Width * 0.1, Height * 0.6, "  该模式指对战玩家控制自己的贪吃蛇多吃食物，杀死对方或");
	outtextxy(Width * 0.1, Height * 0.7, "  时间截止时分数较多的玩家胜利");


	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(Width * 0.85, Height * 0.1, "退出");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.09, Width * 0.93, Height * 0.15);

	FlushBatchDraw();
	/* 在使用Easy库的时候，由于每次都花大量时间绘制背景，导致闪烁厉害。这里用批量绘图方法将所有绘图一次性显示出来，以解决闪烁的问题。
	BeginBatchDraw这个函数用于开始批量绘图。执行后，任何绘图操作都将暂时不输出到屏幕上，直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。*/
	Sleep(5);

	char input;
	if (_kbhit())    //判断是否有输入
	{
		input = _getch();   //根据用户的不同输入来选择，不必输入回车
		if (input == 27)    //Esc退出帮助界面
			gameStatus = 0;
	}

	MOUSEMSG m;		 //定义鼠标消息
	while (MouseHit())    //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.09 && m.y <= Height * 0.15)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键
				gameStatus = 0;
		}
	}

	playoperation();
}

void playoperation()   //执行操作
{
	while (gameStatus == 0)   //进入菜单界面
		menu();
	while (gameStatus == 1)   //进入单人模式界面
		playgame1();
	while (gameStatus == 2)   //进入双人模式界面
		playgame2();
	while (gameStatus == 3)   //进入帮助界面
		help();
	while (gameStatus == 4)   //进入暂停界面
		stop();
	while (gameStatus == 5)   //进入单人结束界面
		over1();
	while (gameStatus == 6)   //进入双人结束界面
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
	settextstyle(28, 0, _T("宋体"));
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
	putimage(0, 0, &img_help);    //显示帮助背景图片
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.42, Height * 0.25, "游戏暂停");
	outtextxy(Width * 0.3, Height * 0.5, "继续游戏");
	outtextxy(Width * 0.55, Height * 0.5, "退出游戏");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.28, Height * 0.48, Width * 0.52, Height * 0.59);
	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.53, Height * 0.48, Width * 0.77, Height * 0.59);

	FlushBatchDraw();
	Sleep(5);

	MOUSEMSG m;		 //定义鼠标消息
	while (MouseHit())    //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.28 && m.x <= Width * 0.52 && m.y >= Height * 0.48 && m.y <= Height * 0.59)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键
			{
				if (temp == 1)
					gameStatus = 1;
				else if (temp == 2)
					gameStatus = 2;
			}
		}
		if (m.x >= Width * 0.53 && m.x <= Width * 0.77 && m.y >= Height * 0.48 && m.y <= Height * 0.59)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键
				gameStatus = 0;
		}
	}
	playoperation();
}

void readRecordFile1()  //读取游戏数据文件存档
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf_s(fp, "%d %d %d %d %d %f %d %d", &score, &location_x, &location_y, &head_x, &head_y, &radius_head, &moveDirection, &moveSpeed);
	fclose(fp);
}

void writeRecordFile1()  //存储游戏数据文件存档
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf_s(fp, "%d %d %d %d %d %f %d %d", score, location_x, location_y, head_x, head_y, radius_head, moveDirection, moveSpeed);
	fclose(fp);
}

void readRecordFile2()  //读取游戏数据文件存档
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf_s(fp, "%d %d %d %d %d %d %f %d %d %d %d", &score1, &head1_x, &head1_y, &score2, &head2_x, &head2_y, &radius_head, &moveDirection1, &moveDirection2, &moveSpeed1, &moveSpeed2);
	fclose(fp);
}

void writeRecordFile2()  //存储游戏数据文件存档
{
	FILE* fp;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf_s(fp, "%d %d %d %d %d %d %f %d %d %d %d", score1, head1_x, head1_y, score2, head2_x, head2_y, radius_head, moveDirection1, moveDirection2, moveSpeed1, moveSpeed2);
	fclose(fp);
}


void playgame1()    //单人游戏
{
	startup1();  // 单人游戏界面初始化
	while (gameStatus == 1)  //  游戏循环执行
	{
		clean1();  // 把之前绘制的内容取消
		updateWithoutInput1();  // 与用户输入无关的更新
		updateWithInput1();     // 与用户输入有关的更新
		show1();  // 显示新画面
		writeRecordFile1();  //存储游戏数据文件存档
		char input;
		if (_kbhit())    //判断是否有输入
		{
			input = _getch();   //根据用户的不同输入来选择，不必输入回车
			if (input == 27)
			{
				gameStatus = 4;
				m++;
			}
		}
	}
	playoperation();
	gameover();     // 游戏结束、后续处理
}

void startup1()  // 单人模式初始化
{
	mciSendString("open .\\校歌.mp3 alias bkmusic", NULL, 0, NULL);   //背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);   //循环播放

	initgraph(Width, Height);    ////初始化画布大小

	//读取图片到img对象中
	loadimage(&img_bk, _T(".\\贪吃蛇背景图.jpg"));
	loadimage(&img_9, _T(".\\p6.jpg"));
	loadimage(&img_10, _T(".\\图6.jpg"));

	if (m == 0)
	{
		//初始化地图位置
		location_x = 0;
		location_y = 0;

		temp = 1;

		//初始化时间
		minute = 3;
		second = 180;
		l = 0;

		//初始化得分
		score = 0;

		//初始化蛇头移动方向向下
		moveDirection = 4;

		//初始化蛇头位置
		head_x = Width / 3;
		head_y = Height / 3;
		radius_head = 10;

		//初始化身体位置
		radius_body = radius_head;
		n = 20;
		body_x[0] = head_x;
		body_y[0] = head_y - 2 * radius_body;
		for (k = 1; k < n; k++)
		{
			body_x[k] = body_x[k - 1];
			body_y[k] = body_y[k - 1] - 2 * radius_body;
		}

		//初始化眼白位置
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;
		radius_eyeb = 5;

		//初始化眼珠位置
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
		radius_eyez = 2;

		//初始化小豆豆npc的位置
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
		readRecordFile1();  //读取游戏数据文件存档

	BeginBatchDraw();
}

void clean1()  // 消除画面
{
	setcolor(BLACK);
	setfillcolor(BLACK);

	fillcircle(head_x, head_y, radius_head);   //消除蛇头

	for (k = 0; k < n; k++)
		fillcircle(body_x[k], body_y[k], radius_body);   //消除蛇身

	//消除眼睛
	fillcircle(eyeb_x1, eyeb_y1, radius_eyeb);   //消除眼白1
	fillcircle(eyeb_x2, eyeb_y2, radius_eyeb);   //消除眼白2
	fillcircle(eyez_x1, eyez_y1, radius_eyez);   //消除眼珠1
	fillcircle(eyez_x2, eyez_y2, radius_eyez);   //消除眼珠2
}

void show1()  // 显示画面
{
	putimage(location_x, location_y, &img_bk);  //在坐标(location_x,location_y)位置显示背景

	//绘制得分
	settextcolor(RGB(200, 150, 0));
	setbkcolor(WHITE);
	settextstyle(30, 0, _T("宋体"));
	putimage(Width - 300, -20, &img_9, NOTSRCERASE);
	putimage(Width - 300, -20, &img_10, SRCINVERT);
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), score);
	outtextxy(Width - 70, 75, s);

	//绘制边框
	setcolor(RGB(200, 150, 0));
	rectangle(Width - 257, 3, Width - 2, 110);

	//绘制黄色蛇头
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(head_x, head_y, radius_head);

	//绘制黄色蛇身
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	for (k = 0; k < n; k++)
		fillcircle(body_x[k], body_y[k], radius_body);

	//绘制眼白
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(eyeb_x1, eyeb_y1, radius_eyeb);
	fillcircle(eyeb_x2, eyeb_y2, radius_eyeb);

	//绘制眼珠
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(eyez_x1, eyez_y1, radius_eyez);
	fillcircle(eyez_x2, eyez_y2, radius_eyez);

	//绘制小豆豆npc
	int i;
	for (i = 0; i < N; i++)
	{
		setcolor(RGB(10, 20, 50));
		setfillcolor(RGB(10, 20, 50));
		fillcircle(ball_x1[i], ball_y1[i], radius1);	// 绘制深蓝圆	1分
		setcolor(RGB(34, 139, 34));
		setfillcolor(RGB(34, 139, 34));
		fillcircle(ball_x2[i], ball_y2[i], radius2);	// 绘制绿圆   2分
		setcolor(RGB(255, 192, 203));
		setfillcolor(RGB(255, 192, 203));
		fillcircle(ball_x3[i], ball_y3[i], radius3);	// 绘制粉圆  3分
	}

	time();    //时间

	FlushBatchDraw();
	// 延时
	Sleep(3);
}

void over1()     //结束画面
{
	putimage(0, 0, &img_over);    //显示结束背景图片
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.42, Height * 0.4, "游戏结束");

	settextcolor(BLACK);
	settextstyle(40, 0, _T("黑体"));
	outtextxy(Width * 0.45, Height * 0.55, "得分：");
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), score);
	outtextxy(Width * 0.55, Height * 0.55, s);

	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(Width * 0.85, Height * 0.85, "退出");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.84, Width * 0.93, Height * 0.90);

	FlushBatchDraw();
	Sleep(5);

	char input;
	if (_kbhit())    //判断是否有输入
	{
		input = _getch();   //根据用户的不同输入来选择，不必输入回车
		if (input == 27)    //Esc退出帮助界面
			gameStatus = 0;
	}

	MOUSEMSG m;		 //定义鼠标消息
	while (MouseHit())    //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.84 && m.y <= Height * 0.90)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键
				gameStatus = 0;
		}
	}

	playoperation();
}

void updateWithoutInput1()  // 与用户输入无关的更新
{
	//控制时间
	if (l >= 59)
	{
		second = second - 1;
		minute = second / 60;
		l = 0;
	}
	else
		l++;

	//蛇身移动
	for (k = n - 1; k > 0; k--)
	{
		body_x[k] = body_x[k - 1];
		body_y[k] = body_y[k - 1];
	}
	body_x[0] = head_x;
	body_y[0] = head_y;

	//蛇头移动
	if (moveDirection == 1)   //a
	{
		head_x -= moveSpeed;

		//眼白移动
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y - radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 2)   //d
	{
		head_x += moveSpeed;

		//眼白移动
		eyeb_x1 = head_x + radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x + radius_head / 2;
		eyeb_y2 = head_y - radius_head / 2;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 3)   //w
	{
		head_y -= moveSpeed;

		//眼白移动
		eyeb_x1 = head_x + radius_head / 2;
		eyeb_y1 = head_y - radius_head / 2;
		eyeb_x2 = head_x - radius_head / 2;
		eyeb_y2 = head_y - radius_head / 2;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}
	if (moveDirection == 4)   //s
	{
		head_y += moveSpeed;

		//眼白移动
		eyeb_x1 = head_x - radius_head / 2;
		eyeb_y1 = head_y + radius_head / 2;
		eyeb_x2 = head_x + radius_head / 2;
		eyeb_y2 = head_y + radius_head / 2;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 5)   //a,w
	{
		head_x -= moveSpeed;
		head_y -= moveSpeed;

		//眼白移动
		eyeb_x1 = head_x + radius_head / 2 - radius_head / 3;
		eyeb_y1 = head_y - radius_head / 3 - radius_head / 3;
		eyeb_x2 = head_x - radius_head / 2 - radius_head / 3;
		eyeb_y2 = head_y + radius_head / 3 - radius_head / 3;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 6)   //a,s
	{
		head_x -= moveSpeed;
		head_y += moveSpeed;

		//眼白移动
		eyeb_x1 = head_x - radius_head / 2 - radius_head / 3;
		eyeb_y1 = head_y - radius_head / 3 + radius_head / 3;
		eyeb_x2 = head_x + radius_head / 2 - radius_head / 3;
		eyeb_y2 = head_y + radius_head / 3 + radius_head / 3;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 7)   //d,s
	{
		head_x += moveSpeed;
		head_y += moveSpeed;

		//眼白移动
		eyeb_x1 = head_x - radius_head / 2 + radius_head / 3;
		eyeb_y1 = head_y + radius_head / 3 + radius_head / 3;
		eyeb_x2 = head_x + radius_head / 2 + radius_head / 3;
		eyeb_y2 = head_y - radius_head / 3 + radius_head / 3;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	if (moveDirection == 8)   //d,w
	{
		head_x += moveSpeed;
		head_y -= moveSpeed;

		//眼白移动
		eyeb_x1 = head_x + radius_head / 2 + radius_head / 3;
		eyeb_y1 = head_y + radius_head / 3 - radius_head / 3;
		eyeb_x2 = head_x - radius_head / 2 + radius_head / 3;
		eyeb_y2 = head_y - radius_head / 3 - radius_head / 3;

		//眼珠移动
		eyez_x1 = eyeb_x1;
		eyez_y1 = eyeb_y1;
		eyez_x2 = eyeb_x2;
		eyez_y2 = eyeb_y2;
	}

	int i;
	for (i = 0; i < N; i++)
	{
		//判断是否吃到豆豆
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

	//判断地图移动
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

void updateWithInput1()  // 与用户输入有关的更新
{
	//蛇头移动
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

	//实现加速
	if ((GetAsyncKeyState(0x20) & 0x8000))  // 空格
		moveSpeed = 4;
	else
		moveSpeed = 2;
}


void playgame2()   //双人模式
{
	startup2();  // 双人游戏界面初始化	
	while (gameStatus == 2)  //  游戏循环执行
	{
		clean2();  // 把之前绘制的内容取消
		updateWithoutInput2();  // 与用户输入无关的更新
		updateWithInput2();     // 与用户输入有关的更新
		show2();  // 显示新画面
		writeRecordFile2();    //存储游戏数据文件存档
		char input;
		if (_kbhit())    //判断是否有输入
		{
			input = _getch();   //根据用户的不同输入来选择，不必输入回车
			if (input == 27)
			{
				gameStatus = 4;
				m++;
			}
		}
	}
	playoperation();
	gameover();     // 游戏结束、后续处理
}

void startup2()   //双人模式初始化
{
	mciSendString("open .\\社会主义好.mp3 alias bkmusic", NULL, 0, NULL);   //背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);   //循环播放

	initgraph(Width, Height);    ////初始化画布大小
	win_player = 0;
	//读取图片到img对象中
	loadimage(&img_bk, ".\\贪吃蛇大地图3.jpg");
	loadimage(&img_1, _T(".\\p3.jpg"));
	loadimage(&img_2, _T(".\\p1.jpg"));
	loadimage(&img_3, _T(".\\p2.jpg"));
	loadimage(&img_4, _T(".\\p4.jpg"));
	loadimage(&img_5, _T(".\\图1.jpg"));
	loadimage(&img_6, _T(".\\图2.jpg"));
	loadimage(&img_7, _T(".\\图3.jpg"));
	loadimage(&img_8, _T(".\\图4.jpg"));

	if (m == 0)
	{
		temp = 2;

		//初始化时间
		minute = 3;
		second = 180;
		l = 0;
		//初始化地图位置
		location_x =0;
		location_y =0;

		//初始化得分
		score1 = 0;
		score2 = 0;

		//初始化1蛇头移动方向向下
		moveDirection1 = 4;

		//初始化2蛇头移动方向向上
		moveDirection2 = 3;

		//初始化1蛇头位置
		head1_x = Width / 4;
		head1_y = Height / 4;
		//初始化2蛇头位置
		head2_x = 3 * Width / 4;
		head2_y = 3 * Height / 4;
		radius_head = 10;//初始化半径

		//初始化1蛇眼白位置
		eyeb1_x1 = head1_x - radius_head / 2;
		eyeb1_y1 = head1_y + radius_head / 2;
		eyeb1_x2 = head1_x - radius_head / 2;
		eyeb1_y2 = head1_y + radius_head / 2;
		//初始化2蛇眼白位置
		eyeb2_x1 = head2_x - radius_head / 2;
		eyeb2_y1 = head2_y + radius_head / 2;
		eyeb2_x2 = head2_x - radius_head / 2;
		eyeb2_y2 = head2_y + radius_head / 2;
		radius1_eyeb = 6;
		radius2_eyeb = 6;

		//初始化1蛇眼珠位置
		eyez1_x1 = eyeb1_x1;
		eyez1_y1 = eyeb1_y1;
		eyez1_x2 = eyeb1_x2;
		eyez1_y2 = eyeb1_y2;
		//初始化2蛇眼珠位置
		eyez2_x1 = eyeb2_x1;
		eyez2_y1 = eyeb2_y1;
		eyez2_x2 = eyeb2_x2;
		eyez2_y2 = eyeb2_y2;
		radius1_eyez = 3;
		radius2_eyez = 3;

		//初始化1蛇身体的位置
		radius1_body = radius_head;
		length1 = 30;			//初始长度
		body1_x[0] = head1_x;
		body1_y[0] = head1_y - 2 * radius1_body;
		for (i = 1; i <= length1; i++)
		{
			body1_x[i] = body1_x[i - 1];
			body1_x[i] = body1_y[i - 1] - 2 * radius1_body;
		}

		//初始化2蛇身体的位置
		radius2_body = radius_head;
		length2 = 30;			//初始长度
		body2_x[0] = head2_x;
		body2_y[0] = head2_y - 2 * radius2_body;
		for (i = 1; i <= length2; i++)
		{
			body2_x[i] = body2_x[i - 1];
			body2_x[i] = body2_y[i - 1] - 2 * radius2_body;
		}

		//初始化小豆豆npc的位置

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

void clean2()  // 消除画面
{
	setcolor(BLACK);
	setfillcolor(BLACK);

	fillcircle(head1_x, head1_y, radius_head);   //消除1蛇头
	fillcircle(head2_x, head2_y, radius_head);   //消除2蛇头

	//消除1蛇眼睛
	fillcircle(eyeb1_x1, eyeb1_y1, radius1_eyeb);   //消除眼白1
	fillcircle(eyeb1_x2, eyeb1_y2, radius1_eyeb);   //消除眼白2
	fillcircle(eyez1_x1, eyez1_y1, radius1_eyez);   //消除眼珠1
	fillcircle(eyez1_x2, eyez1_y2, radius1_eyez);   //消除眼珠2
	//消除2蛇眼睛
	fillcircle(eyeb2_x1, eyeb2_y1, radius2_eyeb);   //消除眼白1
	fillcircle(eyeb2_x2, eyeb2_y2, radius2_eyeb);   //消除眼白2
	fillcircle(eyez2_x1, eyez2_y1, radius2_eyez);   //消除眼珠1
	fillcircle(eyez2_x2, eyez2_y2, radius2_eyez);   //消除眼珠2

	//清除身体
	for (i = 0; i <= length1; i++)
	{
		fillcircle(body1_x[i], body1_y[i], radius1_body);
	}
	for (i = 0; i <= length2; i++)
	{
		fillcircle(body2_x[i], body2_y[i], radius2_body);
	}
}

void show2()  // 显示画面
{
	TCHAR s[80];
	putimage(location_x, location_y, &img_bk);  //在坐标(0,0)位置显示背景
	settextcolor(RGB(200, 150, 0));
	setbkcolor(WHITE);
	settextstyle(30, 0, _T("宋体"));
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

	//绘制边框
	setcolor(RGB(200, 150, 0));
	rectangle(Width - 222, 7, Width - 5, 192);

	//绘制1蛇身体
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	for (i = 0; i <= length1; i++)
	{
		fillcircle(body1_x[i], body1_y[i], radius1_body);
	}
	//绘制2蛇身体
	setcolor(RED);
	setfillcolor(RED);
	for (i = 0; i <= length2; i++)
	{
		fillcircle(body2_x[i], body2_y[i], radius2_body);
	}

	//绘制1蛇头
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(head1_x, head1_y, radius_head);
	//绘制2蛇头
	setcolor(RED);
	setfillcolor(RED);
	fillcircle(head2_x, head2_y, radius_head);

	//绘制眼白
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(eyeb1_x1, eyeb1_y1, radius1_eyeb);
	fillcircle(eyeb1_x2, eyeb1_y2, radius1_eyeb);
	fillcircle(eyeb2_x1, eyeb2_y1, radius2_eyeb);
	fillcircle(eyeb2_x2, eyeb2_y2, radius2_eyeb);

	//绘制眼珠
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(eyez1_x1, eyez1_y1, radius1_eyez);
	fillcircle(eyez1_x2, eyez1_y2, radius1_eyez);
	fillcircle(eyez2_x1, eyez2_y1, radius2_eyez);
	fillcircle(eyez2_x2, eyez2_y2, radius2_eyez);

	//绘制小豆豆npc
	int i;
	for (i = 0; i < K; i++)
	{
		setcolor(RGB(10, 20, 50));
		setfillcolor(RGB(10, 20, 50));
		fillcircle(ball_x1[i], ball_y1[i], radius1);	// 绘制深蓝圆	
		setcolor(RGB(34, 139, 34));
		setfillcolor(RGB(34, 139, 34));
		fillcircle(ball_x2[i], ball_y2[i], radius2);	// 绘制绿圆
		setcolor(RGB(255, 192, 203));
		setfillcolor(RGB(255, 192, 203));
		fillcircle(ball_x3[i], ball_y3[i], radius3);	// 绘制粉圆
	}

	time();												//倒计时

	FlushBatchDraw();
	// 延时
	Sleep(3);
}

void over2()     //结束画面
{
	putimage(0, 0, &img_over);    //显示结束背景图片
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(Width * 0.42, Height * 0.3, "游戏结束");

	settextcolor(BLACK);
	settextstyle(40, 0, _T("黑体"));
	TCHAR s1[5];
	TCHAR s2[5];
	outtextxy(Width * 0.35, Height * 0.45, "玩家1得分：");
	_stprintf_s(s1, _T("%d"), score1);
	outtextxy(Width * 0.6, Height * 0.45, s1);
	outtextxy(Width * 0.35, Height * 0.55, "玩家2得分：");
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
		settextstyle(50, 0, _T("黑体"));
		outtextxy(Width * 0.35, Height * 0.18, "一号玩家获胜！");
	}
	if (win_player == 2)
	{
		settextcolor(RED);
		settextstyle(50, 0, _T("黑体"));
		outtextxy(Width * 0.35, Height * 0.18, "二号玩家获胜！");
	}
	if (win_player == 0)
	{
		settextcolor(RED);
		settextstyle(50, 0, _T("黑体"));
		outtextxy(Width * 0.47, Height * 0.18, "平局！");
	}

	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(Width * 0.85, Height * 0.85, "退出");

	setcolor(RGB(102, 139, 139));
	rectangle(Width * 0.82, Height * 0.84, Width * 0.93, Height * 0.90);

	FlushBatchDraw();
	Sleep(5);

	char input;
	if (_kbhit())    //判断是否有输入
	{
		input = _getch();   //根据用户的不同输入来选择，不必输入回车
		if (input == 27)    //Esc退出帮助界面
			gameStatus = 0;
	}

	MOUSEMSG m;		 //定义鼠标消息
	while (MouseHit())    //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.x >= Width * 0.82 && m.x <= Width * 0.93 && m.y >= Height * 0.84 && m.y <= Height * 0.90)
		{
			if (m.uMsg == WM_LBUTTONDOWN)  //单击左键
				gameStatus = 0;
		}
	}

	playoperation();
}

void control1_body()
{
	//身体移动
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
	//身体移动
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
	//眼珠移动
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

void updateWithoutInput2()  // 与用户输入无关的更新
{
	//控制时间
	if (l >= 49)
	{
		second = second - 1;
		minute = second / 60;
		l = 0;
	}
	else
		l++;

	//1蛇头移动
	if (moveDirection1 == 1)   //a
	{
		//身体移动
		control1_body();

		head1_x -= moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x - radius_head;
		eyeb1_y1 = head1_y - radius_head;
		eyeb1_x2 = head1_x - radius_head;
		eyeb1_y2 = head1_y + radius_head;

		//眼珠移动
		control1_eyez();
	}

	if (moveDirection1 == 2)   //d
	{
		//身体移动
		control1_body();

		head1_x += moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x + radius_head;
		eyeb1_y1 = head1_y + radius_head;
		eyeb1_x2 = head1_x + radius_head;
		eyeb1_y2 = head1_y - radius_head;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 3)   //w
	{
		//身体移动
		control1_body();

		head1_y -= moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x + radius_head;
		eyeb1_y1 = head1_y - radius_head;
		eyeb1_x2 = head1_x - radius_head;
		eyeb1_y2 = head1_y - radius_head;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 4)   //s
	{
		//身体移动
		control1_body();

		head1_y += moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x - radius_head;
		eyeb1_y1 = head1_y + radius_head;
		eyeb1_x2 = head1_x + radius_head;
		eyeb1_y2 = head1_y + radius_head;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 5)	//a,w;
	{

		//身体移动
		control1_body();

		head1_x -= moveSpeed1;
		head1_y -= moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y - radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x - radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 6)	//a,s;
	{

		//身体移动
		control1_body();

		head1_x -= moveSpeed1;
		head1_y += moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y + radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x - radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 7)	//s,d;
	{

		//身体移动
		control1_body();

		head1_x += moveSpeed1;
		head1_y += moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y + radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x + radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//眼珠移动
		control1_eyez();
	}
	if (moveDirection1 == 8)	//w,d;
	{

		//身体移动
		control1_body();

		head1_x += moveSpeed1;
		head1_y -= moveSpeed1;

		//眼白移动
		eyeb1_x1 = head1_x;
		eyeb1_y1 = head1_y - radius_head / (cos(45.0 * pi / 180));
		eyeb1_x2 = head1_x + radius_head / (cos(45.0 * pi / 180));
		eyeb1_y2 = head1_y;

		//眼珠移动
		control1_eyez();
	}
	//2蛇头移动
	if (moveDirection2 == 1)   //left
	{
		//身体移动
		control2_body();

		head2_x -= moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x - radius_head;
		eyeb2_y1 = head2_y - radius_head;
		eyeb2_x2 = head2_x - radius_head;
		eyeb2_y2 = head2_y + radius_head;

		//眼珠移动
		control2_eyez();

	}
	if (moveDirection2 == 2)   //right
	{
		//身体移动
		control2_body();

		head2_x += moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x + radius_head;
		eyeb2_y1 = head2_y + radius_head;
		eyeb2_x2 = head2_x + radius_head;
		eyeb2_y2 = head2_y - radius_head;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 3)   //up
	{
		//身体移动
		control2_body();

		head2_y -= moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x + radius_head;
		eyeb2_y1 = head2_y - radius_head;
		eyeb2_x2 = head2_x - radius_head;
		eyeb2_y2 = head2_y - radius_head;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 4)   //down
	{
		//身体移动
		control2_body();

		head2_y += moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x - radius_head;
		eyeb2_y1 = head2_y + radius_head;
		eyeb2_x2 = head2_x + radius_head;
		eyeb2_y2 = head2_y + radius_head;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 5)	//left&&up
	{

		//身体移动
		control2_body();

		head2_x -= moveSpeed2;
		head2_y -= moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y - radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x - radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 6)	//left&&down
	{

		//身体移动
		control2_body();

		head2_x -= moveSpeed2;
		head2_y += moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y + radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x - radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 7)	//down&&right
	{

		//身体移动
		control2_body();

		head2_x += moveSpeed2;
		head2_y += moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y + radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x + radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//眼珠移动
		control2_eyez();
	}
	if (moveDirection2 == 8)	//up&&right
	{

		//身体移动
		control2_body();

		head2_x += moveSpeed2;
		head2_y -= moveSpeed2;

		//眼白移动
		eyeb2_x1 = head2_x;
		eyeb2_y1 = head2_y - radius_head / (cos(45.0 * pi / 180));
		eyeb2_x2 = head2_x + radius_head / (cos(45.0 * pi / 180));
		eyeb2_y2 = head2_y;

		//眼珠移动
		control2_eyez();
	}
	for (i = 0; i < K; i++)
	{
		//判断1蛇是否吃到豆豆
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
		//判断2蛇是否吃到豆豆
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
	//判断小蛇是否相撞
	//1蛇撞到2蛇
	for (i = 0; i < length2; i++)
	{
		int k;
		if ((head1_x == body2_x[i] && abs(head1_y - body2_y[i]) < 2 * radius2_body) || (head1_y == body2_y[i] && abs(head1_x - body2_x[i]) < 2 * radius2_body))
		{
			win_player = 2;
			gameStatus = 6;
		}
	}
	//2蛇撞到1蛇
	for (i = 0; i < length1; i++)
	{
		int k;
		if ((head2_x == body1_x[i] && abs(head2_y - body1_y[i]) < 2 * radius1_body) || (head2_y == body1_y[i] && abs(head2_x - body1_x[i]) < 2 * radius1_body))
		{
			win_player = 1;
			gameStatus = 6;
		}
	}
	//1蛇出界
	if (head1_x <= location_x + 10 || head1_x >= location_x + 1000 - 10 || head1_y <= location_y + 10 || head1_y >= location_y + 600 - 10)//2362  1417
	{
		gameStatus = 6;
		win_player = 2;
	}
	//2蛇出界
	if (head2_x <= location_x + 10 || head2_x >= location_x + 1000 - 10 || head2_y <= location_y + 10 || head2_y >= location_y + 600 - 10)
	{
		gameStatus = 6;
		win_player = 1;
	}

		
}

void updateWithInput2()  // 与用户输入有关的更新
{
	//1蛇头移动
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
	//2蛇头移动
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
	//1蛇实现加速
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))  // 按下空格
		moveSpeed1 = 4;
	else
		moveSpeed1 = 2;
	//2蛇实现加速
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000))  // 按下回车
		moveSpeed2 = 4;
	else
		moveSpeed2 = 2;
}


int main()
{
	startup();  // 数据菜单界面
	while (gameStatus != 1 && gameStatus != 2)
		playoperation();
	if (gameStatus == 1)    //进行单人模式
		playgame1();
	else if (gameStatus == 2)   //进行双人模式
		playgame2();
	return 0;
}
