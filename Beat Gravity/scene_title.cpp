// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
char key_buf[MAX_KEY];

// �V�[���J�ڗp�ϐ�
extern int nextScene;

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
TITLE title;


// �֐����� ----------------------------------------------------------------------------------------
// �^�C�g���̏����ݒ�
void title_initialize(void)
{
	title.state = 0;
	title.timer = 0;
	title.transition_flg = false;
	title.bgHND = LoadGraph("Data\\Images\\title_bg.png");
    title.spaceHND[0] = LoadGraph("Data\\Images\\space1.png");
    title.spaceHND[1] = LoadGraph("Data\\Images\\space2.png");
    title.BGM = LoadSoundMem("Data\\Sounds\\titleBGM.ogg");
    title.decideSE = LoadSoundMem("Data\\Sounds\\decideSE.ogg");
}

// �^�C�g���̍X�V����
void title_update(void)
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
	switch (title.state)
	{
	case INIT:
		///// �����ݒ� /////
        PlaySoundMem(title.BGM, DX_PLAYTYPE_LOOP, true);

        title.state = NORMAL;
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
        if (key_trg[KEY_INPUT_SPACE])
        {
            PlaySoundMem(title.decideSE, DX_PLAYTYPE_BACK, true);
            nextScene = SCENE_SELECT;
        }
		break;
	}
	title.timer++;
}

// �^�C�g���̕`�揈��
void title_draw(void)
{
	DrawGraph(0, 0, title.bgHND, false);
    DrawGraph(588,825, title.spaceHND[title.timer / 30 % 2], true);

    // debug�p ---------------------------------------------------------
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�[���؂�ւ�");
    DrawFormatString(0, 20, GetColor(255, 255, 255), "title:1�L�[");
    DrawFormatString(0, 40, GetColor(255, 255, 255), "select:2�L�[");
    DrawFormatString(0, 60, GetColor(255, 255, 255), "load:3�L�[");
    DrawFormatString(0, 80, GetColor(255, 255, 255), "game:4�L�[");
    DrawFormatString(0, 100, GetColor(255, 255, 255), "result:5�L�[");
    //---------------------------------------------------------------
}

// �^�C�g���̏I������
void title_end(void)
{
	DeleteGraph(title.bgHND);
    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(title.spaceHND[i]);
    }
    DeleteSoundMem(title.decideSE);
    DeleteSoundMem(title.BGM);
}