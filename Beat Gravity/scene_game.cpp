// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "input.h"
#include "scene_game.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �L�[�p�ϐ�
extern char key_buf[MAX_KEY];

// �C���X�^���X�錾 ---------------------------------------------------------------------------------
GAME game;

extern int nextScene;

// �֐����� ----------------------------------------------------------------------------------------
// �Q�[���̏����ݒ�
void game_initialize(void)
{
	game.state = 0;
	game.titmer = 0;
	game.transition_flg = false;
	game.bgHND = LoadGraph("Data\\Images\\game_bg1.png");
}

// �Q�[���̍X�V����
void game_update(void)
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
	switch (game.state)
	{
	case INIT:
		///// �����ݒ� /////
		game.state++;
		break;

	case NORMAL:
		///// �ʏ펞 /////
		// debug�p-------------------------
		if (key_trg[KEY_INPUT_SPACE])
		{
			nextScene = SCENE_TITLE;
		}
        //---------------------------------
		game_draw();
		break;
	}
	game.titmer++;
}

// �Q�[���̕`�揈��
void game_draw(void)
{
	DrawGraph(0, 0, game.bgHND, false);
}

// �Q�[���̏I������
void game_end(void)
{
	DeleteGraph(game.bgHND);
}