<?php

/**
 * Impements hook_drush_command().
 *
 * @ return
 *  An associative array describing commands.
 */

function rename_drush_command () {
  $items = array();

  $items['rename-module'] = array(
    'description' => 'Renames a module and its hooks.',
    'options' => array(
      'old' => 'The module that will be renamed',
      'new' => 'The new name of the module',
      'destination' => 'The full path where the new module be copied into',
    ),
    'aliases' => array('mrn'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
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
      return dt('Renames a module and its hooks. Usage is drush module-rename --old=fun --new=work --destination=sites/all/modules');
  }
}


/**
 * Run the actual renaming.
 *
 * The function name should be same as command name but with dashes turned to
 * underscores and 'drush_commandfile_' prepended, where 'commandfile' is
 * taken from the file 'commandfile.drush.inc', which in this case is 'sandwich'.
 * Note also that a simplification step is also done in instances where
 * the commandfile name is the same as the beginning of the command name,
 * "drush_example_example_foo" is simplified to just "drush_example_foo".
 * To also implement a hook that is called before your command, implement
 * "drush_hook_pre_example_foo".  For a list of all available hooks for a
 * given command, run drush in --debug mode.
 *
 * @see drush_invoke()
 * @see drush.api.php
 */
function drush_rename_module($module = NULL, $name = NULL) {

  $old = drush_get_option('old');
  $new = drush_get_option('new');
  if (!in_array($old, array_keys(system_rebuild_module_data())) || (!$old_path = drupal_get_path('module', $old))) {
    drush_set_error(dt('The module that was specified does not exist.'));
    exit();
  }
  $destination =  drush_normalize_path(drush_get_option('destination', 'sites/all/modules/custom'));
  $new_path = $destination . "/" . $new;

  drush_log("renaming $old_path to $new_path", 'ok');
  if (drush_copy_dir($old_path, $new_path, FILE_EXISTS_ABORT) ||
    drush_confirm(dt("Do you want to DELETE the existing folder and recreate the copy? THIS MAY CAUSE DATA LOSS!", array('@dir' => $new_path))) &&
    drush_copy_dir($old_path, $new_path, FILE_EXISTS_OVERWRITE)
  ){
    $files = drush_scan_directory($new_path, "/". $old ."/", array('.', '..', 'CVS'));
    print_r($files);
    foreach($files as $file) {
      $new_filename = str_replace($old, $new, $file->filename);
      if (!rename($file->filename, $new_filename)) {
        return FALSE;
      }
    }
    $replace_cmd = "perl -pi -w -e 's/$old/$new/g;' *";
    drush_log("running $replace_cmd in $new_path", 'ok');
    drush_shell_cd_and_exec($new_path, $replace_cmd);
  }
}
