websitecatalog
==============
<<<<<<< HEAD

Update List (please do not delete the list. build the list):

* (10)init: structure chart uploaded to ./resource/
* (9) init: menu driver functions from main
* (8) update: WebsiteCatalog.c
* (7) $sudo touch WebisteCatalog.c
* (6) $sudo mv WebsiteCatalog.c deprecated_WebsiteCatalog.c # previous WebsiteCatalog.c commented out
* (5) menu driver functions // menu
* (4) quit option
* (3) save as option
* (2) save option
* (1) bool isDataModified; // checks if data had been modified after open

TODO (high priority):
(1) write data to file (breadth-first traversal)
(2) 


FIXME (high Priority):
(1) invalid output for Url
(2) bad_access problem


TODO (low priority):
(1) doc for gonkim's Managers

FIXME (low Priority):
(1) memory leaks of unexpectedly exit // through exit();
=======
added:
* (1) bool isDataModified; // checks if data had been modified after open
* (2) save option
* (3) save as option
* (4) quit option

TODO:
* (1) write data to file (breadth-first traversal)

FIXME (High Priority)
* (1) invalid output for Url
* (2) bad_access problem -- (partially?) fixed
* (3) MenuManager.c::_getMenuSelection() always returns MENU_TYPE_DELETE_DATA
      This is because InputManager.c::promptUserSelection() always returns INPUT_VALUE_VALID,
       but it is being called as if it returned the user's selection.
    See MenuManager.c::_promptMenu()
* (4) SingleWebsiteManager.c::getSingleWebsite() does not parse fields properly.
      Memory Leaks.
      Passes char* to websiteCreate() where it should be passing ints
      

FIXME (Low Priority)
* (1) memory leaks of unexpectedly exit // through exit();
>>>>>>> d097ab79baf88d3c71d49d90676269487a3a690c
