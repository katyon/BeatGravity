#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class PLAYER
{
public:
    int state = 0;					// 状態
    int plHND = 0;					// playerのグラフィックデータハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void player_initialize(void);	// プレイヤーの初期設定
void player_update(void);		// プレイヤーの更新処理
void player_draw(void);			// プレイヤーの描画処理
void player_end(void);			// プレイヤーの終了処理