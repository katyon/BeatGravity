#pragma once
// 定数 ----------------------------------------------------------------
#define STAGE_ALLNUM       (25)
#define STAGE_SIZE_X       (1700)
#define STAGE_SIZE_Y       (54)
//#define STAGE1_XCONST    (16)
//#define STAGE1_YCONST    (9)
//#define STAGE2_XCONST    (16)
//#define STAGE2_YCONST    (9)
//#define STAGE3_XCONST    (16)
//#define STAGE3_YCONST    (9)
//#define STAGE4_XCONST    (64)
//#define STAGE4_YCONST    (18)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3,STAGE4
};

enum CHIP
{
    EMPTY, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT,BOTTOM_RIGHT,
    TOP_LCORNER, TOP_RCORNER, BOTTOM_LCORNER, BOTTOM_RCORNER, TOP_INSIDE, BOTTOM_INSIDE,
    HOLE, NEEDLE, JUMP, COIN
};

// クラス --------------------------------------------------------------
class STAGE
{
public:
    int num;                                        // ステージナンバー
    int map_copy[STAGE_SIZE_Y][STAGE_SIZE_X] = { 0 };   // 各ステージのコピー
    int chipHND[STAGE_ALLNUM];                      // マップチップのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void load_mapFile(void);         // ステージの読み込み
void stage_initialize(void);     // ステージの初期設定
int detect_chip(int pl_posX, int pl_posY);  // 対応するマップチップの番号を検出
void stage_draw(void);           // ステージの描画処理
void stage_end(void);            // ステージの終了処理