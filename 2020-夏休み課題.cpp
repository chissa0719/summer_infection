// 
//
//�@���]�H�ƍ������w�Z�@J1919  �����猫
//							
//
//  �f�ތ�
//
//	�V���[�e�B���O(�S��)�Q�l : shootingDX2�����ǉ�.cpp
//								 https://wbt2020.matsue-ct.jp/pluginfile.php/2098/mod_resource/content/1/shootingDX2%E7%88%86%E7%99%BA%E8%BF%BD%E5%8A%A0.cpp
//
//	�V���[�e�B���O(�e�֌W)�Q�l : �Q�[������u���P�|�R �R�D���@���e�����Ă�悤�ɂ��悤 https://dxlib.xsrv.jp/lecture/lecture1_3.html
//
//	�V���[�e�B���O�w�i : ���܂���A�t�^�[�w�i���ޒu����  https://k-after.at.webry.info/201009/article_1.html
//
//  ���@�摜 : ���炷�Ƃ�  https://www.irasutoya.com/2016/05/blog-post_187.html
//
//  �G�@�摜 : silhouetteAC  https://www.silhouette-ac.com/category.html?sw=%E8%8F%8C&nq=&srt=dlrank
//
//�@�E�ۃt�F�[�Y�w�i�摜 : freepik https://jp.freepik.com/free-vector/soap-bubbles-floating-in-the-green-background-vector_4159922.htm#page=1&query=%E3%82%B7%E3%83%A3%E3%83%9C%E3%83%B3%E7%8E%89&position=22
//
//�@�����摜�F 
//
//
//////////////////////////////////////////////////////////////////////

#include<DxLib.h>


#define WAIT_TIME 5
#define ENEMY_NUM 3
#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define CHARACTER_SIZE_X 150
#define CHARACTER_SIZE_Y 120
#define ENEMY_SIZE_X 90
#define ENEMY_SIZE_Y 70
#define CHAR_CLOLOR GetColor( 255, 255, 0 )
#define BLAST_FIG_NUM 16 //��������A�j���̉摜��
#define My_Speed 30 // ���@�ړ����x

struct Position
{
	int x;
	int y;
	int isExist;//���݂�����P�A���Ȃ�������O
};

// �O���[�o���ϐ�
struct Position c; //���@�̏ꏊ 
struct Position e[ENEMY_NUM]; //�G�ꏊ
int enemy_num = ENEMY_NUM; //�����Ă���G�̐�
int time; //�c�莞��
int BlastHandle[BLAST_FIG_NUM]; //�����摜�n���h��
static int level = 0;


// �e�평����
void init()
{
	int i;
	c.x = WINDOW_SIZE_X / 2;
	c.y = WINDOW_SIZE_Y - CHARACTER_SIZE_Y;

	enemy_num = ENEMY_NUM;

	for (i = 0; i < ENEMY_NUM; i++)
	{
		e[i].x = rand() % WINDOW_SIZE_X;
		e[i].y = rand() % WINDOW_SIZE_Y;
		e[i].isExist = TRUE;
	}
}

// ���[�v�̌v�Z
int getWarpPos(int pos, int window_size)
{
	int w;
	w = (pos + window_size) % window_size;
	return w;
}

// ���@�̈ړ�
// �L�[�{�[�h�ɍ��킹�Ĉړ�
void moveRocket()
{

	// �� �L�[
	if (CheckHitKey(KEY_INPUT_RIGHT)) {

		c.x += My_Speed;

	}

	// �� �L�[
	if (CheckHitKey(KEY_INPUT_LEFT)) {

		c.x -= My_Speed;

	}

	c.x = getWarpPos(c.x, WINDOW_SIZE_X); //���[�v
	c.y = getWarpPos(c.y, WINDOW_SIZE_Y);

}

// �G�@�̈ړ�(���[�v�܂�)
void moveEnemy(int i)
{
	e[i].y += 8;
	e[i].x = getWarpPos(e[i].x, WINDOW_SIZE_X);
	e[i].y = getWarpPos(e[i].y, WINDOW_SIZE_Y);
}


int isOnEnemy(int x, int y) {


	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (e[i].isExist == FALSE) {
			continue;
		}


		if (c.x + CHARACTER_SIZE_X + 110 >= e[i].x && c.x <= e[i].x + CHARACTER_SIZE_X - 110 &&
			c.y + CHARACTER_SIZE_Y + 50 >= e[i].y && c.y <= e[i].y + CHARACTER_SIZE_Y - 50) {
			return i;
		}
	}

	return -1;
}

