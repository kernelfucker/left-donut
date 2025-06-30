/* See LICENSE file for license details */
/* left-donut - a donut that spins immediately */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void ld(){
	float R1 = 0, R2 = 0;
	float a, b ,c[1920];
	char scrn[1920];
	printf("\x1b[2J");
	while(1){
		memset(scrn, ' ', 1920);
		memset(c, 0, 7680);
		for(b = 0; b < 6.28; b += 0.07){
			for(a = 0; a < 6.28; a += 0.02){
				float sa = sin(a);
				float cb = cos(b);
				float sR1 = sin(R1);
				float sb = sin(b);
				float cR1 = cos(R1);
				float h = cb + 2;
				float H = 1 / (sa * h * sR1 + sb * cR1 + 5);
				float ca = cos(a);
				float cR2 = cos(R2);
				float sR2 = sin(R2);
				float r = sa * h * cR1 - sb * sR1;
				int x = 40 + 30 * H * (ca * h * cR2 - r * sR2);
				int y = 12 + 15 * H * (ca * h * sR2 + r * cR2);
				int o = x + 80 * y;
				int X = 8 * ((sb * sR1 - sa * cb * cR1) * cR2 - sa * cb * sR1 - sb * cR1 - ca * cb * sR2);
				if(y > 0 && y < 24 && x > 0 && x < 80 && H > c[o]){
					c[o] = H;
					scrn[o] = ".,-~:;=!*#$@"[X > 0 ? X : 0];
				}
			}
		}

		printf("\x1b[H");
		for(int j = 0; j < 1920; j++){
			putchar(j % 80 ? scrn[j] : '\n');
		}

		R1 += 0.04;
		R2 += 0.02;

		usleep(40000);
	}
}

int main(){
	ld();
	return 0;
}
