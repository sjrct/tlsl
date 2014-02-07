//
// include/tl/string.h
//

typedef struct tl_string tl_string_t;

#ifndef _TL_STRING_H_
#define _TL_STRING_H_

#include <stddef.h>

struct tl_string {
	size_t len, size;
	char * str;
};

void tl_str_xset(tl_string_t *, const char *, size_t);
void tl_str_lend(tl_string_t *, char *, size_t);
void tl_str_give(tl_string_t *, char *, size_t);
void tl_str_release(tl_string_t *);

int tl_str_cmp(const tl_string_t *, const tl_string_t *);
void tl_str_cpy(tl_string_t *, const tl_string_t *);
void tl_str_cat(tl_string_t *, const tl_string_t *);

#define tl_str_quote(TLSTR, LITSTR) \
	tl_str_lend(TLSTR, LITSTR, sizeof(LITSTR))

#define tl_str_set(TLSTR, STR) \
	tl_str_xset(TLSTR, STR, strlen(STR))

#define tl_str_slend(TLSTR, STR) \
	tl_str_lend(TLSTR, STR, strlen(STR));

#endif
