#define _SCL_SECURE_NO_WARNINGS
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <iostream>
using namespace std;

struct Image
{
 unsigned *pixels;
 unsigned width, height;
 Image(initializer_list<unsigned> ilu, unsigned width, unsigned height):
 	width(width),
 	height(height)
 {
 	pixels = new unsigned[ilu.size()];
 	copy(ilu.begin(), ilu.end(), pixels);
 }

 vector<unsigned> central_pixels(unsigned colour) const;
 // other functions ...
};

vector<unsigned> Image::central_pixels(unsigned colour) const
{
	vector<unsigned> ret;
	unsigned maxDepth = 0;
	unsigned n = width * height;
	vector<unsigned> depths(n, -1); // default -1
	for(unsigned i = 0u; i < n; i++) {
		if(pixels[i] == colour) {
			unsigned int up = i - width;
			unsigned int down = i + width;
			unsigned int left = i - 1;
			unsigned int right = i + 1;
			if(up < 0 || pixels[up] != colour ||
				down >= n || pixels[down] != colour ||
				left < 0 || left / width < i / width || pixels[left] != colour ||
				right >= n || right / width > i / width || pixels[right] != colour) {
				depths[i] = 1;
				if(depths[i] > maxDepth) maxDepth = depths[i];
			}
			/*
			else {
			// except colour!
			depths[i] = min({ depths[up], depths[down], depths[left], depths[right]}) + 1;
			}
			*/
		}
		
	}

	for(unsigned i = 0u; i < n; i++) {
		unsigned int up = i - width;
		unsigned int down = i + width;
		unsigned int left = i - 1;
		unsigned int right = i + 1;
		if(pixels[i] == colour && 
		   up >= 0 && pixels[up] == colour &&
		   down < n && pixels[down] == colour &&
		   left >= 0 && left / width == i / width && pixels[left] == colour &&
		   right < n && right / width == i / width && pixels[right] == colour) {
			unsigned tempMin = -1; // max
			if(depths[up] < tempMin) tempMin = depths[up];
			if(depths[down] < tempMin) tempMin = depths[down];
			if(depths[left] < tempMin) tempMin = depths[left];
			if(depths[right] < tempMin) tempMin = depths[right];

			depths[i] = tempMin + 1;

			if(depths[i] > maxDepth) maxDepth = depths[i];
		}
	}

	for(unsigned int i = 0u; i < n; i++) {
		if(pixels[i] == colour && depths[i] == maxDepth) ret.push_back(i);
	}

	return ret;
}

int main()
{
	Image image({1,1,4,4,4,4,2,2,2,2,
                 1,1,1,1,2,2,2,2,2,2,
                 1,1,1,1,2,2,2,2,2,2,
                 1,1,1,1,1,3,2,2,2,2,
                 1,1,1,1,1,3,3,3,2,2,
                 1,1,1,1,1,1,3,3,3,3}, 10, 6 );
	auto v = image.central_pixels(1);
	for_each(v.begin(), v.end(), [](unsigned p){ cout << p << ' '; });
	return 0;
               
}