/*int isOnShot(int ShotX, int ShotY) {


	for (int p = 0; p <= ENEMY_NUM; p++) {

		if (e[p].isExist == FALSE) {
			continue;
		}


		if (ShotX + CHARACTER_SIZE_X + 110 >= e[p].x && ShotX <= e[p].x + CHARACTER_SIZE_X - 110 &&
			ShotY + CHARACTER_SIZE_Y + 50 >= e[p].y && ShotY <= e[p].y + CHARACTER_SIZE_Y - 50) {
			return p;
		}


	}

	return -1;

}*/


//�\��
void Draw()
{
	int i;

	// �摜�o�^
	int TITLEpicture = LoadGraph("images/�񓇊���TITLEpicture.jpg"); // �^�C�g���摜
	int ShooterHandle = LoadGraph("images/�񓇊���-�V���[�e�B���O-�h�앞2.png"); // �V���[�e�B���O���@
	int EnemyHandle = LoadGraph("images/�񓇊���-�E�C���X-removebg-preview.png"); // �V���[�e�B���O�G�@
	int BackHandle = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // �V���[�e�B���O�w�i(��)
	int shot = LoadGraph("images/�񓇊���-�V���[�e�B���O-�e.jpg"); // �e�̊G(��)


	// �V���[�e�B���O�w�i��\��
	DrawExtendGraph(0, 0, 1024, 768, BackHandle, FALSE);


	for (i = 0; i < ENEMY_NUM; i++) {
		//�G�@��`��

		if (e[i].isExist == FALSE) {
			continue;
		}

		DrawExtendGraph(e[i].x, e[i].y, e[i].x + ENEMY_SIZE_X, e[i].y + ENEMY_SIZE_Y, EnemyHandle, TRUE);
	}


	//���@��`��
	DrawExtendGraph(c.x, c.y, c.x + CHARACTER_SIZE_X, c.y + CHARACTER_SIZE_Y, ShooterHandle, TRUE);


	//���_�\���@
	DrawFormatString(10, 10, CHAR_CLOLOR, "�c��G��: %d  ����LEVEL: %d", enemy_num, level);


	// �҂�����
	WaitTimer(WAIT_TIME);

}

// ���@�ƓG�̏Փ�
void hit(int attackedEnemy)
{
	static int HitHandle = LoadSoundMem("se_mod04.wav");//�Փˉ��̎��ʔԍ�
	int i;

	for (i = 0; i < BLAST_FIG_NUM; i++)
	{
		DrawGraph(e[attackedEnemy].x - 35, e[attackedEnemy].y - 30, BlastHandle[i], TRUE);
		WaitTimer(30); //�\������������ƌ����Ȃ��̂ŏ����҂�
	}
	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[attackedEnemy].isExist = FALSE;
	enemy_num--;
	level++;
	WaitTimer(1000);
}

// �e�ƓG�̏Փ�
/*void Enemyhit(int hitEnemy) {

	static int HitHandle = LoadSoundMem("se_mod04.wav");//�Փˉ��̎��ʔԍ�

	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[hitEnemy].isExist = FALSE;
	enemy_num--;
	WaitTimer(5);

}*/

//�Q�[���I�[�o�[
void gameOver()
{

	// �摜�o�^
	int badend = LoadGraph("images/�񓇊���-BadEnd-picture.jpg"); // BadEnd�w�i


	// �G���h���[�����o�^
	int end = LoadSoundMem("musics/�񓇊���(�G���h���[����).m4a");


	// �F�擾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// ��ʃN���A
	ClearDrawScreen();


	// �����T�C�Y����
	SetFontSize(30);


	// Bad End�����Đ�
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// �G���h���[��
	for (int s = 15; s <= 3000; s++) {


		// �`���𗠉�ʂɂ��� (��ʃ`�J�`�J�h�~��@)
		SetDrawScreen(DX_SCREEN_BACK);


		// �w�i�`��
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// �c�X�N���[��
		DrawFormatString(380, 900 - s, white, "���ā@�@�����猫");

		DrawFormatString(380, 1100 - s, white, "���y�@�@�����猫");
		DrawFormatString(380, 1300 - s, white, "�ʐ^�@�@yukari");
		DrawFormatString(380, 1400 - s, white, "�@�@�@�@�����猫");

		DrawFormatString(380, 1800 - s, white, "����@�@�����猫");
		DrawFormatString(360, 2000 - s, white, "���싦�́@�@yori");

		DrawFormatString(385, 2800 - s, white, "�`�`Bad End�`�`");


		// ����ʂ̓��e��\��ʂɔ��f (��ʃ`�J�`�J�h�~��A)
		ScreenFlip();


		// ���x����
		WaitTimer(5);


		// �v�����[�O�J�b�g�@�\(���N���b�N�ŃX�L�b�v)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any Key����ʒ����ɂ�����X�N���[����~
		if (s == 2430) {


			// �`����\��ʂɂ��� 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ����Key���������܂őҋ@
			WaitKey();

			break;

		}
		else {

			// ��ʃN���A
			ClearDrawScreen();

		}

	}

}


