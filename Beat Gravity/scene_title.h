#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class TITLE
{
public:
	int state = 0;					// ���
	int pltimer = 0;				// �^�C�}�[
    int bgtimer = 0;
    int plposX = 0;
    int plposY = 0;
    int bgposX = 0;
    int bgposY = 0;
    int gravity = 0;
    int pljumppower = 0;
    int plspeed = 0;
    int box_speedX[3] = { 0 };
    int box_speedY[3] = { 0 };
    int box_moveX[3] = { 0 };
    int box_moveY[3] = { 0 };
    int rndX[3] = { 0 };
    int rndY[3] = { 0 };
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    int plHND[5] = { 0 };
    int spaceHND[2] = { 0 };
    int nextHND = 0;
    int BGM = 0;
    int decideSE = 0;              // ���艹
	bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void title_initialize(void);	// �^�C�g���̏����ݒ�
void title_update(void);		// �^�C�g���̍X�V����
void title_draw(void);			// �^�C�g���̕`�揈��
void title_end(void);			// �^�C�g���̏I������