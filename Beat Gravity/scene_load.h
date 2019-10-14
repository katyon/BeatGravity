#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class LOAD
{
public:
    int state = 0;					// 状態
    int timer = 0;					// タイマー
    int rnd = 0;
    int bgHND[13] = { 0 };			// 背景のデータハンドル
    int bg[6] = { 0 };
    bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void load_initialize(void);
void load_update(void);
void load_draw(void);
void load_end(void);