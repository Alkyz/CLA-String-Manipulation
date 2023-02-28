#include "find.h"

#define MAX_LINES 1000
#define MAX_LEN 1000

char* lineptr[MAX_LINES];
int results[MAX_LINES];

char* str_tolower(char* input){
    char* rv = strdup(input);
    for(int i = 0; i < strlen(rv);i++)
        rv[i] = tolower(rv[i]);
    return rv;
}

char* strstr_fully_matched(char* haystack, char* needle) {
	char* rv;
	char padded_needle[strlen(needle) + 3];
	padded_needle[0] = ' ';
	strcpy(padded_needle + 1, needle);
	padded_needle[strlen(needle) + 1] = ' ';
	padded_needle[strlen(needle) + 2] = '\0';
	
	if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1))
		return haystack;//needle is at the beginning
	
	if ((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the middle.
	
	padded_needle[strlen(needle) + 1] = '\0';
	
	if ((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the end.
}

int getline2(char s[], int lim) {
	int c, i;
	
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	
	s[i] = '\0';
	
	return i;
}

int readlines(char** lineptr, int maxlines) {
	int len, nlines;
	char* p, line[MAX_LEN];
	nlines = 0;
	
	while ((len = getline2(line, MAX_LEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

int main(int argc, char** argv) {
    // FLAGS
    int except = 0;//0 or 1
	int sorted = 0;//0 or 1
	int reversed = 0;//0 or 1
	int partial = 0;//0 or 1
	int numbered = 0;//0 or 1
	int first_occurrence = 0;//0 or 1
	int matched = 0;//0 or 1
	int ignore_case = 0;//0 or 1
	char* pattern = "";
	//....
	//handle command line arguments...
	//similar to #41 of Chapter 5 partII.pptx
	int current_char;
	
	if (argc == 3) {
		while (--argc > 1 && (*++argv)[0] == '-') {
			while (current_char = *++argv[0])
				switch (current_char) {
					case 's':
						sorted = 1;
						break;
					case 'r':
						reversed = 1;
						break;
					case 'x':
						except = 1;
						break;
					case 'm':
						matched = 1;
						break;
					case 'n':
						numbered = 1;
						break;
					case 'f':
						first_occurrence = 1;
						break;
					case 'p':
						partial = 1;
						break;
					case 'c':
						ignore_case = 1;
						break;
					default:
						printf("find: Illegal option %c\n", current_char);
						argc = 0;
						return 0;
						break;
				}
		}
	} else if (argc == 2) {
        
    } else {
		printf("Invalid # of command line arguments.\nRun program with ./find -<flags> <pattern>\n");
		return 0;
	}

	if (++argv) {
		pattern = argv[0];
	} else {
		printf("Pattern missing.");
		return 0;
	}

	if (sorted && reversed) {
		printf("find: Illegal usage. -s and -r can't be used together\n");
		return 0;
	}

	if (first_occurrence && except) {
		printf("find: Illegal usage. -f and -x can't be used together\n");
		return 0;
	}

    if (partial && except) {
        printf("find: Illegal usage. -p and -x can't be used together\n");
        return 0;
    }

    if (ignore_case) {
        pattern = str_tolower(pattern);
    }
	
	int nlines = readlines(lineptr, MAX_LINES);//similar, but not the same as the slide #23 of Chapter 5 partII.pptx
	int no_of_results = 0;
	
	//for(int i = 0; i < nlines; i++)i
	//	printf("\n%s\n", lineptr[i]);
	
	for(int i = 0; i < nlines; i++) {
		if (matched) {
            if (ignore_case) {
              if((strstr_fully_matched(str_tolower(lineptr[i]), pattern) != NULL) != except)
				    results[no_of_results++] = i;
            } else {
    			if((strstr_fully_matched(lineptr[i], pattern) != NULL) != except)
    			    results[no_of_results++] = i;
            }
		} else {
            if (ignore_case) {
              if ((strstr(str_tolower(lineptr[i]), pattern) != NULL) != except)
				results[no_of_results++] = i;  
            } else if ((strstr(lineptr[i], pattern) != NULL) != except)
				results[no_of_results++] = i;
		}
	}
	
	print_results(pattern, matched, first_occurrence, numbered, sorted, partial, reversed, ignore_case, no_of_results);
    return 0;
}
