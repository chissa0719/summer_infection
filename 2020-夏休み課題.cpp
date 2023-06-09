// 
//
//@¼]HÆêåwZ@J1919  ûü´ç«
//							
//
//  fÞ³
//
//	V[eBO(SÊ)Ql : shootingDX2­ÇÁ.cpp
//								 https://wbt2020.matsue-ct.jp/pluginfile.php/2098/mod_resource/content/1/shootingDX2%E7%88%86%E7%99%BA%E8%BF%BD%E5%8A%A0.cpp
//
//	V[eBO(eÖW)Ql : Q[§ìuÀP|R RD©@ªeðÄéæ¤Éµæ¤ https://dxlib.xsrv.jp/lecture/lecture1_3.html
//
//	V[eBOwi : «Ü®êAt^[wiÞu«ê  https://k-after.at.webry.info/201009/article_1.html
//
//  ©@æ : ¢ç·Æâ  https://www.irasutoya.com/2016/05/blog-post_187.html
//
//  G@æ : silhouetteAC  https://www.silhouette-ac.com/category.html?sw=%E8%8F%8C&nq=&srt=dlrank
//
//@EÛtF[Ywiæ : freepik https://jp.freepik.com/free-vector/soap-bubbles-floating-in-the-green-background-vector_4159922.htm#page=1&query=%E3%82%B7%E3%83%A3%E3%83%9C%E3%83%B3%E7%8E%89&position=22
//
//@­æF 
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
#define BLAST_FIG_NUM 16 //­·éAjÌæ
#define My_Speed 30 // ©@Ú®¬x

struct Position
{
	int x;
	int y;
	int isExist;//¶Ýµ½çPA¢È©Á½çO
};

// O[oÏ
struct Position c; //©@Ìê 
struct Position e[ENEMY_NUM]; //Gê
int enemy_num = ENEMY_NUM; //¶«Ä¢éGÌ
int time; //cèÔ
int BlastHandle[BLAST_FIG_NUM]; //­ænh
static int level = 0;


// eíú»
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

// [vÌvZ
int getWarpPos(int pos, int window_size)
{
	int w;
	w = (pos + window_size) % window_size;
	return w;
}

// ©@ÌÚ®
// L[{[hÉí¹ÄÚ®
void moveRocket()
{

	// ¨ L[
	if (CheckHitKey(KEY_INPUT_RIGHT)) {

		c.x += My_Speed;

	}

	// ¨ L[
	if (CheckHitKey(KEY_INPUT_LEFT)) {

		c.x -= My_Speed;

	}

	c.x = getWarpPos(c.x, WINDOW_SIZE_X); //[v
	c.y = getWarpPos(c.y, WINDOW_SIZE_Y);

}

// G@ÌÚ®([vÜÞ)
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


//\¦
void Draw()
{
	int i;

	// æo^
	int TITLEpicture = LoadGraph("images/ñ´õTITLEpicture.jpg"); // ^Cgæ
	int ShooterHandle = LoadGraph("images/ñ´õ-V[eBO-hì2.png"); // V[eBO©@
	int EnemyHandle = LoadGraph("images/ñ´õ-ECX-removebg-preview.png"); // V[eBOG@
	int BackHandle = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // V[eBOwi(¼)
	int shot = LoadGraph("images/ñ´õ-V[eBO-e.jpg"); // eÌG(¼)


	// V[eBOwið\¦
	DrawExtendGraph(0, 0, 1024, 768, BackHandle, FALSE);


	for (i = 0; i < ENEMY_NUM; i++) {
		//G@ð`­

		if (e[i].isExist == FALSE) {
			continue;
		}

		DrawExtendGraph(e[i].x, e[i].y, e[i].x + ENEMY_SIZE_X, e[i].y + ENEMY_SIZE_Y, EnemyHandle, TRUE);
	}


	//©@ð`­
	DrawExtendGraph(c.x, c.y, c.x + CHARACTER_SIZE_X, c.y + CHARACTER_SIZE_Y, ShooterHandle, TRUE);


	//¾_\¦@
	DrawFormatString(10, 10, CHAR_CLOLOR, "cèG: %d  ´õLEVEL: %d", enemy_num, level);


	// Ò¿Ô
	WaitTimer(WAIT_TIME);

}

