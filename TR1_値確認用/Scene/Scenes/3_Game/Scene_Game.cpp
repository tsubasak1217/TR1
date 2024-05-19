#include "Scene_Game.h"

#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Clear.h"
#include "Scene_Transition.h"
#include "SceneManager.h"

Scene_Game::Scene_Game() {
	Init();
}

Scene_Game::~Scene_Game() {
}

void Scene_Game::Init() {
	data_.resize(8);
	complex_.resize(8);
	FFTdata_.resize(8);
	IFFTdata_.resize(8);
	step = 0;
}

void Scene_Game::Update() {
	if(InputKey::trigger[DIK_RETURN]) {
		SceneManager::SetScene(new Scene_Clear());
	}

	if(InputKey::trigger[DIK_SPACE]) {
		step++;
		step > 3 ? step = 0 : step;
	}

	std::complex<double> w = std::polar(1.0,(2.0 * M_PI) / 8.0);

	data_[0] = -33.0;
	data_[1] = -26.0;
	data_[2] = -25.0;
	data_[3] = -23.0;
	data_[4] = -34.0;
	data_[5] = -28.0;
	data_[6] = -27.0;
	data_[7] = -20.0;

	for(int i = 0; i < data_.size(); i++){
		complex_[i] = { data_[i],0.0f };
	}

	std::vector<std::complex<double>>tmp(complex_.size());
	tmp[0] = complex_[0];
	tmp[1] = complex_[4];
	tmp[2] = complex_[2];
	tmp[3] = complex_[6];
	tmp[4] = complex_[1];
	tmp[5] = complex_[5];
	tmp[6] = complex_[3];
	tmp[7] = complex_[7];

	if(step == 1){

		w = std::polar(1.0, (2.0 * M_PI) / 8.0);

		tmp[0] = complex_[0] + complex_[4];
		tmp[1] = complex_[1] + complex_[5];
		tmp[2] = complex_[2] + complex_[6];
		tmp[3] = complex_[3] + complex_[7];
		tmp[4] = (complex_[0] - complex_[4]) * std::pow(w, 0);
		tmp[5] = (complex_[1] - complex_[5]) * std::pow(w, 1);
		tmp[6] = (complex_[2] - complex_[6]) * std::pow(w, 2);
		tmp[7] = (complex_[3] - complex_[7]) * std::pow(w, 3);

	} else if(step == 2){

		tmp[0] = complex_[0] + complex_[4];
		tmp[1] = complex_[1] + complex_[5];
		tmp[2] = complex_[2] + complex_[6];
		tmp[3] = complex_[3] + complex_[7];
		tmp[4] = (complex_[0] - complex_[4]) * std::pow(w, 0);
		tmp[5] = (complex_[1] - complex_[5]) * std::pow(w, 1);
		tmp[6] = (complex_[2] - complex_[6]) * std::pow(w, 2);
		tmp[7] = (complex_[3] - complex_[7]) * std::pow(w, 3);

		w = std::polar(1.0, (2.0 * M_PI) / 4.0);
		std::vector<std::complex<double>>tmp2 = tmp;

		tmp[0] = tmp2[0] + tmp2[2];
		tmp[1] = tmp2[1] + tmp2[3];
		tmp[2] = (tmp2[0] - tmp2[2]) * std::pow(w, 0);
		tmp[3] = (tmp2[1] - tmp2[3]) * std::pow(w, 1);

		tmp[4] = tmp2[4] + tmp2[6];
		tmp[5] = tmp2[5] + tmp2[7];
		tmp[6] = (tmp2[4] - tmp2[6]) * std::pow(w, 0);
		tmp[7] = (tmp2[5] - tmp2[7]) * std::pow(w, 1);

	} else if(step == 3){

		tmp[0] = complex_[0] + complex_[4];
		tmp[1] = complex_[1] + complex_[5];
		tmp[2] = complex_[2] + complex_[6];
		tmp[3] = complex_[3] + complex_[7];
		tmp[4] = (complex_[0] - complex_[4]) * std::pow(w, 0);
		tmp[5] = (complex_[1] - complex_[5]) * std::pow(w, 1);
		tmp[6] = (complex_[2] - complex_[6]) * std::pow(w, 2);
		tmp[7] = (complex_[3] - complex_[7]) * std::pow(w, 3);

		w = std::polar(1.0, (2.0 * M_PI) / 4.0);
		std::vector<std::complex<double>>tmp2 = tmp;

		tmp[0] = tmp2[0] + tmp2[2];
		tmp[1] = tmp2[1] + tmp2[3];
		tmp[2] = (tmp2[0] - tmp2[2]) * std::pow(w, 0);
		tmp[3] = (tmp2[1] - tmp2[3]) * std::pow(w, 1);

		tmp[4] = tmp2[4] + tmp2[6];
		tmp[5] = tmp2[5] + tmp2[7];
		tmp[6] = (tmp2[4] - tmp2[6]) * std::pow(w, 0);
		tmp[7] = (tmp2[5] - tmp2[7]) * std::pow(w, 1);

		w = std::polar(1.0, (2.0 * M_PI) / 2.0);
		tmp2 = tmp;

		tmp[0] = tmp2[0] + tmp2[1];
		tmp[1] = (tmp2[0] - tmp2[1]) * std::pow(w, 0);;

		tmp[2] = tmp2[2] + tmp2[3];
		tmp[3] = (tmp2[2] - tmp2[3]) * std::pow(w, 0);

		tmp[4] = tmp2[4] + tmp2[5];
		tmp[5] = (tmp2[4] - tmp2[5]) * std::pow(w, 0);;

		tmp[6] = tmp2[6] + tmp2[7];
		tmp[7] = (tmp2[6] - tmp2[7]) * std::pow(w, 0);

	} else{
		tmp[0] = complex_[0];
		tmp[1] = complex_[4];
		tmp[2] = complex_[2];
		tmp[3] = complex_[6];
		tmp[4] = complex_[1];
		tmp[5] = complex_[5];
		tmp[6] = complex_[3];
		tmp[7] = complex_[7];
	}

	w = std::polar(1.0, (2.0 * M_PI) / 8.0);

	FFTdata_[0] = complex_[0] + complex_[4];
	FFTdata_[1] = complex_[1] + complex_[5];
	FFTdata_[2] = complex_[2] + complex_[6];
	FFTdata_[3] = complex_[3] + complex_[7];
	FFTdata_[4] = (complex_[0] - complex_[4]) * std::pow(w, 0);
	FFTdata_[5] = (complex_[1] - complex_[5]) * std::pow(w, 1);
	FFTdata_[6] = (complex_[2] - complex_[6]) * std::pow(w, 2);
	FFTdata_[7] = (complex_[3] - complex_[7]) * std::pow(w, 3);

	w = std::polar(1.0, (2.0 * M_PI) / 4.0);
	std::vector<std::complex<double>>tmp2 = FFTdata_;

	FFTdata_[0] = tmp2[0] + tmp2[2];
	FFTdata_[1] = tmp2[1] + tmp2[3];
	FFTdata_[2] = (tmp2[0] - tmp2[2]) * std::pow(w, 0);
	FFTdata_[3] = (tmp2[1] - tmp2[3]) * std::pow(w, 1);

	FFTdata_[4] = tmp2[4] + tmp2[6];
	FFTdata_[5] = tmp2[5] + tmp2[7];
	FFTdata_[6] = (tmp2[4] - tmp2[6]) * std::pow(w, 0);
	FFTdata_[7] = (tmp2[5] - tmp2[7]) * std::pow(w, 1);

	w = std::polar(1.0, (2.0 * M_PI) / 2.0);
	tmp2 = FFTdata_;

	FFTdata_[0] = tmp2[0] + tmp2[1];
	FFTdata_[1] = (tmp2[0] - tmp2[1]) * std::pow(w, 0);

	FFTdata_[2] = tmp2[2] + tmp2[3];
	FFTdata_[3] = (tmp2[2] - tmp2[3]) * std::pow(w, 0);

	FFTdata_[4] = tmp2[4] + tmp2[5];
	FFTdata_[5] = (tmp2[4] - tmp2[5]) * std::pow(w, 0);

	FFTdata_[6] = tmp2[6] + tmp2[7];
	FFTdata_[7] = (tmp2[6] - tmp2[7]) * std::pow(w, 0);

	tmp2 = FFTdata_;

	FFTdata_[0] = tmp2[0];
	FFTdata_[1] = tmp2[4];
	FFTdata_[2] = tmp2[2];
	FFTdata_[3] = tmp2[6];
	FFTdata_[4] = tmp2[1];
	FFTdata_[5] = tmp2[5];
	FFTdata_[6] = tmp2[3];
	FFTdata_[7] = tmp2[7];

	for(int i = 0; i < FFTdata_.size(); i++){
		FFTdata_[i].imag(-FFTdata_[i].imag());
	}

	DFTdata_ = DFT(data_);
	FFTdata_ = FFT(data_);
	IFFTdata_ = IFFT(FFTdata_);
	IDFTdata_ = IDFT(DFTdata_);

	for(int i = 0; i < tmp.size(); i++){
		Novice::ScreenPrintf(20, 60 + 20 * i, "DATA{%3f,%3f}", complex_[i].real(), complex_[i].imag());
		Novice::ScreenPrintf(260, 60 + 20 * i, "FFT{%3f,%3f}", FFTdata_[i].real(), FFTdata_[i].imag());
		//Novice::ScreenPrintf(260, 60 + 20 * i, "DFT{%3f,%3f}", DFTdata_[i].real(), DFTdata_[i].imag());
		//Novice::ScreenPrintf(740, 60 + 20 * i, "IFFT{%3f,%3f}", IFFTdata_[i].real(), IFFTdata_[i].imag());
		Novice::ScreenPrintf(500, 60 + 20 * i, "IFFT{%3f,%3f}", IFFTdata_[i].real(), IFFTdata_[i].imag());
	}
}

