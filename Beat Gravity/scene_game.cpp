// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_game.h"
// ���̐錾 ----------------------------------------------------------------------------------------
struct GAME game;

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
	switch (game.state)
	{
	case INIT:
		///// �����ݒ� /////
		game.state++;
		break;

	case NORMAL:
		///// �ʏ펞 /////
		// debug�p
		if (CheckHitKey(KEY_INPUT_1) == 1)
		{
			nextScene = SCENE_TITLE;
		}
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