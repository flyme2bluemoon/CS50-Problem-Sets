#include <stdio.h>

int main (void) {
	char plain[1000];
	int key;
	
	printf("plain text : ");
	fgets(plain, sizeof(plain), stdin);
	
	printf("key : ");
	scanf("%d", &key);
	key %= 26;
	
	for (int i = 0; plain[i] != '\0'; i++) {
		if (plain[i] >= 'A' && plain[i] <= 'Z') {
			plain[i] += key;
			if (plain[i] > 90) {
				plain[i] %= 90;
				plain[i] += 64;
			}
		} else if (plain[i] >= 'a' && plain[i] <= 'z') {
			plain[i] += key;
			if (plain[i] > 122) {
				plain[i] %= 122;
				plain[i] += 96;
			}
		}
		printf("%c", plain[i]);
	}
	
	printf("\n");
	
	return 0;
}