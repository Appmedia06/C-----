#define R_MAX 3
#define C_MAX 3

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "game.h"

void play(int *playerscore, int *computerscore, int *key, int *note)
{
    int x,y;
    char board[R_MAX][C_MAX];
    
    clear(board, R_MAX, C_MAX);  
    printboard(board, R_MAX, C_MAX);
    while(1)
    {
        printf("請輸入您要的座標位置>");
        scanf("%d%d",&x,&y);
        if(x > R_MAX || y > C_MAX)
        {
            printf("座標輸入錯誤! 請輸入範圍x[1,%d], y[1,%d]\n", R_MAX, C_MAX);
            fflush(stdin);
            continue;
        }
        if(board[x-1][y-1] != ' ')
        {
            printf("座標輸入錯誤! 請選擇沒下過的位子!\n");
            fflush(stdin);
            continue;
        }
        putintoboard(board, 'O', x-1, y-1);
        printboard(board, R_MAX, C_MAX);
        if(Win(board, R_MAX, C_MAX) == 'O')
        {
            printf("恭喜贏得一回合!!!\n");
            *playerscore += 1;
            *note = 1;
            return;
        }
        if(Fulled(board, R_MAX, C_MAX))
        {
            printf("平手!!!\n");
            *note = 1;
            return;
        }
        computer_play(board, R_MAX, C_MAX);
        printboard(board, R_MAX, C_MAX);
        if(Win(board, R_MAX, C_MAX) == 'X')
        {
            printf("您輸了一回合!!!\n");
            *computerscore += 1;
            *note = 1;
            return;
        }
        if(Fulled(board, R_MAX, C_MAX))
        {
            printf("平手!!!\n");
            return;
        }
    }
}
void computer_play(char board[R_MAX][C_MAX], int R, int C)
{
    int x, y;
    search(board, R, C, &x, &y, 'X', 'O');
    printf("電腦下:%d,%d\n",x+1,y+1);
    putintoboard(board, 'X', x, y);
}

void printboard(char board[R_MAX][C_MAX], int R, int C)
{
    for(int j=0; j<R; j++)
    {
        printf(" ---");
    }
    printf("\n");
    for(int i=0; i<C; i++)
    {
        printf("|");
        for(int j=0; j<C; j++)
        {
            printf(" %c",board[i][j]);
            printf(" |");
        }
        printf("\n");
        if(i<R)
        {
            for(int j=0; j<R; j++)
                printf(" ---");
        }
        printf("\n");
    }
}
void clear(char board[R_MAX][C_MAX], int R, int C)
{
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            board[i][j] = ' ';
}
void putintoboard(char board[R_MAX][C_MAX], char ch, int x, int y)
{
    board[x][y] = ch;
}

char Win(char board[R_MAX][C_MAX], int R, int C)
{
    for(int i=0; i<R; i++)
    {
        //橫線//
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return board[i][0];
        //直線//
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return board[0][i];
        //斜線//
        if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
            return board[1][1];
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
            return board[0][2];
    }
}
int Fulled(char board[R_MAX][C_MAX], int R, int C)
{
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            if(board[i][j] == ' ')
                return 0;
    return 1;
}

