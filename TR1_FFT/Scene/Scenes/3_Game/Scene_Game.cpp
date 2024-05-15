#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"
#include "Environment.h"
#include "MyTextureManager.h"


std::complex<float> a;
float theta = 0.0f;

Scene_Game::Scene_Game() {
	Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	isDraw_ = false;
	frameCount_ = 0;
	getFrame_ = 4;
	nyquist_ = (60.0f / float(getFrame_)) * 0.5f;// 最大周波数
	container_.clear();
	container_.push_back(Container());
}

void Scene_Game::Update() {
	if(InputKey::trigger[DIK_RETURN]) {
		//SceneManager::SetScene(new Scene_Clear());

		// データをFFTする
		FFTResult_ = FFT(container_.back().position_);

		// データを解析する
		result_ = TransformFFT(FFTResult_, nyquist_,true);

		// コンテナにコピー
		container_.back().resultX_ = result_;
		container_.back().resultY_ = resultY_;
		container_.back().isDrawFourier_ = true;

		// データをソートする
		//resultX_ = SortFFT(resultX_);
		//resultY_ = SortFFT(resultY_);

		// 振幅の最大値を渡す
		/*if(result_[0].level > resultY_[0].level){
			container_.back().maxLevel_ = result_[0].level;
		} else{
			container_.back().maxLevel_ = resultY_[0].level;
		}*/

		isDrawFourier_ = true;
	}

	// 描画フラグをオンにする
	if(InputKey::mousePos_.x >= windowLT.x && InputKey::mousePos_.x <= windowRB.x) {
		if(InputKey::mousePos_.y >= windowLT.y && InputKey::mousePos_.y <= windowRB.y) {
			if(InputKey::mouseTrigger_[0]) {
				isDraw_ = true;
				container_.back().positionX_.clear();
				container_.back().positionY_.clear();
				container_.back().position_.clear();

				isDrawFourier_ = false;
				container_.back().isDrawFourier_ = false;
				theta = 0.0f;
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
			container_.back().positionX_.push_back(
				float(InputKey::mousePos_.x) - windowCenter.x
			);

			container_.back().positionY_.push_back(
				float(InputKey::mousePos_.y) - windowCenter.y
			);

			container_.back().position_.push_back({
				float(InputKey::mousePos_.x) - windowCenter.x,
				float(InputKey::mousePos_.y) - windowCenter.y
				}
			);
		}
	}

	if(isDrawFourier_){

		if(frameCount_ % getFrame_ == 0){

			// 初期化
			fourierPoint_ = { 0.0f,0.0f };

			for(int i = 0; i < result_.size(); i++){

				// 角度を加算していく
				//resultX_[i].currentTheta += resultX_[i].theta;
				//resultY_[i].currentTheta += resultY_[i].theta;

				Vec2 tmpPos = fourierPoint_;
				float r = result_[i].level;

				Novice::DrawEllipse(
					int(fourierPoint_.x + windowCenter.x),
					int(fourierPoint_.y + windowCenter.y),
					int(r),
					int(r),
					0.0f,
					0x000000ff,
					kFillModeWireFrame
				);

				// 座標の決定
				fourierPoint_.x += r * std::cos(result_[i].phase + (i + 1) * theta);
				fourierPoint_.y += r * std::sin(result_[i].phase + (i + 1) * theta);
			}
		
			theta += ((2.0f * float(M_PI)) / result_.size()) * 0.01f;
			if(theta > 2.0f * 3.14f){
				theta = 0.0f;
			}
		}

	}
}

void Scene_Game::Draw() {

	MyFunc::DrawQuad(
		windowCenter,
		{ (float)kWindowSizeX ,(float)kWindowSizeY},
		0, 0,
		1, 1,
		1.0f, 1.0f,
		"white1x1",
		0.0f,
		0x141136ff
	);

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


	if(isDrawFourier_){

		Novice::DrawEllipse(
			int(windowCenter.x + fourierPoint_.x),
			int(windowCenter.y + fourierPoint_.y),
			20, 20, 0.0f,
			0x000000ff,
			kFillModeSolid
		);
	}


#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
	Novice::ScreenPrintf(20, 40, "container size: %d", container_.size());
	if(container_.size() > 0) {
		Novice::ScreenPrintf(20, 60, "points: %d", container_.back().positionX_.size());
	}
#endif //_DEBUG
}

void Scene_Game::Fin() {
}

std::vector<std::complex<float>> Scene_Game::Exponentiation(std::vector<std::complex<float>> data) {

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

std::vector<std::complex<float>> Scene_Game::FFT(const std::vector<std::complex<float>>& data)
{
	// データ数を2の累乗にする
	std::vector<std::complex<float>>exData = Exponentiation(data);
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
		result[i].real(exData[reserved].real());
		result[i].imag(exData[reserved].imag());
	}

	// バタフライ演算をして結果を求める
	Butterfly(&result);

	return result;
}

// FFTデータを振幅、位相、周波数の要素に分けて格納する
std::vector<FFTResult> Scene_Game::TransformFFT(const std::vector<std::complex<float>>& data, float nyquist,bool XorY)
{
	// データ1刻みごとの周波数の変化(ラジアンに変換する)を計算
	float thetaEvery = (nyquist / float(data.size())) * (2.0f * float(M_PI));

	// 結果を格納する変数
	std::vector<FFTResult> result(data.size());
	
	for(int i = 0; i < result.size(); i++){
		Vec2 vec = { data[i].real(),data[i].imag() };// 複素数からベクトルに変換

		result[i].level = MyFunc::Length(vec)/ result.size();// 絶対値が振幅の大きさ
		if(XorY == true){
			result[i].phase = std::atan2(vec.y, vec.x);// 位相
		} else{
			result[i].phase = std::atan2(vec.x, vec.y);// 位相
		}
		result[i].theta = thetaEvery * i;// 周波数(sin関数で扱う際のラジアン)
		result[i].currentTheta = result[i].phase;
	}

	return result;
}

// 絶対値が大きい要素順に並び替える
std::vector<FFTResult> Scene_Game::SortFFT(const std::vector<FFTResult>& data)
{
	std::vector<FFTResult>result = data;

	for(int i = 0; i < data.size() - 1; ++i) {
		for(int j = 0; j < data.size() - i - 1; ++j) {
			if(result[j].level < result[j + 1].level) {
				std::swap(result[j], result[j + 1]);
			}
		}
	}

	return result;
}
