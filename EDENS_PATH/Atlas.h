#pragma once
#include<easyx.h>
#include<vector>
class Atlas
{
public:
	Atlas()=default;
	~Atlas() = default;
	void loadimages(LPCTSTR path, int num) {
		imgs.clear();
		imgs.reserve(num);
		TCHAR str[256];
		for (int i = 0; i < num; i++) {
			_stprintf_s(str, path, i+1);
			IMAGE img;
			loadimage(&img,str);
			imgs.push_back(img);
		}
	}
	void clear() {
		imgs.clear();
	}
	int getsize() {
		return imgs.size();
	}
	IMAGE* get_image(int index) {
		if (index < 0 || index >= imgs.size()) {
			return nullptr;
		}
		return &imgs[index];
	}

	void add_image(IMAGE img) {
		imgs.push_back(img);
	}
private:
	std::vector<IMAGE> imgs;
};

