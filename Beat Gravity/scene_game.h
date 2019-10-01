#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// 状態
	int titmer = 0;					// タイマー
	int bgHND = 0;					// 背景のデータハンドル
	bool transition_flg = false;	// シーン遷移用のフラグ
};

class PLAYER
{
public:
    int state;       // 状態
    int posX;        // X座標
    int posY;        // Y座標
    int pivotX;      // 中心X座標
    int pivotY;      // 中心Y座標
    int speed;       // X軸方向の速度
    int jumppower;   // ジャンプ力
    bool jumpflg;    // 空中にいるかどうかの判定(空中ならtrue)
    int plHND;       // playerのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void game_initialize(void);	// ゲームの初期設定
void game_update(void);		// ゲームの更新処理
void game_draw(void);		// ゲームの描画処理
void game_end(void);		// ゲームの終了処理

void player_initialize(void);	    // プレイヤーの初期設定
void player_update(void);	    	// プレイヤーの更新処理
void player_draw(void);		    	// プレイヤーの描画処理
void player_end(void);		    	// プレイヤーの終了処理