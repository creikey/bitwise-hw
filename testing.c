#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

// symbol_type is a type of symbol
typedef enum symbol_type {
	RIGHT_SHIFT,
	LEFT_SHIFT,
	PLUS,
	MINUS,
	DIVIDE,
	MULTIPLY
} symbol_type;

const char * symbol_type_names[] = {
	[RIGHT_SHIFT] = ">>",
	[LEFT_SHIFT] = "<<",
	[PLUS] = "+",
	[MINUS] = "-",
	[DIVIDE] = "/",
	[MULTIPLY] = "*"
};

#define SYMBOL_LOWEST RIGHT_SHIFT
#define SYMBOL_HIGHEST MULTIPLY

const int max_symbol_length = 2;

// token_type is a type of a token
typedef enum token_type {
	NUMBER,
	SYMBOL,
	UNKNOWN,
	END
} token_type;

// token is a token containing a pointer to data
typedef struct token {
	token_type type;
	void * data;
} token;

bool is_digit(char to_check) {
	if(to_check < '9' && to_check > '0') {
		return true;
	} else {
		return false;
	}
}

// gets the number of digits in a number
int num_digits (int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}

// gets a number from a string
int parse_numb(char * str, int cr) {
	int to_return = 0;
	int ishift = 0;
	while(is_digit(str[cr])) {
		to_return += (str[cr] - '0') << 10*ishift;
		ishift++;
		cr++;
	}
	return to_return;
}

token * tokenize(char * to_tokenize) {
	if(to_tokenize == NULL ) {
		return NULL;
	}
	token * to_return = malloc(sizeof *to_return);
	int cur_size = 1;
	int to_ret_cur = 0;
	size_t cur = 0;
	token ctok = {0,NULL}; // the current token
	while(cur < strlen(to_tokenize)) {
		switch(to_tokenize[cur]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ctok.type = NUMBER;
				int * to_data = malloc( sizeof *to_data );
				// *to_data = 0;
				*to_data = parse_numb(to_tokenize, cur);
				ctok.data = to_data;
				cur += num_digits(*to_data);
				break;
			default: ;
				ctok.type = UNKNOWN;
				int cur_look_ahead = 1;
				char * cur_str = malloc(sizeof(*cur_str)*max_symbol_length+2);
				/* TODO resolve what symbol the cursor is on */
				while(1) {
					// TODO delete Wunusedthis line for efficiency
					memset(cur_str, '\0', sizeof(*cur_str)*max_symbol_length+2);
					strncpy(cur_str, to_tokenize+cur, cur_look_ahead);
					for(int i = SYMBOL_LOWEST; i < SYMBOL_HIGHEST; i++) {
						if(strcmp(symbol_type_names[i], cur_str) == 0) {
							ctok.type = SYMBOL;
							symbol_type cur_s_type = (symbol_type)i;
							ctok.data = &cur_s_type;
							break;
						}
					}
					cur_look_ahead++;
					if(cur_look_ahead >= max_symbol_length || ctok.type != UNKNOWN) {
						break;
					}

				}
				if( ctok.type == UNKNOWN ) {
					perror("UNKNOWN TOKEN");
				}
				if(*(symbol_type*)ctok.data >= SYMBOL_LOWEST && *(symbol_type*)ctok.data <= SYMBOL_HIGHEST) {
					cur += strlen(symbol_type_names[*(symbol_type*)ctok.data]);
				}
		}

		/* append the current token */
		if( !(to_ret_cur < cur_size) ) {
			cur_size *= 2;
			to_return = realloc(to_return, cur_size*sizeof(*to_return));
		}
		to_return[to_ret_cur] = ctok;
		to_ret_cur++;
		ctok.type = UNKNOWN;
		ctok.data = NULL;
	}
	if( !(to_ret_cur < cur_size) ) {
		cur_size += 1;
		to_return = realloc(to_return, cur_size*sizeof(*to_return));
	}
	to_return[to_ret_cur+1].type = END;
	to_return[to_ret_cur+1].data = NULL;
	return to_return;
}

// prints tokens
void print_tokens(token * to_print) {
	if(to_print == NULL) {
		printf("WARNING: Null passed to print_tokens");
		return;
	}
	for(size_t i = 0;;i++) {
		if(to_print[i].type == END) {
			break;
		}
		if(to_print[i].type == SYMBOL) {
			if(to_print[i].data == NULL) {
				printf("[%d](INVALID - NO STRING TYPE SPECIFIED) ", (int)i);
			} else if(symbol_type_names[*(int*)to_print[i].data] != NULL) {
				// if the name char * isn't null
				printf("[%d](%s) ", (int)i, symbol_type_names[*(int*)to_print[i].data]);
			} else {
				// if the name was null
				printf("[%d](INVALID - NAME %d NOT FOUND) ", (int)i, *(int*)to_print[i].data);
			}
		} else if(to_print[i].type == NUMBER) {
			if(to_print[i].data == NULL) {
				// if the number data was null
				printf("[%d](INVALID - NO NUMBER SPECIFIED) ", (int)i);
			} else {
				// if the number was specified
				printf("[%d](%d) ", (int)i, *(int*)to_print[i].data);
			}
		}
	}
	return;
}

// gets a line of a file
char * read_line(FILE * tr) {
	char * to_return = malloc(sizeof(char));
	int cur_size = 1;
	int cur = 0;
	for(char read = fgetc(tr); read != '\n' && read != EOF ; read = fgetc(tr)) {
		if( !(cur < cur_size) ) {
			cur_size *= 2;
			to_return = realloc(to_return, cur_size*sizeof(char));
		}
		to_return[cur] = read;
		cur++;
	}
	if( !(cur < cur_size) ) {
			cur_size += 1;
			to_return = realloc(to_return, cur_size*sizeof(char));
	}
	to_return[cur+1] = '\0';
	return to_return;
}


bool file_exist( char * filename) {
	if( access( filename, F_OK ) != -1 ) {
	    return true;
	} else {
	    return false;
	}
}

int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("Please input a filename to parse\n");
		return -1;
	}
	if(!file_exist(argv[1])) {
		printf("File '%s' does not exist\n", argv[1]);
		return -1;
	}
	printf("Parsing file %s...\n", argv[1]);
	FILE * fp = fopen(argv[1], "r");
	int i = 0;
	for(char * read = read_line(fp); read[0] != '\n' && strlen(read) > 0; read = read_line(fp)) {
		printf("Reading line %d of file, '%s':\n", i, read);
		token * toks = tokenize(read);
		print_tokens(toks);
		i++;
	}
	return 0;
}
