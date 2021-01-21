#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "toojpeg.h"

unsigned char pixels[160*120*3];

void writeByte(unsigned char oneByte)
{
	int ret = write(1, &oneByte, sizeof(oneByte));
	if(ret != sizeof(oneByte)) {
		fprintf(stderr, "write failed!\n");
		exit(0);
	}
}

int main(int argc, char **argv)
{
	if(argc < 3) {
		fprintf(stderr, "not enough arguments!\n");
		return 1;
	}
	int w = atoi(argv[1]), h = atoi(argv[2]), d = atoi(argv[3]);
	int size = w*h*d;
	if(size <= 0 || size >= 7680*4320*3) {
		fprintf(stderr, "size too large!\n");
		return 1;
	}
	unsigned char *pixels = (unsigned char*)malloc(size);
	int ret = read(0, pixels, size);
	if(ret != size) {
		fprintf(stderr, "read failed!\n");
		return 1;
	}
#if 0
	if(d == 2) {
		int i;
		unsigned char *pixels3 = (unsigned char*)malloc(w*h*3);
		for(i = 0; i < w * h; i++) {
			pixels3[3 * i + 0] = getComp(&pixels[2 * i], TooJpeg::RGB565, TooJpeg::_R);
			pixels3[3 * i + 1] = getComp(&pixels[2 * i], TooJpeg::RGB565, TooJpeg::_G);
			pixels3[3 * i + 2] = getComp(&pixels[2 * i], TooJpeg::RGB565, TooJpeg::_B);
		}
		free(pixels);
		pixels = pixels3;
		d = 3;
	}
#endif
	bool ok = TooJpeg::writeJpeg(writeByte, pixels, w, h, d == 2 ? TooJpeg::RGB565 : TooJpeg::RGB888);
	if(!ok) {
		fprintf(stderr, "writeJpeg failed!\n");
		return 1;
	}
	return 0;
}

