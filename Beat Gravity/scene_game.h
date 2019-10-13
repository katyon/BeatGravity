#pragma once
// �萔 ----------------------------------------------------------------
#define GRAVITY     (2)
#define SCORE_ITEM1  (10)
#define SCORE_ITEM2  (15)
#define SWAP_SPEED  (20)

// �N���X --------------------------------------------------------------
class GAME
{
public:
	int state = 0;					// ���
	int timer = 0;					// �^�C�}�[
    int score = 0;                  // �X�R�A
    int bg1posX = 0;                // �w�iX���W
    int bg1posY = 0;                // �w�iY���W
    int bg1speed = 0;               // �w�i�X�N���[�����x
    int bg2posX = 0;                // �w�iX���W
    int bg2posY = 0;                // �w�iY���W
    int bg2speed = 0;               // �w�i�X�N���[�����x
    int alpha1;                     // ���l
    int alpha2;
    float angle1;                   // �`��p�x
    float angle2;
    bool deathflg = false;          // ���S�Ftrue
    bool clearflg = false;          // �Q�[���N���A�Ftrue
    bool choice = true;             // Yes:true No:false
    int bgHND[4] = { 0 };		    // �w�i�̃f�[�^�n���h��
    int reHND[2] = { 0 };           // ���g���C�I��p�̃f�[�^�n���h��
    int bgmHND = 0;
    int decideSE = 0;
    int choiceSE = 0;
    int deathSE = 0;                // ���SSE
};

class PLAYER
{
public:
    int state = 0;          // ���
    int box_moveX[3] = { 0 };    // �q���p
    int box_moveY[3] = { 0 };
    int box_speedX[3] = { 0 };
    int box_speedY[3] = { 0 };
    int rndX[3] = { 0 };
    int rndY[3] = { 0 };
    int init_posX = 0;      // �Q�[���J�n����X���W
    int init_posY = 0;      // �Q�[���J�n����Y���W
    int posX = 0;           // X���W
    int posY = 0;           // Y���W
    int death_posX[10] = { 0 };
    int death_posY[10] = { 0 };
    int death_rndX[10] = { 0 };
    int death_rndY[10] = { 0 };
    int death_speed = 0;
    int speed = 0;          // X�������̑��x
    int jumppower = 0;      // �W�����v��
    int gravity = 0;        // �v���C���[�ɂ�����d��
    bool gravityflg = true;    // �d�͂����]���Ă��邩�ǂ����̔���(��������true)
    bool grandflg = true;      // �n�ʂɂ��邩�ǂ����̔���(�n�ʂȂ�true)
    int plHND[5] = { 0 };       // player�̃O���t�B�b�N�n���h��
    int deathHND = 0;
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

//void sound_play(void);  // BGM�̍Đ�����