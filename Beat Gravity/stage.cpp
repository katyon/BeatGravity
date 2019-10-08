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
//#pragma region ConstInit
//// ステージ1
//int map1[STAGE1_YCONST][STAGE1_XCONST] = { 0 };
//
//// ステージ2
//int map2[STAGE2_YCONST][STAGE2_XCONST] = { 0 };
//
//// ステージ3
//int map3[STAGE3_YCONST][STAGE3_XCONST] = { 0 };
//
//// debug用
//int map4[STAGE4_YCONST][STAGE4_XCONST] = { 0 }:
//#pragma endregion

// 関数実体 ----------------------------------------------------------------------------------------
// ステージの読み込み
void load_mapFile(void)
{
    FILE *fp = 0;
    switch (stage.num)
    {
    case STAGE1:
        fp = fopen("Data\\Stages\\stage1.txt", "rt");
        break;
    case STAGE2:
        fp = fopen("Data\\Stages\\stage2.txt", "rt");
        break;
    case STAGE3:
        fp = fopen("Data\\Stages\\stage3.txt", "rt");
        break;
    case STAGE4:
        fp = fopen("Data\\Stages\\stage4.txt", "rt");
        break;
    }
    for (int i = 0; i < STAGE_SIZE_Y; i++)
    {

        for (int j = 0; j <STAGE_SIZE_X; j++) {
            fscanf(fp, "%d", &stage.map_copy[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// ステージの初期設定
void stage_initialize(void)
{
    load_mapFile();

    LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 5, 5, CHIP_SIZE, CHIP_SIZE, stage.chipHND);
}

// 対応するマップチップの番号を検出
int detect_chip(int pl_posX, int pl_posY)
{
    return stage.map_copy[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
}

// ステージの描画処理
void stage_draw(void)
{
    for (int y = 0; y < STAGE_SIZE_Y; y++)
    {
        for (int x = 0; x < STAGE_SIZE_X; x++)
        {
            if (stage.map_copy[y][x] != EMPTY)
            {
                if (pl.gravityflg == true)
                {
                    DrawGraph(CHIP_SIZE * x - pl.posX + pl.init_posX, CHIP_SIZE * y - pl.posY + pl.init_posY, stage.chipHND[stage.map_copy[y][x]], true);
                }
                else
                {
                    DrawGraph(CHIP_SIZE * x - pl.posX + pl.init_posX, CHIP_SIZE * y - pl.posY + pl.init_posY, stage.chipHND[stage.map_copy[y][x]], true);
                }
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