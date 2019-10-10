// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_select.h"
#include "scene_title.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
extern char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
SELECT Select;

extern TITLE title;
extern STAGE stage;
// 関数実体 ----------------------------------------------------------------------------------------
void select_initialize(void)
{
    stage.num = STAGE1;
    Select.state = 0;
    Select.timer = 0;
    Select.transition_flg = false;
    Select.bgHND = LoadGraph("Data\\Images\\select_bg.png");
    Select.numHND[STAGE1] = LoadGraph("Data\\Images\\select1.png");
    Select.numHND[STAGE2] = LoadGraph("Data\\Images\\select2.png");
    Select.numHND[STAGE3] = LoadGraph("Data\\Images\\select3.png");
    Select.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
    Select.choiceSE = LoadSoundMem("Data\\Sounds\\choiceSE.ogg");
}

void select_update(void)
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
    switch (Select.state)
    {
    case INIT:
        ///// 初期設定 /////
        PlaySoundMem(title.BGM, DX_PLAYTYPE_LOOP, false);

        Select.state = NORMAL;
        break;

    case NORMAL:
        ///// 通常時 /////
        // debug用 ----------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------

        if (stage.num < STAGE3)
        {
            if (key_trg[KEY_INPUT_RIGHT])
            {
                PlaySoundMem(Select.choiceSE, DX_PLAYTYPE_BACK,true);
                stage.num++;
            }
        }
        if (stage.num > STAGE1)
        {
            if (key_trg[KEY_INPUT_LEFT])
            {
                PlaySoundMem(Select.choiceSE, DX_PLAYTYPE_BACK, true);
                stage.num--;
            }
        }
        if (key_trg[KEY_INPUT_SPACE])
        {
            PlaySoundMem(title.decideSE, DX_PLAYTYPE_BACK, true);
            nextScene = SCENE_GAME;
        }
        break;
    }
    Select.timer++;
}

void select_draw(void)
{
    DrawGraph(0, 0, Select.bgHND, false);
    switch (stage.num)
    {
    case STAGE1:
        DrawGraph(0, 0, Select.numHND[STAGE1], true);
        break;
    case STAGE2:
        DrawGraph(0, 0, Select.numHND[STAGE2], true);
        break;
    case STAGE3:
        DrawGraph(0, 0, Select.numHND[STAGE3], true);
        break;
    }

    // debug用 ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "シーン切り替え");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1キー");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2キー");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3キー");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4キー");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5キー");
    //---------------------------------------------------------------
}

void select_end(void)
{
    DeleteGraph(Select.bgHND);
    DeleteSoundMem(Select.decideSE);
    DeleteSoundMem(Select.choiceSE);
    StopSoundMem(title.BGM);
}