WebsiteCatalog (Ver 1.0)
==============
Everything needed is done!

There is no "Save" feature, only "Save As...", and the input may not be verified as much as it could be.

One change I still plan to make is to shortcircuit the 1st menu option (Insert a Website) so it will tell you there is no room for a Website after you input the url, instead of having you input all fields for no reason.

ADDED
=====
file name delimiter issues resolved 

TODO:
=====
* Add "Save" feature.
* Check if Url is insertable from #1 menu option (Insert a Website)

ValidateManager
===============
ValidateManager and its associated files (ValidateManager.h, ValidateManager.c, constants.h). ValidateManager has extensive validations: one of the best feature of this ValidateManager is that it  has extensive validations for Url, for example, it validates:
* valid: http://www.deanza.edu
* valid: http://deanza.edu
* valid: www.deanza.edu
* invalid: deanza.edu.
* invalid: .deanza.edu
* invalid: deanzaedu


