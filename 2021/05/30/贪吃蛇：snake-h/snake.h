#pragma once
#include<stdio.h>
#include<Windows.h>
#include<conio.h>//控制台的一些文件
#include<time.h>

//宏定义
#define MAP_HEIGHT 20 // 地图高度
#define MAP_WIDTH 40  // 地图的宽度
#define UP 'w'        // 定义上移键
#define DOWN 's'      // 定义下移键
#define LEFT 'a'      // 定义左移键
#define RIGHT 'd'     // 定义右移键

//结构体定义
typedef struct
{
    int x;    // x坐标的位置
    int y;    // y坐标的位置
}Food, Snakenode;

typedef struct //定义蛇的结构体
{
    Snakenode snakeNode[1000]; //表示蛇最多有1000个节点
    int length; //蛇的长度
    int speed;  //蛇移动的速度
}Snake;

void GotoXY(int, int); //光标定位函数
void Hide();     //隐藏光标函数
int Menu();      //主菜单函数
void Help();     //帮助信息
void About();    //关于信息
void InitMap();  //地图初始化
void PrintFood(); //生成食物
int MoveSnake();  //蛇的移动
int IsCorrect(); //自撞或撞墙检测
void SpeedControl(); //速度控制
