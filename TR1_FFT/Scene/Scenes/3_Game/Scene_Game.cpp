#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"
#include "Environment.h"
#include "MyTextureManager.h"


std::complex<float> a;
float theta[2] = { 0.0f };
float t = 0.0f;

Scene_Game::Scene_Game() {
	Init();
	MyFunc::Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	isDraw_ = false;
	frameCount_ = 0;
	getFrame_ = 1;
	nyquist_ = (60.0f / float(getFrame_)) * 0.5f;// 最大周波数
	container_.clear();
	container_.push_back(Container());
}

void Scene_Game::Update() {
	if(InputKey::trigger[DIK_RETURN]) {
		//SceneManager::SetScene(new Scene_Clear());
	}

	if(InputKey::mouseTrigger_[1]) {
		// データをFFTする
		FFTX_ = DFT(container_.back().positionX_);
		FFTY_ = DFT(container_.back().positionY_);
		DFTX_ = DFT(container_.back().positionX_);
		//IFFTX_ = IFFT(FFTX_);
		IDFTX_ = IDFT(FFTX_);

		// データを解析する
		resultX_ = TransformFFT(FFTX_);
		resultY_ = TransformFFT(FFTY_);

		// コンテナにコピー
		container_.back().resultX_ = resultX_;
		container_.back().resultY_ = resultY_;
		container_.back().isDrawFourier_ = true;

		// データをソートする
		resultX_ = SortFFT(resultX_);
		resultY_ = SortFFT(resultY_);

		// 振幅の最大値を渡す
		if(resultX_[0].level > resultY_[0].level){
			container_.back().maxLevel_ = resultX_[0].level;
		} else{
			container_.back().maxLevel_ = resultY_[0].level;
		}

		isDrawFourier_ = true;
	}

	// 描画フラグをオンにする
	if(InputKey::mousePos_.x >= windowLT.x && InputKey::mousePos_.x <= windowRB.x) {
		if(InputKey::mousePos_.y >= windowLT.y && InputKey::mousePos_.y <= windowRB.y) {
			if(InputKey::mouseTrigger_[0]) {
				isDraw_ = true;
				container_.back().positionX_.clear();
				container_.back().positionY_.clear();

				isDrawFourier_ = false;
				container_.back().isDrawFourier_ = false;
				theta[0] = 0.0f;
				theta[1] = 0.0f;
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
		}
	}

	if(isDrawFourier_){
		if(frameCount_ % (getFrame_ * 2) == 0){
			t++;
			t > FFTX_.size() ? t = 0.0f : t;
		}
	} else{
		t = 0.0f;
	}
}

void Scene_Game::Draw() {

	MyFunc::DrawQuad(
		windowCenter,
		{ (float)kWindowSizeX ,(float)kWindowSizeY },
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


		if(frameCount_ % getFrame_ == 0){

			// 初期化
			fourierPoint_[0] = { 0.0f,0.0f };
			fourierPoint_[1] = { 0.0f,0.0f };

			std::complex<float>fourierPos[2];
			fourierPos[0] = { 0.0f,0.0f };
			fourierPos[1] = { 0.0f,0.0f };

			for(int i = 0; i < resultX_.size(); i++){

				theta[0] = (float(2.0 * M_PI) * i * t) / float(FFTX_.size());
				theta[1] = (float(2.0 * M_PI) * i * t) / float(FFTY_.size());

				Vec2 tmpPos1 = fourierPoint_[0];
				Vec2 tmpPos2 = fourierPoint_[1];

				MyFunc::DrawQuad(
					Vec2(
						fourierPoint_[1].x + windowCenter.x + canvasSize.x * 0.5f,
						fourierPoint_[1].y + windowCenter.y),
					Vec2(
						resultY_[i].level * 2,
						resultY_[i].level * 2),
					0, 0, 128, 128,
					1.0f, 1.0f,
					"ellipseLine",
					0.0f,
					0x00ff00ff
				);

				MyFunc::DrawQuad(
					Vec2(
						fourierPoint_[0].x + windowCenter.x,
						fourierPoint_[0].y + windowCenter.y + canvasSize.y * 0.5f),
					Vec2(
						resultX_[i].level * 2,
						resultX_[i].level * 2),
					0, 0, 128, 128,
					1.0f, 1.0f,
					"ellipseLine",
					0.0f,
					0x00ff00ff
				);

				// 座標の決定
				fourierPos[0] += (FFTX_[i] / float(FFTX_.size())) * std::polar(1.0f, theta[0]);
				fourierPos[1] += (FFTY_[i] / float(FFTY_.size())) * std::polar(1.0f, theta[1]);

				fourierPoint_[0] = { fourierPos[0].real(),fourierPos[0].imag() };
				fourierPoint_[1] = { fourierPos[1].imag(),fourierPos[1].real() };

				if(i != resultX_.size() - 1){
					Novice::DrawLine(
						int(tmpPos2.x + windowCenter.x + canvasSize.x * 0.5f),
						int(tmpPos2.y + windowCenter.y),
						int(fourierPoint_[1].x + windowCenter.x + canvasSize.x * 0.5f),
						int(fourierPoint_[1].y + windowCenter.y),
						0x00ff00ff
					);

					Novice::DrawLine(
						int(tmpPos1.x + windowCenter.x),
						int(tmpPos1.y + windowCenter.y + canvasSize.y * 0.5f),
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[0].y + windowCenter.y + canvasSize.y * 0.5f),
						0x00ff00ff
					);

					Novice::DrawEllipse(
						int(fourierPoint_[1].x + windowCenter.x + canvasSize.x * 0.5f),
						int(fourierPoint_[1].y + windowCenter.y),
						4,
						4,
						0.0f,
						0x00ff00ff,
						kFillModeSolid
					);

					Novice::DrawEllipse(
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[0].y + windowCenter.y + canvasSize.y * 0.5f),
						4,
						4,
						0.0f,
						0x00ff00ff,
						kFillModeSolid
					);
				} else{

					Novice::DrawLine(
						int(fourierPoint_[1].x + windowCenter.x + canvasSize.x * 0.5f),
						int(fourierPoint_[1].y + windowCenter.y),
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[1].y + windowCenter.y),
						0xf542efff
					);

					Novice::DrawLine(
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[0].y + windowCenter.y + canvasSize.y * 0.5f),
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[1].y + windowCenter.y),
						0x42a7f5ff
					);

					Novice::DrawEllipse(
						int(fourierPoint_[1].x + windowCenter.x + canvasSize.x * 0.5f),
						int(fourierPoint_[1].y + windowCenter.y),
						4,
						4,
						0.0f,
						0xf542efff,
						kFillModeSolid
					);

					Novice::DrawEllipse(
						int(fourierPoint_[0].x + windowCenter.x),
						int(fourierPoint_[0].y + windowCenter.y + canvasSize.y * 0.5f),
						4,
						4,
						0.0f,
						0x42a7f5ff,
						kFillModeSolid
					);
				}
			}

			Novice::DrawEllipse(
				int(windowCenter.x + fourierPoint_[0].x),
				int(windowCenter.y + fourierPoint_[1].y),
				10, 10, 0.0f,
				0x000000ff,
				kFillModeSolid
			);

			for(int i = 0; i < container_[0].positionX_.size() - 1; i++){
				/*Novice::ScreenPrintf(180 + 100 * i, 0, "[%.2f], ", container_[0].positionX_[i]);
				Novice::ScreenPrintf(180 + 100 * i, 20, "[%.2f], ", FFTX_[i].real());
				Novice::ScreenPrintf(180 + 100 * i, 40, "[%.2f], ", FFTX_[i].imag());
				Novice::ScreenPrintf(180 + 100 * i, 60, "[%.2f], ", IFFTX_[i].real());*/
			}
		}
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

