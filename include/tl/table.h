//
// include/tl/table.h
//

typedef struct tl_field tl_field_t;
typedef struct tl_table tl_table_t;

#ifndef _TL_TABLE_H_
#define _TL_TABLE_H_

typedef struct tl_var tl_var_t;

struct tl_field {
	tl_var_t * key;
	tl_var_t * value;
	tl_field_t * left;
	tl_field_t * right;
};

struct tl_table {
	tl_field_t * root;
};

void tl_store(tl_table_t *, tl_var_t *, tl_var_t *);
tl_var_t * tl_select(tl_table_t *, tl_var_t *);

#endif
