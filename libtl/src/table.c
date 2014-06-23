//
// libtl/src/table.c
//

#include <assert.h>
#include <stdio.h>

#include <stdlib.h>
#include <tl/var.h>

static long compare(const tl_var_t * a, const tl_var_t * b)
{
	if (a->type != b->type)
		return a->type - b->type;

	switch (a->type) {
	case TL_TYPE:
		return a->v.vtype - b->v.vtype;
	case TL_INT:
		return a->v.vint - b->v.vint;
	case TL_FLOAT:
		if (a->v.vfloat > b->v.vfloat) return 1;
		if (a->v.vfloat < b->v.vfloat) return -1;
		return 0;
	case TL_STRING:
		return tl_str_cmp(&a->v.vstring, &b->v.vstring);
	}

	return (ptrdiff_t)a - (ptrdiff_t)b;
}

static tl_field_t ** find(tl_table_t * tbl, const tl_var_t * k)
{
	int cmp;
	tl_field_t ** p = &tbl->root;

	while (*p != NULL) {
		cmp = compare(k, (*p)->key);

		if (cmp < 0)
			p = &(*p)->left;
		else if (cmp > 0)
			p = &(*p)->right;
		else
			break;
	}

	return p;
}

void tl_store(tl_table_t * tbl, tl_var_t * k, tl_var_t * v)
{
	tl_field_t ** p = find(tbl, k);

	if (*p == NULL) {
		*p = malloc(sizeof(tl_field_t));
		(*p)->key = tl_assign(k);
		(*p)->left = NULL;
		(*p)->right = NULL;
	} else {
		tl_release((*p)->value);
	}

	(*p)->value = tl_assign(v);
}

tl_var_t * tl_select(tl_table_t * tbl, tl_var_t * k)
{
	tl_field_t ** p = find(tbl, k);
	if (*p == NULL) return tl_nil;
	return (*p)->value;
}

static int traverse(tl_field_t * f, int (* foo)(tl_var_t *, tl_var_t *, void *), void * data)
{
	if (!foo(f->key, f->value, data)) return 0;
	if (!traverse(f->left, foo, data)) return 0;
	if (!traverse(f->right, foo, data)) return 0;
	return 1;
}

void tl_traverse(tl_table_t * tbl, int (* foo)(tl_var_t *, tl_var_t *, void *), void * data)
{
	traverse(tbl->root, foo, data);
}
