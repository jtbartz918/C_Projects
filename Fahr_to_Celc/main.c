#include <stdio.h>

#define LOWER 0   /*Lower bound*/
#define STEP  20  /*Step*/
#define UPPER 300 /*Upper bound*/

/*Main Function*/
void main(){

int fahr;

for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP){
    printf("fahrenheit: %3d, celcius %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}

}