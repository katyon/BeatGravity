// インクルード -------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------

// インスタンス宣言 ---------------------------------------------------------------------------------
STAGE stage;

extern PLAYER pl;

// ステージ構成 -------------------------------------------------------------------------------------
#pragma region ConstInit
// ステージ1
int map1[STAGE1_YCONST][STAGE1_XCONST] = { 0 };

// ステージ2
int map2[STAGE2_YCONST][STAGE2_XCONST] = { 0 };

// ステージ3
int map3[STAGE3_YCONST][STAGE3_XCONST] = { 0 };

// debug用
int map4[STAGE4_YCONST][STAGE4_XCONST] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,5,5,1,1,6,6,0,0,0,1,1,1,1,1,1,1,0,0,5,6,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0 },
    { 0,2,2,2,2,2,2,0,0,0,2,2,2,2,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,0,0,7,7,2,8,8,0,0,0,2,2,2,2,0,7,8,0,0,2,2,2,0,0,2,2,2,2,2,2,0,2 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};
#pragma endregion

// 関数実体 ----------------------------------------------------------------------------------------
// ステージの読み込み
//void LoadMapFile(void)
//{
//    FILE *fp;
//    switch (stage.num)
//    {
//    case STAGE1:
//        fp = fopen("Data\\stage1.txt", "rt");
//        break;
//    case STAGE2:
//        fp = fopen("Data\\stage2.txt", "rt");
//        break;
//    case STAGE3:
//        fp = fopen("Data\\stage3.txt", "rt");
//        break;
//    case STAGE4:
//        fp = fopen("Data\\stage4.txt", "rt");
//        break;
//    }
//    for (int i = 0; i < STAGE_YMAX; i++)
//    {
//
//        for (int j = 0; j <STAGE_XMAX; j++) {
//            fscanf(fp, "%d", &stage.map_copy[i][j]);
//        }
//        fprintf(fp, "\n");
//    }
//    fclose(fp);
//}

// ステージの初期設定
void stage_initialize(void)
{
    switch (stage.num)
    {
    case STAGE1:
        for (int x = 0; x < STAGE_XMAX; x++)
        {
            for (int y = 0; y < STAGE_YMAX; y++)
            {
                stage.map_copy[y][x] = map1[y][x];
            }
        }
        break;
    case STAGE2:
        for (int x = 0; x < STAGE_XMAX; x++)
        {
            for (int y = 0; y < STAGE_YMAX; y++)
            {
                stage.map_copy[y][x] = map2[y][x];
            }
        }
        break;
    case STAGE3:
        for (int x = 0; x < STAGE_XMAX; x++)
        {
            for (int y = 0; y < STAGE_YMAX; y++)
            {
                stage.map_copy[y][x] = map3[y][x];
            }
        }
        break;

        // debug用
    case STAGE4:
        for (int x = 0; x < STAGE_XMAX; x++)
        {
            for (int y = 0; y < STAGE_YMAX; y++)
            {
                stage.map_copy[y][x] = map4[y][x];
            }
        }
        break;
    }
    //FILE *fp = 0;
    //switch (stage.num)
    //{
    //case STAGE1:
    //    fp = fopen("Data\\Stage\\stage1.txt", "rt");
    //    break;
    //case STAGE2:
    //    fp = fopen("Data\\Stage\\stage2.txt", "rt");
    //    break;
    //case STAGE3:
    //    fp = fopen("Data\\Satge\\stage3.txt", "rt");
    //    break;
    //case STAGE4:
    //    fp = fopen("Data\\Stage\\stage4.txt", "rt");
    //    break;
    //}
    //for (int y = 0; y < STAGE_YMAX; y++)
    //{
    //    for (int x = 0; x < STAGE_XMAX; x++)
    //    {
    //        fscanf(fp, "%d", &stage.map_copy[y][x]);
    //    }
    //    fprintf(fp, "\n");
    //}
    //fclose(fp);

    LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 4, 4, CHIP_SIZE, CHIP_SIZE, stage.chipHND);
}

// 対応するマップチップの番号を検出
int detect_chip(int pl_posX, int pl_posY)
{
    return stage.map_copy[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
}

// ステージの描画処理
void stage_draw(void)
{
    for (int y = 0; y < STAGE_YMAX; y++)
    {
        for (int x = 0; x < STAGE_XMAX; x++)
        {
            switch (stage.map_copy[y][x])
            {
            //case EMPTY:
            //    DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[EMPTY], true);
            //    break;
            case TOP:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[TOP], true);
                break;
            case BOTTOM:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[BOTTOM], true);
                break;
            case LEFT:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[LEFT], true);
                break;
            case RIGHT:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[RIGHT], true);
                break;
            case TOP_LCORNER:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[TOP_LCORNER], true);
                break;
            case TOP_RCORNER:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[TOP_RCORNER], true);
                break;
            case BOTTOM_LCORNER:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[BOTTOM_LCORNER], true);
                break;
            case BOTTOM_RCORNER:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[BOTTOM_RCORNER], true);
                break;
            case INSIDE:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[INSIDE], true);
                break;
            case HOLE:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[HOLE], true);
                break;
            case COIN:
                DrawGraph(CHIP_SIZE * x - pl.posX + GAME_SCREEN_WIDTH / 2, CHIP_SIZE * y, stage.chipHND[COIN], true);
                break;
            }
        }
    }
}

// ステージの終了処理
void stage_end(void)
{
    for (int i = 0; i < STAGE_ALLNUM; i++)
    {
        DeleteGraph(stage.chipHND[i]);
    }
}