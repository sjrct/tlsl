TLSL
====
TLSL is a primarily functional scripting language. It is still in its early
stages and as a result not the most functional (haha get it? its funny) language
in the world.

Installation
------------
To build the program, type `make` in the top directory to build all the parts of
the program. The file `libtl.so` in `libtl` needs to be symlinked or copied into
the `/usr/lib` directory or another directory in the library path. Then, you can
run the interpreter, `tli`, from its directory also called `tli`. As of now, it
needs to be run from that directory in order to know where `tlbones.so` is, but
that will change in the future.

Types
-----
* **nil**
  This type represents the absence of value. All unset values are equivalent
  to nil, and all values set to nil are equivalent to unset values.
* **type**
  An integer type that enumerates all of the types of the language. Can be
  equal to any of the types listed here.
* **int**
  Normally equivalent to C's `long` type. This is set in `tl/config.h`, if one
  wishes to change that.
* **float**
  Normally equivalent to C's `double` type. This is set in `tl/config.h`, if one
  wishes to change that.
* **string**
  A string type. The characters of the string are of C's `char` type.
* **list**
   A car-cdr style linked list.
* **function**
   A function.
* **table**
   A key-value pair based table. The table is stored as a binary tree. All types
   can be stored as a key or value, though setting a key equal to nil it
   equivalent to deleting it, and trying to access an unset key will return nil.
