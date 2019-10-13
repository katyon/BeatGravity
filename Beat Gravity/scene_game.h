#pragma once
// 定数 ----------------------------------------------------------------
#define GRAVITY     (2)
#define SCORE_ITEM1  (10)
#define SCORE_ITEM2  (15)
#define SWAP_SPEED  (20)

// クラス --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// 状態
	int timer = 0;					// タイマー
    int score = 0;                  // スコア
    int bg1posX = 0;                // 背景X座標
    int bg1posY = 0;                // 背景Y座標
    int bg1speed = 0;               // 背景スクロール速度
    int bg2posX = 0;                // 背景X座標
    int bg2posY = 0;                // 背景Y座標
    int bg2speed = 0;               // 背景スクロール速度
    int alpha1;                     // α値
    int alpha2;
    float angle1;                   // 描画角度
    float angle2;
    bool deathflg = false;          // 死亡：true
    bool clearflg = false;          // ゲームクリア：true
    bool choice = true;             // Yes:true No:false
    int bgHND[4] = { 0 };		    // 背景のデータハンドル
    int reHND[2] = { 0 };           // リトライ選択用のデータハンドル
    int bgmHND = 0;
    int decideSE = 0;
    int choiceSE = 0;
    int deathSE = 0;                // 死亡SE
};

class PLAYER
{
public:
    int state = 0;          // 状態
    int box_moveX[3] = { 0 };    // 子分用
    int box_moveY[3] = { 0 };
    int box_speedX[3] = { 0 };
    int box_speedY[3] = { 0 };
    int rndX[3] = { 0 };
    int rndY[3] = { 0 };
    int init_posX = 0;      // ゲーム開始時のX座標
    int init_posY = 0;      // ゲーム開始時のY座標
    int posX = 0;           // X座標
    int posY = 0;           // Y座標
    int death_posX[10] = { 0 };
    int death_posY[10] = { 0 };
    int death_rndX[10] = { 0 };
    int death_rndY[10] = { 0 };
    int death_speed = 0;
    int speed = 0;          // X軸方向の速度
    int jumppower = 0;      // ジャンプ力
    int gravity = 0;        // プレイヤーにかかる重力
    bool gravityflg = true;    // 重力が反転しているかどうかの判定(下向きでtrue)
    bool grandflg = true;      // 地面にいるかどうかの判定(地面ならtrue)
    int plHND[5] = { 0 };       // playerのグラフィックハンドル
    int deathHND = 0;
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