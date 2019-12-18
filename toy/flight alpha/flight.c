//作者：童楠
//作品：不可视飞行棋
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int randN(void);                                                   //生成随机数
int check(int ar[][4], int n);                                     //检测未出发棋子
void over(int ar[][2], int piece[][4], int pos, int color, int n); //检测迭子与撞子
void reset(int ar[][2], int pos);
int work(int piece[][4], int color); //确定走棋
int win(int ar[][4], int color);     //检测胜利
void map(void);

int main(void)
{
    int i, k, r, n, pos, tim;
    int gryb;
    int start;
    int number;
    int cycle;
    int round = 1;
    int winner = 0;
    int count;
    int board[52];              //绿 1 ，红 2，黄 3，蓝 4
    int condition[52][2] = {0}; //绿 1 ，红 2，黄 3，蓝 4
    //int fly[52]={[4]=4,[17]=1,[30]=2,[43]=3};  // 4-->16, 17-->29, 30-->42, 43-->3
    //int entrance[52]={[10]=2,[23]=3,[36]=4,[49]=1};
    int fly[52] = {0};
    int entrance[52] = {0};
    char player[5] = "0GRYB";
    int piece[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}}; //绿红黄蓝
    fly[4] = 4;
    fly[17] = 1;
    fly[30] = 2;
    fly[43] = 3; //标记跳子和飞棋点
    memset(condition, 0, sizeof(condition));
    printf(" ________________________________________________\n"); //交互界面
    printf("|                   飞行棋                       |\n");
    printf("|                (选择一个数字)                  |\n");
    printf("|                  1.开始                        |\n");
    printf("|                  2.帮助                        |\n");
    printf("|                  3.说明                        |\n");
    printf("|                  4.退出                        |\n");
    printf(" ================================================\n ");
    putchar('\n');
