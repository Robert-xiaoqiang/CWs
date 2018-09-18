#include <vector>
using namespace std;

typedef unsigned char u8;

vector <u8> processImage (const vector <u8> &imageData, int height, int width, vector <vector <float>> weights)
{
	int row, col;
	vector<u8> ret(imageData.size());

	for(row = 0; row < height; row++)
		for(col = 0; col < width; col++) 
			for(int i = 0; i < 3; i++)
			ret[(row + i) * width + col + i] = imageData[(row + i) * width + col + i] * weights[row][col];
	return ret;
}


#include <vector>
#include <cmath>
using namespace std;

typedef unsigned char u8;

vector <u8> processImage (const vector <u8> &imageData, int height, int width, vector <vector <float>> weights) {
  vector <u8> result(height*width*3);
  float R, im;
  int linearCoorRes = 0, linearCoorKer = 0, yk, xk, Y, X, Yi, Xi;
  
  //Each pixel loop
  for (int y = 0; y<height; y++){
    for (int x = 0; x<width; x++){
      for (int RGB = 0; RGB<=2; RGB++){
        linearCoorRes = y*width*3 + x*3 + RGB;
        
        //Kernel loop - Convolution
        R = 0;
        for (Y = y - floor(weights.size()/2), yk = 0; Y<=y + floor(weights.size()/2); Y++, yk++){
          for (X = x - floor(weights.size()/2), xk = 0; X<=x + floor(weights.size()/2); X++, xk++){
            Xi = X, Yi = Y;
            
            if (Y<0) Yi=0;
            if (X<0) Xi=0;
            if (Y>=height) Yi = height-1;
            if (X>=width) Xi = width-1;
            
            linearCoorKer = Yi*width*3 + Xi*3 + RGB;
            im = (float) imageData[linearCoorKer];
            R += (im*weights[yk][xk]);
          }
        }
        if (R>255) R=255;
        if (R<0) R=0;
        result[linearCoorRes] = (u8) floor((R));
      }
    }
  }
  return result;
}