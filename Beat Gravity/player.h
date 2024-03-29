#pragma once
// 定数 ----------------------------------------------------------------


// クラス --------------------------------------------------------------
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
void player_initialize(void);	    // プレイヤーの初期設定
void player_update(void);	    	// プレイヤーの更新処理
void player_draw(void);		    	// プレイヤーの描画処理
void player_end(void);		    	// プレイヤーの終了処理