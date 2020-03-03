#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>

#define  N 22      //游戏界面边长 /含边框

using namespace std;

int gamealive;

int x_1, y_1;

int x, y;

long start;

char key;

class snake_position
{
public:

    int x, y;

    snake_position() {};

    void initialize(int &);//坐标初始化
};

void snake_position::initialize(int &j)
{
    x = 1;

    y = j;
}

snake_position position[(N - 2)*(N - 2)]; //定义 贪吃蛇坐标类 数组
/**
*我是想将贪吃蛇在内存抽象为一条直线，
*用来动态存储头和尾的坐标
*head和tail变量就是指蛇头蛇尾在这个数组中的位置
*方便读出在字符二维数组的行列数
*/


//下面定义贪吃蛇的棋盘图
class snake_map
{

private:

    char s[N][N];//定义贪吃蛇棋盘，包括墙壁。

    int grade, length;//等级长度

    int gamespeed; //前进时间间隔

    char direction; //方向

    int head, tail;//头尾

    int score;

    bool gameauto;//自动升级模式

public:

    snake_map(int h = 3, int t = 0, int l = 4, char d = 77 , int s = 0) :length(l), direction(d), head(h), tail(t), score(s) {}// 初始情况下，向右运动(char d = 77)

    void initialize();   //初始化函数

    void show_game();//输出贪吃蛇棋盘信息

    void getgrade();//输入选择等级

    void display();//输出等级，得分情况以及称号

    void setpoint();//随机产生方块 

    bool updata_game();//操作部分
};



//定义初始化函数，将贪吃蛇的棋盘图进行初始化
void snake_map::initialize()
{
    int i, j;


    for (i = 1; i <= N - 2; i++)
    {
        for (j = 1; j <= N - 2; j++)
        {
            s[i][j] = ' ';
        }
    }//初始化贪吃蛇棋盘中间空白部分

    for (i = 1; i <= 3; i++)

        s[1][i] = '*';

    s[1][4] = '#';//蛇身

    for (i = 0; i <= N - 1; i++)

        s[0][i] = s[N - 1][i] = '-'; //初始化贪吃蛇棋盘上下墙壁

    for (i = 1; i <= N - 2; i++)

        s[i][0] = s[i][N - 1] = '|'; //初始化贪吃蛇棋盘左右墙壁
}


//输出贪吃蛇棋盘信息
void snake_map::show_game()

{

    system("cls"); // 清屏

    int i, j;

    cout << endl;

    for (i = 0; i < N; i++)
    {

        cout << '\t';

        for (j = 0; j < N; j++)

            cout << s[i][j] << ' '; // 输出贪吃蛇棋盘

        if (i == 2) cout << "\t等级：" << grade;

        if (i == 6) cout << "\t速度：" << gamespeed;

        if (i == 10) cout << "\t得分：" << score << "分";

        if (i == 14) cout << "\t暂停：按一下空格键";

        if (i == 18) cout << "\t继续：按一下空格键";

        cout << endl;
    }
}


//输入选择等级
void snake_map::getgrade()
{
    cin >> grade;

    while (grade > 7 || grade < 1)
    {
        cout << "请输入数字1-7选择等级，输入其他数字无效\n";

        cin.clear();
        getchar();//清空一下输入流，吞掉换行

        cin >> grade;
    }
    gameauto = false;   //默认为false
    switch (grade)
    {
    case 1: gamespeed = 1000;  break;

    case 2: gamespeed = 800;  break;

    case 3: gamespeed = 600;  break;

    case 4: gamespeed = 400;  break;

    case 5: gamespeed = 200;  break;

    case 6: gamespeed = 100; break;

    case 7: grade = 1; gamespeed = 1000; gameauto = true ; break;
    }

}


//输出等级，得分情况以及称号
void snake_map::display()
{

    cout << "\n\t\t\t\t等级：" << grade;

    cout << "\n\n\n\t\t\t\t速度：" << gamespeed;

    cout << "\n\n\n\t\t\t\t得分：" << score << "分";

}


//随机产生方块 
void snake_map::setpoint()
{
    srand((unsigned int)time(0));

    do
    {

        x_1 =  rand() % (N - 2) + 1;

        y_1 =  rand() % (N - 2) + 1;

    } while (s[x_1][y_1] != ' ');

    s[x_1][y_1] = '*';
}


