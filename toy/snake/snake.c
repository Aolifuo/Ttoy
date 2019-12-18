/*
作者：童楠
作品：贪吃蛇
平台：Windows
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define INITIALIZATION \
    do                 \
    {                  \
        initmap();     \
        initsnake();   \
        re_map();      \
        food_xy();     \
        re_map();      \
        drawmap();     \
    } while (0)
#define X_L 27
#define Y_W 23

void menu(void); //生成菜单
void end(void);  //生成结果
void block(int);
void initmap(void);     //初始化地图
void drawmap(void);     //绘制地图
void re_map(void);      //刷新地图
void initsnake(void);   //初始化小蛇
void food_xy(void);     //生成食物
void keyboardhit(void); //检测键盘输入
void move(void);        //小蛇坐标移动
void event(void);       //检测事件(撞墙，咬尾)
void hide(void);        //隐藏光标

enum spectrum
{
    up = 'w',
    down = 's',
    left = 'a',
    right = 'd'
};

typedef struct
{
    int x[X_L * Y_W + 1];
    int y[X_L * Y_W + 1];
    int length;
    int X;
    int Y;
} SNAKE; //小蛇的结构体
typedef struct
{
    int x;
    int y;
} FOOD; //食物结构体

SNAKE snake;
FOOD food;
int map[X_L + 1][Y_W + 1] = {0};
int is_longer = 0, gameover = 0, choice = 0, speed = 300; //choice 用于选择 ,is_longer判断是否变长,gameover判断游戏是否结束,speed为速度
enum spectrum direction = right;

int main(void)
{
    while (1)
    {
        gameover = 0;
        menu();
        if (choice == 5)
            break; //选择5退出
        system("cls");
        INITIALIZATION;
        puts("按任意键开始");
        getch();
        while (1)
        {
            hide();
            Sleep(speed);
            keyboardhit();
            initmap();
            re_map();
            event();
            system("cls");
            drawmap();
            if (gameover)
                break; //游戏结束
        }
        if (gameover)
            end();
    }
    system("cls");
    puts("感谢游玩");
    system("pause");
    return 0;
}

void menu(void)
{
aaa:
    system("cls");
    puts("\n\n");
    puts("        贪   吃   蛇");
    puts("---------------------------");
    puts(" 请 选 择（WASD控制方向）");
    puts("          1.简单   ");
    puts("          2.普通   ");
    puts("          3.困难   ");
    puts("          4.超难   ");
    puts("          5.退出   ");
    puts("----------------------------");
    choice = getch();
    switch (choice) //难度选项
    {
    case '1':
        speed = 300;
        break;
    case '2':
        speed = 150;
        break;
    case '3':
        speed = 50;
        break;
    case '4':
        speed = 25;
        break;
    case '5':
        choice = 5;
        break;
    default:
        goto aaa;
        break;
    }
}

void end(void)
{
    system("cls");
    printf("总长度:%d \n", snake.length);
    system("pause");
}

void block(int n)
{
    for (int i = 1; i < n; i++)
        printf("■");
    puts("■");
}

void initmap(void)
{
    for (int y = 1; y <= Y_W; y++)
    {
        for (int x = 1; x <= X_L; x++)
        {
            map[x][y] = 0;
        }
    }
}

void re_map(void)
{
    for (int i = 1; i <= snake.length; i++)
    {
        map[snake.x[i]][snake.y[i]] = 1;
    }
}

void drawmap(void)
{
    block(X_L + 2);
    for (int y = 1; y <= Y_W; y++)
    {
        printf("■");
        for (int x = 1; x <= X_L; x++)
        {
            if (snake.x[1] == x && snake.y[1] == y)
                printf("■");
            else if (map[x][y])
                printf("□");
            else if (food.x == x && food.y == y)
                printf("◆");
            else
                printf("  ");
        }
        printf("■\n");
    }
    block(X_L + 2);
}

void initsnake(void) //12 13,12
{
    snake.X = X_L / 2;
    snake.Y = Y_W / 2;

    for (int i = 1; i <= X_L * Y_W; i++)
    {
        snake.x[i] = 0;
        snake.y[i] = 0;
    }
    snake.length = 2;
    snake.x[1] = snake.X;
    snake.y[1] = snake.Y;
    snake.x[2] = X_L / 2 - 1;
    snake.y[2] = Y_W / 2;
}

void food_xy(void)
{
    srand(clock());
    do
    {
        food.x = rand() % X_L + 1;
        food.y = rand() % Y_W + 1;
    } while (map[food.x][food.y]); //随机生成食物并不与蛇重合
}

void keyboardhit(void)
{
    char key = (char)direction;
    int flag = 1;
    if (kbhit())
    {
        key = getch();
    }
    switch ((enum spectrum)key)
    {
    case right:
        if (direction == left)
            flag = 0;
        else
            snake.X++;
        break;
    case left:
        if (direction == right)
            flag = 0;
        else
            snake.X--;
        break;
    case up:
        if (direction == down)
            flag = 0;
        else
            snake.Y--;
        break;
    case down:
        if (direction == up)
            flag = 0;
        else
            snake.Y++;
        break;
    default:
        flag = 0;
        break;
    }
    if (flag)
    {
        direction = ((enum spectrum)key);
        move();
    }
}

void move(void)
{
    if (is_longer == 0 && map[snake.X][snake.Y] != 1) //整体移动蛇身
    {
        for (int i = snake.length; i > 1; i--)
        {
            snake.x[i] = snake.x[i - 1];
            snake.y[i] = snake.y[i - 1];
        }
        snake.x[1] = snake.X;
        snake.y[1] = snake.Y;
    }
    else if (is_longer && map[snake.X][snake.Y] != 1)
    {
        snake.x[snake.length] = snake.x[snake.length - 1];
        snake.y[snake.length] = snake.y[snake.length - 1];
        for (int i = snake.length; i > 1; i--)
        {
            snake.x[i] = snake.x[i - 1];
            snake.y[i] = snake.y[i - 1];
        }
        snake.x[1] = snake.X;
        snake.y[1] = snake.Y;
    }
    else
    {
        gameover = 1;
    }
}

void event(void)
{
    if (snake.X == food.x && snake.Y == food.y) //判断是否碰到食物
    {
        snake.length++;
        is_longer = 1;
        food_xy();
    }
    else
    {
        is_longer = 0;
    }
    if (snake.X > X_L || snake.X < 1 || snake.Y > Y_W || snake.Y < 1) //判断是否撞墙
        gameover = 1;
}

void hide(void) //隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
