#include "Container.h"
#include <Novice.h>
#include "InputKey.h" 
#include "Environment.h"

void Container::Draw(int getFrame) {

	int size = 1;
	getFrame;

	for(int n = 0; n < 2; n++){

		std::vector<Vec2>tmp = pos_[n];
		int color = 0;
		n == 0 ? color = 0xff0000ff : color = 0x0000ffff;

		for(int n2 = 0; n2 < tmp.size(); n2++) {
			tmp[n2] += windowCenter;
		}

		if(tmp.size() > 3) {
			for(int i = 0; i < tmp.size() - 3; i++) {
				if(i % 3 == 0) {
					for(int j = 0; j < size; j++) {

						Vec2 pos1 =
							MyFunc::CatmullRom(
								tmp[i], tmp[i + 1], tmp[i + 2], tmp[i + 3],
								float(j) / float(size)
							);

						Vec2 pos2 =
							MyFunc::CatmullRom(
								tmp[i], tmp[i + 1], tmp[i + 2], tmp[i + 3],
								float(j + 1) / float(size)
							);

						Novice::DrawLine(
							int(pos1.x),
							int(pos1.y),
							int(pos2.x),
							int(pos2.y),
							color
						);
					}
				}
			}

			for(int j = 0; j < size; j++) {

				Vec2 pos1 =
					MyFunc::CatmullRom(
						tmp.back() - 3, tmp.back() - 2, tmp.back() - 1, tmp.back(),
						float(j) / float(size)
					);

				Vec2 pos2 =
					MyFunc::CatmullRom(
						tmp.back() - 3, tmp.back() - 2, tmp.back() - 1, tmp.back(),
						float(j + 1) / float(size)
					);

				Novice::DrawLine(
					int(pos1.x),
					int(pos1.y),
					int(pos2.x),
					int(pos2.y),
					color
				);

				Novice::DrawLine(
					int(pos2.x),
					int(pos2.y),
					int(tmp.back().x),
					int(tmp.back().y),
					color
				);
			}
		}
	}
}