// ©@ÆGÌÕË
void hit(int attackedEnemy)
{
	static int HitHandle = LoadSoundMem("se_mod04.wav");//ÕË¹Ì¯ÊÔ
	int i;

	for (i = 0; i < BLAST_FIG_NUM; i++)
	{
		DrawGraph(e[attackedEnemy].x - 35, e[attackedEnemy].y - 30, BlastHandle[i], TRUE);
		WaitTimer(30); //\¦ª·¬éÆ©¦È¢ÌÅ­µÒÂ
	}
	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[attackedEnemy].isExist = FALSE;
	enemy_num--;
	level++;
	WaitTimer(1000);
}

// eÆGÌÕË
/*void Enemyhit(int hitEnemy) {

	static int HitHandle = LoadSoundMem("se_mod04.wav");//ÕË¹Ì¯ÊÔ

	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[hitEnemy].isExist = FALSE;
	enemy_num--;
	WaitTimer(5);

}*/

//Q[I[o[
void gameOver()
{

	// æo^
	int badend = LoadGraph("images/ñ´õ-BadEnd-picture.jpg"); // BadEndwi


	// Gh[¹o^
	int end = LoadSoundMem("musics/ñ´õ(Gh[¹).m4a");


	// Fæ¾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// æÊNA
	ClearDrawScreen();


	// ¶TCY²®
	SetFontSize(30);


	// Bad End¹ðÄ¶
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// Gh[
	for (int s = 15; s <= 3000; s++) {


		// `ææð æÊÉ·é (æÊ`J`Jh~ô@)
		SetDrawScreen(DX_SCREEN_BACK);


		// wi`æ
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// cXN[
		DrawFormatString(380, 900 - s, white, "´Ä@@ûü´ç«");

		DrawFormatString(380, 1100 - s, white, "¹y@@ûü´ç«");
		DrawFormatString(380, 1300 - s, white, "Ê^@@yukari");
		DrawFormatString(380, 1400 - s, white, "@@@@ûü´ç«");

		DrawFormatString(380, 1800 - s, white, "»ì@@ûü´ç«");
		DrawFormatString(360, 2000 - s, white, "»ì¦Í@@yori");

		DrawFormatString(385, 2800 - s, white, "``Bad End``");


		//  æÊÌàeð\æÊÉ½f (æÊ`J`Jh~ôA)
		ScreenFlip();


		// ¬x²®
		WaitTimer(5);


		// v[OJbg@\(¶NbNÅXLbv)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any KeyªæÊÉ«½çXN[â~
		if (s == 2430) {


			// `ææð\æÊÉ·é 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ½©Keyª³êéÜÅÒ@
			WaitKey();

			break;

		}
		else {

			// æÊNA
			ClearDrawScreen();

		}

	}

}


