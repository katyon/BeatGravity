#pragma once
// 定数 ----------------------------------------------------------------
#define STAGE_ALLNUM     (16)
#define STAGE_XMAX       (256)
#define STAGE_YMAX       (36)
#define STAGE1_XCONST    (16)
#define STAGE1_YCONST    (9)
#define STAGE2_XCONST    (16)
#define STAGE2_YCONST    (9)
#define STAGE3_XCONST    (16)
#define STAGE3_YCONST    (9)
#define STAGE4_XCONST    (64)
#define STAGE4_YCONST    (18)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3,STAGE4
};

enum CHIP
{
    EMPTY, TOP, BOTTOM, LEFT, RIGHT, LCORNER, RCORNER, INSIDE, 
    HOLE,
};

// クラス --------------------------------------------------------------
class STAGE
{
public:
    int num;                                        // ステージナンバー
    int map_copy[STAGE_YMAX][STAGE_XMAX] = { 0 };   // 各ステージのコピー
    int chipHND[STAGE_ALLNUM];                      // マップチップのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void stage_initialize(void);     // ステージの初期設定
int detect_chip(int pl_posX, int pl_posY);  // 対応するマップチップの番号を検出
void stage_draw(void);           // ステージの描画処理
void stage_end(void);            // ステージの終了処理