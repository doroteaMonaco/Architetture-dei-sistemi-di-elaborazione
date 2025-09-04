#include <stdlib.h>
#include <stdint.h>

extern int ASM_funct(int, int, int, int, int, int, int*);
extern int check_square(int, int, int);
extern float my_division(float*, float*);

extern int Matrix_Coordinates[];
extern uint8_t ROWS[];
extern uint8_t COLUMNS[];

int main(void){

	volatile int i, x, y, area = 0;
	volatile int r = 5;
	float raggio, area_f;
	volatile float result;
	volatile int R = ROWS[0], C = COLUMNS[0];
	
	raggio = (float)(r*r);
	
	for(i=0; i<(R)*(C); i+=2){
		x = Matrix_Coordinates[i];
		y = Matrix_Coordinates[i+1];
		
		area += check_square(x, y, r);
	}
	
	area_f = (float) area;
	result = my_division(&area_f, &raggio);
	while(1);
}
