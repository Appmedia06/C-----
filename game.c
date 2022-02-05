#define R_MAX 3
#define C_MAX 3

#include "stdio.h"
#include "stdlib.h"
#include "game.h"
#include "functionbase.c"


int main()
{
    printf("///////////////圈圈叉叉:人工智慧\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    printrule();

    while(1)
    {
        fflush(stdin);
        char totaloption;


        int* key_ptr; //判斷是否打完五戰三勝
        int* note_ptr; //判斷是否重印menu
        int* playerscore_ptr; //玩家比數
        int* computerscore_ptr; //電腦比數
        int* set; //滿足條件
        

        key_ptr = (int *) malloc(sizeof(int)); 
        note_ptr = (int *) malloc(sizeof(int));
        set = (int *) malloc(sizeof(int));

        playerscore_ptr = (int *) malloc(sizeof(int));
        computerscore_ptr = (int *) malloc(sizeof(int));

        *set = 0;
        *key_ptr = 1;
        *note_ptr = 0;

        *playerscore_ptr = 0;
        *computerscore_ptr = 0;

        totalmenu();
        totaloption = getchar();
        if(totaloption == 'a')
        {
            if(*note_ptr == 0)
                menu();
            int count=0;

            while(*key_ptr)
            {
                fflush(stdin);
                if(*note_ptr != 0)
                {   
                    menu();
                }

                char* option;
                option = (char *) malloc(sizeof(char));
                scanf("%c",&*option);
                
                if(*option == '1' || *option == '2')
                {
                    switch(*option)
                    {
                        case '1':
                            ++count;
                            if(count <= 4)
                                printf("第%d回合\n", count);
                            if(count > 4)
                                printf("最後一回合!\n");
                            play(playerscore_ptr, computerscore_ptr, key_ptr , note_ptr);
                            free(option);
                            if(*playerscore_ptr == 3)
                            {   
                                printf("遊戲結束，比數為%d : %d\n", *playerscore_ptr, *computerscore_ptr);
                                printf("恭喜獲勝!!!\n");
                                break;
                            }
                            if(*computerscore_ptr == 3)
                            {   
                                printf("遊戲結束，比數為%d : %d\n", *playerscore_ptr, *computerscore_ptr);
                                printf("電腦獲勝!!!\n");
                                break;
                            }
                            if(*playerscore_ptr < 3 || *computerscore_ptr < 3)
                                printf("目前比數:%d:%d\n",*playerscore_ptr, *computerscore_ptr);    
                        case '2':
                            *key_ptr = -1;
                            break;
                    }
                    if(*option == '2')
                    {
                        break;
                    }
                    if(*playerscore_ptr == 3 || *computerscore_ptr == 3)
                    {
                        *set = 1;
                        free_data(key_ptr, note_ptr, playerscore_ptr, computerscore_ptr);
                        break;
                    }
                }
                else
                {
                    printf("輸入錯誤!! 請重新輸入\n");
                    *note_ptr = 1;
                    continue;
                }
            }
        }
        if(totaloption == 'b')
        {
            return 0;
        }
        if((totaloption != 'a' || totaloption != 'b') && *set == 0)
        {
            printf("輸入錯誤!! 請重新輸入\n");
            continue;
        }
    }
}