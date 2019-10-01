// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------

// インスタンス宣言 ---------------------------------------------------------------------------------
STAGE stage;

// ステージ構成 ------------------------------------------------------------------------------------
#pragma region ConstInit
// ステージ1
int const1[STAGE1_YCONST][STAGE1_XCONST] = { 0 };

// ステージ2
int const2[STAGE2_YCONST][STAGE2_XCONST] = { 0 };

// ステージ3
int const3[STAGE3_YCONST][STAGE3_XCONST] = { 0 };

// debug用
int const4[STAGE4_YCONST][STAGE4_XCONST] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};
#pragma endregion

// 関数実体 ----------------------------------------------------------------------------------------
// ステージの初期設定
void stage_initialize(void)
{
    // debug用
    stage.num = STAGE4;

    LoadDivGraph("Data//Images//stage.png", STAGE_ALLNUM, 4, 4, CHIP_SIZE, CHIP_SIZE, stage.chipHND);
}

// 対応するマップチップの番号を検出
int detect_chip(int pl_posX, int pl_posY, int stage_num)
{
    switch (stage_num)
    {
    case STAGE1:
        return const1[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
        break;
    case STAGE2:
        return const2[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
        break;
    case STAGE3:
        return const3[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
        break;
        // debug用
    case STAGE4:
        return const4[pl_posY / CHIP_SIZE][pl_posX / CHIP_SIZE];
        break;
    }
}

// ステージの描画処理
void stage_draw(void)
{
    switch (stage.num)
    {
    case STAGE1:

        break;
    case STAGE2:

        break;
    case STAGE3:

        break;
        // debug用
    case STAGE4:
        for (int i = 0; i < STAGE4_YCONST; i++)
        {
            for (int j = 0; j < STAGE4_XCONST; j++)
            {
                switch (const4[i][j])
                {
                case UP:
                    DrawGraph(CHIP_SIZE * j, CHIP_SIZE * i, stage.chipHND[0], true);
                    break;
                case DOWN:
                    DrawGraph(CHIP_SIZE * j, CHIP_SIZE * i, stage.chipHND[1], true);
                    break;
                case LEFT:
                    DrawGraph(CHIP_SIZE * j, CHIP_SIZE * i, stage.chipHND[2], true);
                    break;
                case RIGHT:
                    DrawGraph(CHIP_SIZE * j, CHIP_SIZE * i, stage.chipHND[3], true);
                    break;
                }
            }
        }
        break;
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