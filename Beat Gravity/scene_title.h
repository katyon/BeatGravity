#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class TITLE
{
public:
	int state = 0;					// ���
	int timer = 0;					// �^�C�}�[
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    int BGM = 0;
    int decideSE = 0;              // ���艹
	bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void title_initialize(void);	// �^�C�g���̏����ݒ�
void title_update(void);		// �^�C�g���̍X�V����
void title_draw(void);			// �^�C�g���̕`�揈��
void title_end(void);			// �^�C�g���̏I������