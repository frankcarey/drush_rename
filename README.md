This was adapted / completed from Sam Kotter's sandbox drupal project here: https://drupal.org/sandbox/skottler/1275264

This has been lightly tested, so USE AT YOUR OWN RISK. Make sure you backup your code before you do anything.

It worked well for me when neededing to completely change a module name and all of it's hooks.

Installation
-----------

Clone into your .drush file and it should show up as a new drush command.

Usage
-----

    rename-module (mrn)   Renames a module and its hooks.
    
    Options:
     --destination                             The full path where the new module be copied into
     --new                                     The new name of the module
     --old                                     The module that will be renamed
    
    Example:
    drush module-rename --old=fun --new=work --destination=sites/all/modules

