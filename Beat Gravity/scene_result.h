#pragma once
// 定数 ----------------------------------------------------------------
#define Score_h 5

// クラス --------------------------------------------------------------
class RESULT
{
public:
    int state = 0;					// 状態
    int timer = 0;					// タイマー
    int bgHND = 0;					// 背景のデータハンドル
    bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void result_initialize(void);
void result_update(void);
void result_draw(void);
void result_end(void);