aaa:
    printf("请选择一个数字");
    printf("--> ");
    scanf("%d", &start);
    if (start == 4)
    {
        system("cls");
        printf("感谢游玩！\n");
    }
    else if (start == 1)
    {
        printf("\n请选择游玩人数(1~4)");
        printf("--> ");
        scanf("%d", &number);
        printf("\n共 %d 人游玩，还有 %d 个为计算机(自动)\n", number, 4 - number); //记录玩家数和计算机玩家数
        printf("\n载入地图中……\n");
        for (tim = 1; tim <= 25; tim++)
        {
            Sleep(200);
            printf("■");
        }
        printf("\n\n载入完成，开始游戏！\n");
        Sleep(3000);
        system("cls");
        for (i = 0, k = 4; i != 52; i++) //构建棋盘
        {
            board[i] = k;
            k++;
            k = (k - 1) % 4 + 1;
        }
        srand((unsigned)time(NULL));
        for (cycle = 1; winner == 0; cycle++) //cycle记录哪个玩家的回合
        {
            cycle = (cycle - 1) % 4 + 1;
            if (cycle == 1)
            {
                system("cls");
                map();
                printf("____________________________回合 %d______________________________\n", round); //回合数
                round++;
            }
            printf("\n=============%c==============\n", player[cycle]);
            if (cycle <= number) //判断是否是玩家，若是由玩家操控，若不是则全自动
                system("pause");
            count = randN();
            while (count == 6) //若投掷6点可循环执行
            {
                printf("%d 点\n", count);
                if ((n = check(piece, cycle - 1)) != -1) //检测未出发棋子
                {
                    piece[cycle - 1][n] = (cycle - 1) * 13;
                    printf("第 %d 个棋子出来\n", n + 1);
                    pos = piece[cycle - 1][n] % 52;
                    over(condition, piece, pos, cycle, k);
                }
                else
                {
                    k = work(piece, cycle); //确定移动的棋子
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += count;
                    printf("第 %d 个棋子移动 %d 格,", k + 1, count);
                    pos = piece[cycle - 1][k] % 52;
                    printf("当前位置 %d\n", pos);
                    over(condition, piece, pos, cycle, k);        //判断和执行迭子和撞子
                    if (cycle == board[pos] && fly[pos] != cycle) //检测跳子
                    {
                        printf("遇到同样的颜色向前移动4格,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 4;
                        pos = (pos + 4) % 52;
                        printf("当前位置 %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                        if (fly[pos] == cycle) //检测飞棋
                        {
                            printf("遇到了跳跃点，移动12格,");
                            reset(condition, piece[cycle - 1][k] % 52);
                            piece[cycle - 1][k] += 12;
                            pos = (pos + 12) % 52;
                            printf("当前位置 %d\n", pos);
                            over(condition, piece, pos, cycle, k);
                        }
                    }
                    else if (fly[pos] == cycle) //检测飞棋
                    {
                        printf("遇到了跳跃点，移动16格,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 16;
                        pos = (pos + 16) % 52;
                        printf("当前位置 %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                    }
                }
                if (cycle <= number)
                    system("pause");
                count = randN();
            }
            if ((k = work(piece, cycle)) < 4) //检测出发棋子
            {
                printf("%d 点\n", count);
                reset(condition, piece[cycle - 1][k] % 52);
                piece[cycle - 1][k] += count;
                printf("第 %d 个棋子移动 %d 格,", k + 1, count);
                pos = piece[cycle - 1][k] % 52;
                printf("当前位置 %d\n", pos);
                over(condition, piece, pos, cycle, k);
                if (cycle == board[pos])
                {
                    printf("遇到同样的颜色向前移动4格,");
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += 4;
                    pos = (pos + 4) % 52;
                    printf("当前位置 %d\n", pos);
                    over(condition, piece, pos, cycle, k);
                    if (fly[pos] == cycle)
                    {
                        printf("遇到了跳跃点，移动12格,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 12;
                        pos = (pos + 12) % 52;
                        printf("当前位置 %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                    }
                }
                else if (fly[pos] == cycle)
                {
                    printf("遇到了跳跃点，移动16格,");
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += 16;
                    pos = (pos + 16) % 52;
                    printf("当前位置 %d\n", pos);
                    over(condition, piece, pos, cycle, k);
                }
            }
            else //没有出发棋子
            {
                printf("%d 点\n", count);
                printf("无法移动\n");
            }
            winner = win(piece, cycle);
            if (cycle == 4)
                system("pause");
            else
                Sleep(1000);
        }
    }
    else if (start == 2)
    {
        printf("-----------------------------------------------------飞行棋 帮助---------------------------------------------------------------\n");
        printf("本游戏按照飞行棋游戏模式编写,游戏规则如下\n");
        printf("1.起飞：当投掷6点时按顺序将待定棋子(-1)进入起飞状态(0)，并继续投骰子，若连续6点可连续投掷\n");
        printf("2.移动：投掷6点时且棋子全部进入起飞状态时或未投掷6点且有棋子进入起飞状态时，按顺序移动棋子\n");
        printf("3.迭子：己方的棋子走至同一格内，可迭在一起，称为“迭子”。当敌方的棋子正好停留在“迭子”上方时，敌方棋子与2架迭子棋子同时返回停机坪\n");
        printf("4.跳子：棋子在地图行走时，如果停留在和自己颜色相同格子，可以向前一个相同颜色格子作跳跃(向前移动4格)\n");
        printf("5.飞棋：棋子移动到特殊位置(程序内标记)时，若棋子是跳子过来的移动12格，否则移动16格\n");
        printf("6.终点与胜利：当棋子计数>=50 时 不再有迭子和跳子判定，当棋子计数>=55时则到终点，当所有棋子到达终点即为胜利\n");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        goto aaa;
    }
    else if (start == 3)
    {
        printf("\n");
        printf("暂无\n");
        printf("\n");
        goto aaa;
    }
    else
    {
        printf("非法输入，请输入1~4\n");
        goto aaa;
    }
    if (winner != 0)
    {
        printf("\n胜利者是 %c", player[winner]);
    }
    system("pause");
    return 0;
}

int randN(void)
{
    int n;
    n = rand() % 6 + 1;
    return n;
}
int check(int ar[][4], int n)
{
    int i, k;
    int r = -1;
    for (i = 0; i != 4; i++)
    {
        if (ar[n][i] == -1)
        {
            r = i;
            break;
        }
    }
    return r;
}
void over(int ar[][2], int piece[][4], int pos, int color, int n)
{
    int i, j;
    char player[5] = "0GRYB";
    int gryb = ar[pos][0];
    if (piece[gryb - 1][j] >= (gryb - 1) * 13 + 50)
        return;
    if (color != gryb)
    {
        if (ar[pos][1] >= 2)
        {
            printf("遇到%c方迭子\n", player[gryb]);
            printf("敌方与己方棋子重置\n");
            piece[color - 1][n] = -1;
            ar[pos][0] = ar[pos][1] = 0;
            for (j = 3; j > -1; j--)
                if (piece[gryb - 1][j] % 52 == pos)
                    piece[gryb - 1][j] = -1;
        }
        else if (ar[pos][1] == 1)
        {
            printf("遇到%c方棋子\n", player[gryb]);
            printf("敌方棋子重置\n");
            ar[pos][0] = color;
            ar[pos][1] = 1;
            for (j = 3; j > -1; j--)
                if (piece[gryb - 1][j] % 52 == pos)
                    piece[gryb - 1][j] = -1;
        }
        else
        {
            ar[pos][0] = color;
            ar[pos][1]++;
        }
    }
    else
    {
        printf("你遇到自己棋子\n");
        ar[pos][1]++;
    }
}
void reset(int ar[][2], int pos)
{
    ar[pos][1]--;
    if (ar[pos][1] == 0)
        ar[pos][0] = 0;
}
int work(int piece[][4], int color)
{
    int i;
    for (i = 0; i != 4; i++)
        if (piece[color - 1][i] > -1 && piece[color - 1][i] < (color - 1) * 13 + 55)
        {
            break;
        }
    return i;
}
int win(int ar[][4], int color)
{
    int winner, i, k;
    for (i = 0, k = 0; i != 4; i++)
    {
        if (ar[color - 1][i] >= (color - 1) * 13 + 55)
            k++;
    }
    if (k == 4)
        winner = color;
    else
        winner = 0;
    return winner;
}
void map(void)
{
    printf("\n");
    printf("1 1     1 4 3 2 1 4 3\n");
    printf("1 1     2     2     2\n");
    printf("        3     2     1\n");
    printf("4 3 2 1 4-----2-----4 3 2 1 4\n");
    printf("1       |     2     |       3\n");
    printf("2       |     2     |       2\n");
    printf("3 3 3 3 3 3       3 3 3 3 3 1\n");
    printf("4       |     2     |       4\n");
    printf("1       |     2     |       3\n");
    printf("2 3 4 1 2-----2-----2 3 4 1 2\n");
    printf("        3     2     1\n");
    printf("        4     2     4\n");
    printf("        1 2 3 4 1 2 3\n");
    printf("\n");
}
