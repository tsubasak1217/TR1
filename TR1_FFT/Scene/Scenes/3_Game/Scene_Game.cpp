#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"
#include "Environment.h"
#include "MyFunc.h"
#include "MyTextureManager.h"


std::complex<float> a;

Scene_Game::Scene_Game() {
	Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	isDraw_ = false;
	frameCount_ = 0;
	getFrame_ = 4;
	container_.clear();
}

void Scene_Game::Update() {
	if(InputKey::trigger[DIK_RETURN]) {
		//SceneManager::SetScene(new Scene_Clear());
		container_.push_back(Container());
	}

	// 描画フラグをオンにする
	if(InputKey::mousePos_.x >= windowLT.x && InputKey::mousePos_.x <= windowRB.x) {
		if(InputKey::mousePos_.y >= windowLT.y && InputKey::mousePos_.y <= windowRB.y) {
			if(InputKey::mouseTrigger_[0]) {
				isDraw_ = true;
				container_.push_back(Container());
			}
		}
	}

	// 描画フラグが立っているときの処理
	if(isDraw_) {

		frameCount_++;

		// マウスが離されたら描画終了
		if(InputKey::mouseRelease_[0]) {
			isDraw_ = false;
			frameCount_ = 0;
		}

		// getFrameのフレームごとに座標を取得してコンテナに入れる
		if(frameCount_ % getFrame_ == 0) {
			container_.back().positions_.push_back({
				float(InputKey::mousePos_.x),
				float(InputKey::mousePos_.y)
				}
			);
		}
	}
}

void Scene_Game::Draw() {

	MyFunc::DrawQuad(
		windowCenter,
		canvasSize,
		0, 0,
		1, 1,
		1.0f, 1.0f,
		"white1x1",
		0.0f,
		0xffffffff
	);

	if(container_.size() > 0) {
		container_.back().Draw(getFrame_);
	}

	std::vector<double>test(8, 0);

	test = {
		1.5,
		-3.2,
		2.0,
		0.25,
		3.0,
		1.0,
		4.05,
		3.14
	};

	std::vector<std::complex<double>>aaa(8);
	std::vector<float>test2(8, 0);
	for(int i = 0; i < 8; i++){
		aaa[i].real(test[i]);
		test2[i] = float(test[i]);
	}

	std::vector<std::complex<double>>c = aaa;

	aaa[0] = c[0];
	aaa[1] = c[4];
	aaa[2] = c[2];
	aaa[3] = c[6];
	aaa[4] = c[1];
	aaa[5] = c[5];
	aaa[6] = c[3];
	aaa[7] = c[7];

	std::vector<std::complex<double>>b = aaa;

	b[0] = ((aaa[0] + aaa[4]) + (aaa[2] + aaa[6])) + ((aaa[1] + aaa[5]) + (aaa[3] + aaa[7]));
	b[1] = ((aaa[0] + aaa[4]) + (aaa[2] + aaa[6])) - ((aaa[1] + aaa[5]) + (aaa[3] + aaa[7]));
	b[2] = ((aaa[0] + aaa[4]) - (aaa[2] + aaa[6])) + ((aaa[1] + aaa[5]) - (aaa[3] + aaa[7])) * std::pow(std::polar(1.0, -2.0 * M_PI / 4.0),1);
	b[3] = ((aaa[0] + aaa[4]) - (aaa[2] + aaa[6])) - ((aaa[1] + aaa[5]) - (aaa[3] + aaa[7])) * std::pow(std::polar(1.0, -2.0 * M_PI / 4.0), 1);
	b[4] = ((aaa[0] - aaa[4]) + (aaa[2] - aaa[6]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 2)) + ((aaa[1] - aaa[5]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 1) + (aaa[3] - aaa[7]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 3));
	b[5] = ((aaa[0] - aaa[4]) + (aaa[2] - aaa[6]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 2)) - ((aaa[1] - aaa[5]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 1) + (aaa[3] - aaa[7]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 3));
	b[6] = ((aaa[0] - aaa[4]) - (aaa[2] - aaa[6]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 2)) + ((aaa[1] - aaa[5]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 1) - (aaa[3] - aaa[7]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 3)) * std::pow(std::polar(1.0, -2.0 * M_PI / 4.0), 1);
	b[7] = ((aaa[0] - aaa[4]) - (aaa[2] - aaa[6]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 2)) - ((aaa[1] - aaa[5]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 1) - (aaa[3] - aaa[7]) * std::pow(std::polar(1.0, -2.0 * M_PI / 8.0), 3)) * std::pow(std::polar(1.0, -2.0 * M_PI / 4.0), 1);

	std::vector<std::complex<float>>result = FFT(test2);

	for(int i = 0; i < result.size(); i++){
		Novice::ScreenPrintf(5, 80 + i * 20, "result[%d] : { %f,  %f }", i, result[i].real(), result[i].imag());
		Novice::ScreenPrintf(5, 80 + int(result.size()) * 20 + i * 20, "b[%d] : { %lf,  %lf }", i, b[i].real(), b[i].imag());
	}

#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
	Novice::ScreenPrintf(20, 40, "container size: %d", container_.size());
	if(container_.size() > 0) {
		Novice::ScreenPrintf(20, 60, "points: %d", container_.back().positions_.size());
	}
#endif //_DEBUG
}

