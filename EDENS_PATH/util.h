#pragma once
#include<easyx.h>
using namespace std;
#pragma comment(lib,"MSIMG32.LIB")
void DrawTransparent(int x, int y, int width, int height, COLORREF color, double alpha) {
	IMAGE buffer;
	int screenWidth = getwidth();
	int screenHeight = getheight();
	getimage(&buffer, 0, 0, screenWidth, screenHeight);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	DWORD* dst = GetImageBuffer(&buffer);

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			int px = x + i;
			int py = y + j;
			if (px >= 0 && px < screenWidth && py >= 0 && py < screenHeight) {
				int index = py * screenWidth + px;
				COLORREF pixelColor = dst[index];
				int pr = GetRValue(pixelColor);
				int pg = GetGValue(pixelColor);
				int pb = GetBValue(pixelColor);

				int nr = (int)(alpha * r + (1 - alpha) * pr);
				int ng = (int)(alpha * g + (1 - alpha) * pg);
				int nb = (int)(alpha * b + (1 - alpha) * pb);

				dst[index] = RGB(nr, ng, nb);
			}
		}
	}

	putimage(0, 0, &buffer);
}
inline void putimagealpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void filp_image(IMAGE* from, IMAGE* to) 
{
	int w = from->getwidth();
	int h = from->getheight();
	Resize(to, w, h);
	DWORD* from_buffer = GetImageBuffer(from);
	DWORD* to_buffer = GetImageBuffer(to);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx_from = y * w + x;
			int idx_to = y * w + (w - x - 1);
			to_buffer[idx_to] = from_buffer[idx_from];
		}
	}
}

int randint(int l,int r) {
	return rand() % (r - l + 1) + l;
}