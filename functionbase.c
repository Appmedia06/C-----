#define R_MAX 3
#define C_MAX 3

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "game.h"

void play(int *playerscore, int *computerscore, int *key, int *note)
{
    int x, y;
    char board[R_MAX][C_MAX];
    
    clear(board, R_MAX, C_MAX);  
    printboard(board, R_MAX, C_MAX);
    while(1)
    {
        printf("�п�J�z�n���y�Ц�m>");
        scanf("%d%d",&x,&y);
        if(x > R_MAX || y > C_MAX)
        {
            printf("�y�п�J���~! �п�J�d��x[1,%d], y[1,%d]\n", R_MAX, C_MAX);
            fflush(stdin);
            continue;
        }
        if(board[x-1][y-1] != ' ')
        {
            printf("�y�п�J���~! �п�ܨS�U�L����l!\n");
            fflush(stdin);
            continue;
        }
        putintoboard(board, 'O', x-1, y-1);
        printboard(board, R_MAX, C_MAX);
        if(Win(board, R_MAX, C_MAX) == 'O')
        {
            printf("����Ĺ�o�@�^�X!!!\n");
            *playerscore += 1;
            *note = 1;
            return;
        }
        if(Fulled(board, R_MAX, C_MAX))
        {
            printf("����!!!\n");
            *note = 1;
            return;
        }
        computer_play(board, R_MAX, C_MAX);
        printboard(board, R_MAX, C_MAX);
        if(Win(board, R_MAX, C_MAX) == 'X')
        {
            printf("�z��F�@�^�X!!!\n");
            *computerscore += 1;
            *note = 1;
            return;
        }
        if(Fulled(board, R_MAX, C_MAX))
        {
            printf("����!!!\n");
            return;
        }
    }
}
void computer_play(char board[R_MAX][C_MAX], int R, int C)
{
    int x, y;
    search(board, R, C, &x, &y, 'X', 'O');
    printf("�q���U:%d,%d\n",x+1,y+1);
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
        //��u//
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return board[i][0];
        //���u//
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return board[0][i];
        //�׽u//
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
    //�q���M����Ӥ覡���//

    //��"��"���//
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
            puts("���ժ��u���");
            *X = i;
            *Y = key;
            return;
        }
    }
    //�Q��"�C"���//
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
            puts("���վ�u���");
            *X = key;
            *Y = i;
            return;
        }
    }
    //���չ﨤���//
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
        puts("���չ﨤���");
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
        puts("���չ﨤���");
        *X = key;
        *Y = R - key - 1;
        return;
    }

    //�q������a���//

    //��������//
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
            puts("��������");
            *X = i;
            *Y = key;
            return;
        }
    }

    //����C���//
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
            puts("����C���");
            *X = loc;
            *Y = i;
            return;
        }
    }
     
    //����﨤���//
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
        puts("����﨤�u���");
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
        puts("���ժ���﨤�u���");
        *X = key;
        *Y = R - key - 1;
        return;
    }

    //�H���U//
    printf("�q���H���U\n");
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
    printf("�W�h�p�U:\n");
    printf("1.�ѱz����A�ڤ謰O�A�Ĥ謰X\n\n");
    printf("2.�п�J�y��(�e�̬���b�A��̬��a�b)\n");
    printf("�Ҧp:�ڭn��������!�п�J2 2\n\n");
    printf("3.���s���@���u�����\n\n");
    printf("4.�Ĥ��ԤT�Ө�A��Ĺ��T�������\n\n");
    printf("5.�C�@�^�X�����ɡA�Ы�enter��A����\n\n");
    printf("���z�C���r��!\n\n");
}
void totalmenu()
{
    puts("a.�}�l�o���C��  b.�h�X");
}
void menu()
{
    puts("1.�}�l�o�^�X  2.�h�X");
}

void free_data(int *key, int *note, int *playerscore, int *computerscore)
{
    free(key);
    free(note);
    free(playerscore);
    free(computerscore);
}