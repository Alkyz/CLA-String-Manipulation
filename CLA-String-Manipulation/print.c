#include "find.h"

// void partial_print(char* line, char* pattern) {
//     if (strlen(line) <= strlen(pattern) + 15) {
//         int x;
//         for (x = 0; x < strlen(line); x++) {
//             printf("%c", line[x]);
//         }
//     } else {
//         int i, j, k, l;
//         j = 0;
//         k = 0;
//         l = strlen(line);
//         for (i = 0; i < l; i++) {
//             if (*(line + i) == *(pattern + j)) {
//                  ++j;
//             } else {
//                 j = 0;
//             }
//             if (j == strlen(pattern)) {
//                 if ((i - j) <= 10 && i <= 10) {
//                     while (k < 10) {
//                         printf("%c", line[k]);
//                         ++k;
//                     }
//                     printf("...");
//                     l -= 6;
//                     while (l < strlen(line)) {
//                         printf("%c", line[l]);
//                         ++l;
//                     }
//                     break;
//                 } else if ((i - j) <= 10 && i >= 10) {
//                     while (k < i) {
//                         printf("%c", line[k]);
//                         ++k;
//                     }
//                     printf("...");
//                     l -= 6;
//                     while (l < strlen(line)) {
//                         printf("%c", line[l]);
//                         ++l;
//                     }
//                     printf(" \n");
//                     break;
//                 } else if ((i - j) > l - 6)  {
//                     while (k < 10) {
//                         printf("%c", line[k]);
//                         ++k;
//                     }
//                     printf("...");
//                     l -= 6;
//                     while (l < strlen(line)) {
//                         printf("%c", line[l]);
//                         ++l;
//                     }
//                     printf(" \n");
//                     break;
//                 } else if ((i - j) < (l - 6) && i > (l - 6)) {
//                     while (k < 10) {
//                         printf("%c", line[k]);
//                         ++k;
//                     }
//                     printf("...");
//                     k = i - j;
//                     while (k < l) {
//                         printf("%c", line[i - j]);
//                         ++k;
//                     }
//                     printf(" \n");
//                     break;
//                 } else {
//                     while (k < 10) {
//                         printf("%c", line[k]);
//                         ++k;
//                     }
//                     printf("...");
//                     printf("%s", pattern);
//                     printf("...");
//                     l -= 6;
//                     while (l < strlen(line)) {
//                         printf("%c", line[l]);
//                         ++l;
//                     }
//                     printf(" \n");
//                     break;
//                 }
//             }
//         }
//     }
// }

void reverse(char* v[], int no_of_results) {
	char* temp;
	int i, j;

	for (i = 0, j = no_of_results - 1; i < j; i++, j--) {
		temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}
}

void swap(char* v[], int i, int j) {
	char* temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void quicksort(char* v[], int left, int right) {
	int i, last;
	void swap(char* v[], int i, int j);

	if (left >= right)
		return;
	
	swap(v, left, (left + right)/2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	quicksort(v, left, last - 1);
	quicksort(v, last + 1, right);
}

void print_results(char* pattern, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int ignore_case, int no_of_results) {
	char** sentences = (char**) malloc(no_of_results * sizeof(char*));
	
	for (int i = 0; i < no_of_results; i++) {
		sentences[i] = strdup(lineptr[results[i]]);
	}
	
	if (sorted) {
		quicksort(sentences, 0, no_of_results - 1);
	}else if (reversed) {
		reverse(sentences, no_of_results);
	}

	printf("\n\n");
	
	for (int i = 0; i < no_of_results; i++) {
		if (numbered)
			printf("%d. ", results[i] + 1); 
		if (first_occurrence)
			if (matched)
				printf("@%d: ", strstr_fully_matched(sentences[i], pattern) - sentences[i]);
			else
				printf("@%d: ", strstr(sentences[i], pattern) - sentences[i]);

        if (partial) {
            int a = 0;
            int b = strlen(sentences[i]) - 6;
            // partial_print(sentences[i], pattern);
            while (a <= 10) {
                printf("%c", sentences[i][a]);
                ++a;
            }
            printf("...");
            printf(pattern);
            printf("...");
            while (b <= strlen(sentences[i])) {
                printf("%c", sentences[i][b]);
                ++b;
            }
          }
		
		printf("%s\n", sentences[i]);
		
	}
}
