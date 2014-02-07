//
// include/tl/var.h
//

typedef struct tl_var tl_var_t;

#ifndef _TL_VAR_H_
#define _TL_VAR_H_

#include <tl/config.h>
#include <tl/string.h>
#include <tl/list.h>
#include <tl/function.h>
#include <tl/table.h>

#define TL_NIL       0
#define TL_TYPE      1
#define TL_INT       2
#define TL_FLOAT     3
#define TL_STRING    4
#define TL_LIST      5
#define TL_FUNCTION  6
#define TL_TABLE     7
#define TL_MAX_TYPES 8

#define TL_STATIC 1
#define TL_BLOCK  2
#define TL_SYMBOL 4

struct tl_var {
	unsigned refs;
	unsigned flags;
	tl_type_t type;

	union {
		tl_type_t     vtype;
		tl_int_t      vint;
		tl_float_t    vfloat;
		tl_string_t   vstring;
		tl_list_t     vlist;
		tl_function_t vfunction;
		tl_table_t    vtable;
	} v;
};

extern tl_var_t * tl_nil;
extern tl_var_t * tl_types[TL_MAX_TYPES];

extern char * tl_nil_name;
extern char * tl_type_names[TL_MAX_TYPES];

tl_var_t * tl__create(tl_type_t);
tl_var_t * tl_create_int(tl_int_t);
tl_var_t * tl_create_float(tl_float_t);
tl_var_t * tl_create_function(tl_var_t *, tl_var_t *, tl_var_t *);
tl_var_t * tl_create_cfunction(tl_cfunction_t);
tl_var_t * tl_create_table(void);

tl_var_t * tl_create_string(void);
tl_var_t * tl_create_str_xset(const char *, size_t);
tl_var_t * tl_create_str_lend(char *, size_t);
tl_var_t * tl_create_str_give(char *, size_t);

#define tl_create_str_quote(LITSTR) \
	tl_create_str_lend(LITSTR, sizeof(LITSTR))

#define tl_create_str_set(STR) \
	tl_create_str_xset(STR, strlen(STR))

#define tl_create_str_slend(STR) \
	tl_create_str_lend(STR, strlen(STR))

tl_var_t * tl_assign(tl_var_t *);
tl_var_t * tl_copy_var(tl_var_t *);
tl_var_t * tl_cast_var(tl_var_t *, tl_type_t);

void tl_release(tl_var_t *);

#endif
