#pragma once
// �萔 ----------------------------------------------------------------

// �\���� --------------------------------------------------------------
struct GAME
{
	int state = 0;					// ���
	int titmer = 0;					// �^�C�}�[
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
	bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void game_initialize(void);	// �Q�[���̏����ݒ�
void game_update(void);		// �Q�[���̍X�V����
void game_draw(void);		// �Q�[���̕`�揈��
void game_end(void);		// �Q�[���̏I������