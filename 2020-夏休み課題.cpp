// 
//
//　松江工業高等専門学校　J1919  髙橋千賢
//							
//
//  素材元
//
//	シューティング(全般)参考 : shootingDX2爆発追加.cpp
//								 https://wbt2020.matsue-ct.jp/pluginfile.php/2098/mod_resource/content/1/shootingDX2%E7%88%86%E7%99%BA%E8%BF%BD%E5%8A%A0.cpp
//
//	シューティング(弾関係)参考 : ゲーム制作講座１－３ ３．自機が弾を撃てるようにしよう https://dxlib.xsrv.jp/lecture/lecture1_3.html
//
//	シューティング背景 : きまぐれアフター背景資材置き場  https://k-after.at.webry.info/201009/article_1.html
//
//  自機画像 : いらすとや  https://www.irasutoya.com/2016/05/blog-post_187.html
//
//  敵機画像 : silhouetteAC  https://www.silhouette-ac.com/category.html?sw=%E8%8F%8C&nq=&srt=dlrank
//
//　殺菌フェーズ背景画像 : freepik https://jp.freepik.com/free-vector/soap-bubbles-floating-in-the-green-background-vector_4159922.htm#page=1&query=%E3%82%B7%E3%83%A3%E3%83%9C%E3%83%B3%E7%8E%89&position=22
//
//　爆発画像： 
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
#define BLAST_FIG_NUM 16 //爆発するアニメの画像数
#define My_Speed 30 // 自機移動速度

struct Position
{
	int x;
	int y;
	int isExist;//存在したら１、いなかったら０
};

// グローバル変数
struct Position c; //自機の場所 
struct Position e[ENEMY_NUM]; //敵場所
int enemy_num = ENEMY_NUM; //生きている敵の数
int time; //残り時間
int BlastHandle[BLAST_FIG_NUM]; //爆発画像ハンドル
static int level = 0;


// 各種初期化
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

// ワープの計算
int getWarpPos(int pos, int window_size)
{
	int w;
	w = (pos + window_size) % window_size;
	return w;
}

// 自機の移動
// キーボードに合わせて移動
void moveRocket()
{

	// → キー
	if (CheckHitKey(KEY_INPUT_RIGHT)) {

		c.x += My_Speed;

	}

	// → キー
	if (CheckHitKey(KEY_INPUT_LEFT)) {

		c.x -= My_Speed;

	}

	c.x = getWarpPos(c.x, WINDOW_SIZE_X); //ワープ
	c.y = getWarpPos(c.y, WINDOW_SIZE_Y);

}

// 敵機の移動(ワープ含む)
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


//表示
void Draw()
{
	int i;

	// 画像登録
	int TITLEpicture = LoadGraph("images/列島感染TITLEpicture.jpg"); // タイトル画像
	int ShooterHandle = LoadGraph("images/列島感染-シューティング-防護服2.png"); // シューティング自機
	int EnemyHandle = LoadGraph("images/列島感染-ウイルス-removebg-preview.png"); // シューティング敵機
	int BackHandle = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // シューティング背景(仮)
	int shot = LoadGraph("images/列島感染-シューティング-弾.jpg"); // 弾の絵(仮)


	// シューティング背景を表示
	DrawExtendGraph(0, 0, 1024, 768, BackHandle, FALSE);


	for (i = 0; i < ENEMY_NUM; i++) {
		//敵機を描く

		if (e[i].isExist == FALSE) {
			continue;
		}

		DrawExtendGraph(e[i].x, e[i].y, e[i].x + ENEMY_SIZE_X, e[i].y + ENEMY_SIZE_Y, EnemyHandle, TRUE);
	}


	//自機を描く
	DrawExtendGraph(c.x, c.y, c.x + CHARACTER_SIZE_X, c.y + CHARACTER_SIZE_Y, ShooterHandle, TRUE);


	//得点表示　
	DrawFormatString(10, 10, CHAR_CLOLOR, "残り敵数: %d  感染LEVEL: %d", enemy_num, level);


	// 待ち時間
	WaitTimer(WAIT_TIME);

}

