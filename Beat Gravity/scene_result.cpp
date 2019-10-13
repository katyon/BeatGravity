// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "ranking.h"
#include "scene_result.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------
extern int H_score[Score_h];
extern bool R_flg;
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
RESULT result;

extern STAGE stage;
extern COMMON common;
extern GAME game;
// 関数実体 ----------------------------------------------------------------------------------------
void result_initialize(void)
{
    result.state = 0;
    result.timer = 0;
    result.transition_flg = false;
    result.bgHND = LoadGraph("Data\\Images\\result_bg.png");
    result.spaceHND[0] = LoadGraph("Data\\Images\\space1.png");
    result.spaceHND[1] = LoadGraph("Data\\Images\\space2.png");
    result.BGM = LoadSoundMem("Data\\Sounds\\resultBGM.ogg");
}

void result_update(void)
{
#pragma region KeyUpdate
    //キーの設定
    char key[MAX_KEY];              //押されている間処理が続く
    char key_trg[MAX_KEY] = { 0 };  //押された瞬間だけ処理

    GetHitKeyStateAll(key);

    for (int n = 0; n < MAX_KEY; n++)
    {
        if (key[n] && !(key_buf[n])) key_trg[n] = key[n];
        key_buf[n] = key[n];
    }
#pragma endregion
    switch (result.state)
    {
    case INIT:
        ///// 初期設定 /////
        // ランキング
        if (R_flg == true)
        {
            rank_update();
            R_flg = false;
        }

        result.state = NORMAL;
        break;

    case NORMAL:
        ///// 通常時 /////
        if (key_trg[KEY_INPUT_SPACE])
        {
            nextScene = SCENE_TITLE;
        }

        break;
    }

    result.timer++;
}

void result_draw(void)
{
    DrawGraph(0, 0, result.bgHND, true);
    DrawExtendGraph(688, 920, 1200,1060,result.spaceHND[result.timer / 30 % 2], true);

    switch (stage.num)
    {
    case STAGE1:
        DrawFormatStringToHandle(250, 70, GetColor(255, 255, 255), common.font, "STAGE1");
        break;
    case STAGE2:
        DrawFormatStringToHandle(250, 70, GetColor(255, 255, 255), common.font, "STAGE2");
        break;
    case STAGE3:
        DrawFormatStringToHandle(250, 70, GetColor(255, 255, 255), common.font, "STAGE3");
        break;
    }
    DrawFormatStringToHandle(880, 220, GetColor(255, 255, 255), common.font, "%d", game.score);
    DrawFormatStringToHandle(880, 340, GetColor(255, 255, 255), common.font, "%d", H_score[0]);
    DrawFormatStringToHandle(880, 440, GetColor(255, 255, 255), common.font, "%d", H_score[1]);
    DrawFormatStringToHandle(880, 530, GetColor(255, 255, 255), common.font, "%d", H_score[2]);
    DrawFormatStringToHandle(880, 620, GetColor(255, 255, 255), common.font, "%d", H_score[3]);
    DrawFormatStringToHandle(880, 720, GetColor(255, 255, 255), common.font, "%d", H_score[4]);
}

void result_end(void)
{
    DeleteGraph(result.bgHND);
}