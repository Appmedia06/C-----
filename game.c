#define R_MAX 3
#define C_MAX 3

#include "stdio.h"
#include "stdlib.h"
#include "game.h"
#include "functionbase.c"


int main()
{
    printf("///////////////���e�e:�H�u���z\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    printrule();

    while(1)
    {
        fflush(stdin);
        char totaloption;


        int* key_ptr; //�P�_�O�_�������ԤT��
        int* note_ptr; //�P�_�O�_���Lmenu
        int* playerscore_ptr; //���a���
        int* computerscore_ptr; //�q�����
        int* set; //��������
        

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
                                printf("��%d�^�X\n", count);
                            if(count > 4)
                                printf("�̫�@�^�X!\n");
                            play(playerscore_ptr, computerscore_ptr, key_ptr , note_ptr);
                            free(option);
                            if(*playerscore_ptr == 3)
                            {   
                                printf("�C�������A��Ƭ�%d : %d\n", *playerscore_ptr, *computerscore_ptr);
                                printf("�������!!!\n");
                                break;
                            }
                            if(*computerscore_ptr == 3)
                            {   
                                printf("�C�������A��Ƭ�%d : %d\n", *playerscore_ptr, *computerscore_ptr);
                                printf("�q�����!!!\n");
                                break;
                            }
                            if(*playerscore_ptr < 3 || *computerscore_ptr < 3)
                                printf("�ثe���:%d:%d\n",*playerscore_ptr, *computerscore_ptr);    
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
                    printf("��J���~!! �Э��s��J\n");
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
            printf("��J���~!! �Э��s��J\n");
            continue;
        }
    }
}