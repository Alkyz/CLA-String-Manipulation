#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* strstr_fully_matched(char* haystack, char* needle);
void print_results(char* pattern, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int ignore_case, int no_of_results);

extern char* lineptr[];
extern int results[];
