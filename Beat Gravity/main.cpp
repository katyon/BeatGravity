// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"
#include "scene_game.h"

// 変数 --------------------------------------------------------------------------------------------
// シーン切り替え用変数
int curScene;
int nextScene;

// WinMain -----------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// フルスクリーンモードで起動
	//ChangeWindowMode(FALSE);

	// ゲーム画面の解像度を設定(32ビットカラー(フルカラー))
	SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);

	// 背景を黒に
	SetBackgroundColor(0, 0, 0);

	// ウインドウのタイトルを設定
	SetMainWindowText("Beat Gravity");

	// ブレンドモードの設定(ノーブレンド)
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ゲームシーンの設定
	curScene = SCENE_TITLE;
	nextScene = SCENE_TITLE;

	// ライブラリの初期化
	if (DxLib_Init() < 0)
		return -1;

	// タイトルの初期化

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// ESCキーが押されるか、ウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		clsDx();

		// 入力状態の更新処理

		// ゲームシーン切り替え
		if (nextScene != curScene)	// 次フレームでシーン変更があれば
		{
			switch (curScene)		// 現シーンの終了処理を行う
			{
			case SCENE_TITLE:
				title_end();
				break;
			case SCENE_GAME:
				game_end();
				break;
			}

			switch (nextScene)		// 次シーンの初期化を行う
			{
			case SCENE_TITLE:
				title_initialize();
				break;
			case SCENE_GAME:
				game_initialize();
				break;
			}
			curScene = nextScene;	// 現シーンに次シーンを代入
		}

		// 現在のシーンの更新処理
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			break;
		case SCENE_GAME:
			game_update();
			break;
		}

		// 現在のシーンの描画処理
		switch (curScene)
		{
		case SCENE_TITLE:
			title_draw();
			break;
		case SCENE_GAME:
			game_draw();
			break;
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// 現在のシーンの終了処理
	switch (curScene)
	{
	case SCENE_TITLE:
		title_end();
		break;
	case SCENE_GAME:
		game_end();
		break;
	}

	// 全グラフィックの削除
	DxLib::InitGraph();

	// 全音データの削除
	InitSoundMem();

	// ライブラリの終了処理
	DxLib::DxLib_End();

	// ソフト終了
	return 0;
}