// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_select.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
SELECT Select;


// �֐����� ----------------------------------------------------------------------------------------
void select_initialize(void)
{
    Select.state = 0;
    Select.timer = 0;
    Select.transition_flg = false;
    Select.bgHND = LoadGraph("Data\\Images\\select_bg.png");
}

void select_update(void)
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
    switch (Select.state)
    {
    case INIT:
        ///// �����ݒ� /////
        Select.state++;
        break;

    case NORMAL:
        ///// �ʏ펞 /////
        // debug�p ----------------------
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_TITLE;
        if (key_trg[KEY_INPUT_2])nextScene = SCENE_SELECT;
        if (key_trg[KEY_INPUT_3])nextScene = SCENE_LOAD;
        if (key_trg[KEY_INPUT_4])nextScene = SCENE_GAME;
        if (key_trg[KEY_INPUT_1])nextScene = SCENE_RESULT;
        //-------------------------------
        break;
    }
    Select.timer++;
}

void select_draw(void)
{
    DrawGraph(0, 0, Select.bgHND, false);
}

void select_end(void)
{
    DeleteGraph(Select.bgHND);
}