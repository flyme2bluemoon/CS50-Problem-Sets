#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main (void) {
	int letter_count = 0;
	int word_count = 1;
	int sentence_count = 0;
	char array[1000];
	bool flag = true;
	
	
	printf("Text : ");
	for (int i = 0; i < 1000 && flag; i++) {
		scanf("%c", &array[i]);
		if (array[i] == 10) {
			array[i] = '\0';
			flag = false;
		}
		if (array[i] >= 'A' && array[i] <= 'z') {
			letter_count++;
		} else if (array[i] == ' '){
			word_count++;
		} else if (array[i] == '.' || array[i] == '!' || array[i] == '?') {
			sentence_count++;
		}
	}
	
	double index = 0.0588 * (100.0 / word_count * letter_count) - 0.296 * (100.0 / word_count * sentence_count) - 15.8;
	
	index = rint(index);
	
	printf("Letter Count\t%d\nWord Count\t%d\nSentence Count\t%d\nIndex\t%.f\n", letter_count, word_count, sentence_count, index);
	
	return 0;
}