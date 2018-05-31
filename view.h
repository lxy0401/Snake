#pragma once

typedef struct UI
{
    int gameZoneWidth;
    int gameZoneHeight;

    int marginTop;
    int marginLeft;

    char* snakeBlock;
    char* foodBlock;
    char* wallBlock;
    int blockWidthh;
}UI;

void UIInitialize(UI* pUI,int gameZoneWidth,int gameZoneHeight);

void UIIDisplayFoodBlockAtXY(const UI* pUI,int x,int,y);

void UICleanBlockAtXY(const UI* pUI,int x,int y);

void UIDisplaySnakeBlookAtXY(const UI* pUI,int x,int y);

void UIDesyroy(UI* pUI);

void UIDisplayWizaid(const UI* pUI);

void UIDisplayGAmeZone(const UI* pUI);
