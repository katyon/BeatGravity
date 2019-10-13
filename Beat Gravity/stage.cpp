// インクルード -------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------

// インスタンス宣言 ---------------------------------------------------------------------------------
STAGE stage;

extern GAME game;
extern PLAYER pl;
// 関数実体 ----------------------------------------------------------------------------------------
// ステージの読み込み
void load_mapFile(void)
{
    FILE *fp1 = 0, *fp2 = 0/*, *fp3 = 0*/;
    fp1 = fopen("Data\\Stages\\stage1.txt", "rt");
    fp2 = fopen("Data\\Stages\\stage2.txt", "rt");
    //fp3 = fopen("Data\\Stages\\stage3.txt", "rt");
    for (int i = 0; i < STAGE_SIZE_Y; i++)
    {

        for (int j = 0; j <STAGE_SIZE_X; j++)
        {
            fscanf(fp1, "%d", &stage.map1[i][j]);
            fscanf(fp2, "%d", &stage.map2[i][j]);
            //fscanf(fp3, "%d", &stage.map3[i][j]);
        }
        fprintf(fp1, "\n");
        fprintf(fp2, "\n");
        //fprintf(fp3, "\n");
    }
    fclose(fp1);
    fclose(fp2);
    //fclose(fp3);
}

// ステージの初期設定
void stage_initialize(void)
{
    for (int y = 0; y < STAGE_SIZE_Y; y++)
    {
        for (int x = 0; x <STAGE_SIZE_X; x++)
        {
            switch (stage.num)
            {
            case STAGE1:
                stage.map_copy[y][x] = stage.map1[y][x];
                break;
            case STAGE2:
                stage.map_copy[y][x] = stage.map2[y][x];
                break;
            //case STAGE3:
            //    stage.map_copy[y][x] = stage.map3[y][x];
            //    break;
            }
        }
    }

    LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 6, 7, CHIP_SIZE, CHIP_SIZE, stage.chipHND);

    game.bgHND[0] = LoadGraph("Data\\Images\\game_bg1W.png");
    game.bgHND[1] = LoadGraph("Data\\Images\\game_bg2W.png");
    game.bgHND[2] = LoadGraph("Data\\Images\\game_bg1R.png");
    game.bgHND[3] = LoadGraph("Data\\Images\\game_bg2R.png");
    game.reHND[0] = LoadGraph("Data\\Images\\retry_yes.png");
    game.reHND[1] = LoadGraph("Data\\Images\\retry_no.png");
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
                if (stage.map_copy[y][x] != HOLE)
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
}

// ステージの終了処理
void stage_end(void)
{
    for (int i = 0; i < STAGE_ALLNUM; i++)
    {
        DeleteGraph(stage.chipHND[i]);
    }
}