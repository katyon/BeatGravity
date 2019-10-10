#pragma once
// 定数 ----------------------------------------------------------------
#define STAGE_ALLNUM       (36)
#define STAGE_SIZE_X       (1700)
#define STAGE_SIZE_Y       (54)

enum STAGENUM
{
    STAGE1, STAGE2, STAGE3
};

enum CHIP
{
    EMPTY, BOTTOM, BOTTOM_LCORNER, BOTTOM_RCORNER, BOTTOM_INSIDE, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM_AIR, BOTTOM_LAIR, BOTTOM_RAIR,
    TOP, TOP_LCORNER, TOP_RCORNER, TOP_INSIDE, TOP_LEFT, TOP_RIGHT, TOP_AIR, TOP_LAIR, TOP_RAIR, DARK, LDARK, RDARK,
    HOLE, BOTTOM_NEEDLE, TOP_NEEDLE, AIRJUMP, BOTTOM_JUMPPAD, TOP_JUMPPAD, ITEM1, ITEM2, CHANGE_GRAVITY, GOAL
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