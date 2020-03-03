#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>

#define  N 22      //��Ϸ����߳� /���߿�

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

    void initialize(int &);//�����ʼ��
};

void snake_position::initialize(int &j)
{
    x = 1;

    y = j;
}

snake_position position[(N - 2)*(N - 2)]; //���� ̰���������� ����
/**
*�����뽫̰�������ڴ����Ϊһ��ֱ�ߣ�
*������̬�洢ͷ��β������
*head��tail��������ָ��ͷ��β����������е�λ��
*����������ַ���ά�����������
*/


//���涨��̰���ߵ�����ͼ
class snake_map
{

private:

    char s[N][N];//����̰�������̣�����ǽ�ڡ�

    int grade, length;//�ȼ�����

    int gamespeed; //ǰ��ʱ����

    char direction; //����

    int head, tail;//ͷβ

    int score;

    bool gameauto;//�Զ�����ģʽ

public:

    snake_map(int h = 3, int t = 0, int l = 4, char d = 77 , int s = 0) :length(l), direction(d), head(h), tail(t), score(s) {}// ��ʼ����£������˶�(char d = 77)

    void initialize();   //��ʼ������

    void show_game();//���̰����������Ϣ

    void getgrade();//����ѡ��ȼ�

    void display();//����ȼ����÷�����Լ��ƺ�

    void setpoint();//����������� 

    bool updata_game();//��������
};



//�����ʼ����������̰���ߵ�����ͼ���г�ʼ��
void snake_map::initialize()
{
    int i, j;


    for (i = 1; i <= N - 2; i++)
    {
        for (j = 1; j <= N - 2; j++)
        {
            s[i][j] = ' ';
        }
    }//��ʼ��̰���������м�հײ���

    for (i = 1; i <= 3; i++)

        s[1][i] = '*';

    s[1][4] = '#';//����

    for (i = 0; i <= N - 1; i++)

        s[0][i] = s[N - 1][i] = '-'; //��ʼ��̰������������ǽ��

    for (i = 1; i <= N - 2; i++)

        s[i][0] = s[i][N - 1] = '|'; //��ʼ��̰������������ǽ��
}


//���̰����������Ϣ
void snake_map::show_game()

{

    system("cls"); // ����

    int i, j;

    cout << endl;

    for (i = 0; i < N; i++)
    {

        cout << '\t';

        for (j = 0; j < N; j++)

            cout << s[i][j] << ' '; // ���̰��������

        if (i == 2) cout << "\t�ȼ���" << grade;

        if (i == 6) cout << "\t�ٶȣ�" << gamespeed;

        if (i == 10) cout << "\t�÷֣�" << score << "��";

        if (i == 14) cout << "\t��ͣ����һ�¿ո��";

        if (i == 18) cout << "\t��������һ�¿ո��";

        cout << endl;
    }
}


