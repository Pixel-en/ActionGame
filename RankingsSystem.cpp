#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"OutText.h"

namespace
{
	IPDATA IpAddr;
	int NetUDPHandle;
	const unsigned short SERVER_PORT = 8888;
	int RecvSize, TotalRecvSize;

	BYTE Data[500];
	char Buff[256];

	int mojiSize = 32;
	int AsciiCodeEN = 65;
	struct NData
	{
		int posX1;
		int posY1;
		int posX2;
		int posY2;
		int Ascii;
	};

	int dcx1 = 900;
	int dcy1 = 400;
	int dcx2 = dcx1 + mojiSize;
	int dcy2 = dcy1 + mojiSize;

	
	int nowMojiCount = -1;
	bool InCnPrevKey = false;

	int prevX1, prevY1, prevX2, prevY2;

	
	char cName[256];

	const int Y = 6;
	const int X = 7;
	int del_space_enter = 48;
	NData N[Y][X];

	bool inPrev = false;

	enum PrevKey {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};

	int PrevKey;
}



RankingsSystem::RankingsSystem(GameObject* parent)
	: GameObject(parent, "RankingsSystem"), width(0), height(0), csv(nullptr), output_(false), tText(nullptr), InputHandle(0),SetEnd(false),Name(),
	eraseAlpha(0),eraseTime(0),eraseTimer(0),flame(0),x1(0),y1(0),x2(0),y2(0),space(0),word(0),count(0),a(0),n(0),MaxWord(0)
{
}

RankingsSystem::~RankingsSystem()
{
}

void RankingsSystem::Initialize()
{
	output_csv_file_path_ScoreData = "Assets\\Rankings\\RankingsSystem.csv";
	output_csv_file_path_SortData = "Assets\\Rankings\\RankingsSystemClearSort.csv";
	csv = new CsvReader(output_csv_file_path_ScoreData);
	width = csv->GetColumns(0);
	height = csv->GetLines();

	SetEnd = false;

	eraseTime = 1.2f;
	eraseTimer = 0.0f;
	flame = 1.0f / 60.0f;
	eraseAlpha = 0;

	x1 = 455;
	y1 = 440;
	x2 = 455;
	y2 = 445;


	cx1 = dcx1;
	cy1 = dcy1; 
	cx2 = dcx2;
	cy2 = dcy2;
	prevKey = false;

	space = 14;
	word = 23;
	count = 0;
	MaxWord = 10;

	nowDevice = PAD;

	str = "";

	
	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput(MaxWord,FALSE,TRUE,FALSE);

	//N[y][x]に位置情報posX1,X2,Y1,Y2を挿入
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (y == 0 && x == 6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
				del_space_enter++;
			}
			else if (y == 1 && x ==6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
				del_space_enter++;
			}
			else if (y == 2 && x == 6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
			}
			else if(AsciiCodeEN < 91 && x < 5){
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,AsciiCodeEN };
				AsciiCodeEN++;
			}
			else {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,0};
			}
		}
	}
	str = cName;
}

void RankingsSystem::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &pad);

	if (output_) {
		switch (nowDevice)
		{
		case KEY_AND_MOUSE:
		{
			// 入力が終了している場合は終了
			if (CheckKeyInput(InputHandle) != 0) {
				if (!SetEnd) {
					SetRankings(Name, 500);

					SetEnd = true;
					SortScore();
				}
			}
			// 作成したキー入力ハンドルをアクティブにする
			SetActiveKeyInput(InputHandle);

			//入力モードを描画
			DrawKeyInputModeString(640, 480);

			// 入力途中の文字列を描画
			DrawKeyInputString(0, 0, InputHandle);

			// 入力された文字列を取得
			GetKeyInputString(Name, InputHandle);
			break;
		}
		case PAD:
		{
			break;
		}
		default: break;
		}
	}
}

void RankingsSystem::Draw()
{
	if (output_) {
		switch (nowDevice)
		{
		case KEY_AND_MOUSE:
		{
			DrawWriteUI();
			break;
		}
		case PAD:
		{
			DrawWriteUICn();
			break;
		}
		default:
			break;
		}
		
	}
}

void RankingsSystem::Release()
{
}

void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path_ScoreData, std::ios::app);
	ofs_csv_file << _Pname << "," << _Pscore;
	ofs_csv_file << std::endl;
	ofs_csv_file.close();
}

void RankingsSystem::SortScore()
{
	csv = new CsvReader(output_csv_file_path_ScoreData);
	height = csv->GetLines();
	if (height > 1) {
		for (int h = 1; h < height; h++) {
			Rankings.insert(std::pair<std::string, float>(csv->GetString(h, 0), csv->GetFloat(h, 1)));
		}

		for (std::map<std::string, float>::iterator it = Rankings.begin(); it != Rankings.end(); it++) {
			r.push_back({ it->second, it->first });
		}

		sort(r.rbegin(), r.rend());
	}

	std::ofstream ofs_csv_file(output_csv_file_path_SortData);
	ofs_csv_file << "PlayerName" << "," << "PlayerScore";
	ofs_csv_file << std::endl;
	for (auto itr = r.begin(); itr != r.end(); ++itr) {
		ofs_csv_file << itr->second << "," << itr->first;
		ofs_csv_file << std::endl;
		ofs_csv_file.close();
	}
}

void RankingsSystem::DrawWriteUI()
{
	std::string str = Name;
	
	NameBar(str, word, space, 450, 405, 455, 435, eraseTimer, eraseTime);

	//入力可能文字数がわかるボックス表示
	for (int i = 0; i < MaxWord; i++) {
		if (i > 0) {
			n = a + space;
			DrawBoxAA(n, y1, n + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = n + word;
		}
		else
		{
			DrawBoxAA(x1, y1, x2 + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = x2 + word;
		}
	}
	DrawBoxAA(430, 380,(x1+25) + MaxWord*word +( MaxWord-1 )* space, 450, GetColor(255, 255, 255), FALSE); //入力枠線
	tText->DrawString(Name, 450, 400);
}

void RankingsSystem::DrawWriteUICn()
{
	char b;

	//選択文字の表示
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			b = static_cast<char>(N[y][x].Ascii);
			std::string str(1, b);
			if (str == "0") {
				tText->DrawStringJ("ケス", N[y][x].posX1 - 1, N[y][x].posY1 + 4);
			}
			else if (str == "1") {
				tText->DrawStringJ("クウハク", N[y][x].posX1 - 1, N[y][x].posY1 + 4);
			}
			else if (str == "2") {
				tText->DrawStringJ("ケッテイ", N[y][x].posX1 - 1, N[y][x].posY1 + 4);
			}
			else {
				tText->DrawString(str, N[y][x].posX1 - 1, N[y][x].posY1 + 4);
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_UP) || pad.ThumbLY >= 10000) {
		if (prevKey == false) {
			PrevKey = UP;
			prevY1 = cy1;
			prevY2 = cy2;
			cy1 -= mojiSize;
			cy2 -= mojiSize;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_RIGHT) || pad.ThumbLX >= 10000) {
		if(prevKey == false) {
			PrevKey = RIGHT;
			prevX1 = cx1;
			prevX2 = cx2;
			cx1 += mojiSize;
			cx2 += mojiSize;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_DOWN) || pad.ThumbLY <= -10000) {
		
		if (prevKey == false) {
			PrevKey = DOWN;
			prevY1 = cy1;
			prevY2 = cy2;
			cy1 += mojiSize;
			cy2 += mojiSize;
		}
		prevKey = true;
	} else if (CheckHitKey(KEY_INPUT_LEFT) || pad.ThumbLX <= -10000) {
		
		if (prevKey == false) {
			PrevKey = LEFT;
			prevX1 = cx1;
			prevX2 = cx2;
		    cx1 -= mojiSize;
			cx2 -= mojiSize;
		}
		prevKey = true;
	}
	else {
		prevKey = false;
	}
	
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (N[y][x].posX1 == cx1 && N[y][x].posY1 == cy1 && N[y][x].posX2 == cx2 && N[y][x].posY2 == cy2 && N[y][x].Ascii == 0) {
				
				if (cx2 > prevX2) {
					cx2 = cx2 + 35;
					cx1 = cx1 + 35;
				}
				else
				if (cy2 > prevY2) {
					cy2 = cy2 - 35;
					cy1 = cy2 - 35;
				}else
				if (cx2 < prevX2) {
					cx2 = cx2 - 35;
					cx1 = cx2 - 35;
				}
				
			}
		}
	}

	//枠線外にはみ出さない用の処理
	if (cx1 < N[0][0].posX1) { //←
		cx1 = N[0][0].posX1;
		cx2 = N[0][0].posX2;
	}

	if (cy1 < N[0][0].posY1) { //↑
		cy1 = N[0][0].posY1;
		cy2 = N[0][0].posY2;
	}

	if (cx2 > N[Y - 1][X - 1].posX2) { //→
		cx2 = N[Y - 1][X - 1].posX2;
		cx1 = N[Y - 1][X - 1].posX1;
	}

	if (cy2 > N[Y - 1][X - 1].posY2) { //↓
		cy2 = N[Y - 1][X - 1].posY2;
		cy1 = N[Y - 1][X - 1].posY1;
	}
	
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (N[y][x].posX1 == cx1 && N[y][x].posY1 == cy1 && N[y][x].posX2 == cx2 && N[y][x].posY2 == cy2 && N[y][x].Ascii == 0) {
				
				switch (PrevKey) {
				case UP:
				{

				}
				case RIGHT:
				{
					

					if (cx2 > prevX2) {
						bool find = false;
						for (int y = 0; y < Y; y++) {
							for (int x = 0; x < X; x++) {
								if (N[y][x].posX1 == cx1 && N[y][x].posY1 == cy1 && N[y][x].posX2 == cx2 && N[y][x].posY2 == cy2) {
									for (int sarch = x; sarch < X; sarch++) {
										if (!find) {
											if (N[y][sarch].Ascii != 0) {
												cx1 = N[y][sarch].posX1;
												cx2 = N[y][sarch].posX2;
												cy1 = N[y][sarch].posY1;
												cy2 = N[y][sarch].posY2;
												find = true;
											}
											else {
												cx1 = prevX1;
												cx2 = prevX2;
											}
										}

									}

								}
							}
						}
						find = false;
					}
					break;
				
				}
				case DOWN:
				{
					if (cy2 > prevY2) {
						cy2 = prevY2;
						cy1 = prevY1;
					}
					break;
				}
				case LEFT:
				{
					if (cx1 < prevX1) {
						bool find = false;
						for (int y = 0; y < Y; y++) {
							for (int x = 0; x < X; x++) {
								if (N[y][x].posX1 == cx1 && N[y][x].posY1 == cy1 && N[y][x].posX2 == cx2 && N[y][x].posY2 == cy2) {
									for (int sarch = x; sarch > 0; sarch--) {
										if (!find) {
											if (N[y][sarch].Ascii != 0) {
												cx1 = N[y][sarch].posX1;
												cx2 = N[y][sarch].posX2;
												cy1 = N[y][sarch].posY1;
												cy2 = N[y][sarch].posY2;
												find = true;
											}
											else {
												cx1 = prevX1;
												cx2 = prevX2;
											}
										}

									}

								}
							}
						}
					}
					break;
				}
				default: break;
				}
			}
		}
	}

	DrawBoxAA(cx1, cy1, cx2,cy2, GetColor(255, 255, 255), FALSE);

	

	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (cx1 == N[y][x].posX1 && cy1 == N[y][x].posY1 && cx2 == N[y][x].posX2 && cy2 == N[y][x].posY2) {
				if (CheckHitKey(KEY_INPUT_RETURN)||pad.Buttons[XINPUT_BUTTON_A]) {
					if (InCnPrevKey == false) {
						char cAscii = static_cast<char>(N[y][x].Ascii);
						std::string cAscii_ToString(1, cAscii);
						if (cAscii == 48) {
							cAscii = 127;
							if (nowMojiCount >= 0) {
								if (nowMojiCount == MaxWord -1) {
									str.erase(nowMojiCount);
									nowMojiCount = nowMojiCount -1;
								}
								else {
									str.erase(nowMojiCount);
									nowMojiCount = nowMojiCount - 1;
								}
							}
						}else if (cAscii == 49) {
							cAscii = 32;
							cAscii_ToString = cAscii;
							if (nowMojiCount == MaxWord -1 ) {
								str.erase(nowMojiCount);
								str.insert(nowMojiCount,cAscii_ToString);
							}
							else {
								nowMojiCount++;
								str.insert(nowMojiCount,cAscii_ToString);
								
							}
						}else if (cAscii == 50) {
							const std::string strl(str);
							
							//UDP通信用ソケットハンドルを作成
							NetUDPHandle = MakeUDPSocket(-1);
							IpAddr.d1 = 192;
							IpAddr.d2 = 168;
							IpAddr.d3 = 56;
							IpAddr.d4 = 1;

							
							//文字列送信
							///*NetWorkSendUDP(NetUDPHandle, IpAddr,SERVER_PORT,strl.c_str(),strl.size());*/

							IPDATA IPAddress[1];
							int IPNum;
							GetMyIPAddress(IPAddress, 1, &IPNum);
							std::string Ip;
							unsigned char* ip[5];
							ip[0] = &IPAddress[0].d1 ;
							ip[1] = &IPAddress[0].d2 ;
							ip[2] = &IPAddress[0].d3 ;
							ip[3] = &IPAddress[0].d4 ;

							std::ostringstream ipStr;
							ipStr << static_cast<int>(ip[0][0]) << "."
								<< static_cast<int>(ip[1][0]) << "."
								<< static_cast<int>(ip[2][0]) << "."
								<< static_cast<int>(ip[3][0]);

							Ip = ipStr.str();

							NetWorkSendUDP(NetUDPHandle,IpAddr, SERVER_PORT,Ip.c_str(),Ip.size());

							NetUDPHandle = MakeUDPSocket(SERVER_PORT);

							while (CheckNetWorkRecvUDP(NetUDPHandle) == FALSE) {
								if (ProcessMessage() < 0) break;
							}

							//文字列の受信
							/*NetWorkRecvUDP(NetUDPHandle, NULL, NULL, Buff, 256, FALSE);*/

						

							//UDPソケットハンドルの削除
							DeleteUDPSocket(NetUDPHandle);

							/*SetRankings(strl, 2345);*/

						}
						else {
							if (nowMojiCount == MaxWord -1){
								str.erase(nowMojiCount);
								str.insert(nowMojiCount,cAscii_ToString);
							}
							else {
								nowMojiCount++;
								str.insert(nowMojiCount,cAscii_ToString);
								
							}
						}
						
						
					}
					InCnPrevKey = true;
				}
				else {
					InCnPrevKey = false;
				}
			}
		}
	}

	NameBar(str, word, space, 450, 405, 455, 435, eraseTimer, eraseTime);

	//入力可能文字数がわかるボックス表示
	for (int i = 0; i < MaxWord; i++) {
		if (i > 0) {
			n = a + space;
			DrawBoxAA(n, y1, n + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = n + word;
		}
		else
		{
			DrawBoxAA(x1, y1, x2 + word, y2, GetColor(255, 255, 255), TRUE); //した棒
			a = x2 + word;
		}
	}

	DrawBoxAA(430, 380, (x1 + 25) + MaxWord * word + (MaxWord - 1) * space, 450, GetColor(255, 255, 255), FALSE); //入力枠線
	tText->DrawString(str,450,400);
}



void RankingsSystem::NameBar(std::string _str, float _fSize, float _space,float _x1, float _y1, float _x2, float _y2, float _eraseTimer, float _eraseTime)
{
	float eraseAlpha;
	static float eTimer = _eraseTimer;
	static float eTime = _eraseTime;
	//文字入力バー表示
	if (eTimer > eTime) {
		eTimer = 0.0f;
		eraseAlpha = 0;
	}
	eTimer += 1.0f/60.0f;
	eraseAlpha = 255 - 255 * eTimer / eTime;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, eraseAlpha);
	_str.size();
	if (_str.size() > 0) {
		DrawBoxAA(_x1 + (_fSize + _space) * _str.size(), _y1, _x2 + (_fSize + _space) * _str.size(), _y2, GetColor(255, 255, 255), TRUE);//入力バー
	}
	else {
		DrawBoxAA(_x1, _y1, _x2, _y2, GetColor(255, 255, 255), TRUE);//入力バー
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


