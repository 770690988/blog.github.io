#include "snake.h"

int main()
{
    srand((unsigned int)time(0));     //�������������
    int end = 1, result;
    while (end) {
        result = Menu();
        switch (result)
        {
        case 1://��ʼ��Ϸ
            InitMap();
            while (MoveSnake());
            break;
        case 2://������Ϣ
            Help();
            break;
        case 3://������Ϣ
            About();
            break;
        case 0://��������
            end = 0;
            break;
        }
    }
}