// 自機と敵の衝突
void hit(int attackedEnemy)
{
	static int HitHandle = LoadSoundMem("se_mod04.wav");//衝突音の識別番号
	int i;

	for (i = 0; i < BLAST_FIG_NUM; i++)
	{
		DrawGraph(e[attackedEnemy].x - 35, e[attackedEnemy].y - 30, BlastHandle[i], TRUE);
		WaitTimer(30); //表示が早すぎると見えないので少し待つ
	}
	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[attackedEnemy].isExist = FALSE;
	enemy_num--;
	level++;
	WaitTimer(1000);
}

// 弾と敵の衝突
/*void Enemyhit(int hitEnemy) {

	static int HitHandle = LoadSoundMem("se_mod04.wav");//衝突音の識別番号

	PlaySoundMem(HitHandle, DX_PLAYTYPE_BACK);
	e[hitEnemy].isExist = FALSE;
	enemy_num--;
	WaitTimer(5);

}*/

//ゲームオーバー
void gameOver()
{

	// 画像登録
	int badend = LoadGraph("images/列島感染-BadEnd-picture.jpg"); // BadEnd背景


	// エンドロール音登録
	int end = LoadSoundMem("musics/列島感染(エンドロール音).m4a");


	// 色取得
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// 画面クリア
	ClearDrawScreen();


	// 文字サイズ調整
	SetFontSize(30);


	// Bad End音を再生
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// エンドロール
	for (int s = 15; s <= 3000; s++) {


		// 描画先を裏画面にする (画面チカチカ防止策①)
		SetDrawScreen(DX_SCREEN_BACK);


		// 背景描画
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// 縦スクロール
		DrawFormatString(380, 900 - s, white, "原案　　髙橋千賢");

		DrawFormatString(380, 1100 - s, white, "音楽　　髙橋千賢");
		DrawFormatString(380, 1300 - s, white, "写真　　yukari");
		DrawFormatString(380, 1400 - s, white, "　　　　髙橋千賢");

		DrawFormatString(380, 1800 - s, white, "製作　　髙橋千賢");
		DrawFormatString(360, 2000 - s, white, "製作協力　　yori");

		DrawFormatString(385, 2800 - s, white, "～～Bad End～～");


		// 裏画面の内容を表画面に反映 (画面チカチカ防止策②)
		ScreenFlip();


		// 速度調整
		WaitTimer(5);


		// プロローグカット機能(左クリックでスキップ)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any Keyが画面中央にきたらスクロール停止
		if (s == 2430) {


			// 描画先を表画面にする 
			SetDrawScreen(DX_SCREEN_FRONT);


			// 何かKeyが押されるまで待機
			WaitKey();

			break;

		}
		else {

			// 画面クリア
			ClearDrawScreen();

		}

	}

}


