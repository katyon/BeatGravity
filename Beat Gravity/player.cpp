//// �C���N���[�h -------------------------------------------------------------------------------------
//#include "DxLib.h"
//
//#include "common.h"
//#include "input.h"
//#include "player.h"
//#include "stage.h"
//
//// �ϐ� --------------------------------------------------------------------------------------------
//// �L�[�p�ϐ�
//extern char key_buf[MAX_KEY];
//
//// �V�[���J�ڗp�ϐ�
//extern int nextScene;
//
//// �C���X�^���X�錾 ---------------------------------------------------------------------------------
//PLAYER pl;
//
//// �֐����� ----------------------------------------------------------------------------------------
//// �v���C���[�̏����ݒ�
//void player_initialize(void)
//{
//    pl.state = 0;
//    pl.posX = 0;
//    pl.posY = 0;
//    pl.pivotX = 0;
//    pl.pivotY = 0;
//    pl.speed = 5;
//    pl.jumppower = 0;
//    pl.jumpflg = false;
//    pl.plHND = LoadGraph("Data\\Images\\player.png");
//}
//
//// �v���C���[�̍X�V����
//void player_update(void)
//{
//#pragma region KeyUpdate
//    //�L�[�̐ݒ�
//    char key[MAX_KEY];              //������Ă���ԏ���������
//    char key_trg[MAX_KEY] = { 0 };  //�����ꂽ�u�Ԃ�������
//
//    GetHitKeyStateAll(key);
//
//    for (int n = 0; n < MAX_KEY; n++)
//    {
//        if (key[n] && !(key_buf[n])) key_trg[n] = key[n];
//        key_buf[n] = key[n];
//    }
//#pragma endregion
//
//    // �v���C���[�̒��S���W���X�V
//    pl.pivotX = pl.posX + CHIP_SIZE / 2;
//    pl.pivotY = pl.posY + CHIP_SIZE / 2;
//
//    // �}�b�v�`�b�v���Ƃ̋���
//    // ��
//    if (detect_chip(pl.posX, pl.posY + CHIP_SIZE, STAGE4) == 1 ||
//        detect_chip(pl.posX + CHIP_SIZE, pl.posY + CHIP_SIZE, STAGE4) == 1)
//    {
//        // �󒆂ɂ��邩�ǂ����̔���
//        pl.jumpflg = false;
//        // �ړ�����
//        pl.posY = pl.posY / CHIP_SIZE * CHIP_SIZE;
//        pl.jumppower = 0;
//    }
//    else
//    {
//        pl.jumpflg = true;
//    }
//
//    // ���R����
//    pl.posY -= pl.jumppower;
//    pl.jumppower -= 1;
//
//    // �W�����v
//    if (pl.jumpflg == true && key[KEY_INPUT_SPACE])
//    {
//        pl.jumppower = 20;
//    }
//    // debug�p------------------
//    if (key[KEY_INPUT_LEFT])
//    {
//        pl.posX -= pl.speed;
//    }
//    if (key[KEY_INPUT_RIGHT])
//    {
//        pl.posX += pl.speed;
//    }
//    if (key[KEY_INPUT_UP])
//    {
//        pl.posY -= 50;
//    }
//    if (key[KEY_INPUT_DOWN])
//    {
//        pl.posY += pl.speed;
//    }
//    //---------------------------
//}
//
//// �v���C���[�̕`�揈��
//void player_draw(void)
//{
//    DrawGraph(pl.posX, pl.posY, pl.plHND, true);
//    // debug�p
//    DrawBox(pl.posX, pl.posY, pl.posX + CHIP_SIZE - 1, pl.posY + CHIP_SIZE - 1, GetColor(1, 1, 1), FALSE);
//}
//
//// �v���C���[�̏I������
//void player_end(void)
//{
//    DeleteGraph(pl.plHND);
//}