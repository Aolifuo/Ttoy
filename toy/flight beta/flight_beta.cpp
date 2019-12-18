#include <bits/stdc++.h>
#include <windows.h>
using namespace std; //0->none,1->green,2->red,3->yellow,4->blue
static int map[52] = {0};
static int block_col[52];
static int fly_pos[52] = {0};
static int final[1 + 4][5] = {0};
class flight
{
    friend int collision(flight *, int, int);

public:
    int _step[4 + 1] = {0};
    void get_color(int col) { color = col; }
    int standby()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] == -1)
                return i;
        }
        return -1;
    }
    int available()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] != -1 && is_end[i] == 0)
                return i;
        }
        return 0;
    }
    int number(int p)
    {
        int count = 0;
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] == p)
                count++;
        }
        return count;
    }
    void reset(int n)
    {
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] == n)
            {
                pos[i] = -1;
                _step[i] = 0;
            }
        }
        sync_to_map();
    }
    void take_off(int n) { pos[n] = (color - 1) * 13; }
    void jump(int n)
    {
        pos[n] = (pos[n] + 4) % 52;
        _step[n] += n;
        disabled(n);
        end_judge();
    }
    void fly(int n)
    {
        pos[n] = (pos[n] + 12) % 52;
        _step[n] += n;
        disabled(n);
        end_judge();
    }
    int go(int step, int &c)
    {
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] > -1)
            {
                c = i;
                pos[i] = (pos[i] + step) % 52;
                _step[i] += step;
                disabled(i);
                end_judge();
                return pos[i];
            }
            else if (pos[i] == -2 && is_end[i] != 1)
            {
                c = i;
                ::final[color][_step[i] - 50] = 0;
                _step[i] += step;
                if (_step[i] > 54)
                    _step[i] = 54;
                ::final[color][_step[i] - 50] = color;
                end_judge();
                return pos[i];
            }
        }
        return -1;
    }
    void sync_to_map()
    {
        clear();
        for (int i = 1; i <= 4; i++)
        {
            if (pos[i] >= 0)
            {
                ::map[pos[i]] = color;
            }
        }
    }
    bool is_win()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (!is_end[i])
                return false;
        }
        return true;
    }

private:
    int color;
    int pos[4 + 1] = {-1, -1, -1, -1, -1};

    int is_end[4 + 1] = {0};
    void clear()
    {
        for (auto &c : ::map)
        {
            if (c == color)
                c = 0;
        }
    }
    void end_judge()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (_step[i] >= 54)
            {
                is_end[i] = 1;
                pos[i] = -2;
                _step[i] = 54;
                sync_to_map();
            }
        }
    }
    void disabled(int n)
    {
        if (_step[n] >= 50)
        {
            pos[n] = -2;
            if (_step[n] <= 54)
            {
                ::final[color][_step[n] - 50] = color;
            }
            sync_to_map();
        }
    }
};
flight player[1 + 4];
int dice();
int collision(flight *, int, int);
void print_map();

int main()
{
    int point, round, temp, temp_;
    extern flight player[4 + 1];
    for (int k = 1; k <= 4; k++)
    {
        player[k].get_color(k);
    }
    for (int i = 0, k = 4; i != 52; i++)
    {
        block_col[i] = k;
        k++;
        k = (k - 1) % 4 + 1;
    }
    fly_pos[4] = 4;
    fly_pos[17] = 1;
    fly_pos[30] = 2;
    fly_pos[43] = 3;
    srand((unsigned)time(NULL));
    for (round = 1; !player[round].is_win(); round++, round = (round - 1) % 4 + 1)
    {
    dice:
        if ((point = dice()) == 6)
        {
            if ((temp = player[round].standby()) == -1)
                goto loop;
            else
            {
                player[round].take_off(temp);
                collision(player, round, (round - 1) * 13);
                goto dice;
            }
        }
        else
        {
            if (temp = player[round].available())
                goto loop;
            else
                continue;
        }
    loop:
        temp = player[round].go(point, temp_);
        print_map();
        if (temp < 0)
        {
            if (point == 6 && !player[round].is_win())
                goto dice;
            else if (player[round].is_win())
                goto end;
            else
                continue;
        }
        while (1)
        {
            if (collision(player, round, temp) == 2)
            {
                if (point == 6)
                    goto dice;
                else
                    break;
            }
            else
            {
                if (round == block_col[temp])
                {
                    player[round].jump(temp_);
                    if (round == fly_pos[temp])
                        player[round].fly(temp_);
                    collision(player, round, temp);
                    break;
                }
                else
                {
                    if (round == fly_pos[temp])
                    {
                        player[round].fly(temp_);
                        player[round].jump(temp_);
                        collision(player, round, temp);
                        break;
                    }
                    else
                    {
                        player[round].sync_to_map();
                        print_map();
                        if (point == 6)
                            goto dice;
                        else
                            break;
                    }
                }
            }
        }
    }
end:
    print_map();
    cout << round << "win" << endl;
    system("pause");
    return 0;
}