void gameclear()
{

	// �摜�o�^
	int badend = LoadGraph("images/�񓇊���-BadEnd-picture.jpg"); // �w�i


	// �G���h���[�����o�^
	int end = LoadSoundMem("musics/�񓇊���(�G���h���[����).m4a");


	// �F�擾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// ��ʃN���A
	ClearDrawScreen();


	// �����T�C�Y����
	SetFontSize(30);


	// Bad End�����Đ�
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// �G���h���[��
	for (int s = 15; s <= 3000; s++) {


		// �`���𗠉�ʂɂ��� (��ʃ`�J�`�J�h�~��@)
		SetDrawScreen(DX_SCREEN_BACK);


		// �w�i�`��
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// �c�X�N���[��
		DrawFormatString(380, 900 - s, white, "���ā@�@�����猫");

		DrawFormatString(380, 1100 - s, white, "���y�@�@�����猫");
		DrawFormatString(380, 1300 - s, white, "�ʐ^�@�@yukari");
		DrawFormatString(380, 1400 - s, white, "�@�@�@�@�����猫");

		DrawFormatString(380, 1800 - s, white, "����@�@�����猫");
		DrawFormatString(360, 2000 - s, white, "���싦�́@�@yori");

		DrawFormatString(385, 2800 - s, white, "�`�`Happy End�`�`");


		// ����ʂ̓��e��\��ʂɔ��f (��ʃ`�J�`�J�h�~��A)
		ScreenFlip();


		// ���x����
		WaitTimer(5);


		// �v�����[�O�J�b�g�@�\(���N���b�N�ŃX�L�b�v)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any Key����ʒ����ɂ�����X�N���[����~
		if (s == 2430) {


			// �`����\��ʂɂ��� 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ����Key���������܂őҋ@
			WaitKey();

			break;

		}
		else {

			// ��ʃN���A
			ClearDrawScreen();

		}

	}

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	int day = 0; // ���t
	int i = 0;
	int Mx, My; // �}�E�X���W
	extern int level; // �������x��(�O���ɐ錾�ς݂̍��}��extern)
	int time = 20000; // �V���[�e�B���O���Ԑ���
	int ShotX, ShotY, ShotFlag = 0; // �e�̍��W�A�e�̃t���O
	int SikakuW, SikakuH, ShotW, ShotH;


	// �E�B���h�E���[�h�ɕύX
	ChangeWindowMode(TRUE);


	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1024, 768, 32);


	// �}�E�X��\��
	SetMouseDispFlag(TRUE);


	// DxLib������
	if (DxLib_Init() == -1)
	{
		return -1;
	}


	// �^�C�g�����o�^
	int TITLE = LoadSoundMem("musics/�񓇊���(�^�C�g�����.m4a");


	// �V���[�e�B���O���o�^
	int shooting = LoadSoundMem("musics/�񓇊���(�V���[�e�B���O��).m4a");


	// �E�ۃt�F�[�Y���o�^
	int kill = LoadSoundMem("musics/�񓇊���(�E�ۃt�F�[�Y��).m4a");


	// �􂤉��o�^
	int washsound = LoadSoundMem("musics/�񓇊���(�􂤉�).mp3");


	// �G���h���[�����o�^
	int end = LoadSoundMem("musics/�񓇊���(�G���h���[����).m4a");


	// �^�C�g�����Đ�
	PlaySoundMem(TITLE, DX_PLAYTYPE_LOOP);


	// �F�擾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);
	int crimson = GetColor(220, 20, 60);
	int deepskyblue = GetColor(0, 191, 255);
	int green = GetColor(153, 255, 0);
	int blue = GetColor(0, 153, 255);
	int black = GetColor(0, 0, 0);


	// �摜�o�^
	int TITLEpicture = LoadGraph("images/�񓇊���TITLEpicture.jpg"); // �^�C�g���摜
	int Chara = LoadGraph("images/�񓇊���-�V���[�e�B���O-�h�앞2.png"); // �V���[�e�B���O���@
	int virus = LoadGraph("images/�񓇊���-�E�C���X-removebg-preview.png"); // �V���[�e�B���O�G�@
	int shootingpicture = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // �V���[�e�B���O�w�i(��)
	int ShotGraph = LoadGraph("images/�񓇊���-�V���[�e�B���O-�e.jpg"); // �e�̊G(��)
	int badend = LoadGraph("images/�񓇊���-BadEnd-picture.jpg"); // BadEnd�w�i
	int wash = LoadGraph("images/�񓇊���-�E�ۃt�F�[�Y�w�i.jpg"); // �E�ۃt�F�[�Y�w�i



	// �^�C�g�����(ESC���������܂Ń��[�v)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// �^�C�g���摜�\��
		DrawExtendGraph(0, 0, 1024, 768, TITLEpicture, FALSE);


		// �^�C�g�������\��
		SetFontSize(90);
		DrawFormatString(200, 70, porple, "�񓇊���");
		SetFontSize(30);
		DrawFormatString(150, 170, white, "�`�N�͂��̊�@�����킹��̂��`");


		// �e��R�}���h�z�u
		SetFontSize(40);
		DrawFormatString(440, 400, porple2, "START");


		// �}�E�X�̍��W�擾
		GetMousePoint(&Mx, &My);


		// �u�͂��߂�v���N���b�N�ŃQ�[���X�^�[�g
		if (Mx >= 436 && Mx <= 546 && My <= 432 && My >= 400 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			break;
		}


	}


	// ��ʃN���A
	ClearDrawScreen();


	// �����T�C�Y����
	SetFontSize(20);


	// �v�����[�O

	for (int i = 1; i <= 1600; i++) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// �`���𗠉�ʂɂ��� (��ʃ`�J�`�J�h�~��@)
		SetDrawScreen(DX_SCREEN_BACK);


		// �c�X�N���[��
		DrawFormatString(170, 600 - i, white, "20�~�~�N....");

		DrawFormatString(170, 700 - i, white, "��X�̈�����񓇂́A");
		DrawFormatString(170, 800 - i, white, "�Љ�o�ς⋳��@�ւ���������");
		DrawFormatString(170, 900 - i, white, "���������������m�̋ۂɍ���|�M����Ă���B");

		DrawFormatString(170, 1000 - i, white, "���̖��m�Ȃ�ۂ̊�������");
		DrawFormatString(170, 1100 - i, white, "��������ʊ��ɓ����ɒ���");
		DrawFormatString(170, 1200 - i, white, "�N�͓c�ɗE�҂ƂȂ鎖���ł���̂�!?");

		DrawFormatString(420, 2000 - i, white, "Press any Key");


		// ����ʂ̓��e��\��ʂɔ��f (��ʃ`�J�`�J�h�~��A)
		ScreenFlip();


		WaitTimer(20);


		// �v�����[�O�J�b�g�@�\(���N���b�N�ŃX�L�b�v)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && i > 15) {

			i = 1599;

		}


		// Press any Key����ʒ����ɂ�����X�N���[����~
		if (i == 1600) {


			// �`����\��ʂɂ��� 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ����Key���������܂őҋ@
			WaitKey();

			break;

		}
		else {

			// ��ʃN���A
			ClearDrawScreen();

		}

	}


	// ��ʃN���A
	ClearDrawScreen();


	// ���y���~
	StopSoundMem(TITLE);


	// 3���ڂ܂Ŋ������Ȃ���΃Q�[���N���A
	while (day <= 3) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// ���t�\��
		SetFontSize(60);
		day++;
		DrawFormatString(370, 350, crimson, " %d �� ��", day);
		SetFontSize(30);
		DrawFormatString(390, 550, white, "Press any Key...");


		// ���͑҂�
		WaitKey();


		// �V���[�e�B���O�w�i��\��
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// �V���[�e�B���O�����Đ�
		PlaySoundMem(shooting, DX_PLAYTYPE_LOOP);


		// �������(��)
		SetFontSize(30);
		DrawFormatString(310, 100, white, "�h��t�F�[�Y�@�������");
		DrawFormatString(110, 250, white, "�E�����Ă���׋ۂ��A���R�[���e�Ō����E�����I�I");
		DrawFormatString(110, 300, white, "�E���肭��ۂɓ������Ă��܂��ƁA����LEVEL���P�㏸�I�I");
		DrawFormatString(110, 350, white, "�E����LEVEL��3�ȏ�ő��Q�[���I�[�o�[�I�I");
		DrawFormatString(290, 450, white, "�ړ��@��[ �� ]�@�E[ �� ]");
		DrawFormatString(310, 500, white, "�e�̔��ˁ@���N���b�N");
		DrawFormatString(390, 650, white, "Press any Key");


		// ���͑҂�
		WaitKey();


		// ��ʃN���A
		ClearDrawScreen();


		// �h��t�F�[�Y(���Ԑ؂�܂Ń��[�v)

		init();
		Draw();


		for (time = 20000; time >= 0; time--) {


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// �`���𗠉�ʂɂ��� (��ʃ`�J�`�J�h�~��@)
			SetDrawScreen(DX_SCREEN_BACK);


			int attackedEnemy;


			// ���@�̈ړ�
			moveRocket();


			// �G�@�̈ړ�
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				moveEnemy(j);
			}


			// ���b�Z�[�W���[�v�ɑ��鏈��������
			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// �e�̔���(�X�y�[�X�L�[�Ŕ���)
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && ShotFlag == 0) {

				int Bw, Bh, Sw, Sh;

				// ���@�ƒe�̉摜�̃T�C�Y�𓾂�
				GetGraphSize(Chara, &Bw, &Bh);
				GetGraphSize(ShotGraph, &Sw, &Sh);


				// ���@�̃O���t�B�b�N�̃T�C�Y�𓾂�
				GetGraphSize(Chara, &SikakuW, &SikakuH);


				// �e�̃O���t�B�b�N�̃T�C�Y�𓾂�
				GetGraphSize(ShotGraph, &ShotW, &ShotH);


				// �e�̈ʒu���Z�b�g�A�ʒu�����@�̒��S�ɂ���
				ShotX = ((Bw - Sw) / 2 + c.x) - 15;
				ShotY = ((Bh - Sh) / 2 + c.y) + 50;

				// �t���O����
				ShotFlag = 1;

			}


			//��ʕ\��
			Draw();


			// ���@�̒e�̈ړ�
			if (ShotFlag == 1)
			{
				// �e�̈ړ����x
				ShotY -= 50;

				// ��ʊO�ɍs���ƁA�e�͏���
				if (ShotY < -30)
				{
					// �t���O��܂�
					ShotFlag = 0;
				}

				// ��ʂɒe��`�悷��
				DrawGraph(ShotX - 46, ShotY + 50, ShotGraph, FALSE);
			}


			//���@�ƓG�̓����蔻��
			attackedEnemy = isOnEnemy(c.x, c.y);

			if (attackedEnemy >= 0)
			{
				hit(attackedEnemy);
			}


			// �G�@�ƒe�̓����蔻��
			/*if (ShotFlag == 1)
			{
				if (((ShotX - 46 > c.x && ShotX - 46 < c.x + ) ||(c.x > ShotX - 46 && c.x < ShotX - 46 + ShotW)) &&
					((ShotY + 50 > c.y && ShotY + 50 < c.y + SikakuH) ||(c.y > ShotY + 50 && c.y < ShotY + 50 + ShotH)))
				{
					// �G�ɓ�����ƁA�e������
					ShotFlag = 0;
				}
			}*/

			/*hitEnemy = isOnShot(ShotX, ShotY);

			if (hitEnemy >= 0) {

				Enemyhit(hitEnemy);

			}*/



			// ����ʂ̓��e��\��ʂɔ��f (��ʃ`�J�`�J�h�~��A)
			ScreenFlip();

			//��ʃN���A
			ClearDrawScreen();


			// �G��S���|���Ə����𔲂���(�r���Ŋ������Ă��A�Q�[���͑����d�l)
			if (enemy_num == 0) {


				// �`����\��ʂɂ���
				SetDrawScreen(DX_SCREEN_FRONT);

				break;

			}

		}


		// ��ʃN���A
		ClearDrawScreen();


		// �V���[�e�B���O�w�i��\��
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// ���y���~
		StopSoundMem(shooting);


		// �t�F�[�Y�I�����b�Z�[�W
		SetFontSize(30);
		DrawFormatString(300, 300, white, "�`�`�h��t�F�[�Y�I���`�`");
		SetFontSize(20);
		DrawFormatString(400, 450, white, "Press Any Key!!!");


		//���_�\��
		SetFontSize(30);
		DrawFormatString(10, 10, CHAR_CLOLOR, "�c��G��: %d  ����LEVEL: %d", enemy_num, level);


		// ���͑҂�
		WaitKey();


		// ��ʃN���A
		ClearDrawScreen();


		// ���Ãt�F�[�Y(�h��t�F�[�Y�Ŋ��������ꍇ)(Bad End)
		if (level >= 3) {


			// ���y���~
			StopSoundMem(shooting);


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// Bad End���b�Z�[�W
			SetFontSize(60);
			DrawFormatString(335, 100, crimson, "GAME OVER");
			SetFontSize(40);
			DrawFormatString(290, 290, white, "�������Ă��܂���.....");
			SetFontSize(20);
			DrawFormatString(410, 650, white, "Press Any Key...");
			WaitKey();


			// �G���h���[��
			gameOver();


			// �I������
			DxLib_End();
			return 0;

		}


		// ���y���~
		StopSoundMem(shooting);


		// ��ʏ���
		ClearDrawScreen();


		// 3���Ԋ������Ȃ���΃N���A
		if (day == 3) {

			break;

		}


		// �t�F�[�Y�ŗL���Đ�
		PlaySoundMem(kill, DX_PLAYTYPE_LOOP);


		// �w�i��\��
		DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


		// ���쁕�d�l����
		SetFontSize(30);
		DrawFormatString(310, 100, black, "�E�ۃt�F�[�Y�@�������");
		DrawFormatString(110, 250, black, "�E�h��t�F�[�Y�Ŏ󂯂��ۂ��򂵂悤�I�I");
		DrawFormatString(110, 300, black, "�E��x�̎E�ۃt�F�[�Y���ƂɁA����LEVEL���P�����I�I");
		DrawFormatString(110, 400, black, "������LEVEL��GAMECLEAR�܂ň����p����܂��B");
		DrawFormatString(110, 450, black, "�������Ȃ��ꍇ�A��Փx�����ˏオ��܂��B");
		DrawFormatString(385, 650, black, "Press any Key�I");


		// ���͑҂�
		WaitKey();
		ClearDrawScreen();


		// �E�ۃt�F�[�Y(ESC���������܂Ń��[�v)
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


			// �w�i��\��
			DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


			// �}�E�X�̍��W�擾
			GetMousePoint(&Mx, &My);


			// �R�}���h�\��
			SetFontSize(40);
			DrawFormatString(310, 200, black, "�ǂ��炩���N���b�N�I�I");
			DrawFormatString(410, 450, black, "����");
			DrawFormatString(375, 550, black, "�����Ȃ�");
			//DrawFormatString(10, 10, black, "%d  %d", Mx, My);



			// ���􂤏ꍇ
			if (Mx >= 410 && Mx <= 567 && My <= 487 && My >= 453 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// ��ʏ���
				ClearDrawScreen();


				// �w�i���ēx�\��
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// ���b�Z�[�W�\��
				SetFontSize(40);
				DrawFormatString(300, 120, black, "����LEVEL���P���������I�I");
				DrawFormatString(320, 250, black, " (�O) ����LEVEL  %d", level);
				DrawFormatString(315, 350, black, "�@�@�@�@�@�@�@�@ ��");


				// ����LEVEL��������
				level--;


				DrawFormatString(320, 450, black, "(����)����LEVEL  %d", level);
				SetFontSize(30);
				DrawFormatString(375, 640, black, "Press Any Key!!");


				// ���͑҂�
				WaitKey();
				break;

			}


			// �����Ȃ��ꍇ
			if (Mx >= 374 && Mx <= 613 && My <= 585 && My >= 554 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// ��ʏ���
				ClearDrawScreen();


				// �w�i���ēx�\��
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// ���b�Z�[�W�\��
				SetFontSize(40);
				DrawFormatString(320, 300, black, "����LEVEL�͕ς��Ȃ�...");
				DrawFormatString(340, 400, black, "���݂̊���LEVEL  %d", level);
				DrawFormatString(375, 550, black, "Press Any Key!!");


				// ���͑҂�
				WaitKey();
				break;

			}


		}


		// BGM���~
		StopSoundMem(kill);


		// ��ʏ���
		ClearDrawScreen();


	}


	// �Q�[���N���A����
	ClearDrawScreen();
	StopSoundMem(wash);
	SetFontSize(60);
	DrawFormatString(325, 100, white, "GAME CLEAR!!!");
	DrawFormatString(425, 400, white, "Press any Key!!");
	WaitKey();
	ClearDrawScreen();
	gameclear();

	WaitKey();


	// �I������
	DxLib_End();

	return 0;

}