void search(char board[R_MAX][C_MAX], int R, int C, int *X, int *Y, char ch, char ch2)
{
    //電腦尋找獲勝方式獲勝//

    //使"行"獲勝//
    for(int i=0; i<R; i++) 
    {   
        int count = 0;
        int key = -1;
        for(int j = 0; j < C; j++)
        {
            if(board[i][j] == ch)
                count++;
            else if(board[i][j] == ' ')
                    key = j; 
        }
        if(count == 2 && board[i][key] == ' ' && key != -1)
        {
            puts("嘗試直線獲勝");
            *X = i;
            *Y = key;
            return;
        }
    }
    //想使"列"獲勝//
    for(int i=0; i<R; i++)
    {
        int count = 0;
        int key = -1;
        for(int j=0; j<C; j++)
        {
            if(board[j][i] == ch)
                count++;
            else if(board[j][i] == ' ')
                key = j;
        }
        if(count == 2 && board[key][i] == ' ' && key != -1)
        {
            puts("嘗試橫線獲勝");
            *X = key;
            *Y = i;
            return;
        }
    }
    //嘗試對角獲勝//
    int key = -1;
    int count = 0;
    for(int i=0; i<R; i++)
    {
        if(board[i][i] == ch)
            count++;
        else if(board[i][i] == ' ')
            key = i;
    }
    if(count >=2 && key != -1)
    {
        puts("嘗試對角獲勝");
        *X = key;
        *Y = key;
        return;
    }
    key = -1;
    count = 0;
    for(int i=0; i<R; i++)
    {
        if(board[i][R-i-1] == ch)
            count++;
        else if(board[i][R-i-1] == ' ')
            key = i;
    }
    if(count >=2 && key != -1)
    {
        puts("嘗試對角獲勝");
        *X = key;
        *Y = R - key - 1;
        return;
    }

    //電腦阻止玩家獲勝//

    //阻止行獲勝//
    for(int i = 0; i < R; i++)
    {
        int count = 0;
        int key = -1;
        for(int j = 0; j < C; j++)
        {
            if(board[i][j] == ch2)
                count++;
            else if(board[i][j] == ' ')
                key = j;
        }
        if(count == 2 && key != -1)
        {
            puts("阻止行獲勝");
            *X = i;
            *Y = key;
            return;
        }
    }

    //阻止列獲勝//
    for(int i = 0; i < R; i++)
    {
        int count = 0;
        int loc = -1;
        for(int j = 0; j < C; j++)
        {
            if(board[j][i] == ch2)
                count++;
            else if(board[j][i] == ' ')
                loc = j;
        }
        if(count == 2 && loc != -1)
        {
            puts("阻止列獲勝");
            *X = loc;
            *Y = i;
            return;
        }
    }
     
    //阻止對角獲勝//
    key = -1;
    count = 0;
    for(int i = 0; i < R; i++)
    {
        if(board[i][i] == ch2)
            count++;
        else if(board[i][i] == ' ')
            key = i;
    }
    if(count == 2 && key != -1)
    {
        puts("阻止對角線獲勝");
        *X = key;
        *Y = key;
        return; 
    }
    key = -1;
    count = 0;
    for(int i = 0; i < R; i++)
    {
        if(board[i][R - i - 1] == ch2)
            count ++;
        else if(board[i][R - i -1] == ' ')
            key = i;
    }
    if(count == 2 && key != -1)
    {
        puts("嘗試阻止對角線獲勝");
        *X = key;
        *Y = R - key - 1;
        return;
    }

    //隨機下//
    printf("電腦隨機下\n");
    srand((unsigned int)time(NULL));
    while(1)
    {
        int x = rand() % R_MAX;
        int y = rand() % C_MAX;
        if(board[x][y] == ' ')
        {
            *X = x;
            *Y = y;
            return;
        }
    }
}

void printrule()
{
    printf("規則如下:\n");
    printf("1.由您先攻，我方為O，敵方為X\n\n");
    printf("2.請輸入座標(前者為橫軸，後者為縱軸)\n");
    printf("例如:我要中間那格!請輸入2 2\n\n");
    printf("3.先連成一條線者獲勝\n\n");
    printf("4.採五戰三勝制，先贏到三分者獲勝\n\n");
    printf("5.每一回合結束時，請按enter鍵，謝謝\n\n");
    printf("祝您遊玩愉快!\n\n");
}
void totalmenu()
{
    puts("a.開始這場遊戲  b.退出");
}
void menu()
{
    puts("1.開始這回合  2.退出");
}

void free_data(int *key, int *note, int *playerscore, int *computerscore)
{
    free(key);
    free(note);
    free(playerscore);
    free(computerscore);
}
