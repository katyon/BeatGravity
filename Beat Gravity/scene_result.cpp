// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
#include "ranking.h"
#include "scene_result.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];


// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
RESULT result;

// �֐����� ----------------------------------------------------------------------------------------

void result_initialize(void)
{
    result.state = 0;
    result.timer = 0;
    result.transition_flg = false;
    result.bgHND = LoadGraph("Data\\Images\\result_bg.png");
}

void result_update(void)
{
#pragma region KeyUpdate
    //�L�[�̐ݒ�
    char key[MAX_KEY];              //������Ă���ԏ���������
    char key_trg[MAX_KEY] = { 0 };  //�����ꂽ�u�Ԃ�������

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
        ///// �����ݒ� /////
        result.state++;
        break;

    case NORMAL:
        ///// �ʏ펞 /////
        // debug�p ----------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------
        
        // �����L���O

        if (R_flg == true) {
            rank_update();
            R_flg = false;
        }
        break;
    }
    result.timer++;
}

void result_draw(void)
{
    DrawGraph(0, 0, result.bgHND, false);

    // debug�p ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5�L�[");
    //---------------------------------------------------------------
}

void result_end(void)
{
    DeleteGraph(result.bgHND);
}