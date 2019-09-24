#pragma once
// 定数 ----------------------------------------------------------------

// 構造体 --------------------------------------------------------------
struct GAME
{
	int state = 0;					// 状態
	int titmer = 0;					// タイマー
	int bgHND = 0;					// 背景のデータハンドル
	bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void game_initialize(void);	// ゲームの初期設定
void game_update(void);		// ゲームの更新処理
void game_draw(void);		// ゲームの描画処理
void game_end(void);		// ゲームの終了処理