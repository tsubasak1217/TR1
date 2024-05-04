#include "Container.h"
#include <Novice.h>
#include "MyFunc.h"
#include "InputKey.h" 

void Container::Draw(int getFrame) {

	int size = (int(float(getFrame) / 4.0f) * 3) * 16;

	if (positions_.size() > 3) {
		for (int i = 0; i < positions_.size() - 3; i++) {
			if (i % 3 == 0) {
				for (int j = 0; j < size; j++) {

					Vec2 pos1 =
						MyFunc::CatmullRom(
							positions_[i], positions_[i + 1], positions_[i + 2], positions_[i + 3],
							float(j) / float(size)
						);

					Vec2 pos2 =
						MyFunc::CatmullRom(
							positions_[i], positions_[i + 1], positions_[i + 2], positions_[i + 3],
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

		for (int j = 0; j < size; j++) {

			Vec2 pos1 =
				MyFunc::CatmullRom(
					positions_.back() - 3, positions_.back() - 2, positions_.back() - 1, positions_.back(),
					float(j) / float(size)
				);

			Vec2 pos2 =
				MyFunc::CatmullRom(
					positions_.back() - 3, positions_.back() - 2, positions_.back() - 1, positions_.back(),
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
				int(positions_.back().x),
				int(positions_.back().y),
				0xff0000ff
			);
		}
	}
}