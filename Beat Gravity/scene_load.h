#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class LOAD
{
public:
    int state = 0;					// 状態
    int timer = 0;					// タイマー
    int bgHND = 0;					// 背景のデータハンドル
    bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void load_initialize(void);
void load_update(void);
void load_draw(void);
void load_end(void);