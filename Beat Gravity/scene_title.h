#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class TITLE
{
public:
	int state = 0;					// 状態
	int pltimer = 0;				// タイマー
    int bgtimer = 0;
    int plposX = 0;
    int plposY = 0;
    int bgposX = 0;
    int bgposY = 0;
    int gravity = 0;
    int pljumppower = 0;
    int plspeed = 0;
    int box_speedX[3] = { 0 };
    int box_speedY[3] = { 0 };
    int box_moveX[3] = { 0 };
    int box_moveY[3] = { 0 };
    int rndX[3] = { 0 };
    int rndY[3] = { 0 };
	int bgHND = 0;					// 背景のデータハンドル
    int plHND[5] = { 0 };
    int spaceHND[2] = { 0 };
    int nextHND = 0;
    int BGM = 0;
    int decideSE = 0;              // 決定音
	bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void title_initialize(void);	// タイトルの初期設定
void title_update(void);		// タイトルの更新処理
void title_draw(void);			// タイトルの描画処理
void title_end(void);			// タイトルの終了処理