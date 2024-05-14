#include "Container.h"
#include <Novice.h>
#include "InputKey.h" 
#include "Environment.h"

void Container::Draw(int getFrame) {

	int size = (int(float(getFrame) / 4.0f) * 3) * 16;

	std::vector<Vec2>positions(positionX_.size());

	for(int i = 0; i < positions.size(); i++){
		positions[i] = {
		positionX_[i] + windowCenter.x,
		positionY_[i] + windowCenter.y
		};
	}

	if(positions.size() > 3) {
		for(int i = 0; i < positions.size() - 3; i++) {
			if(i % 3 == 0) {
				for(int j = 0; j < size; j++) {

					Vec2 pos1 =
						MyFunc::CatmullRom(
							positions[i], positions[i + 1], positions[i + 2], positions[i + 3],
							float(j) / float(size)
						);

					Vec2 pos2 =
						MyFunc::CatmullRom(
							positions[i], positions[i + 1], positions[i + 2], positions[i + 3],
							float(j + 1) / float(size)
						);

					Novice::DrawLine(
						int(pos1.x),
						int(pos1.y),
						int(pos2.x),
						int(pos2.y),
						0xff0000ff
					);
				}
			}
		}

		for(int j = 0; j < size; j++) {

			Vec2 pos1 =
				MyFunc::CatmullRom(
					positions.back() - 3, positions.back() - 2, positions.back() - 1, positions.back(),
					float(j) / float(size)
				);

			Vec2 pos2 =
				MyFunc::CatmullRom(
					positions.back() - 3, positions.back() - 2, positions.back() - 1, positions.back(),
					float(j + 1) / float(size)
				);

			Novice::DrawLine(
				int(pos1.x),
				int(pos1.y),
				int(pos2.x),
				int(pos2.y),
				0xff0000ff
			);

			Novice::DrawLine(
				int(pos2.x),
				int(pos2.y),
				int(positions.back().x),
				int(positions.back().y),
				0xff0000ff
			);
		}


		if(isDrawFourier_){

			float devideEvery = ((windowCenter.x - canvasSize.x * 0.5f) * 0.95f) / resultX_.size();
			float sukima = ((windowCenter.x - canvasSize.x * 0.5f) * 0.05f) * 0.5f;

			for(int i = 0; i < resultX_.size(); i++){

				float lengthX = (resultX_[i].level / maxLevel_) * canvasSize.y;
				float lengthY = (resultY_[i].level / maxLevel_) * canvasSize.y;

				Novice::DrawLine(
					int(sukima + devideEvery * i),
					int(windowCenter.y + canvasSize.y * 0.5f),
					int(sukima + devideEvery * i),
					int(windowCenter.y + canvasSize.y * 0.5f - lengthX),
					0x42a7f5ff
				);

				Novice::DrawLine(
					int(sukima + windowCenter.x + (canvasSize.y * 0.5f) + devideEvery * i),
					int(windowCenter.y + canvasSize.y * 0.5f),
					int(sukima + windowCenter.x + (canvasSize.y * 0.5f) + devideEvery * i),
					int(windowCenter.y + canvasSize.y * 0.5f - lengthY),
					0xf542efff
				);
			}
		}
	}
}