#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class RESULT
{
public:
    int state = 0;					// 状態
    int timer = 0;					// タイマー
    int scenetimer = 0;
    int sceneposX = 0;
    int sceneposY = 0;
    int bgHND = 0;					// 背景のデータハンドル
    int spaceHND[2] = { 0 };
    int sceneHND = 0;
    int BGM = 0;
    int decideSE = 0;
    bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void result_initialize(void);
void result_update(void);
void result_draw(void);
void result_end(void);

