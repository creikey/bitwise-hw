#ifndef H_STBUFF
#define H_STBUFF

typedef struct strbuff {
  int len;
  int max_len;
  char * str;
} strbuff;

// creates a new stretchy string buffer
strbuff * n_strbuff();

// appends a new character
void strbuff_append(strbuff * buff, char to_append);

// gets a normal string from a stretchy buff
char * get_string(strbuff * to_read);

// delete a stretchy buffer
void del_strbuff(strbuff * to_del);

void test_strbuff();
void test_stbuff();

#endif // H_STBUFF
