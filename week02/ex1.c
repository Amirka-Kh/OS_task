#include <limits.h>
#include <float.h>
int main() 
{ 
    int int_value = INT_MAX;
    float float_value = FLT_MAX;
    double double_value = DBL_MAX;
    printf("Max values: int = %d, float = %f, double = %f\n", int_value, float_value, double_value); 
    printf("size of values: int = %d, float = %d, double = %d", sizeof(int_value), sizeof(float_value), sizeof(double_value));
     
    return 0; 
} 
