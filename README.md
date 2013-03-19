websitecatalog
==============

This branch is a branch with a less robust menu, file, and validation system.
However, all the code works and has no memory leaks. Also, all the functions are documented.

The code is not amazingly clean, there are several places where code is duplicated,
when it should be its own function.

This is a backup plan in case we cannot get Gon's code to work by Wednesday.

FIXME (High Priority)
======================
* HashManager is severely buggy, causes memory leaks, invalid result, and program crash.
    * hashRemove has infinte loop (while statement ending with semicolon)
    * search marks synonyms as the same key