void Scene_Game::Butterfly(std::vector<std::complex<float>>* data, bool inverse)
{
	// 要素の半分の数を求める
	size_t halfStep = data->size() / 2;

	// 要素数が1のときはこれ以上半分にできないため、処理されない
	if(halfStep < 1){ return; }

	// 要素を前半と後半に分けて再帰処理するため、変数を用意
	std::vector<std::complex<float>> newDataFiestHalf(halfStep);
	std::vector<std::complex<float>> newDataSecondHalf(halfStep);

	// 逆変換の際には反対周りになるようにする
	std::complex<float> w = std::polar(1.0f, float(-2.0 * M_PI * (inverse ? -1.0 : 1.0)) / float(data->size()));

	for(size_t i = 0; i < halfStep; i++){
		// バタフライ演算の本体
		newDataFiestHalf[i] = (*data)[i] + (*data)[i + halfStep];
		newDataSecondHalf[i] = ((*data)[i] - (*data)[i + halfStep]);
		newDataSecondHalf[i] *= std::pow(w, i);
	}

	// 前半と後半に分けて再帰処理
	Butterfly(&newDataFiestHalf, inverse);
	Butterfly(&newDataSecondHalf, inverse);

	// 返ってきた結果を結合して引数のポインタの値を更新
	newDataFiestHalf.insert(newDataFiestHalf.end(), newDataSecondHalf.begin(), newDataSecondHalf.end());
	*data = newDataFiestHalf;
}

