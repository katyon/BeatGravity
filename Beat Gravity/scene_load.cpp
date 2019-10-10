// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_load.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
LOAD load;


// �֐����� ----------------------------------------------------------------------------------------
void load_initialize(void)
{
    load.state = 0;
    load.timer = 0;
    load.transition_flg = false;
    load.bgHND = LoadGraph("Data\\Images\\load_bg.png");
}

void load_update(void)
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
    switch (load.state)
    {
    case INIT:
        ///// �����ݒ� /////
        load.state = NORMAL;
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
        break;
    }
    load.timer++;
}

void load_draw(void)
{
    DrawGraph(0, 0, load.bgHND, false);

    // debug�p ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5�L�[");
    //---------------------------------------------------------------
}

void load_end(void)
{
    DeleteGraph(load.bgHND);
}