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
      'module' => 'The module that will be renamed',
      'destination' => 'The full destination folder for the new module',
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
      return dt('Renames a module and its hooks. Usage is drush module-rename --module=fun --name=work');
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

  $options = array(
    'module' => drush_get_option('module'),
    'destination' => drush_get_option('destination'),
  );

  if (!module_exists($options['module'])) {
    drush_set_error(dt('The module that was specified does not exist.'));
  }
  else {
    if (!empty($options['destination']) && !is_dir($options['destination'])) {
      drush_mkdir($options['destination']);
    }
    else {
      drush_print('The destination directory for the new module already exists, moving on.');
    }

    $path = drupal_get_path('module', $options['module']);
    $files = scandir($path);

    $name = array_reverse(explode('/', $options['destination']));

    foreach($files as $file) {
      $filename = explode('.', $file);
      if (is_dir($options['destination']) && !empty($filename[1])) {
        drush_shell_cd_and_exec($path, 'cp %s %s/%s', $file, $options['destination'], $filename[0] . '.' . $filename[1]);
        //drush_print(print_r($filename));
      }
    }
  }
}
