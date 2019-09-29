#pragma once
// 定数 ----------------------------------------------------------------
#define STAGE_ALLNUM     (16)
#define STAGE1_XCONST    (16)
#define STAGE1_YCONST    (9)
#define STAGE2_XCONST    (16)
#define STAGE2_YCONST    (9)
#define STAGE3_XCONST    (16)
#define STAGE3_YCONST    (9)
#define STAGE4_XCONST    (25)
#define STAGE4_YCONST    (15)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3,STAGE4
};

enum CHIP
{
    UP, DOWN, LEFT, RIGHT, HOLE
};

// クラス --------------------------------------------------------------
class STAGE
{
public:
    int num;                                  // ステージナンバー
    int chipHND[STAGE_ALLNUM];                // マップチップのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void stage_initialize(void);     // ステージの初期設定
int detect_chip(int pl_posX, int pl_posY, int stage_num);  // 対応するマップチップの番号を検出
void stage_draw(void);           // ステージの描画処理
void stage_end(void);            // ステージの終了処理