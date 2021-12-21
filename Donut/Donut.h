#pragma once
#include <sstream>
#include <cmath>

class DonutRender {
private:
	std::string zRender;

	float* zBuffer;
	char* output;
public:
	DonutRender() {
		zRender = ".,-~:;=!*#$@";
		zBuffer = new float[1760];
		output = new char[1760];
	}

	~DonutRender() {
		delete[] zBuffer;
		delete[] output;
	}

	std::string renderDonut(float A, float B) {
		memset(output, ' ', 1760);
		memset(zBuffer, 0, 7040);
		for (float j = 0; j < 6.28; j += 0.07) {
			for (float i = 0; i < 6.28; i += 0.02) {
				float c = sin(i);
				float d = cos(j);
				float e = sin(A);
				float f = sin(j);
				float g = cos(A);
				float h = d + 2;
				float depth = 1 / (c * h * e + f * g + 5);

				float l = cos(i);
				float m = cos(B);
				float n = sin(B);
				float t = c * h * g - f * e;

				int x = 40 + 30 * depth * (l * h * m - t * n);
				int y = 12 + 15 * depth * (l * h * n + t * m);
				int o = x + 80 * y;
				int index = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
				if (y > 0 && y < 22 && x > 0 && x < 80 && depth > zBuffer[o]) {
					zBuffer[o] = depth;
					output[o] = zRender[index > 0 ? index : 0];
				}
			}
		}

		std::stringstream ss;
		for (int k = 0; k < 1760; ++k) {
			if (k % 80) {
				ss << output[k];
			}
			else {
				ss << std::endl;
			}
		}
		return ss.str();
	}
};