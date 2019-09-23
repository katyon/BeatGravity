// �C���N���[�h -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "scene_title.h"
#include "scene_game.h"

// �ϐ� --------------------------------------------------------------------------------------------
// �V�[���؂�ւ��p�ϐ�
int curScene;
int nextScene;

// WinMain -----------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// �t���X�N���[�����[�h�ŋN��
	//ChangeWindowMode(FALSE);

	// �Q�[����ʂ̉𑜓x��ݒ�(32�r�b�g�J���[(�t���J���[))
	SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);

	// �w�i������
	SetBackgroundColor(0, 0, 0);

	// �E�C���h�E�̃^�C�g����ݒ�
	SetMainWindowText("Beat Gravity");

	// �u�����h���[�h�̐ݒ�(�m�[�u�����h)
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �Q�[���V�[���̐ݒ�
	curScene = SCENE_TITLE;
	nextScene = SCENE_TITLE;

	// ���C�u�����̏�����
	if (DxLib_Init() < 0)
		return -1;

	// �^�C�g���̏�����

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// ESC�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ��N���A
		ClearDrawScreen();

		clsDx();

		// ���͏�Ԃ̍X�V����

		// �Q�[���V�[���؂�ւ�
		if (nextScene != curScene)	// ���t���[���ŃV�[���ύX�������
		{
			switch (curScene)		// ���V�[���̏I���������s��
			{
			case SCENE_TITLE:
				title_end();
				break;
			case SCENE_GAME:
				game_end();
				break;
			}

			switch (nextScene)		// ���V�[���̏��������s��
			{
			case SCENE_TITLE:
				title_initialize();
				break;
			case SCENE_GAME:
				game_initialize();
				break;
			}
			curScene = nextScene;	// ���V�[���Ɏ��V�[������
		}

		// ���݂̃V�[���̍X�V����
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			break;
		case SCENE_GAME:
			game_update();
			break;
		}

		// ���݂̃V�[���̕`�揈��
		switch (curScene)
		{
		case SCENE_TITLE:
			title_draw();
			break;
		case SCENE_GAME:
			game_draw();
			break;
		}

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// ���݂̃V�[���̏I������
	switch (curScene)
	{
	case SCENE_TITLE:
		title_end();
		break;
	case SCENE_GAME:
		game_end();
		break;
	}

	// �S�O���t�B�b�N�̍폜
	DxLib::InitGraph();

	// �S���f�[�^�̍폜
	InitSoundMem();

	// ���C�u�����̏I������
	DxLib::DxLib_End();

	// �\�t�g�I��
	return 0;
}