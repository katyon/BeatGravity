#define _CRT_SECURE_NO_WARNINGS

// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "ranking.h"
#include "scene_game.h"
#include "scene_result.h"
#include "stage.h"

// 変数 --------------------------------------------------------------------------------------------

// インスタンス宣言 ---------------------------------------------------------------------------------
extern GAME game;
extern STAGE stage;
// 関数実体 ----------------------------------------------------------------------------------------
int H_score[Score_h] = { 0,0,0,0,0 };
bool R_flg = true;

void rank_update(void)
{
 
    FILE *fp = 0;
    switch (stage.num)
    {
    case STAGE1:
        fp = fopen("Data\\Score\\scrsave1.txt", "r");
        break;
    case STAGE2:
        fp = fopen("Data\\Score\\scrsave2.txt", "r");
        break;
    //case STAGE3:
    //    fp = fopen("Data\\Score\\scrsave3.txt", "r");
    //    break;
    }
    if (fp != NULL)
    {
        for (int i = 0; i < Score_h; i++)
        {
            //fread(&H_score[i], sizeof(int), 1, fp);
            fscanf(fp, "%d", &H_score[i]);
        }
    }
    if (fp != NULL)
    {
        fclose(fp);
    }

    for (int i = 0; i < Score_h; i++)
    {
        if (H_score[i] <= game.score)
        {
            RankSort(i);
            break;
        }
    }

    switch (stage.num)
    {
    case STAGE1:
        fp = fopen("Data\\Score\\scrsave1.txt", "w");
        break;
    case STAGE2:
        fp = fopen("Data\\Score\\scrsave2.txt", "w");
        break;
    //case STAGE3:
    //    fp = fopen("Data\\Score\\scrsave3.txt", "w");
    //    break;
    }
    if (fp != NULL)
    {
        for (int i = 0; i < Score_h; i++)
        {
            //fwrite(&H_score[i], sizeof(int), 1, fp);
            fprintf(fp, "%d\n", H_score[i]);
        }
    }
    if (fp != NULL)
    {
        fclose(fp);
    }
}

void RankSort(int id) 
{
    for (int i = Score_h - 1; i >= id; i--)
    {
        if (i == id)
        {
            H_score[i] = game.score;
            break;
        }
        else
        {
            H_score[i] = H_score[i - 1];
        }
    }
}