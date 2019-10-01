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
	title.titmer = 0;
	title.transition_flg = false;
	title.bgHND = LoadGraph("Data\\Images\\title_bg.png");
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
		title.state++;
		break;

	case NORMAL:
		///// �ʏ펞 /////
        // debug�p ----------------------
        if (key_trg[KEY_INPUT_LSHIFT])
		{
			nextScene = SCENE_GAME;
		}
        //-------------------------------
		title_draw();
		break;
	}
	title.titmer++;
}

// �^�C�g���̕`�揈��
void title_draw(void)
{
	DrawGraph(0, 0, title.bgHND, false);
}

// �^�C�g���̏I������
void title_end(void)
{
	DeleteGraph(title.bgHND);
}