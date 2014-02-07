//
// libtl/src/string.c
//

#include <stdlib.h>
#include <string.h>
#include <tl/string.h>

void tl_str_xset(tl_string_t * str, const char * buf, size_t len)
{
	tl_str_release(str);
	str->len = len;
	str->size = len + 1;
	str->str = malloc(len + 1);
	strcpy(str->str, buf);
}

void tl_str_lend(tl_string_t * str, char * buf, size_t len)
{
	tl_str_release(str);
	str->len = len;
	str->size = 0;
	str->str = buf;
}

void tl_str_give(tl_string_t * str, char * buf, size_t len)
{
	tl_str_release(str);
	str->len = len;
	str->size = len;
	str->str = buf;
}

void tl_str_release(tl_string_t * str)
{
	if (str->size > 0)
		free(str->str);
}

int tl_str_cmp(const tl_string_t * a, const tl_string_t * b)
{
	int i;

	if (a->len != b->len)
		return a->len - b->len;

	for (i = 0; i < a->len; i++)
		if (a->str[i] != b->str[i])
			return a->str[i] - b->str[i];

	return 0;
}
