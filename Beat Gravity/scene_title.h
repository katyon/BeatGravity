#pragma once
// �萔 ----------------------------------------------------------------

// �\���� --------------------------------------------------------------
struct TITLE
{
	int state = 0;					// ���
	int titmer = 0;					// �^�C�}�[
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
	bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void title_initialize(void);	// �^�C�g���̏����ݒ�
void title_update(void);		// �^�C�g���̍X�V����
void title_draw(void);			// �^�C�g���̕`�揈��
void title_end(void);			// �^�C�g���̏I������