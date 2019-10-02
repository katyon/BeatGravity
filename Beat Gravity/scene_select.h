#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class SELECT
{
public:
    int state = 0;					// 状態
    int timer = 0;					// タイマー
    int bgHND = 0;					// 背景のデータハンドル
    bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void select_initialize(void);
void select_update(void);
void select_draw(void);
void select_end(void);