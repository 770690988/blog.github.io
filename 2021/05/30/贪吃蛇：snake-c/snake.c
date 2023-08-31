#include "snake.h"

// ȫ�ֱ���
Snake snake; //�����߽ṹ�����
Food food;   //����ʳ��ṹ�����
char now_Dir = RIGHT; //��ǰ��ͷ����
char direction = RIGHT; //Ԥ����ͷ����

int Menu()
{
    GotoXY(40, 12);   //��λ����λ��
    printf("��ӭ����̰����С��Ϸ");
    GotoXY(43, 14);
    printf("1. ��ʼ��Ϸ");
    GotoXY(43, 16);
    printf("2. ����");
    GotoXY(43, 18);
    printf("3. ����");
    GotoXY(43, 20);
    printf("����������˳���Ϸ");
    Hide();    //���ع��
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

//��궨λ����
void GotoXY(int x, int y)
{
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

//���ع��
void Hide()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
    SetConsoleCursorInfo(hout, &cor_info);//���ع��

}

void About()
{
    GotoXY(30, 12);
    printf("���ݵ��ӿƼ���ѧ--��������ۺ�ʵ����ҵ");
    GotoXY(43, 14);
    printf("̰����-����̨��Ϸ");
    GotoXY(43, 16);
    printf("������������ϼ��˵�");
    Hide();    //���ع��
    char ch = _getch();
    system("cls");
}

void Help()
{
    GotoXY(40, 12);
    printf("w ��                      ");
    GotoXY(40, 14);
    printf("s ��                      ");
    GotoXY(40, 16);
    printf("a ��                      ");
    GotoXY(40, 18);
    printf("d ��                      ");
    GotoXY(45, 22);
    printf("������������ϼ��˵�      ");
    char ch = _getch();
    system("cls");
}

void InitMap()
{
    Hide();   //���ع��
    //������ͷλ���ڵ�ͼ������
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake. snakeNode[0].y); //����ƶ�����ͷλ��
    printf("@"); //��ͷ
    snake.length = 3; //��ʼ����
    snake.speed = 250; //��ʼ�ٶ�
    now_Dir = RIGHT; // ��ǰ��ͷ�ĳ���

    //��ʾ�ߵ�����
    for (int i = 1; i < snake.length; i++) {
        //���������������λ�ú���ͷλ����ͬ
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
        printf("*");
    }

    //���ɵ�ͼ���±߽�
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
    PrintFood();  //����ʳ��
    GotoXY(50, 5);
    printf("��ǰ�÷֣�0");
}


void PrintFood()
{
    int flag = 1;
    while (flag) {
        flag = 0;

        //����ʳ����������
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //ѭ���ж�ʳ���λ���ܷ�����ߵ�λ���ص�������ص�����������ʳ���λ��
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("o"); //�˴���ʳ����o����ʾ
}


int MoveSnake()
{
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1]; //��¼��β
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("*");

    //��Ӧ���̵Ĳ���
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
    case UP:snake.snakeNode[0].y--; break; //����
    case DOWN:snake.snakeNode[0].y++; break; //����
    case LEFT:snake.snakeNode[0].x--; break; //����
    case RIGHT:snake.snakeNode[0].x++; break; //����
    }

    //��ӡ��ͷ
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //�ж��Ƿ�Ե�ʳ������ͷ��λ�ú�ʳ���λ����ͬ��ʾ�Ե�ʳ��
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        snake.length++; //�Ե�ʳ���߳���һ
        flag = 1; //1��ʾ�Ե�ʳ��
        snake.snakeNode[snake.length - 1] = temp;  // �Ե�ʳ���β��һ��
    }
    //����ߴ�ʱ��״̬
    //û�Ե�ʳ���ʱ����ԭ������β��ӡһ���ո�ȥ��ԭ������β��
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    }
    else {
        PrintFood();
        GotoXY(50, 5);
        printf("��ǰ�÷֣�%d", snake.length - 3);  //��ӡ�÷֣��÷�Ϊ�߳���3
    }

    //�ж��Ƿ�����
    if (!IsCorrect()) {
        system("cls");
        GotoXY(45, 14);
        printf("���յ÷֣�%d", snake.length - 3);
        GotoXY(45, 16);
        printf("��Ϸ������"); 
        GotoXY(45, 18);
        printf("��������������˵�");
            char c = _getch();
        system("cls");
        return 0;
    }

    //�����ٶ�
    SpeedControl();
    Sleep(snake.speed);
    return 1;
}

int IsCorrect()
{
    if (snake.snakeNode[0].x <= 0 || snake.snakeNode[0].y <= 0 || snake.snakeNode[0].x >= MAP_WIDTH - 1 || snake.snakeNode[0].y >= MAP_HEIGHT - 1){
        return 0; 
    }
    
    for (int i = 1; i < snake.length; i++) {//�ж��Ƿ��غ�
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