void Scene_Game::Fin() {
}

std::vector<float> Scene_Game::Exponentiation(std::vector<float> data) {

	assert(data.size() >= 2);

	// iをcontainerのデータ数以上で一番近い2のべき乗の数にする
	size_t i = 2;
	for(i = 2; i < data.size(); i *= 2) {}

	// iとcontainerのデータ数の差を求める
	i = i - data.size();

	// データ数を2のべき乗個にするため、差の個数分、0で埋める
	for(int j = 0; j < i; j++) {
		data.push_back(0.0f);
	}

	return data;
}

void Scene_Game::Butterfly(std::vector<std::complex<float>>* data)
{

	size_t halfStep = data->size() / 2;

	if(halfStep >= 1){

		std::vector<std::complex<float>> newDataEven(halfStep);
		std::vector<std::complex<float>> newDataOdd(halfStep);
		std::complex<float> w = std::polar(1.0f, float(-2.0 * M_PI) / data->size());

		for(size_t i = 0; i < halfStep; i++){

			newDataEven[i] = (*data)[i] + (*data)[i + halfStep];
			newDataOdd[i] = ((*data)[i] - (*data)[i + halfStep]);
			newDataOdd[i] *= std::pow(w, i);
		}

		Butterfly(&newDataEven);
		Butterfly(&newDataOdd);

		newDataEven.insert(newDataEven.end(),newDataOdd.begin(), newDataOdd.end());
		*data = newDataEven;
	}
}

std::vector<std::complex<float>> Scene_Game::FFT(const std::vector<float>& data)
{
	// データ数を2の累乗にする
	std::vector<float>exData = Exponentiation(data);
	std::vector<std::complex<float>>result(exData.size(), 0);

	// 要素を表すのに必要な最低のビット数を求める
	int bitMax = 1;
	for(int i = 2; i < exData.size(); i *= 2){ bitMax++; }

	// ビットの左右反転と要素の入れ替え
	for(int i = 0; i < exData.size(); i++){

		uint32_t indexNum = i;
		uint32_t reserved = 0;

		for(int j = 0; j < bitMax; j++){
			reserved |= indexNum & 0x1;
			if(j != bitMax - 1){
				indexNum >>= 1;
				reserved <<= 1;
			}
		}

		// 反転して求めた要素を複素数ベクトルの実部に代入
		result[i].real(exData[reserved]);
	}

	// バタフライ演算をして結果を求める
	Butterfly(&result);

	return result;
}
