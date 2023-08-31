#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//����̨��һЩ�ļ�
#include<time.h>

//�궨��
#define MAP_HEIGHT 20 // ��ͼ�߶�
#define MAP_WIDTH 40  // ��ͼ�Ŀ��
#define UP 'w'        // �������Ƽ�
#define DOWN 's'      // �������Ƽ�
#define LEFT 'a'      // �������Ƽ�
#define RIGHT 'd'     // �������Ƽ�

//�ṹ�嶨��
typedef struct
{
    int x;    // x�����λ��
    int y;    // y�����λ��
}Food, Snakenode;

typedef struct //�����ߵĽṹ��
{
    Snakenode snakeNode[1000]; //��ʾ�������1000���ڵ�
    int length; //�ߵĳ���
    int speed;  //���ƶ����ٶ�
}Snake;

void GotoXY(int, int); //��궨λ����
void Hide();     //���ع�꺯��
int Menu();      //���˵�����
void Help();     //������Ϣ
void About();    //������Ϣ
void InitMap();  //��ͼ��ʼ��
void PrintFood(); //����ʳ��
int MoveSnake();  //�ߵ��ƶ�
int IsCorrect(); //��ײ��ײǽ���
void SpeedControl(); //�ٶȿ���
