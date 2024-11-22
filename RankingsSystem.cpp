#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"OutText.h"
#include"ScoreAndTimeAndMap.h"
#include <unordered_map>

namespace
{
	IPDATA IpAddr;
	int NetUDPHandle;
	const unsigned short SERVER_PORT = 8888;
	const unsigned short CLIENT_PORT = 8080;

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

	const float MOVETIME{ 1.0f };

	bool sendrecv;
}



RankingsSystem::RankingsSystem(GameObject* parent)
	: GameObject(parent, "RankingsSystem"), width(0), height(0), csv(nullptr), output_(false), tText(nullptr), InputHandle(0), SetEnd(false), Name(),
	eraseAlpha(0), eraseTime(0), eraseTimer(0), flame(0), x1(0), y1(0), x2(0), y2(0), space(0), word(0), count(0), a(0), n(0), MaxWord(0)
{
	transform_.position_ = { 0,0,0 };
}

RankingsSystem::~RankingsSystem()
{
}

void RankingsSystem::Initialize()
{
	output_csv_file_path_RecvRankingsSortData = "Assets\\Rankings\\RecvRankingsSortData.csv";
	csv = new CsvReader(output_csv_file_path_RecvRankingsSortData);
	width = csv->GetColumns(0);
	height = csv->GetLines();

	tText = Instantiate<OutText>(GetParent());

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


	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput(MaxWord, FALSE, TRUE, FALSE);

	//N[y][x]�Ɉʒu���posX1,X2,Y1,Y2��}��
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (y == 0 && x == 6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
				del_space_enter++;
			}
			else if (y == 1 && x == 6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
				del_space_enter++;
			}
			else if (y == 2 && x == 6) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,del_space_enter };
			}
			else if (AsciiCodeEN < 91 && x < 5) {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,AsciiCodeEN };
				AsciiCodeEN++;
			}
			else {
				N[y][x] = { dcx1 + mojiSize * x,dcy1 + mojiSize * y,dcx2 + mojiSize * x,dcy2 + mojiSize * y,0 };
			}
		}
	}
	str = cName;

	sendrecv = false;
	RecvOK_ = false;
	movetiemr_ = MOVETIME;
}

void RankingsSystem::Update()
{
	if (!sendrecv) {
		GetJoypadXInputState(DX_INPUT_PAD1, &pad);
	}
	if (output_) {
		switch (nowDevice)
		{
		case KEY_AND_MOUSE:
		{
			// ���͂��I�����Ă���ꍇ�͏I��
			if (CheckKeyInput(InputHandle) != 0) {
				if (!SetEnd) {
					///*SetRankings(Name, 500);*/

					SetEnd = true;
					/*SortScore();*/
				}
			}
			// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
			SetActiveKeyInput(InputHandle);

			//���̓��[�h��`��
			DrawKeyInputModeString(640, 480);

			// ���͓r���̕������`��
			DrawKeyInputString(0, 0, InputHandle);

			// ���͂��ꂽ��������擾
			GetKeyInputString(Name, InputHandle);
			break;
		}
		case PAD:
		{
			if (sendrecv)
				Move();
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

void RankingsSystem::DrawWriteUI()
{
	std::string str = Name;

	NameBar(str, word, space, 450, 405, 455, 435, eraseTimer, eraseTime);

	//���͉\���������킩��{�b�N�X�\��
	for (int i = 0; i < MaxWord; i++) {
		if (i > 0) {
			n = a + space;
			DrawBoxAA(n, y1, n + word, y2, GetColor(255, 255, 255), TRUE); //�����_
			a = n + word;
		}
		else
		{
			DrawBoxAA(x1, y1, x2 + word, y2, GetColor(255, 255, 255), TRUE); //�����_
			a = x2 + word;
		}
	}
	DrawBoxAA(430, 380, (x1 + 25) + MaxWord * word + (MaxWord - 1) * space, 450, GetColor(255, 255, 255), FALSE); //���͘g��
	tText->DrawString(Name, 450, 400);
}

void RankingsSystem::DrawWriteUICn()
{
	char b;

	//�I�𕶎��̕\��
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			b = static_cast<char>(N[y][x].Ascii);
			std::string str(1, b);
			if (str == "0") {
				tText->DrawStringJ("�P�X", N[y][x].posX1 - 1 + transform_.position_.x, N[y][x].posY1 + transform_.position_.y + 4);
			}
			else if (str == "1") {
				tText->DrawStringJ("�N�E�n�N", N[y][x].posX1 - 1 + transform_.position_.x, N[y][x].posY1 + transform_.position_.y + 4);
			}
			else if (str == "2") {
				tText->DrawStringJ("�P�b�e�C", N[y][x].posX1 - 1 + transform_.position_.x, N[y][x].posY1 + transform_.position_.y + 4);
			}
			else {
				tText->DrawString(str, N[y][x].posX1 - 1 + transform_.position_.x, N[y][x].posY1 + transform_.position_.y + 4);
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
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT) || pad.ThumbLX >= 10000) {
		if (prevKey == false) {
			PrevKey = RIGHT;
			prevX1 = cx1;
			prevX2 = cx2;
			cx1 += mojiSize;
			cx2 += mojiSize;
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN) || pad.ThumbLY <= -10000) {

		if (prevKey == false) {
			PrevKey = DOWN;
			prevY1 = cy1;
			prevY2 = cy2;
			cy1 += mojiSize;
			cy2 += mojiSize;
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) || pad.ThumbLX <= -10000) {

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


	//�g���O�ɂ͂ݏo���Ȃ��p�̏���
	if (cx1 < N[0][0].posX1) { //��
		cx1 = N[0][0].posX1;
		cx2 = N[0][0].posX2;
	}

	if (cy1 < N[0][0].posY1) { //��
		cy1 = N[0][0].posY1;
		cy2 = N[0][0].posY2;
	}

	if (cx2 > N[Y - 1][X - 1].posX2) { //��
		cx2 = N[Y - 1][X - 1].posX2;
		cx1 = N[Y - 1][X - 1].posX1;
	}

	if (cy2 > N[Y - 1][X - 1].posY2) { //��
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

	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (cx1 == N[y][x].posX1 && cy1 == N[y][x].posY1 && cx2 == N[y][x].posX2 && cy2 == N[y][x].posY2 ) {
				if (N[y][x].Ascii == 48) {
					/*DrawBox(cx1, cy1, cx2 + mojiSize + 4, cy2, GetColor(255, 255, 255), FALSE);*/
					DrawLine(cx1+transform_.position_.x, cy2+transform_.position_.y, cx2+transform_.position_.x + mojiSize + 4,cy2+transform_.position_.y, GetColor(255, 255, 255), FALSE);
				}
				else if (N[y][x].Ascii == 49) {
				/*	DrawBox(cx1, cy1, cx2 + (mojiSize + 4)*3 , cy2, GetColor(255, 255, 255), FALSE);*/
					DrawLine(cx1+transform_.position_.x, cy2+transform_.position_.y, cx2+transform_.position_.x + (mojiSize + 4) * 3, cy2+transform_.position_.y, GetColor(255, 255, 255), FALSE);
				}
				else if (N[y][x].Ascii == 50) {
					/*DrawBox(cx1, cy1, cx2 + (mojiSize + 4) *3, cy2, GetColor(255, 255, 255), FALSE);*/
					DrawLine(cx1+transform_.position_.x, cy2+transform_.position_.y, cx2+transform_.position_.x + (mojiSize + 4) * 3, cy2+transform_.position_.y, GetColor(255, 255, 255), FALSE);
				}
				else {
					/*DrawBox(cx1, cy1, cx2, cy2, GetColor(255, 255, 255), FALSE);*/
					DrawLine(cx1+transform_.position_.x, cy2+transform_.position_.y, cx2+transform_.position_.x , cy2+transform_.position_.y, GetColor(255, 255, 255), FALSE);
				}
			
			}
		}
	}



	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			if (cx1 == N[y][x].posX1 && cy1 == N[y][x].posY1 && cx2 == N[y][x].posX2 && cy2 == N[y][x].posY2) {
				if (CheckHitKey(KEY_INPUT_RETURN) || pad.Buttons[XINPUT_BUTTON_A]) {
					if (InCnPrevKey == false) {
						char cAscii = static_cast<char>(N[y][x].Ascii);
						std::string cAscii_ToString(1, cAscii);
						if (cAscii == 48) {
							cAscii = 127;
							if (nowMojiCount >= 0) {
								if (nowMojiCount == MaxWord - 1) {
									str.erase(nowMojiCount);
									nowMojiCount = nowMojiCount - 1;
								}
								else {
									str.erase(nowMojiCount);
									nowMojiCount = nowMojiCount - 1;
								}
							}
						}
						else if (cAscii == 49) {
							cAscii = 32;
							cAscii_ToString = cAscii;
							if (nowMojiCount == MaxWord - 1) {
								str.erase(nowMojiCount);
								str.insert(nowMojiCount, cAscii_ToString);
							}
							else {
								nowMojiCount++;
								str.insert(nowMojiCount, cAscii_ToString);

							}
							//����
						}
						else if (cAscii == 50) {
							/*std::string strl(str);*/

							//UDP�ʐM�p�\�P�b�g�n���h�����쐬
							NetUDPHandle = MakeUDPSocket(-1);
							IpAddr.d1 = 192;
							IpAddr.d2 = 168;
							/*IpAddr.d3 = 42;
							IpAddr.d4 = 16;*/
							IpAddr.d3 = 43;
							IpAddr.d4 = 42;

							IPDATA IPAddress[2];
							int IPNum;
							GetMyIPAddress(IPAddress, 2, &IPNum);
							std::string Ip;
							unsigned char* ip[5];
							ip[0] = &IPAddress[1].d1;
							ip[1] = &IPAddress[1].d2;
							ip[2] = &IPAddress[1].d3;
							ip[3] = &IPAddress[1].d4;

							std::ostringstream ipStr;
							ipStr << static_cast<int>(ip[0][0]) << "."
								<< static_cast<int>(ip[1][0]) << "."
								<< static_cast<int>(ip[2][0]) << "."
								<< static_cast<int>(ip[3][0]);

							Ip = ipStr.str();

							std::string SendData = str + "." + std::to_string(ScoreAndTimeAndMap::GetScore()) + ":" + Ip;


							//�����񑗐M
							assert(NetWorkSendUDP(NetUDPHandle, IpAddr, SERVER_PORT, SendData.c_str(), SendData.size()) >= 0);
							DeleteUDPSocket(NetUDPHandle);



							NetUDPHandle = MakeUDPSocket(CLIENT_PORT);

							while (CheckNetWorkRecvUDP(NetUDPHandle) == FALSE) {
								if (ProcessMessage() < 0) break;
							}

							std::vector<std::string> nData;
							std::vector<std::string> rData;
							std::vector<std::string> sData;

							//������̎�M
							if (NetWorkRecvUDP(NetUDPHandle, NULL, NULL, Buff, 256, FALSE) >= 0) {

								std::string line = Buff;
								std::stringstream line2(line);
								std::string s;

								std::vector<std::string> splitData;

								while (std::getline(line2, s, ':')) {
									splitData.push_back(s);
								}

								std::stringstream split1(splitData[0]);
								std::stringstream split2(splitData[1]);
								std::stringstream split3(splitData[2]);

								while (std::getline(split1, s, '.')) {
									rData.push_back(s);
								}

								while (std::getline(split2, s, '.')) {
									nData.push_back(s);
								}

								while (std::getline(split3, s, '.')) {
									sData.push_back(s);
								}

								RecvDataInsert(nData,sData,rData);
							}
							else {
								nData.clear();
								sData.clear();
								rData.clear();
								RecvDataInsert(nData, sData,rData);
							}
							//UDP�\�P�b�g�n���h���̍폜
							DeleteUDPSocket(NetUDPHandle);

							/*SetRankings(strl, 2345);*/
							sendrecv = true;

						}
						else {
							if (nowMojiCount == MaxWord - 1) {
								str.erase(nowMojiCount);
								str.insert(nowMojiCount, cAscii_ToString);
							}
							else {
								nowMojiCount++;
								str.insert(nowMojiCount, cAscii_ToString);

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

	//���͉\���������킩��{�b�N�X�\��
	for (int i = 0; i < MaxWord; i++) {
		if (i > 0) {
			n = a + space;
			DrawBoxAA(n + transform_.position_.x, y1 + transform_.position_.y, n + transform_.position_.x + word, y2 + transform_.position_.y, GetColor(255, 255, 255), TRUE); //�����_
			a = n + word;
		}
		else
		{
			DrawBoxAA(x1 + transform_.position_.x, y1 + transform_.position_.y, x2 + transform_.position_.x + word, y2 + transform_.position_.y, GetColor(255, 255, 255), TRUE); //�����_
			a = x2 + word;
		}
	}

	DrawBoxAA(transform_.position_.x + 430, transform_.position_.y + 380,
		(x1+transform_.position_.x + 25) + MaxWord * word + (MaxWord - 1) * space, transform_.position_.y + 450, GetColor(255, 255, 255), FALSE); //���͘g��
	tText->DrawString(str, transform_.position_.x + 450, transform_.position_.y + 400);
}

void RankingsSystem::NameBar(std::string _str, float _fSize, float _space, float _x1, float _y1, float _x2, float _y2, float _eraseTimer, float _eraseTime)
{
	_x1 += transform_.position_.x;
	_y1 += transform_.position_.y;
	_x2 += transform_.position_.x;
	_y2 += transform_.position_.y;

	float eraseAlpha;
	static float eTimer = _eraseTimer;
	static float eTime = _eraseTime;
	//�������̓o�[�\��
	if (eTimer > eTime) {
		eTimer = 0.0f;
		eraseAlpha = 0;
	}
	eTimer += 1.0f / 60.0f;
	eraseAlpha = 255 - 255 * eTimer / eTime;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, eraseAlpha);
	_str.size();
	if (_str.size() > 0) {
		DrawBoxAA(_x1 + (_fSize + _space) * _str.size(), _y1, _x2 + (_fSize + _space) * _str.size(), _y2, GetColor(255, 255, 255), TRUE);//���̓o�[
	}
	else {
		DrawBoxAA(_x1, _y1, _x2, _y2, GetColor(255, 255, 255), TRUE);//���̓o�[
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void RankingsSystem::RecvDataInsert(std::vector<std::string> n, std::vector<std::string> s,std::vector<std::string> r)
{
	std::ofstream ofs_csv_file(output_csv_file_path_RecvRankingsSortData);
	ofs_csv_file << "Rank" << "," <<"PlayerName" << "," << "PlayerScore";
	ofs_csv_file << std::endl;
	std::vector<std::string> rnsData;
	/*std::map <float, std::string,std::string> Data;*/
	/*std::vector<std::pair<float, std::string>> data;*/
	if (n.empty()) {
		ofs_csv_file << "�f�[�^����M�ł��܂���ł���" << std::endl;
	}
	else {
		for (int i = 0; i < n.size(); i++) {
			ofs_csv_file << r[i] << "," << n[i] << "," << s[i];
			ofs_csv_file << std::endl;
		}
		/*for (int i = 0; i < n.size(); i++) {
			Data.insert(std::pair<float, std::string>(s[i], n[i]));
		}
		for (auto it = Data.rbegin(); it != Data.rend(); it++) {
			ofs_csv_file << it->second << "," << it->first ;
			ofs_csv_file << std::endl;
		}*/
	}
	/*for (int i = 0; i < n.size();i++) {
			Data.insert(std::pair<std::string, float>(n[i], s[i]));
	}
	for (std::unordered_map<std::string, float>::iterator it = Data.begin(); it != Data.end(); it++) {
		data.push_back({ it->second, it->first });
	}

	for (std::unordered_map<std::string, float>::iterator it = Data.begin(); it != Data.end(); it++) {
		ofs_csv_file << it->first << "," << it->second;
		ofs_csv_file << std::endl;
	}*/
	ofs_csv_file.close();
}

void RankingsSystem::Move()
{
	movetiemr_ -= Time::DeltaTime();
	if (movetiemr_ < 0) {
		RecvOK_ = true;
		transform_.position_.x -= 400 * Time::DeltaTime();
		if (transform_.position_.x <= -1300)
			KillMe();
	}
}