void Scene_Game::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(20, 20, "scene: Game");
#endif //_DEBUG
}

void Scene_Game::Fin() {
}

std::vector<double> Scene_Game::Exponentiation(std::vector<double> data) 
{

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

void Scene_Game::Butterfly(std::vector<std::complex<double>>* data, bool inverse)
{
	// 要素の半分の数を求める
	size_t halfStep = data->size() / 2;

	// 要素数が1のときはこれ以上半分にできないため、処理されない
	if(halfStep < 1){ return; }

	// 要素を前半と後半に分けて再帰処理するため、変数を用意
	std::vector<std::complex<double>> newDataFiestHalf(halfStep);
	std::vector<std::complex<double>> newDataSecondHalf(halfStep);

	// 逆変換の際には反対周りになるようにする
	std::complex<double> w = std::polar(1.0, double(-2.0 * M_PI * (inverse ? -1.0 : 1.0)) / double(data->size()));

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

std::vector<std::complex<double>> Scene_Game::FFT(const std::vector<double>& data)
{
	// データ数を2の累乗にする
	std::vector<double>exData = Exponentiation(data);
	std::vector<std::complex<double>>tmp(exData.size(), 0);
	std::vector<std::complex<double>>result(exData.size(), 0);
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

std::vector<std::complex<double>> Scene_Game::DFT(const std::vector<double>& data)
{
	double PI2 = (2.0 * M_PI);
	int indexSize = int(data.size());

	std::complex<double>imaginary(0, 1);
	std::vector<std::complex<double>> tmp(indexSize, std::complex<double>(0.0, 0.0));
	std::vector<std::complex<double>> result(indexSize, std::complex<double>(0.0, 0.0));

	for(int i = 0; i < indexSize; i++){
		tmp[i].real(data[i]);
	}

	for(int i = 0; i < indexSize; i++){
		for(int j = 0; j < indexSize; j++){
			double angle = (PI2 * i * j) / double(indexSize);
			result[i] += tmp[j] * std::exp(-imaginary * angle);
		}
	}

	return result;
}

std::vector<std::complex<double>> Scene_Game::IDFT(const std::vector<std::complex<double>>& FFTdata)
{
	double PI2 = (2.0 * M_PI);
	int indexSize = int(FFTdata.size());
	std::complex<double>imaginary(0, 1);
	std::vector<std::complex<double>> result(indexSize, std::complex<double>(0.0, 0.0));

	for(int i = 0; i < indexSize; i++){
		for(int j = 0; j < indexSize; j++){
			double angle = (PI2 * i * j) / double(indexSize);
			result[i] += FFTdata[j] * std::exp(imaginary * angle);
		}
		result[i] /= double(indexSize);
	}

	return result;
}

std::vector<std::complex<double>> Scene_Game::IFFT(const std::vector<std::complex<double>>& FFTdata)
{
	std::vector<std::complex<double>>tmp(FFTdata.size(), 0);
	std::vector<std::complex<double>>result(FFTdata.size(), 0);
	for(int i = 0; i < FFTdata.size(); i++){ tmp[i] = FFTdata[i]; }

	// バタフライ演算をして結果を求める
	Butterfly(&tmp, true);

	// サイズで割る
	for(int i = 0; i < tmp.size(); i++){
		tmp[i] /= double(tmp.size());
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