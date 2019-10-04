#pragma once
// 定数 ----------------------------------------------------------------
#define GRAVITY     (2)
#define SCORE_COIN  (20)

// クラス --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// 状態
	int timer = 0;					// タイマー
    int score = 0;                  // スコア
    int bgposX = 0;                 // 背景X座標
    int bgposY = 0;                 // 背景Y座標
    int bgspeed = 0;                // 背景スクロール速度
    int alpha1;                     // α値
    int alpha2;
    float angle1;                   // 描画角度
    float angle2;
    bool deathflg = false;          // 死亡：true
    bool clearflg = false;          // ゲームクリア：true
    bool choice = true;             // Yes:true No:false
    int bgHND[2] = { 0 };		    // 背景のデータハンドル
    int reHND[2] = { 0 };           // リトライ選択用のデータハンドル
    int bgmHND = 0;                 // BGMサウンドハンドル
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
    int plHND[5];       // playerのグラフィックハンドル
};

// プロトタイプ宣言 -----------------------------------------------------
void game_initialize(void);	// ゲームの初期設定
void game_update(void);		// ゲームの更新処理
void game_draw(void);		// ゲームの描画処理
void game_end(void);		// ゲームの終了処理

void player_initialize(void);	    // プレイヤーの初期設定
void player_draw(void);		    	// プレイヤーの描画処理
void player_end(void);		    	// プレイヤーの終了処理

void retry_draw(void);  // リトライの描画処理

//void sound_play(void);  // BGMの再生処理