void gameclear()
{

	// æo^
	int badend = LoadGraph("images/ñ´õ-BadEnd-picture.jpg"); // wi


	// Gh[¹o^
	int end = LoadSoundMem("musics/ñ´õ(Gh[¹).m4a");


	// Fæ¾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// æÊNA
	ClearDrawScreen();


	// ¶TCY²®
	SetFontSize(30);


	// Bad End¹ðÄ¶
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// Gh[
	for (int s = 15; s <= 3000; s++) {


		// `ææð æÊÉ·é (æÊ`J`Jh~ô@)
		SetDrawScreen(DX_SCREEN_BACK);


		// wi`æ
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// cXN[
		DrawFormatString(380, 900 - s, white, "´Ä@@ûü´ç«");

		DrawFormatString(380, 1100 - s, white, "¹y@@ûü´ç«");
		DrawFormatString(380, 1300 - s, white, "Ê^@@yukari");
		DrawFormatString(380, 1400 - s, white, "@@@@ûü´ç«");

		DrawFormatString(380, 1800 - s, white, "»ì@@ûü´ç«");
		DrawFormatString(360, 2000 - s, white, "»ì¦Í@@yori");

		DrawFormatString(385, 2800 - s, white, "``Happy End``");


		//  æÊÌàeð\æÊÉ½f (æÊ`J`Jh~ôA)
		ScreenFlip();


		// ¬x²®
		WaitTimer(5);


		// v[OJbg@\(¶NbNÅXLbv)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any KeyªæÊÉ«½çXN[â~
		if (s == 2430) {


			// `ææð\æÊÉ·é 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ½©Keyª³êéÜÅÒ@
			WaitKey();

			break;

		}
		else {

			// æÊNA
			ClearDrawScreen();

		}

	}

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	int day = 0; // út
	int i = 0;
	int Mx, My; // }EXÀW
	extern int level; // ´õx(OÉé¾ÏÝÌ}Ìextern)
	int time = 20000; // V[eBOÔ§À
	int ShotX, ShotY, ShotFlag = 0; // eÌÀWAeÌtO
	int SikakuW, SikakuH, ShotW, ShotH;


	// EBhE[hÉÏX
	ChangeWindowMode(TRUE);


	// æÊ[hÌÝè
	SetGraphMode(1024, 768, 32);


	// }EXð\¦
	SetMouseDispFlag(TRUE);


	// DxLibú»
	if (DxLib_Init() == -1)
	{
		return -1;
	}


	// ^Cg¹o^
	int TITLE = LoadSoundMem("musics/ñ´õ(^CgæÊ.m4a");


	// V[eBO¹o^
	int shooting = LoadSoundMem("musics/ñ´õ(V[eBO¹).m4a");


	// EÛtF[Y¹o^
	int kill = LoadSoundMem("musics/ñ´õ(EÛtF[Y¹).m4a");


	// ô¤¹o^
	int washsound = LoadSoundMem("musics/ñ´õ(ô¤¹).mp3");


	// Gh[¹o^
	int end = LoadSoundMem("musics/ñ´õ(Gh[¹).m4a");


	// ^Cg¹Ä¶
	PlaySoundMem(TITLE, DX_PLAYTYPE_LOOP);


	// Fæ¾
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);
	int crimson = GetColor(220, 20, 60);
	int deepskyblue = GetColor(0, 191, 255);
	int green = GetColor(153, 255, 0);
	int blue = GetColor(0, 153, 255);
	int black = GetColor(0, 0, 0);


	// æo^
	int TITLEpicture = LoadGraph("images/ñ´õTITLEpicture.jpg"); // ^Cgæ
	int Chara = LoadGraph("images/ñ´õ-V[eBO-hì2.png"); // V[eBO©@
	int virus = LoadGraph("images/ñ´õ-ECX-removebg-preview.png"); // V[eBOG@
	int shootingpicture = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // V[eBOwi(¼)
	int ShotGraph = LoadGraph("images/ñ´õ-V[eBO-e.jpg"); // eÌG(¼)
	int badend = LoadGraph("images/ñ´õ-BadEnd-picture.jpg"); // BadEndwi
	int wash = LoadGraph("images/ñ´õ-EÛtF[Ywi.jpg"); // EÛtF[Ywi



	// ^CgæÊ(ESCª³êéÜÅ[v)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// ^Cgæ\¦
		DrawExtendGraph(0, 0, 1024, 768, TITLEpicture, FALSE);


		// ^Cg¶\¦
		SetFontSize(90);
		DrawFormatString(200, 70, porple, "ñ´õ");
		SetFontSize(30);
		DrawFormatString(150, 170, white, "`NÍ±Ìë@ð©í¹éÌ©`");


		// eíR}hzu
		SetFontSize(40);
		DrawFormatString(440, 400, porple2, "START");


		// }EXÌÀWæ¾
		GetMousePoint(&Mx, &My);


		// uÍ¶ßévðNbNÅQ[X^[g
		if (Mx >= 436 && Mx <= 546 && My <= 432 && My >= 400 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			break;
		}


	}


	// æÊNA
	ClearDrawScreen();


	// ¶TCY²®
	SetFontSize(20);


	// v[O

	for (int i = 1; i <= 1600; i++) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// `ææð æÊÉ·é (æÊ`J`Jh~ô@)
		SetDrawScreen(DX_SCREEN_BACK);


		// cXN[
		DrawFormatString(170, 600 - i, white, "20~~N....");

		DrawFormatString(170, 700 - i, white, "äXÌ¤·éñÍA");
		DrawFormatString(170, 800 - i, white, "ÐïoÏâ³ç@Öð¬³¹");
		DrawFormatString(170, 900 - i, white, "½ðàº©·¢mÌÛÉ¡â|M³êÄ¢éB");

		DrawFormatString(170, 1000 - i, white, "±Ì¢mÈéÛÌ´õ©ç");
		DrawFormatString(170, 1100 - i, white, "©çðçèÂÂÊ¸É¬¢É§Ý");
		DrawFormatString(170, 1200 - i, white, "NÍcÉEÒÆÈéªÅ«éÌ©!?");

		DrawFormatString(420, 2000 - i, white, "Press any Key");


		//  æÊÌàeð\æÊÉ½f (æÊ`J`Jh~ôA)
		ScreenFlip();


		WaitTimer(20);


		// v[OJbg@\(¶NbNÅXLbv)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && i > 15) {

			i = 1599;

		}


		// Press any KeyªæÊÉ«½çXN[â~
		if (i == 1600) {


			// `ææð\æÊÉ·é 
			SetDrawScreen(DX_SCREEN_FRONT);


			// ½©Keyª³êéÜÅÒ@
			WaitKey();

			break;

		}
		else {

			// æÊNA
			ClearDrawScreen();

		}

	}


	// æÊNA
	ClearDrawScreen();


	// ¹yðâ~
	StopSoundMem(TITLE);


	// 3úÚÜÅ´õµÈ¯êÎQ[NA
	while (day <= 3) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// út\¦
		SetFontSize(60);
		day++;
		DrawFormatString(370, 350, crimson, " %d ú Ú", day);
		SetFontSize(30);
		DrawFormatString(390, 550, white, "Press any Key...");


		// üÍÒ¿
		WaitKey();


		// V[eBOwið\¦
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// V[eBO¹ðÄ¶
		PlaySoundMem(shooting, DX_PLAYTYPE_LOOP);


		// ìà¾(¼)
		SetFontSize(30);
		DrawFormatString(310, 100, white, "hätF[Y@ìà¾");
		DrawFormatString(110, 250, white, "EÁÄ­é×ÛðAR[eÅ¿E»¤II");
		DrawFormatString(110, 300, white, "Eè­éÛÉ½ÁÄµÜ¤ÆA´õLEVELªPã¸II");
		DrawFormatString(110, 350, white, "E´õLEVELª3ÈãÅ¦Q[I[o[II");
		DrawFormatString(290, 450, white, "Ú®@¶[ © ]@E[ ¨ ]");
		DrawFormatString(310, 500, white, "eÌ­Ë@¶NbN");
		DrawFormatString(390, 650, white, "Press any Key");


		// üÍÒ¿
		WaitKey();


		// æÊNA
		ClearDrawScreen();


		// hätF[Y(ÔØêÜÅ[v)

		init();
		Draw();


		for (time = 20000; time >= 0; time--) {


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// `ææð æÊÉ·é (æÊ`J`Jh~ô@)
			SetDrawScreen(DX_SCREEN_BACK);


			int attackedEnemy;


			// ©@ÌÚ®
			moveRocket();


			// G@ÌÚ®
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				moveEnemy(j);
			}


			// bZ[W[vÉãíéð·é
			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// eÌ­Ë(Xy[XL[Å­Ë)
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && ShotFlag == 0) {

				int Bw, Bh, Sw, Sh;

				// ©@ÆeÌæÌTCYð¾é
				GetGraphSize(Chara, &Bw, &Bh);
				GetGraphSize(ShotGraph, &Sw, &Sh);


				// ©@ÌOtBbNÌTCYð¾é
				GetGraphSize(Chara, &SikakuW, &SikakuH);


				// eÌOtBbNÌTCYð¾é
				GetGraphSize(ShotGraph, &ShotW, &ShotH);


				// eÌÊuðZbgAÊuð©@ÌSÉ·é
				ShotX = ((Bw - Sw) / 2 + c.x) - 15;
				ShotY = ((Bh - Sh) / 2 + c.y) + 50;

				// tOÝ
				ShotFlag = 1;

			}


			//æÊ\¦
			Draw();


			// ©@ÌeÌÚ®
			if (ShotFlag == 1)
			{
				// eÌÚ®¬x
				ShotY -= 50;

				// æÊOÉs­ÆAeÍÁ¸
				if (ShotY < -30)
				{
					// tOðÜé
					ShotFlag = 0;
				}

				// æÊÉeð`æ·é
				DrawGraph(ShotX - 46, ShotY + 50, ShotGraph, FALSE);
			}


			//©@ÆGÌ½è»è
			attackedEnemy = isOnEnemy(c.x, c.y);

			if (attackedEnemy >= 0)
			{
				hit(attackedEnemy);
			}


			// G@ÆeÌ½è»è
			/*if (ShotFlag == 1)
			{
				if (((ShotX - 46 > c.x && ShotX - 46 < c.x + ) ||(c.x > ShotX - 46 && c.x < ShotX - 46 + ShotW)) &&
					((ShotY + 50 > c.y && ShotY + 50 < c.y + SikakuH) ||(c.y > ShotY + 50 && c.y < ShotY + 50 + ShotH)))
				{
					// GÉ½éÆAeðÁ·
					ShotFlag = 0;
				}
			}*/

			/*hitEnemy = isOnShot(ShotX, ShotY);

			if (hitEnemy >= 0) {

				Enemyhit(hitEnemy);

			}*/



			//  æÊÌàeð\æÊÉ½f (æÊ`J`Jh~ôA)
			ScreenFlip();

			//æÊNA
			ClearDrawScreen();


			// GðSõ|·Æð²¯é(rÅ´õµÄàAQ[Í±­dl)
			if (enemy_num == 0) {


				// `ææð\æÊÉ·é
				SetDrawScreen(DX_SCREEN_FRONT);

				break;

			}

		}


		// æÊNA
		ClearDrawScreen();


		// V[eBOwið\¦
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// ¹yðâ~
		StopSoundMem(shooting);


		// tF[YI¹bZ[W
		SetFontSize(30);
		DrawFormatString(300, 300, white, "``hätF[YI¹``");
		SetFontSize(20);
		DrawFormatString(400, 450, white, "Press Any Key!!!");


		//¾_\¦
		SetFontSize(30);
		DrawFormatString(10, 10, CHAR_CLOLOR, "cèG: %d  ´õLEVEL: %d", enemy_num, level);


		// üÍÒ¿
		WaitKey();


		// æÊNA
		ClearDrawScreen();


		// ¡ÃtF[Y(hätF[YÅ´õµ½ê)(Bad End)
		if (level >= 3) {


			// ¹yðâ~
			StopSoundMem(shooting);


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// Bad EndbZ[W
			SetFontSize(60);
			DrawFormatString(335, 100, crimson, "GAME OVER");
			SetFontSize(40);
			DrawFormatString(290, 290, white, "´õµÄµÜÁ½.....");
			SetFontSize(20);
			DrawFormatString(410, 650, white, "Press Any Key...");
			WaitKey();


			// Gh[
			gameOver();


			// I¹
			DxLib_End();
			return 0;

		}


		// ¹yðâ~
		StopSoundMem(shooting);


		// æÊÁ
		ClearDrawScreen();


		// 3úÔ´õµÈ¯êÎNA
		if (day == 3) {

			break;

		}


		// tF[YÅL¹Ä¶
		PlaySoundMem(kill, DX_PLAYTYPE_LOOP);


		// wið\¦
		DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


		// ìdlà¾
		SetFontSize(30);
		DrawFormatString(310, 100, black, "EÛtF[Y@ìà¾");
		DrawFormatString(110, 250, black, "EhätF[YÅó¯½Ûðôòµæ¤II");
		DrawFormatString(110, 300, black, "EêxÌEÛtF[Y²ÆÉA´õLEVELªP¸­II");
		DrawFormatString(110, 400, black, "¦´õLEVELÍGAMECLEARÜÅø«pªêÜ·B");
		DrawFormatString(110, 450, black, "¦èðôíÈ¢êAïÕxªµËãªèÜ·B");
		DrawFormatString(385, 650, black, "Press any KeyI");


		// üÍÒ¿
		WaitKey();
		ClearDrawScreen();


		// EÛtF[Y(ESCª³êéÜÅ[v)
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


			// wið\¦
			DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


			// }EXÌÀWæ¾
			GetMousePoint(&Mx, &My);


			// R}h\¦
			SetFontSize(40);
			DrawFormatString(310, 200, black, "Ç¿ç©ðNbNII");
			DrawFormatString(410, 450, black, "èðô¤");
			DrawFormatString(375, 550, black, "èðôíÈ¢");
			//DrawFormatString(10, 10, black, "%d  %d", Mx, My);



			// èðô¤ê
			if (Mx >= 410 && Mx <= 567 && My <= 487 && My >= 453 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// æÊÁ
				ClearDrawScreen();


				// wiðÄx\¦
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// bZ[W\¦
				SetFontSize(40);
				DrawFormatString(300, 120, black, "´õLEVELªPºªÁ½II");
				DrawFormatString(320, 250, black, " (O) ´õLEVEL  %d", level);
				DrawFormatString(315, 350, black, "@@@@@@@@ «");


				// ´õLEVELðº°é
				level--;


				DrawFormatString(320, 450, black, "(»Ý)´õLEVEL  %d", level);
				SetFontSize(30);
				DrawFormatString(375, 640, black, "Press Any Key!!");


				// üÍÒ¿
				WaitKey();
				break;

			}


			// èðôíÈ¢ê
			if (Mx >= 374 && Mx <= 613 && My <= 585 && My >= 554 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// æÊÁ
				ClearDrawScreen();


				// wiðÄx\¦
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// bZ[W\¦
				SetFontSize(40);
				DrawFormatString(320, 300, black, "´õLEVELÍÏíçÈ¢...");
				DrawFormatString(340, 400, black, "»ÝÌ´õLEVEL  %d", level);
				DrawFormatString(375, 550, black, "Press Any Key!!");


				// üÍÒ¿
				WaitKey();
				break;

			}


		}


		// BGMðâ~
		StopSoundMem(kill);


		// æÊÁ
		ClearDrawScreen();


	}


	// Q[NA
	ClearDrawScreen();
	StopSoundMem(wash);
	SetFontSize(60);
	DrawFormatString(325, 100, white, "GAME CLEAR!!!");
	DrawFormatString(425, 400, white, "Press any Key!!");
	WaitKey();
	ClearDrawScreen();
	gameclear();

	WaitKey();


	// I¹
	DxLib_End();

	return 0;

}