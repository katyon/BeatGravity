// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"

// 変数 --------------------------------------------------------------------------------------------
// キー用変数
char key_buf[MAX_KEY];

// シーン遷移用変数
extern int nextScene;

// インスタンス宣言 ---------------------------------------------------------------------------------
TITLE title;


// 関数実体 ----------------------------------------------------------------------------------------
// タイトルの初期設定
void title_initialize(void)
{
	title.state = 0;
	title.pltimer = 0;
    title.bgtimer = 0;
    title.plposX = -100;
    title.plposY = 600;
    title.bgposX = GAME_SCREEN_WIDTH;
    title.bgposY = 0;
    title.gravity = 2;
    title.pljumppower = 25;
    title.plspeed = 13;
    title.box_speedX[0] = 5;
    title.box_speedY[0] = 2;
    title.box_speedX[1] = 4;
    title.box_speedY[1] = 3;
    title.box_speedX[2] = 3;
    title.box_speedY[2] = 2;
    for (int i = 0; i < 3; i++)
    {
        title.box_moveX[i] = 0;
        title.box_moveY[i] = 0;
        title.rndX[i] = 0;
        title.rndY[i] = 0;
    }
	title.transition_flg = false;
	title.bgHND = LoadGraph("Data\\Images\\title_bg.png");
    LoadDivGraph("Data\\Images\\player.png", 5, 5, 1, 60, 60, title.plHND);
    title.spaceHND[0] = LoadGraph("Data\\Images\\space1.png");
    title.spaceHND[1] = LoadGraph("Data\\Images\\space2.png");
    title.nextHND = LoadGraph("Data\\Images\\next.png");
    title.BGM = LoadSoundMem("Data\\Sounds\\titleBGM.ogg");
    title.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
}

// タイトルの更新処理
void title_update(void)
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
	switch (title.state)
	{
	case INIT:
		///// 初期設定 /////
        PlaySoundMem(title.BGM, DX_PLAYTYPE_LOOP, true);

        title.state = NORMAL;
		break;

	case NORMAL:
		///// 通常時 /////
        // debug用 ----------------------
        //if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        //if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        //if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        //if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        //if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------
        if (key_trg[KEY_INPUT_SPACE])
        {
            PlaySoundMem(title.decideSE, DX_PLAYTYPE_BACK, true);
            title.state = NEXT;
        }

        title.gravity += 2;
        if (title.gravity > 30)
        {
            title.gravity = 30;
        }
        // ジャンプ
        if (title.pltimer == 60 || title.pltimer == 75)
        {
            title.gravity -= title.pljumppower;
        }
        if (title.plposY > 780 - CHIP_SIZE)
        {
            title.plposY = 780 - CHIP_SIZE;
            title.gravity = 0;
        }
        if (title.plposX > 2200)
        {
            title.plposX = -100;
            title.pltimer = 0;
        }
        title.plposX += title.plspeed;
        title.plposY += title.gravity;

		break;
    case NEXT:
        title.gravity += 2;
        if (title.gravity > 30)
        {
            title.gravity = 30;
        }
        // ジャンプ
        if (title.pltimer == 60 || title.pltimer == 75)
        {
            title.gravity -= title.pljumppower;
        }
        if (title.plposY > 780 - CHIP_SIZE)
        {
            title.plposY = 780 - CHIP_SIZE;
            title.gravity = 0;
        }
        if (title.plposX > 2200)
        {
            title.plposX = -100;
            title.pltimer = 0;
        }
        title.plposX += title.plspeed;
        title.plposY += title.gravity;

        title.bgposX -= title.bgtimer;
        if (title.bgposX < 0)
        {
            title.bgposX = 0;
            nextScene = SCENE_SELECT;
        }

        title.bgtimer++;
        break;
	}
	title.pltimer++;
}

// タイトルの描画処理
void title_draw(void)
{
    unsigned int Cr;
    Cr = GetColor(0, 0, 0);

    DrawGraph(title.bgposX - GAME_SCREEN_WIDTH, 0, title.bgHND, true);
    DrawGraph(588 + title.bgposX - GAME_SCREEN_WIDTH, 825, title.spaceHND[title.pltimer / 30 % 2], true);

    DrawGraph(title.plposX, title.plposY, title.plHND[title.pltimer / 3 % 5], true);
    if (title.plposY > 780 - CHIP_SIZE)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - title.box_moveX[0] * 2);

        for (int i = 0; i < 3; i++)
        {
            DrawBox(title.plposX - 10 - title.rndX[i] - title.box_moveX[i], title.plposY + CHIP_SIZE - title.rndY[i] - title.box_moveY[i],
                title.plposX - title.rndX[i] - title.box_moveX[i], title.plposY + CHIP_SIZE, Cr, true);
        }

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        for (int i = 0; i < 3; i++)
        {
            if (title.box_moveX[i] > 80)
            {
                title.rndX[i] = GetRand(6) * 5;
                title.rndY[i] = GetRand(6) * 5;
                title.box_moveX[i] = 0;
                title.box_moveY[i] = 0;
                title.box_speedY[i] = title.box_speedY[i] * -1;
            };
            if (title.box_moveY[i] > 30)
            {
                title.box_speedY[i] = title.box_speedY[i] * -1;
            }
            title.box_moveX[i] += title.box_speedX[i];
            title.box_moveY[i] += title.box_speedY[i];
        }
    }
    DrawGraph(title.bgposX, title.bgposY, title.nextHND, true);
}

// タイトルの終了処理
void title_end(void)
{
	DeleteGraph(title.bgHND);
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(title.spaceHND[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        DeleteGraph(title.plHND[i]);
    }
    DeleteGraph(title.nextHND);
    DeleteSoundMem(title.decideSE);
    DeleteSoundMem(title.BGM);
}
