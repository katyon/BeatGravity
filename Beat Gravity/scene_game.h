#pragma once
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// ���
	int titmer = 0;					// �^�C�}�[
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
	bool transition_flg = false;	// �V�[���J�ڗp�̃t���O
};

class PLAYER
{
public:
    int state;       // ���
    int posX;        // X���W
    int posY;        // Y���W
    int pivotX;      // ���SX���W
    int pivotY;      // ���SY���W
    int speed;       // X�������̑��x
    int jumppower;   // �W�����v��
    bool jumpflg;    // �󒆂ɂ��邩�ǂ����̔���(�󒆂Ȃ�true)
    int plHND;       // player�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void game_initialize(void);	// �Q�[���̏����ݒ�
void game_update(void);		// �Q�[���̍X�V����
void game_draw(void);		// �Q�[���̕`�揈��
void game_end(void);		// �Q�[���̏I������

void player_initialize(void);	    // �v���C���[�̏����ݒ�
void player_update(void);	    	// �v���C���[�̍X�V����
void player_draw(void);		    	// �v���C���[�̕`�揈��
void player_end(void);		    	// �v���C���[�̏I������