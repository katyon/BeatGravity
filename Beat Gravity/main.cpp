// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "scene_load.h"
#include "scene_result.h"
#include "scene_select.h"
#include "scene_title.h"

// 変数 --------------------------------------------------------------------------------------------
// シーン切り替え用変数
int curScene;
int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------


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

	// タイトルの初期設定
	title_initialize();

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// ESCキーが押されるか、ウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		clsDx();

		// ゲームシーン切り替え
		if (nextScene != curScene)
		{
            // 現シーンの終了処理を行う
#pragma region NowEnd
			switch (curScene)
			{
			case SCENE_TITLE:
				title_end();
				break;
            case SCENE_SELECT:
                select_end();
                break;
            case SCENE_LOAD:
                load_end();
                break;
			case SCENE_GAME:
				game_end();
				break;
            case SCENE_RESULT:
                result_end();
                break;
			}
#pragma endregion
            // 次シーンの初期化を行う
#pragma region NextInitialize
			switch (nextScene)
			{
            case SCENE_TITLE:
                title_initialize();
                break;
            case SCENE_SELECT:
                select_initialize();
                break;
            case SCENE_LOAD:
                load_initialize();
                break;
            case SCENE_GAME:
                game_initialize();
                break;
            case SCENE_RESULT:
                result_initialize();
                break;
			}
#pragma endregion
			curScene = nextScene;
		}

		// 現在のシーンの更新処理
#pragma region NowUpdate
		switch (curScene)
		{
        case SCENE_TITLE:
            title_update();
            break;
        case SCENE_SELECT:
            select_update();
            break;
        case SCENE_LOAD:
            load_update();
            break;
        case SCENE_GAME:
            game_update();
            break;
        case SCENE_RESULT:
            result_update();
            break;
		}
#pragma endregion

		// 現在のシーンの描画処理
#pragma region NowDraw
		switch (curScene)
		{
        case SCENE_TITLE:
            title_draw();
            break;
        case SCENE_SELECT:
            select_draw();
            break;
        case SCENE_LOAD:
            load_draw();
            break;
        case SCENE_GAME:
            game_draw();
            break;
        case SCENE_RESULT:
            result_draw();
            break;
		}
#pragma endregion

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// 現在のシーンの終了処理
#pragma region NowEnd
	switch (curScene)
	{
    case SCENE_TITLE:
        title_end();
        break;
    case SCENE_SELECT:
        select_end();
        break;
    case SCENE_LOAD:
        load_end();
        break;
    case SCENE_GAME:
        game_end();
        break;
    case SCENE_RESULT:
        result_end();
        break;
	}
#pragma endregion

	// 全グラフィックの削除
	DxLib::InitGraph();

	// 全音データの削除
	InitSoundMem();

	// ライブラリの終了処理
	DxLib::DxLib_End();

	// ソフト終了
	return 0;
}