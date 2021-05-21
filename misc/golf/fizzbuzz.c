
// Try 1: 160 chars
// int main(){for(int i=0;i++<100;){if(!(i%3)&&!(i%5))printf("FizzBuzz\n");else if(!(i%3))printf("Fizz\n");else if(!(i%5))printf("Buzz\n");else printf("%d\n",i);}}

// Try 2: 155 chars
// int main(){for(int i=0;i++<100;){if(i%3==0){if(i%5==0)printf("FizzBuzz\n");else printf("Fizz\n");} else if(i%5==0)printf("Buzz\n");else printf("%d\n",i);}}

// Try 3: 155 chars
// #define P(x) printf(#x"\n")
// int main(){for(int i=0;i++<100;){if(i%3==0){if(i%5==0)P(FizzBuzz);else P(Fizz);}else if(i%5==0)P(Buzz);else printf("%d\n",i);}}

// Try 4: 149 chars
// #define P(x) printf(#x"\n")
// int main(){for(int i=0;i++<100;){if(i%3==0){(i%5==0)?P(FizzBuzz):P(Fizz);}else if(i%5==0)P(Buzz);else printf("%d\n",i);}}

// Try 5: 122 chars
// #define P(x) printf(#x"\n")
// int main(){for(int i=0;i++<100;)i%3?(i%5?printf("%d\n",i):P(Buzz)):(i%5?P(Fizz):P(FizzBuzz));}

// Try 6: 121 chars
// int main(){for(int i=0;i++<100;)i%3?(i%5?printf("%d\n",i):printf("Buzz\n")):(i%5?printf("Fizz\n"):printf("FizzBuzz\n"));}

// Try 7: 118 chars
// int main(i){for(i--;i++<100;i%3?(i%5?printf("%d\n",i):printf("Buzz\n")):(i%5?printf("Fizz\n"):printf("FizzBuzz\n")));}

// Try 8: 112 chars
// #define P printf(
// int main(i){for(i--;i++<100;i%3?(i%5?P"%d\n",i):P"Buzz\n")):(i%5?P"Fizz\n"):P"FizzBuzz\n")));}

// Try 9: 100 chars
#define P printf(
main(i){for(i--;i++<100;i%3&&i%5?P"%d",i):i%3?0:P"Fizz"),i%5?0:P"Buzz"),P"\n"));}
