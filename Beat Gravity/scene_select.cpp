// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_select.h"
#include "stage.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
SELECT Select;

extern STAGE stage;
// �֐����� ----------------------------------------------------------------------------------------
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
    Select.numHND[STAGE4] = LoadGraph("Data\\Images\\select4.png");
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
        if (key_trg[KEY_INPUT_5])nextScene = SCENE_RESULT;
        //-------------------------------

        if (stage.num < STAGE4)
        {
            if (key_trg[KEY_INPUT_RIGHT])
            {
                stage.num++;
            }
        }
        if (stage.num > STAGE1)
        {
            if (key_trg[KEY_INPUT_LEFT])
            {
                stage.num--;
            }
        }
        if (key_trg[KEY_INPUT_SPACE])
        {
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
    case STAGE4:
        DrawGraph(0, 0, Select.numHND[STAGE4], true);
        break;
    }

    // debug�p ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5�L�[");
    //---------------------------------------------------------------
}

void select_end(void)
{
    DeleteGraph(Select.bgHND);
}