//
// libtl/src/eval.c
//

#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <tl/tl.h>

#define VAR  1
#define CHAR 2

typedef struct {
	int type;
	union {
		tl_var_t * v;
		char c;
	} u;
} token;

static int isspec(char c)
{
	const char specs[] = "`~!@$%^&*-=+[]{}\\|:,./<>?";
	unsigned i;

	for (i = 0; i < sizeof(specs) - 1; i++) {
		if (c == specs[i]) return 1;
	}

	return 0;
}

static int is_digit(char c, int radix)
{
	switch (radix) {
	case 10: return c >= '0' && c <= '9';
	case 010: return c >= '0' && c <= '7';
	case 0x10: return (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
	}
	assert(0);
	return 0;
}

static tl_var_t * get_number(char ** pbuf)
{
	int radix;
	unsigned long tot = 0;
	char * b = *pbuf;

	if (*b == '0') {
		b++;

		if (*b == 'x' || *b == 'X') {
			++b;
			radix = 0x10;
		} else {
			radix = 010;
		}
	} else {
		radix = 10;
	}

	while (is_digit(*b, radix)) {
		tot *= radix;
		tot += *b;

		if (*b >= 'a') tot -= 'a' + 10;
		else if (*b >= 'A') tot -= 'A' + 10;
		else tot -= '0';

		b++;
	}

	*pbuf = b;
	return tl_create_int(tot);
}

static token next_token(char ** pbuf)
{
#define REALLOC_SIZE 32

	token t;
	int i = 0;
	char * str = NULL;
	char * buf = *pbuf;

	while (isspace(*buf) || *buf == '#') {
		if (*buf == '#') while (*buf != '\n') buf++;
		buf++;
	}
	t.type = VAR;

	if (isalpha(*buf) || *buf == '_') {
		for (i = 1; isalpha(buf[i]) || isdigit(buf[i]) || buf[i] == '_'; i++);
		t.u.v = tl_create_str_lend(buf, i);
		t.u.v->flags |= TL_SYMBOL;
	}
	else if (isdigit(*buf)) {
		t.u.v = get_number(&buf);
	}
	else if (isspec(*buf)) {
		for (i = 1; isspec(buf[i]); i++);
		t.u.v = tl_create_str_lend(buf, i);
		t.u.v->flags |= TL_SYMBOL;
	}
	else if (*buf == '\'') {
		buf++;
		for (i = 0; buf[i] != '\'' && buf[i] != 0; i++);
		t.u.v = tl_create_str_lend(buf, i);
		buf++;
	}
	else if (*buf == '"') {
		buf++;
		for (i = 0; *buf != '"' && *buf != 0; i++) {
			if (i % REALLOC_SIZE == 0)
				str = realloc(str, i + REALLOC_SIZE + 1);

			if (*buf == '\\') {
				switch (*++buf) {
				case 't': str[i] = '\t'; break;
				case 'n': str[i] = '\n'; break;
				case 'r': str[i] = '\r'; break;
				case 'v': str[i] = '\v'; break;
				default: str[i] = *buf;
				}
			} else {
				str[i] = *buf;
			}
		}

		str[i] = 0;
		t.u.v = tl_create_str_lend(buf + 1, i);
	} else {
		t.type = CHAR;
		t.u.c = *buf;
		buf++;
	}

	*pbuf = buf + i;
	return t;

#undef REALLOC_SIZE
}

static tl_var_t * parse_next(char ** pbuf)
{
	tl_var_t * after, * ls;
	token t = next_token(pbuf);

	if (t.type == CHAR) {
		switch (t.u.c) {
		case ')':
		case 0:
			return tl_nil;
		case ';':
			after = parse_next(pbuf);
			if (after != tl_nil) {
				if (~after->flags & TL_BLOCK)
					after = tl_cons(after, tl_nil);
				else
					after->flags &= ~TL_BLOCK;

				after = tl_cons(tl_nil, after);
				after->flags |= TL_BLOCK;
			}
			return after;
		case '(':
			t.u.v = parse_next(pbuf);
			break;
		default:
			// TODO
			assert(0);
		}
	}

	after = parse_next(pbuf);
	assert(after->type == TL_LIST || after == tl_nil);

	if (after->flags & TL_BLOCK) {
		assert(tl_car(after)->type == TL_LIST || tl_car(after) == tl_nil);
		after->v.vlist.car = tl_cons(t.u.v, tl_car(after));
		ls = after;
	} else {
		ls = tl_cons(t.u.v, after);
	}

	return ls;
}

tl_var_t * tl_parse(char * buf)
{
	return parse_next(&buf);
}
