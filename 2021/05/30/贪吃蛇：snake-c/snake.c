#include "snake.h"

// 全局变量
Snake snake; //定义蛇结构体变量
Food food;   //定义食物结构体变量
char now_Dir = RIGHT; //当前蛇头方向
char direction = RIGHT; //预期蛇头方向

int Menu()
{
    GotoXY(40, 12);   //定位光标的位置
    printf("欢迎来到贪吃蛇小游戏");
    GotoXY(43, 14);
    printf("1. 开始游戏");
    GotoXY(43, 16);
    printf("2. 帮助");
    GotoXY(43, 18);
    printf("3. 关于");
    GotoXY(43, 20);
    printf("其他任意键退出游戏");
    Hide();    //隐藏光标
    char ch;
    int result = 0;
    ch = _getch();
    switch (ch)
    {
    case '1': result = 1; break;
    case '2': result = 2; break;
    case '3': result = 3; break;
    }
    system("cls");
    return result;
}

//光标定位函数
void GotoXY(int x, int y)
{
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

//隐藏光标
void Hide()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
    SetConsoleCursorInfo(hout, &cor_info);//隐藏光标

}

void About()
{
    GotoXY(30, 12);
    printf("杭州电子科技大学--程序设计综合实践作业");
    GotoXY(43, 14);
    printf("贪吃蛇-控制台游戏");
    GotoXY(43, 16);
    printf("按任意键返回上级菜单");
    Hide();    //隐藏光标
    char ch = _getch();
    system("cls");
}

void Help()
{
    GotoXY(40, 12);
    printf("w 上                      ");
    GotoXY(40, 14);
    printf("s 下                      ");
    GotoXY(40, 16);
    printf("a 左                      ");
    GotoXY(40, 18);
    printf("d 右                      ");
    GotoXY(45, 22);
    printf("按任意键返回上级菜单      ");
    char ch = _getch();
    system("cls");
}

void InitMap()
{
    Hide();   //隐藏光标
    //设置蛇头位置在地图的中心
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake. snakeNode[0].y); //光标移动到蛇头位置
    printf("@"); //蛇头
    snake.length = 3; //初始长度
    snake.speed = 250; //初始速度
    now_Dir = RIGHT; // 当前蛇头的朝向

    //显示蛇的身体
    for (int i = 1; i < snake.length; i++) {
        //设置蛇身的纵坐标位置和蛇头位置相同
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
        printf("*");
    }

    //生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("-");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("-");

    }
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GotoXY(0, i);
        printf("|");
        GotoXY(MAP_WIDTH - 1, i);
        printf("|");
    }
    PrintFood();  //生成食物
    GotoXY(50, 5);
    printf("当前得分：0");
}


void PrintFood()
{
    int flag = 1;
    while (flag) {
        flag = 0;

        //生成食物的随机坐标
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物的位置能否而后蛇的位置重叠，如果重叠则重新设置食物的位置
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("o"); //此处的食物用o来表示
}


int MoveSnake()
{
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1]; //记录蛇尾
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("*");

    //响应键盘的操作
    if (_kbhit()) {
        direction = _getch();
        switch (direction)
        {
        case UP:
            if (now_Dir != DOWN)
                now_Dir = direction;
            break;
        case DOWN:
            if (now_Dir != UP)
                now_Dir = direction;
            break;
        case RIGHT:
            if (now_Dir != LEFT)
                now_Dir = direction;
            break;
        case LEFT:
            if (now_Dir != RIGHT)
                now_Dir = direction;
            break;
        }
    }

    switch (now_Dir)
    {
    case UP:snake.snakeNode[0].y--; break; //上移
    case DOWN:snake.snakeNode[0].y++; break; //下移
    case LEFT:snake.snakeNode[0].x--; break; //左移
    case RIGHT:snake.snakeNode[0].x++; break; //右移
    }

    //打印蛇头
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        snake.length++; //吃到食物蛇长加一
        flag = 1; //1表示吃到食物
        snake.snakeNode[snake.length - 1] = temp;  // 吃到食物，蛇尾加一节
    }
    //输出蛇此时的状态
    //没吃到食物的时候，在原来的蛇尾打印一个空格，去掉原来的蛇尾、
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    }
    else {
        PrintFood();
        GotoXY(50, 5);
        printf("当前得分：%d", snake.length - 3);  //打印得分，得分为蛇长减3
    }

    //判断是否死亡
    if (!IsCorrect()) {
        system("cls");
        GotoXY(45, 14);
        printf("最终得分：%d", snake.length - 3);
        GotoXY(45, 16);
        printf("游戏结束！"); 
        GotoXY(45, 18);
        printf("按任意键返回主菜单");
            char c = _getch();
        system("cls");
        return 0;
    }

    //调整速度
    SpeedControl();
    Sleep(snake.speed);
    return 1;
}

int IsCorrect()
{
    if (snake.snakeNode[0].x <= 0 || snake.snakeNode[0].y <= 0 || snake.snakeNode[0].x >= MAP_WIDTH - 1 || snake.snakeNode[0].y >= MAP_HEIGHT - 1){
        return 0; 
    }
    
    for (int i = 1; i < snake.length; i++) {//判断是否重合
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
            return 0;
        }
    }
    return 1;
}

void SpeedControl()
{
    switch (snake.length)
    {
    case 6:
        snake.speed = 200;
        break;
    case 9:
        snake.speed = 180;
        break;
    case 12:
        snake.speed = 160;
        break;
    case 15:
        snake.speed = 140;
        break;
    case 18:
        snake.speed = 120;
        break;
    case 21:
        snake.speed = 100;
        break;
    case 24:
        snake.speed = 80;
        break;
    case 27:
        snake.speed = 60;
        break;
    case 30:
        snake.speed = 40;
        break;
    default:
        break;
    }
}
