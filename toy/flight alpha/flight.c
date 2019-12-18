//���ߣ�ͯ�
//��Ʒ�������ӷ�����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int randN(void);                                                   //���������
int check(int ar[][4], int n);                                     //���δ��������
void over(int ar[][2], int piece[][4], int pos, int color, int n); //��������ײ��
void reset(int ar[][2], int pos);
int work(int piece[][4], int color); //ȷ������
int win(int ar[][4], int color);     //���ʤ��
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
    int board[52];              //�� 1 ���� 2���� 3���� 4
    int condition[52][2] = {0}; //�� 1 ���� 2���� 3���� 4
    //int fly[52]={[4]=4,[17]=1,[30]=2,[43]=3};  // 4-->16, 17-->29, 30-->42, 43-->3
    //int entrance[52]={[10]=2,[23]=3,[36]=4,[49]=1};
    int fly[52] = {0};
    int entrance[52] = {0};
    char player[5] = "0GRYB";
    int piece[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}}; //�̺����
    fly[4] = 4;
    fly[17] = 1;
    fly[30] = 2;
    fly[43] = 3; //������Ӻͷ����
    memset(condition, 0, sizeof(condition));
    printf(" ________________________________________________\n"); //��������
    printf("|                   ������                       |\n");
    printf("|                (ѡ��һ������)                  |\n");
    printf("|                  1.��ʼ                        |\n");
    printf("|                  2.����                        |\n");
    printf("|                  3.˵��                        |\n");
    printf("|                  4.�˳�                        |\n");
    printf(" ================================================\n ");
    putchar('\n');