//����ѡ��ȼ�
void snake_map::getgrade()
{
    cin >> grade;

    while (grade > 7 || grade < 1)
    {
        cout << "����������1-7ѡ��ȼ�����������������Ч\n";

        cin.clear();
        getchar();//���һ�����������̵�����

        cin >> grade;
    }
    gameauto = false;   //Ĭ��Ϊfalse
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


//����ȼ����÷�����Լ��ƺ�
void snake_map::display()
{

    cout << "\n\t\t\t\t�ȼ���" << grade;

    cout << "\n\n\n\t\t\t\t�ٶȣ�" << gamespeed;

    cout << "\n\n\n\t\t\t\t�÷֣�" << score << "��";

}


//����������� 
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


//��������
bool snake_map::updata_game() 
{
    gamealive = 1;

    key = direction;

    start = clock();

    while ((gamealive = (clock() - start <= gamespeed)) && !_kbhit());//����м����»�ʱ�䳬���Զ�ǰ��ʱ��������ֹѭ��

    if (gamealive)
    {
        _getch();

            key = _getch();
    }


    if (key == ' ')
    {
        while (_getch() != ' ') { };//����ʵ�ֵ��ǰ��ո����ͣ�����ո�������Ĺ��ܣ�����֪Ϊ��ԭ����Ҫ�����¿ո���ܼ��������Ǹ�bug��
    }
    else
    {
        direction = key;
    }

    switch (direction)
    {
    case 72: x = position[head].x - 1; y = position[head].y     ; break; // ����

    case 80: x = position[head].x + 1; y = position[head].y     ; break; // ����

    case 75: x = position[head].x      ; y = position[head].y - 1; break; // ����

    case 77: x = position[head].x      ; y = position[head].y + 1; break;// ����

    }

    if (!(direction == 72 || direction == 80 || direction == 75 || direction == 77))   // �����Ƿ����
    {
        gamealive = false;
    }
    else if (s[x][y] != ' ' && !(x == x_1 && y == y_1))    // ��ͷ�����Ƿ���λ��
    {
        gamealive = false;
    }
    else if (x == x_1 && y == y_1) //�Ե�����
    { 
        length++;

        if (length >= 8 && gameauto)//�Զ�����
        {
            length -= 8;

            grade++;

            if (gamespeed >= 200)
            {
                gamespeed -= 200; // �ı�̰����ǰ���ٶ�
            }
            else
            {
                gamespeed = 100;
            }
        }

        s[x][y] = '#';  //������ͷ

        s[position[head].x][position[head].y] = '*'; //��ԭ����ͷ��Ϊ����

        head = (head + 1) % ((N - 2)*(N - 2));   

        position[head].x = x;

        position[head].y = y;//ȡ��ͷ����

        show_game();

        gamealive = true;

        score += grade * 20;  //�ӷ�

        setpoint();   //�����·��� 
    }

    else// ���Է��� 
    { 
        s[position[tail].x][position[tail].y] = ' ';//����β�ÿ�

        tail = (tail + 1) % ((N - 2) * (N - 2));//������β����

        s[position[head].x][position[head].y] = '*';  //����ͷ��Ϊ����

        head = (head + 1) % ((N - 2) * (N - 2));

        position[head].x = x;

        position[head].y = y;

        s[position[head].x][position[head].y] = '#'; //������ͷ

        gamealive = true;

    }
    return gamealive;
}



//====================================
//����������
//====================================


int main()
{
    char ctn = 'y';

    bool nodead;

    cout << "̰����2.0" << endl;
    cout << "\t__author__: Len " << endl;
    cout << "\n\n\n\t\t\t ���������ʼ" << endl;

    _getch();

    while (ctn == 'y')
    {
        system("cls"); // ����

        snake_map snake;

        snake.initialize();

        cout << "\n\n����������ѡ����Ϸ�ȼ���(�ٶ�Ϊˢ�¼������λ��ms)" << endl;

        cout << "\n\n\n\t\t\t1.�ȼ�һ���ٶ� 1000 \n\n\t\t\t2.�ȼ������ٶ� 800 \n\n\t\t\t3.�ȼ������ٶ� 600 ";

        cout << "\n\n\t\t\t4.�ȼ��ģ��ٶ� 400 \n\n\t\t\t5.�ȼ��壺�ٶ� 200 \n\n\t\t\t6.�ȼ������ٶ� 100 \n\n\t\t\t7.�Զ�����ģʽ" << endl;

        snake.getgrade();

        for (int i = 1; i <=4; i++)
        {
            position[i - 1].initialize(i);
        }

        snake.setpoint();  //������һ������ 

        do
        {
            snake.show_game();

            nodead = snake.updata_game();

        } while (nodead);

        system("cls"); 



        cout << "\n\n\n\t\t\t\tGameover��\n\n" << endl;

        snake.display();

        cout << "\n\n\n\t\t    �Ƿ�ѡ�������Ϸ������ y ������n �˳�" << endl;

        cin >> ctn;

    }

    return 0;
}
