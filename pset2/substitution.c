#include <stdio.h>
#include <stdbool.h>

int main (void) {
	char plain[1000];
	char key[26];
	bool upper = false;
	
	printf("plain text : ");
	fgets(plain, sizeof(plain), stdin);
	
	printf("key : ");
	for (int i = 0; i < 26; i++) {
		key[i] = getchar();
		if (key[i] >= 'A' && key[i] <= 'Z') {
			key[i] += 32;
		} else if (key[i] <= 64 || (key[i] >= 91 && key[i] <= 96) || key[i] >= 123) {
			i--;
		}
	}
	
	for (int i = 0; plain[i] != '\0'; i++) {
		if (plain[i] >= 'a' && plain[i] <= 'z') {
			printf("%c", key[plain[i] - 97]);
		} else if (plain[i] >= 'A' && plain[i] <= 'Z') {
			printf("%c", (key[plain[i] - 65]) - 32);
		} else {
			printf("%c", plain[i]);
		}
	}
	
	return 0;
}