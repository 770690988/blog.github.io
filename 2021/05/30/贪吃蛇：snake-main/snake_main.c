#include "snake.h"

int main()
{
    srand((unsigned int)time(0));     //生成随机数种子
    int end = 1, result;
    while (end) {
        result = Menu();
        switch (result)
        {
        case 1://开始游戏
            InitMap();
            while (MoveSnake());
            break;
        case 2://帮助信息
            Help();
            break;
        case 3://关于信息
            About();
            break;
        case 0://结束程序
            end = 0;
            break;
        }
    }
}
