MERGE ME
========
I have successfully tested this branch. Please merge the files to PlanB after you approve.


WebsiteCatalog
==============
Everything needed is done!

There is no "Save" feature, only "Save As...", and the input may not be verified as much as it could be.

One change I still plan to make is to shortcircuit the 1st menu option (Insert a Website) so it will tell you there is no room for a Website after you input the url, instead of having you input all fields for no reason.



ValidateManager
===============
ValidateManager and its associated files (ValidateManager.h, ValidateManager.c, constants.h). ValidateManager has extensive validations: one of the best feature of this ValidateManager is that it  has extensive validations for Url, for example, it validates:
* valid: http://www.deanza.edu
* valid: http://deanza.edu
* valid: www.deanza.edu
* invalid: deanza.edu.
* invalid: .deanza.edu
* invalid: deanzaedu

Formating for WebsiteCatalog:
I prefer to use the diagonal-braces placement; therefore, I am formatting it with diagonal braces for the codes I edited. If you want to revert this change, please reset the head to the following branch: 606f4a9de293e319d9f50dec30f3eedd33ddcbec