aaa:
    printf("��ѡ��һ������");
    printf("--> ");
    scanf("%d", &start);
    if (start == 4)
    {
        system("cls");
        printf("��л���棡\n");
    }
    else if (start == 1)
    {
        printf("\n��ѡ����������(1~4)");
        printf("--> ");
        scanf("%d", &number);
        printf("\n�� %d �����棬���� %d ��Ϊ�����(�Զ�)\n", number, 4 - number); //��¼������ͼ���������
        printf("\n�����ͼ�С���\n");
        for (tim = 1; tim <= 25; tim++)
        {
            Sleep(200);
            printf("��");
        }
        printf("\n\n������ɣ���ʼ��Ϸ��\n");
        Sleep(3000);
        system("cls");
        for (i = 0, k = 4; i != 52; i++) //��������
        {
            board[i] = k;
            k++;
            k = (k - 1) % 4 + 1;
        }
        srand((unsigned)time(NULL));
        for (cycle = 1; winner == 0; cycle++) //cycle��¼�ĸ���ҵĻغ�
        {
            cycle = (cycle - 1) % 4 + 1;
            if (cycle == 1)
            {
                system("cls");
                map();
                printf("____________________________�غ� %d______________________________\n", round); //�غ���
                round++;
            }
            printf("\n=============%c==============\n", player[cycle]);
            if (cycle <= number) //�ж��Ƿ�����ң���������Ҳٿأ���������ȫ�Զ�
                system("pause");
            count = randN();
            while (count == 6) //��Ͷ��6���ѭ��ִ��
            {
                printf("%d ��\n", count);
                if ((n = check(piece, cycle - 1)) != -1) //���δ��������
                {
                    piece[cycle - 1][n] = (cycle - 1) * 13;
                    printf("�� %d �����ӳ���\n", n + 1);
                    pos = piece[cycle - 1][n] % 52;
                    over(condition, piece, pos, cycle, k);
                }
                else
                {
                    k = work(piece, cycle); //ȷ���ƶ�������
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += count;
                    printf("�� %d �������ƶ� %d ��,", k + 1, count);
                    pos = piece[cycle - 1][k] % 52;
                    printf("��ǰλ�� %d\n", pos);
                    over(condition, piece, pos, cycle, k);        //�жϺ�ִ�е��Ӻ�ײ��
                    if (cycle == board[pos] && fly[pos] != cycle) //�������
                    {
                        printf("����ͬ������ɫ��ǰ�ƶ�4��,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 4;
                        pos = (pos + 4) % 52;
                        printf("��ǰλ�� %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                        if (fly[pos] == cycle) //������
                        {
                            printf("��������Ծ�㣬�ƶ�12��,");
                            reset(condition, piece[cycle - 1][k] % 52);
                            piece[cycle - 1][k] += 12;
                            pos = (pos + 12) % 52;
                            printf("��ǰλ�� %d\n", pos);
                            over(condition, piece, pos, cycle, k);
                        }
                    }
                    else if (fly[pos] == cycle) //������
                    {
                        printf("��������Ծ�㣬�ƶ�16��,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 16;
                        pos = (pos + 16) % 52;
                        printf("��ǰλ�� %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                    }
                }
                if (cycle <= number)
                    system("pause");
                count = randN();
            }
            if ((k = work(piece, cycle)) < 4) //����������
            {
                printf("%d ��\n", count);
                reset(condition, piece[cycle - 1][k] % 52);
                piece[cycle - 1][k] += count;
                printf("�� %d �������ƶ� %d ��,", k + 1, count);
                pos = piece[cycle - 1][k] % 52;
                printf("��ǰλ�� %d\n", pos);
                over(condition, piece, pos, cycle, k);
                if (cycle == board[pos])
                {
                    printf("����ͬ������ɫ��ǰ�ƶ�4��,");
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += 4;
                    pos = (pos + 4) % 52;
                    printf("��ǰλ�� %d\n", pos);
                    over(condition, piece, pos, cycle, k);
                    if (fly[pos] == cycle)
                    {
                        printf("��������Ծ�㣬�ƶ�12��,");
                        reset(condition, piece[cycle - 1][k] % 52);
                        piece[cycle - 1][k] += 12;
                        pos = (pos + 12) % 52;
                        printf("��ǰλ�� %d\n", pos);
                        over(condition, piece, pos, cycle, k);
                    }
                }
                else if (fly[pos] == cycle)
                {
                    printf("��������Ծ�㣬�ƶ�16��,");
                    reset(condition, piece[cycle - 1][k] % 52);
                    piece[cycle - 1][k] += 16;
                    pos = (pos + 16) % 52;
                    printf("��ǰλ�� %d\n", pos);
                    over(condition, piece, pos, cycle, k);
                }
            }
            else //û�г�������
            {
                printf("%d ��\n", count);
                printf("�޷��ƶ�\n");
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
        printf("-----------------------------------------------------������ ����---------------------------------------------------------------\n");
        printf("����Ϸ���շ�������Ϸģʽ��д,��Ϸ��������\n");
        printf("1.��ɣ���Ͷ��6��ʱ��˳�򽫴�������(-1)�������״̬(0)��������Ͷ���ӣ�������6�������Ͷ��\n");
        printf("2.�ƶ���Ͷ��6��ʱ������ȫ���������״̬ʱ��δͶ��6���������ӽ������״̬ʱ����˳���ƶ�����\n");
        printf("3.���ӣ���������������ͬһ���ڣ��ɵ���һ�𣬳�Ϊ�����ӡ������з�����������ͣ���ڡ����ӡ��Ϸ�ʱ���з�������2�ܵ�������ͬʱ����ͣ��ƺ\n");
        printf("4.���ӣ������ڵ�ͼ����ʱ�����ͣ���ں��Լ���ɫ��ͬ���ӣ�������ǰһ����ͬ��ɫ��������Ծ(��ǰ�ƶ�4��)\n");
        printf("5.���壺�����ƶ�������λ��(�����ڱ��)ʱ�������������ӹ������ƶ�12�񣬷����ƶ�16��\n");
        printf("6.�յ���ʤ���������Ӽ���>=50 ʱ �����е��Ӻ������ж��������Ӽ���>=55ʱ���յ㣬���������ӵ����յ㼴Ϊʤ��\n");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        goto aaa;
    }
    else if (start == 3)
    {
        printf("\n");
        printf("����\n");
        printf("\n");
        goto aaa;
    }
    else
    {
        printf("�Ƿ����룬������1~4\n");
        goto aaa;
    }
    if (winner != 0)
    {
        printf("\nʤ������ %c", player[winner]);
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
            printf("����%c������\n", player[gryb]);
            printf("�з��뼺����������\n");
            piece[color - 1][n] = -1;
            ar[pos][0] = ar[pos][1] = 0;
            for (j = 3; j > -1; j--)
                if (piece[gryb - 1][j] % 52 == pos)
                    piece[gryb - 1][j] = -1;
        }
        else if (ar[pos][1] == 1)
        {
            printf("����%c������\n", player[gryb]);
            printf("�з���������\n");
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
        printf("�������Լ�����\n");
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
