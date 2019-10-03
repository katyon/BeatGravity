#pragma once
// 定数 ----------------------------------------------------------------
#define Score_h 5

// クラス --------------------------------------------------------------

// プロトタイプ宣言 -----------------------------------------------------
void rank_initialize(void);
void rank_update(void);
void rank_draw(void);
void rank_end(void);

extern int H_score[Score_h];
extern bool R_flg;