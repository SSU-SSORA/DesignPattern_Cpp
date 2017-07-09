//리눅스 함수임 
//따라서 윈도우에서는 작동 안되여 ㅜ.ㅜ+
#include <stdio.h>
#include <string.h>
int main() {
	char str_apple[] = "apple";
	char str_apple2[] = "Apple";
	char str_apple3[] = " Apple";
	char str_applell[] = "Applell";
	
	printf("%s with %s = %d\n", str_apple, str_apple, strncasecmp(str_apple, str_apple, 3));
	printf("%s with %s = %d\n", str_apple, str_apple2, strncasecmp(str_apple, str_apple2, 3));
	printf("%s with %s = %d\n", str_apple, str_apple3, strncasecmp(str_apple, str_apple3, 3));
	printf("%s with %s = %d\n", str_apple, str_applell, strncasecmp(str_apple, str_applell, 3));

}