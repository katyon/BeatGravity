#pragma once
// 定数 ----------------------------------------------------------------
#define GRAVITY (1)

// クラス --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// 状態
	int titmer = 0;					// タイマー
	int bgHND = 0;					// 背景のデータハンドル
	bool nextSceneflg = false;  	// シーン遷移用のフラグ
};

class PLAYER
{
public:
    int state;       // 状態
    int posX;        // X座標
    int posY;        // Y座標
    int speed;       // X軸方向の速度
    int jumppower;   // ジャンプ力
    int gravity;     // プレイヤーにかかる重力
    bool gravityflg; // 重力が反転しているかどうかの判定(下向きでtrue)
    bool grandflg;   // 地面にいるかどうかの判定(地面ならtrue)
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