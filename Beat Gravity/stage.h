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
    int chip;                                 // マップチップの種類分け用
    int const1[STAGE1_XCONST][STAGE1_YCONST]; // ステージ1の構成
    int const2[STAGE2_XCONST][STAGE2_YCONST]; // ステージ2の構成
    int const3[STAGE3_XCONST][STAGE3_YCONST]; // ステージ3の構成
    int const4[STAGE4_XCONST][STAGE4_YCONST]; // debug用の構成
    int stageHND[STAGE_ALLNUM];               // stageのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void stage_initialize(void);    // ステージの初期設定
void stage_draw(void);          // ステージの描画処理
void stage_end(void);           // ステージの終了処理