void gameclear()
{

	// 画像登録
	int badend = LoadGraph("images/列島感染-BadEnd-picture.jpg"); // 背景


	// エンドロール音登録
	int end = LoadSoundMem("musics/列島感染(エンドロール音).m4a");


	// 色取得
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);


	// 画面クリア
	ClearDrawScreen();


	// 文字サイズ調整
	SetFontSize(30);


	// Bad End音を再生
	PlaySoundMem(end, DX_PLAYTYPE_LOOP);


	// エンドロール
	for (int s = 15; s <= 3000; s++) {


		// 描画先を裏画面にする (画面チカチカ防止策①)
		SetDrawScreen(DX_SCREEN_BACK);


		// 背景描画
		DrawExtendGraph(0, 0, 1024, 768, badend, FALSE);


		// 縦スクロール
		DrawFormatString(380, 900 - s, white, "原案　　髙橋千賢");

		DrawFormatString(380, 1100 - s, white, "音楽　　髙橋千賢");
		DrawFormatString(380, 1300 - s, white, "写真　　yukari");
		DrawFormatString(380, 1400 - s, white, "　　　　髙橋千賢");

		DrawFormatString(380, 1800 - s, white, "製作　　髙橋千賢");
		DrawFormatString(360, 2000 - s, white, "製作協力　　yori");

		DrawFormatString(385, 2800 - s, white, "～～Happy End～～");


		// 裏画面の内容を表画面に反映 (画面チカチカ防止策②)
		ScreenFlip();


		// 速度調整
		WaitTimer(5);


		// プロローグカット機能(左クリックでスキップ)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && s > 15) {

			s = 2429;

		}


		// Press any Keyが画面中央にきたらスクロール停止
		if (s == 2430) {


			// 描画先を表画面にする 
			SetDrawScreen(DX_SCREEN_FRONT);


			// 何かKeyが押されるまで待機
			WaitKey();

			break;

		}
		else {

			// 画面クリア
			ClearDrawScreen();

		}

	}

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	int day = 0; // 日付
	int i = 0;
	int Mx, My; // マウス座標
	extern int level; // 感染レベル(外部に宣言済みの合図のextern)
	int time = 20000; // シューティング時間制限
	int ShotX, ShotY, ShotFlag = 0; // 弾の座標、弾のフラグ
	int SikakuW, SikakuH, ShotW, ShotH;


	// ウィンドウモードに変更
	ChangeWindowMode(TRUE);


	// 画面モードの設定
	SetGraphMode(1024, 768, 32);


	// マウスを表示
	SetMouseDispFlag(TRUE);


	// DxLib初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}


	// タイトル音登録
	int TITLE = LoadSoundMem("musics/列島感染(タイトル画面.m4a");


	// シューティング音登録
	int shooting = LoadSoundMem("musics/列島感染(シューティング音).m4a");


	// 殺菌フェーズ音登録
	int kill = LoadSoundMem("musics/列島感染(殺菌フェーズ音).m4a");


	// 洗う音登録
	int washsound = LoadSoundMem("musics/列島感染(洗う音).mp3");


	// エンドロール音登録
	int end = LoadSoundMem("musics/列島感染(エンドロール音).m4a");


	// タイトル音再生
	PlaySoundMem(TITLE, DX_PLAYTYPE_LOOP);


	// 色取得
	int white = GetColor(255, 255, 255);
	int porple = GetColor(204, 0, 204);
	int porple2 = GetColor(102, 0, 153);
	int crimson = GetColor(220, 20, 60);
	int deepskyblue = GetColor(0, 191, 255);
	int green = GetColor(153, 255, 0);
	int blue = GetColor(0, 153, 255);
	int black = GetColor(0, 0, 0);


	// 画像登録
	int TITLEpicture = LoadGraph("images/列島感染TITLEpicture.jpg"); // タイトル画像
	int Chara = LoadGraph("images/列島感染-シューティング-防護服2.png"); // シューティング自機
	int virus = LoadGraph("images/列島感染-ウイルス-removebg-preview.png"); // シューティング敵機
	int shootingpicture = LoadGraph("images/128235714438216224102_BG41f2.jpg"); // シューティング背景(仮)
	int ShotGraph = LoadGraph("images/列島感染-シューティング-弾.jpg"); // 弾の絵(仮)
	int badend = LoadGraph("images/列島感染-BadEnd-picture.jpg"); // BadEnd背景
	int wash = LoadGraph("images/列島感染-殺菌フェーズ背景.jpg"); // 殺菌フェーズ背景



	// タイトル画面(ESCが押されるまでループ)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// タイトル画像表示
		DrawExtendGraph(0, 0, 1024, 768, TITLEpicture, FALSE);


		// タイトル文字表示
		SetFontSize(90);
		DrawFormatString(200, 70, porple, "列島感染");
		SetFontSize(30);
		DrawFormatString(150, 170, white, "～君はこの危機をかわせるのか～");


		// 各種コマンド配置
		SetFontSize(40);
		DrawFormatString(440, 400, porple2, "START");


		// マウスの座標取得
		GetMousePoint(&Mx, &My);


		// 「はじめる」をクリックでゲームスタート
		if (Mx >= 436 && Mx <= 546 && My <= 432 && My >= 400 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			break;
		}


	}


	// 画面クリア
	ClearDrawScreen();


	// 文字サイズ調整
	SetFontSize(20);


	// プロローグ

	for (int i = 1; i <= 1600; i++) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// 描画先を裏画面にする (画面チカチカ防止策①)
		SetDrawScreen(DX_SCREEN_BACK);


		// 縦スクロール
		DrawFormatString(170, 600 - i, white, "20××年....");

		DrawFormatString(170, 700 - i, white, "我々の愛する列島は、");
		DrawFormatString(170, 800 - i, white, "社会経済や教育機関を混乱させ");
		DrawFormatString(170, 900 - i, white, "命をも脅かす未知の菌に今や翻弄されている。");

		DrawFormatString(170, 1000 - i, white, "この未知なる菌の感染から");
		DrawFormatString(170, 1100 - i, white, "自らを守りつつ果敢に闘いに挑み");
		DrawFormatString(170, 1200 - i, white, "君は田舎勇者となる事ができるのか!?");

		DrawFormatString(420, 2000 - i, white, "Press any Key");


		// 裏画面の内容を表画面に反映 (画面チカチカ防止策②)
		ScreenFlip();


		WaitTimer(20);


		// プロローグカット機能(左クリックでスキップ)
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && i > 15) {

			i = 1599;

		}


		// Press any Keyが画面中央にきたらスクロール停止
		if (i == 1600) {


			// 描画先を表画面にする 
			SetDrawScreen(DX_SCREEN_FRONT);


			// 何かKeyが押されるまで待機
			WaitKey();

			break;

		}
		else {

			// 画面クリア
			ClearDrawScreen();

		}

	}


	// 画面クリア
	ClearDrawScreen();


	// 音楽を停止
	StopSoundMem(TITLE);


	// 3日目まで感染しなければゲームクリア
	while (day <= 3) {


		if (ProcessMessage() == -1)
		{
			DxLib_End();
			return 0;
		}


		// 日付表示
		SetFontSize(60);
		day++;
		DrawFormatString(370, 350, crimson, " %d 日 目", day);
		SetFontSize(30);
		DrawFormatString(390, 550, white, "Press any Key...");


		// 入力待ち
		WaitKey();


		// シューティング背景を表示
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// シューティング音を再生
		PlaySoundMem(shooting, DX_PLAYTYPE_LOOP);


		// 操作説明(仮)
		SetFontSize(30);
		DrawFormatString(310, 100, white, "防御フェーズ　操作説明");
		DrawFormatString(110, 250, white, "・迫ってくる細菌をアルコール弾で撃ち殺そう！！");
		DrawFormatString(110, 300, white, "・迫りくる菌に当たってしまうと、感染LEVELが１上昇！！");
		DrawFormatString(110, 350, white, "・感染LEVELが3以上で即ゲームオーバー！！");
		DrawFormatString(290, 450, white, "移動　左[ ← ]　右[ → ]");
		DrawFormatString(310, 500, white, "弾の発射　左クリック");
		DrawFormatString(390, 650, white, "Press any Key");


		// 入力待ち
		WaitKey();


		// 画面クリア
		ClearDrawScreen();


		// 防御フェーズ(時間切れまでループ)

		init();
		Draw();


		for (time = 20000; time >= 0; time--) {


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// 描画先を裏画面にする (画面チカチカ防止策①)
			SetDrawScreen(DX_SCREEN_BACK);


			int attackedEnemy;


			// 自機の移動
			moveRocket();


			// 敵機の移動
			for (int j = 0; j < ENEMY_NUM; j++)
			{
				moveEnemy(j);
			}


			// メッセージループに代わる処理をする
			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// 弾の発射(スペースキーで発射)
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && ShotFlag == 0) {

				int Bw, Bh, Sw, Sh;

				// 自機と弾の画像のサイズを得る
				GetGraphSize(Chara, &Bw, &Bh);
				GetGraphSize(ShotGraph, &Sw, &Sh);


				// 自機のグラフィックのサイズを得る
				GetGraphSize(Chara, &SikakuW, &SikakuH);


				// 弾のグラフィックのサイズを得る
				GetGraphSize(ShotGraph, &ShotW, &ShotH);


				// 弾の位置をセット、位置を自機の中心にする
				ShotX = ((Bw - Sw) / 2 + c.x) - 15;
				ShotY = ((Bh - Sh) / 2 + c.y) + 50;

				// フラグ建設
				ShotFlag = 1;

			}


			//画面表示
			Draw();


			// 自機の弾の移動
			if (ShotFlag == 1)
			{
				// 弾の移動速度
				ShotY -= 50;

				// 画面外に行くと、弾は消失
				if (ShotY < -30)
				{
					// フラグを折る
					ShotFlag = 0;
				}

				// 画面に弾を描画する
				DrawGraph(ShotX - 46, ShotY + 50, ShotGraph, FALSE);
			}


			//自機と敵の当たり判定
			attackedEnemy = isOnEnemy(c.x, c.y);

			if (attackedEnemy >= 0)
			{
				hit(attackedEnemy);
			}


			// 敵機と弾の当たり判定
			/*if (ShotFlag == 1)
			{
				if (((ShotX - 46 > c.x && ShotX - 46 < c.x + ) ||(c.x > ShotX - 46 && c.x < ShotX - 46 + ShotW)) &&
					((ShotY + 50 > c.y && ShotY + 50 < c.y + SikakuH) ||(c.y > ShotY + 50 && c.y < ShotY + 50 + ShotH)))
				{
					// 敵に当たると、弾を消す
					ShotFlag = 0;
				}
			}*/

			/*hitEnemy = isOnShot(ShotX, ShotY);

			if (hitEnemy >= 0) {

				Enemyhit(hitEnemy);

			}*/



			// 裏画面の内容を表画面に反映 (画面チカチカ防止策②)
			ScreenFlip();

			//画面クリア
			ClearDrawScreen();


			// 敵を全員倒すと処理を抜ける(途中で感染しても、ゲームは続く仕様)
			if (enemy_num == 0) {


				// 描画先を表画面にする
				SetDrawScreen(DX_SCREEN_FRONT);

				break;

			}

		}


		// 画面クリア
		ClearDrawScreen();


		// シューティング背景を表示
		DrawExtendGraph(0, 0, 1024, 768, shootingpicture, FALSE);


		// 音楽を停止
		StopSoundMem(shooting);


		// フェーズ終了メッセージ
		SetFontSize(30);
		DrawFormatString(300, 300, white, "～～防御フェーズ終了～～");
		SetFontSize(20);
		DrawFormatString(400, 450, white, "Press Any Key!!!");


		//得点表示
		SetFontSize(30);
		DrawFormatString(10, 10, CHAR_CLOLOR, "残り敵数: %d  感染LEVEL: %d", enemy_num, level);


		// 入力待ち
		WaitKey();


		// 画面クリア
		ClearDrawScreen();


		// 治療フェーズ(防御フェーズで感染した場合)(Bad End)
		if (level >= 3) {


			// 音楽を停止
			StopSoundMem(shooting);


			if (ProcessMessage() == -1)
			{
				DxLib_End();
				return 0;
			}


			// Bad Endメッセージ
			SetFontSize(60);
			DrawFormatString(335, 100, crimson, "GAME OVER");
			SetFontSize(40);
			DrawFormatString(290, 290, white, "感染してしまった.....");
			SetFontSize(20);
			DrawFormatString(410, 650, white, "Press Any Key...");
			WaitKey();


			// エンドロール
			gameOver();


			// 終了処理
			DxLib_End();
			return 0;

		}


		// 音楽を停止
		StopSoundMem(shooting);


		// 画面消去
		ClearDrawScreen();


		// 3日間感染しなければクリア
		if (day == 3) {

			break;

		}


		// フェーズ固有音再生
		PlaySoundMem(kill, DX_PLAYTYPE_LOOP);


		// 背景を表示
		DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


		// 操作＆仕様説明
		SetFontSize(30);
		DrawFormatString(310, 100, black, "殺菌フェーズ　操作説明");
		DrawFormatString(110, 250, black, "・防御フェーズで受けた菌を洗浄しよう！！");
		DrawFormatString(110, 300, black, "・一度の殺菌フェーズごとに、感染LEVELが１減少！！");
		DrawFormatString(110, 400, black, "※感染LEVELはGAMECLEARまで引き継がれます。");
		DrawFormatString(110, 450, black, "※手を洗わない場合、難易度が跳ね上がります。");
		DrawFormatString(385, 650, black, "Press any Key！");


		// 入力待ち
		WaitKey();
		ClearDrawScreen();


		// 殺菌フェーズ(ESCが押されるまでループ)
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {


			// 背景を表示
			DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


			// マウスの座標取得
			GetMousePoint(&Mx, &My);


			// コマンド表示
			SetFontSize(40);
			DrawFormatString(310, 200, black, "どちらかをクリック！！");
			DrawFormatString(410, 450, black, "手を洗う");
			DrawFormatString(375, 550, black, "手を洗わない");
			//DrawFormatString(10, 10, black, "%d  %d", Mx, My);



			// 手を洗う場合
			if (Mx >= 410 && Mx <= 567 && My <= 487 && My >= 453 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// 画面消去
				ClearDrawScreen();


				// 背景を再度表示
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// メッセージ表示
				SetFontSize(40);
				DrawFormatString(300, 120, black, "感染LEVELが１下がった！！");
				DrawFormatString(320, 250, black, " (前) 感染LEVEL  %d", level);
				DrawFormatString(315, 350, black, "　　　　　　　　 ↓");


				// 感染LEVELを下げる
				level--;


				DrawFormatString(320, 450, black, "(現在)感染LEVEL  %d", level);
				SetFontSize(30);
				DrawFormatString(375, 640, black, "Press Any Key!!");


				// 入力待ち
				WaitKey();
				break;

			}


			// 手を洗わない場合
			if (Mx >= 374 && Mx <= 613 && My <= 585 && My >= 554 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {


				// 画面消去
				ClearDrawScreen();


				// 背景を再度表示
				DrawExtendGraph(0, 0, 1024, 768, wash, FALSE);


				// メッセージ表示
				SetFontSize(40);
				DrawFormatString(320, 300, black, "感染LEVELは変わらない...");
				DrawFormatString(340, 400, black, "現在の感染LEVEL  %d", level);
				DrawFormatString(375, 550, black, "Press Any Key!!");


				// 入力待ち
				WaitKey();
				break;

			}


		}


		// BGMを停止
		StopSoundMem(kill);


		// 画面消去
		ClearDrawScreen();


	}


	// ゲームクリア処理
	ClearDrawScreen();
	StopSoundMem(wash);
	SetFontSize(60);
	DrawFormatString(325, 100, white, "GAME CLEAR!!!");
	DrawFormatString(425, 400, white, "Press any Key!!");
	WaitKey();
	ClearDrawScreen();
	gameclear();

	WaitKey();


	// 終了処理
	DxLib_End();

	return 0;

}