//操作部分
bool snake_map::updata_game() 
{
    gamealive = 1;

    key = direction;

    start = clock();

    while ((gamealive = (clock() - start <= gamespeed)) && !_kbhit());//如果有键按下或时间超过自动前进时间间隔则终止循环

    if (gamealive)
    {
        _getch();

            key = _getch();
    }


    if (key == ' ')
    {
        while (_getch() != ' ') { };//这里实现的是按空格键暂停，按空格键继续的功能，但不知为何原因，需要按两下空格才能继续。这是个bug。
    }
    else
    {
        direction = key;
    }

    switch (direction)
    {
    case 72: x = position[head].x - 1; y = position[head].y     ; break; // 向上

    case 80: x = position[head].x + 1; y = position[head].y     ; break; // 向下

    case 75: x = position[head].x      ; y = position[head].y - 1; break; // 向左

    case 77: x = position[head].x      ; y = position[head].y + 1; break;// 向右

    }

    if (!(direction == 72 || direction == 80 || direction == 75 || direction == 77))   // 按键非方向键
    {
        gamealive = false;
    }
    else if (s[x][y] != ' ' && !(x == x_1 && y == y_1))    // 蛇头碰到非方块位置
    {
        gamealive = false;
    }
    else if (x == x_1 && y == y_1) //吃到方块
    { 
        length++;

        if (length >= 8 && gameauto)//自动升级
        {
            length -= 8;

            grade++;

            if (gamespeed >= 200)
            {
                gamespeed -= 200; // 改变贪吃蛇前进速度
            }
            else
            {
                gamespeed = 100;
            }
        }

        s[x][y] = '#';  //更新蛇头

        s[position[head].x][position[head].y] = '*'; //将原先蛇头变为蛇身

        head = (head + 1) % ((N - 2)*(N - 2));   

        position[head].x = x;

        position[head].y = y;//取蛇头坐标

        show_game();

        gamealive = true;

        score += grade * 20;  //加分

        setpoint();   //产生新方块 
    }

    else// 不吃方块 
    { 
        s[position[tail].x][position[tail].y] = ' ';//将蛇尾置空

        tail = (tail + 1) % ((N - 2) * (N - 2));//更新蛇尾坐标

        s[position[head].x][position[head].y] = '*';  //将蛇头更为蛇身

        head = (head + 1) % ((N - 2) * (N - 2));

        position[head].x = x;

        position[head].y = y;

        s[position[head].x][position[head].y] = '#'; //更新蛇头

        gamealive = true;

    }
    return gamealive;
}



//====================================
//主函数部分
//====================================


int main()
{
    char ctn = 'y';

    bool nodead;

    cout << "贪吃蛇2.0" << endl;
    cout << "\t__author__: Len " << endl;
    cout << "\n\n\n\t\t\t 按任意键开始" << endl;

    _getch();

    while (ctn == 'y')
    {
        system("cls"); // 清屏

        snake_map snake;

        snake.initialize();

        cout << "\n\n请输入数字选择游戏等级：(速度为刷新间隔，单位：ms)" << endl;

        cout << "\n\n\n\t\t\t1.等级一：速度 1000 \n\n\t\t\t2.等级二：速度 800 \n\n\t\t\t3.等级三：速度 600 ";

        cout << "\n\n\t\t\t4.等级四：速度 400 \n\n\t\t\t5.等级五：速度 200 \n\n\t\t\t6.等级六：速度 100 \n\n\t\t\t7.自动升级模式" << endl;

        snake.getgrade();

        for (int i = 1; i <=4; i++)
        {
            position[i - 1].initialize(i);
        }

        snake.setpoint();  //产生第一个方块 

        do
        {
            snake.show_game();

            nodead = snake.updata_game();

        } while (nodead);

        system("cls"); 



        cout << "\n\n\n\t\t\t\tGameover！\n\n" << endl;

        snake.display();

        cout << "\n\n\n\t\t    是否选择继续游戏？输入 y 继续，n 退出" << endl;

        cin >> ctn;

    }

    return 0;
}
