// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"
// ���̐錾 ----------------------------------------------------------------------------------------
struct TITLE title;

extern int nextScene;

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
	switch (title.state)
	{
	case INIT:
		///// �����ݒ� /////
		title.state++;
		break;

	case NORMAL:
		///// �ʏ펞 /////
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			nextScene = SCENE_GAME;
		}
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