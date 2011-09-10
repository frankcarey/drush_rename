<?php

/**
 * Impements hook_drush_command().
 *
 * @ return
 *  An associative array describing commands.
 */

function rename_drush_command () {
  $items = array();

  $items['module-rename'] = array(
    'description' => 'Renames a module and its hooks.',
    'arguments' => array(
      'module' => 'The module that will be renamed',
      'name' => 'The new name for the module',
    ),
    'aliases' => array('mrn'),
    'bootstrap' => DRUPAL_BOOTSTRAP_DRUSH,
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'. This hook is optional. If a command
 * does not implement this hook, the command's description is used instead.
 *
 * This hook is also used to look up help metadata, such as help
 * category title and summary.  See the comments below for a description.
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function rename_drush_help($section) {
  switch ($section) {
    case 'drush:module-rename':
      return dt('Renames a modules and its hooks. Usage is drush module-rename {module} {new name}');
  }
}

/**
 * Run the actual renaming.
 */
function drush_rename() {
  
}
