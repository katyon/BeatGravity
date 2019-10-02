#pragma once
// �萔 ----------------------------------------------------------------
#define GRAVITY (1)

// �N���X --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// ���
	int timer = 0;					// �^�C�}�[
    int score = 0;                  // �X�R�A
    int bgposX = 0;                 // �w�iX���W
    int bgposY = 0;                 // �w�iY���W
    int bgspeed = 0;                // �w�i�X�N���[�����x
    bool deathflg = false;          // ���S�Ftrue
    bool clearflg = false;          // �Q�[���N���A�Ftrue
    bool choice = true;             // Yes:true No:false
	int bgHND = 0;					// �w�i�̃f�[�^�n���h��
    int reHND[2] = { 0 };           // ���g���C�I��p�̃f�[�^�n���h��
};

class PLAYER
{
public:
    int state;       // ���
    int posX;        // X���W
    int posY;        // Y���W
    int speed;       // X�������̑��x
    int jumppower;   // �W�����v��
    int gravity;     // �v���C���[�ɂ�����d��
    bool gravityflg; // �d�͂����]���Ă��邩�ǂ����̔���(��������true)
    bool grandflg;   // �n�ʂɂ��邩�ǂ����̔���(�n�ʂȂ�true)
    int plHND;       // player�̃O���t�B�b�N�n���h��
};

// �v���g�^�C�v�錾 -----------------------------------------------------
void game_initialize(void);	// �Q�[���̏����ݒ�
void game_update(void);		// �Q�[���̍X�V����
void game_draw(void);		// �Q�[���̕`�揈��
void game_end(void);		// �Q�[���̏I������

void player_initialize(void);	    // �v���C���[�̏����ݒ�
void player_draw(void);		    	// �v���C���[�̕`�揈��
void player_end(void);		    	// �v���C���[�̏I������

void retry_draw(void);  // ���g���C�̕`�揈��