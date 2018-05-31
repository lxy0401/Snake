#pragma once
typedef struct Position
{
    int x;
    int y;
}Position;

typedef struct Node
{
    Position position;
    struct Node* pNext;
}Node;

//方向控制
typedef enum Direction
{
    UP,//上
    DOWM,//下
    LEFT,//左
    RIGHT,//右
}Direction;

//蛇的结构体
typedef struct Snake
{
    Direction directory;//蛇的方向
    Node* pHead;//蛇的头结点
}Snake;

//游戏中的结构体
typedef struct Game
{
    int gameZoneWidth;//游戏边界（宽）
    int gameZoneHeight;//游戏边界（高）
    Snake snake;//蛇
    Position foodPosition;//食物
    int score;//得分
    int scorePerFood;
    int interval;//时间间隔
}Game;
