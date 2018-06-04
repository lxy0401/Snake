#include "controller.h"
#include "view.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

static void _SnakeInitialize(Snake* pSnake)
{
    int i;
    int initLength = 3;
    int x = 5;
    int y = 5;

    pSnake->pHead = NULL;
    for(i = 0;i < initLength;i++)
    {
        Node* pNode = (Node*)malloc(sizeof(Node));
        assert(pNode != NULL);
        pNode->position.x = x + i;
        pNode->position.y = y;
        pNode->pNext = pSnake->pHead;
        pSnake->pHead = pNode;
    }
    pSnake->direction = RIGHT;
}

static bool _IsOverlapSnake(int x,int y,const Snake* pSnake)
{
    assert(pSnake != NULL);
    Node* pos = pSnake->pHead;
    while(pos)
    {
        if(pos->position.x == x && pos->position.y == y)
        {
            return true;
        }
        pos = pos->pNext;
    }
    return false;
}



static void _GenerateFood(Position* pPosition,int width,int height,const Snake* pSnake)
{
    int x;
    int y;
    do{
        x = rand() % width;
        y = rand() % height;
    }while(_IsOverlapSnake(x,y,pSnake));
    pPosition->x = x;
    pPosition->y = y;
}

void GameInitialize(Game* pGame)
{
    assert(pGame != NULL);
    pGame->gameZoneWidth = 16;
    pGame->gameZoneHeight = 14;
    pGame->score = 0;
    pGame->scorePerFood = 10;
    pGame->interval = 300;

    _SnakeInitialize(&pGame->snake);
    _GenerateFood(&pGame->foodPosition,pGame->gameZoneWidth,pGame->gameZoneHeight,&pGame->snake);
}

void GameRun(Game* pGame)
{
    UI ui;
    UIInitialize(&ui,pGame->gameZoneWidth,pGame->gameZoneHeight);
    UIDisplayWizaid(&ui);
    UIDisplayGameZone(&ui);
    UIIDisplayFoodBlockAtXY(&ui,pGame->foodPosition.x,pGame->foodPosition.y);
    _DisplaySnake(&ui,&pGame->snake);

    while(1)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            if(pGame->snake.direction != DOWN)
            {
                pGame->snake.direction = UP;
            }
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            if(pGame->snake.direction != UP)
            {
                pGame->snake.direction = DOWN;
            }
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            if(pGame->snake.direction != RIGHT)
            {
                pGame->snake.direction = LEFT;
            }
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            if(pGame->snake.direction != LEFT)
            {
                pGame->snake.direction = RIGHT;
            }
        }

        Position nextPosition = _GetNextPosition(&pGame->snake);
        if(_IsEatFood(pGame->foodPosition,nextPosition))
        {
            _AddHeadDisplay(&ui,nextPosition,&pGame->snake);
            _GenerateFood(&pGame->foodPosition,pGame->gameZoneWidth,pGame->gameZoneHeight,&pGame->snake);
            UIDisplayFoodBlockAtXY(&ui,pGame->foodPosition.x,pGame->foodPosition.y);
            pGame->score += pGame->scorePerFood;
        }
        else
        {
            _RemoveTailAndDisplay(&ui,&pGame->snake);
            _AddHeadDisplay(&ui,nextPosition,&pGame->snake);
        }
        if(_IsKilledByWall(nextPosition,pGame->gameZoneWidth,pGame->gameZoneHeight))
        {
            break;
        }
        if(_IsKilledBySelf(nextPosition,&pGame->snake))
        {
            break;
        }
        Sleep(pGame->interval);
    }
    UIDesyroy(&ui);
}

void GameDestroy(Game* pGame)
{
    Node* pNode;
    Node* pNext;
    for(pNode = pGame->snake.pHead;pNode != NULL;pNode = pNext)
    {
        pNext = pNode->pNext;
        free(pNode);
    }
}
