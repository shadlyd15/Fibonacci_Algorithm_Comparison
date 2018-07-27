#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long fibonacci(unsigned long n){
	if(0 == n) return 0;
	if(1 == n) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

unsigned int better_fibonacci(unsigned long n){
	if( n == 0 ) return 0;
	unsigned long * ptr_f = (unsigned long*)malloc(n * sizeof(unsigned long));
	if(ptr_f){
		ptr_f[0] = 0, ptr_f[1] = 1;
		for(unsigned long i = 2; i < n + 1; i++){
			ptr_f[i] = ptr_f[i - 1] + ptr_f[i - 2];
		}
		return ptr_f[n];	
	}
	return 0;
}

unsigned int better_space_fibonacci(unsigned long n){
	if( n == 0 ) return 0;
	unsigned long a = 0, b = 1, c = 0;
	for(unsigned long i = 2; i < n + 1; i++){
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

unsigned int power(unsigned int x, unsigned int y){
	if(0 == y) return 1;
	if(y & 1){
		return x*power(x, y - 1);
	} else{
		int a = power(x, y/2);
		return a*a;
	}
}

uint8_t matrix_multiplication(unsigned int matrix_1[2][2], unsigned int matrix_2[2][2]){
	if(matrix_1 && matrix_2){
		unsigned int w = matrix_1[0][0] * matrix_2[0][0] + matrix_1[0][1] * matrix_2[1][0];
		unsigned int x = matrix_1[0][0] * matrix_2[0][1] + matrix_1[0][1] * matrix_2[1][1];
		unsigned int y = matrix_1[1][0] * matrix_2[0][0] + matrix_1[1][1] * matrix_2[1][0];
		unsigned int z = matrix_1[1][0] * matrix_2[0][1] + matrix_1[1][1] * matrix_2[1][1];
		matrix_1[0][0] = w;
		matrix_1[0][1] = x;
		matrix_1[1][0] = y;
		matrix_1[1][1] = z;
		return 1;
	}
	return 0;
}

uint8_t matrix_power(unsigned int matrix[2][2], unsigned int n){
	unsigned int base_matrix[2][2];
	base_matrix[0][0] = matrix[0][0];
	base_matrix[1][0] = matrix[1][0];
	base_matrix[0][1] = matrix[0][1];
	base_matrix[1][1] = matrix[1][1];
	for(unsigned int i = 2; i < n + 1; i++){
		matrix_multiplication(matrix, base_matrix);
	}
}

uint8_t optimized_matrix_power(unsigned int matrix[2][2], unsigned int n){
	if(0 == n || 1 == n) return 0;
	unsigned int base_matrix[2][2];
	base_matrix[0][0] = matrix[0][0];
	base_matrix[1][0] = matrix[1][0];
	base_matrix[0][1] = matrix[0][1];
	base_matrix[1][1] = matrix[1][1];
	optimized_matrix_power(matrix, n/2);
	matrix_multiplication(matrix, matrix);
	if(n & 1){
		matrix_multiplication(matrix, base_matrix);
	}
}

unsigned int matrix_fibonacci(unsigned int n){
	if(0 == n) return 0;
	unsigned int matrix[2][2];
	unsigned int base_matrix[2][2] = {{1,1},{1,0}};
	matrix_power(base_matrix, n - 1);
	return base_matrix[0][0];
}

unsigned int optimized_matrix_fibonacci(unsigned int n){
	if(0 == n) return 0;
	unsigned int matrix[2][2];
	unsigned int base_matrix[2][2] = {{1,1},{1,0}};
	optimized_matrix_power(base_matrix, n - 1);
	return base_matrix[0][0];
}

int main(int argc, char const *argv[]){
	unsigned long n = 100000;
	clock_t start = 0;

	start = clock();
	printf("%luth better_fibonacci : %lu\n", n, better_fibonacci(n));
	printf("CPU Clock Time Taken : %d\n", clock() - start);

	start = clock();
	printf("%luth better_space_fibonacci : %lu\n", n, better_space_fibonacci(n));
	printf("CPU Clock Time Taken : %d\n", clock() - start);


	start = clock();
	printf("%luth matrix_fibonacci : %lu\n", n, matrix_fibonacci(n));
	printf("CPU Clock Time Taken : %d\n", clock() - start);

	start = clock();
	printf("%luth optimized_matrix_fibonacci : %lu\n", n, optimized_matrix_fibonacci(n));
	printf("CPU Clock Time Taken : %d\n", clock() - start);

	printf("Power : %d\n", power(3, 3));

	// start = clock();
	// printf("%luth fibonacci : %lu\n", n, fibonacci(n));
	// printf("CPU Clock Time Taken : %d\n", clock() - start);
	return 0;
}