int dice()
{
    int n = rand() % 6 + 1;
    return n;
}
int collision(flight *item, int color, int pos)
{
    if (::map[pos] != color)
    {
        if (item[::map[pos]].number(pos) == 1)
        {
            item[::map[pos]].reset(pos);
            print_map();
            return 1;
        }
        else if (item[::map[pos]].number(pos) == 2)
        {
            item[::map[pos]].reset(pos);
            item[color].reset(pos);
            print_map();
            return 2;
        }
        else if (::map[pos] == 0)
        {
            item[color].sync_to_map();
            print_map();
            return 0;
        }
    }
    else
    {
        item[color].sync_to_map();
        print_map();
        return 0;
    }
    return 0;
}
void print_map()
{
    extern int map[52];
    extern int final[1 + 4][5];
    extern flight player[1 + 4];
    system("cls");
    ostringstream out;
    out
        << player[1]._step[4] << " " << player[1]._step[3] << "                       " << player[2]._step[3] << " " << player[2]._step[4] << '\n'
        << player[1]._step[2] << " " << player[1]._step[1] << "                       " << player[2]._step[1] << " " << player[2]._step[2] << '\n'
        << "        " << map[7] << " " << map[8] << " " << map[9] << " " << map[10] << " " << map[11] << " " << map[12] << " " << map[13] << '\n'
        << "        " << map[6] << "     " << final[2][0] << "     " << map[14] << '\n'
        << "        " << map[5] << "     " << final[2][1] << "     " << map[15] << '\n'
        << map[0] << " " << map[1] << " " << map[2] << " " << map[3] << " " << map[4] << "     " << final[2][2] << "     " << map[16] << " " << map[17] << " " << map[18] << " " << map[19] << " " << map[20] << '\n'
        << map[51] << "             " << final[2][3] << "             " << map[21] << '\n'
        << map[50] << "             " << final[2][4] << "             " << map[22] << '\n'
        << map[49] << " " << final[1][0] << " " << final[1][1] << " " << final[1][2] << " " << final[1][3] << " " << final[1][4] << "       " << final[3][4] << " " << final[3][3] << " " << final[3][2] << " " << final[3][1] << " " << final[3][0] << " " << map[23] << '\n'
        << map[48] << "             " << final[4][4] << "             " << map[24] << '\n'
        << map[47] << "             " << final[4][3] << "             " << map[25] << '\n'
        << map[46] << " " << map[45] << " " << map[44] << " " << map[43] << " " << map[42] << "     " << final[4][2] << "     " << map[30] << " " << map[29] << " " << map[28] << " " << map[27] << " " << map[26] << '\n'
        << "        " << map[41] << "     " << final[4][1] << "     " << map[31] << '\n'
        << "        " << map[40] << "     " << final[4][0] << "     " << map[32] << '\n'
        << "        " << map[39] << " " << map[38] << " " << map[37] << " " << map[36] << " " << map[35] << " " << map[34] << " " << map[33] << '\n'
        << player[4]._step[2] << " " << player[4]._step[1] << "                       " << player[3]._step[1] << " " << player[3]._step[2] << '\n'
        << player[4]._step[4] << " " << player[4]._step[3] << "                       " << player[3]._step[3] << " " << player[3]._step[4];
    cout << out.str() << endl;
    Sleep(100);
}