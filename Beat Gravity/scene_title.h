#pragma once
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
class TITLE
{
public:
	int state = 0;					// 状態
	int timer = 0;					// タイマー
	int bgHND = 0;					// 背景のデータハンドル
    int BGM = 0;
    int decideSE = 0;              // 決定音
	bool transition_flg = false;	// シーン遷移用のフラグ
};

// プロトタイプ宣言 -----------------------------------------------------
void title_initialize(void);	// タイトルの初期設定
void title_update(void);		// タイトルの更新処理
void title_draw(void);			// タイトルの描画処理
void title_end(void);			// タイトルの終了処理