std::vector<std::complex<float>> Scene_Game::FFT(const std::vector<float>& data)
{
	// データ数を2の累乗にする
	std::vector<float>exData = Exponentiation(data);
	std::vector<std::complex<float>>tmp(exData.size(), 0);
	std::vector<std::complex<float>>result(exData.size(), 0);
	for(int i = 0; i < exData.size(); i++){ tmp[i].real(exData[i]); }

	// バタフライ演算をして結果を求める
	Butterfly(&tmp, false);

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
		result[i] = tmp[reserved];
	}

	return result;
}

std::vector<std::complex<float>> Scene_Game::DFT(const std::vector<float>& data)
{
	float PI2 = float(2.0 * M_PI);
	int indexSize = int(data.size());

	std::vector<std::complex<float>> tmp(indexSize, std::complex<float>(0.0f, 0.0f));
	std::vector<std::complex<float>> result(indexSize, std::complex<float>(0.0f, 0.0f));
	std::complex<float>imaginary(0, 1);

	for(int i = 0; i < indexSize; i++){
		// 複素数として計算するため、floatのデータを複素数型complexの実部にコピー。虚部は0。
		tmp[i].real(data[i]);
	}

	for(int i = 0; i < indexSize; i++){// いまどのデータをフーリエ変換しているか。公式でいう"t"。

		for(int j = 0; j < indexSize; j++){// ここからフーリエ変換の本体

			float angle = (PI2 * i * j) / float(indexSize);// 2πtx/Nの部分
			result[i] += tmp[j] * std::exp(-imaginary * angle);// f(x) * e を計算 (std::exp()が"e"を作成してくれる関数)

		}
	}

	return result;
}

std::vector<std::complex<float>> Scene_Game::IDFT(const std::vector<std::complex<float>>& FFTdata)
{
	float PI2 = float(2.0 * M_PI);
	int indexSize = int(FFTdata.size());
	std::vector<std::complex<float>> result(indexSize, std::complex<float>(0.0f, 0.0f));

	for(int i = 0; i < indexSize; i++){

		for(int j = 0; j < indexSize; j++){
			float angle = (PI2 * i * j) / float(indexSize);
			result[i] += FFTdata[j] * std::polar(1.0f, angle);
		}

		result[i] /= float(indexSize);// 要素数で割って正規化する
	}

	return result;
}

std::complex<float> Scene_Game::IDFT(const std::vector<std::complex<float>>& FFTdata, float time)
{
	time = std::clamp(time, 0.0f, float(FFTdata.size() - 1));
	float PI2 = float(2.0 * M_PI);
	int indexSize = int(FFTdata.size());
	std::complex<float> result(0, 0);

	for(int j = 0; j < indexSize; j++){
		float angle = (PI2 * time * j) / float(indexSize);
		result += FFTdata[j] * std::polar(1.0f, angle);
	}
	result /= float(indexSize);

	return result;
}

std::vector<std::complex<float>> Scene_Game::IFFT(const std::vector<std::complex<float>>& FFTdata)
{
	std::vector<std::complex<float>>tmp(FFTdata.size(), 0);
	std::vector<std::complex<float>>result(FFTdata.size(), 0);
	for(int i = 0; i < FFTdata.size(); i++){ tmp[i] = FFTdata[i]; }

	// バタフライ演算をして結果を求める
	Butterfly(&tmp, true);

	// サイズで割る
	for(int i = 0; i < tmp.size(); i++){
		tmp[i] /= float(tmp.size());
	}

	// 要素を表すのに必要な最低のビット数を求める
	int bitMax = 1;
	for(int i = 2; i < FFTdata.size(); i *= 2){ bitMax++; }

	// ビットの左右反転と要素の入れ替え
	for(int i = 0; i < FFTdata.size(); i++){

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
		result[i] = tmp[reserved];
	}

	return result;
}

// FFTデータを振幅、位相、周波数の要素に分けて格納する
std::vector<FFTResult> Scene_Game::TransformFFT(const std::vector<std::complex<float>>& data)
{
	// 結果を格納する変数
	std::vector<FFTResult> result(data.size());

	for(int i = 0; i < result.size(); i++){
		Vec2 vec = { data[i].real(),data[i].imag() };// 複素数からベクトルに変換

		result[i].level = MyFunc::Length(vec) / result.size();// 絶対値が振幅の大きさ
		result[i].phase = std::atan2(vec.y, vec.x);// 位相
		result[i].theta = (float(M_PI * 2.0) * i) / data.size();
		result[i].index = i;
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
