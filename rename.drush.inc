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
    ),
    'aliases' => array('mrn'),
    'bootstrap' => DRUPAL_BOOTSTRAP_DRUSH,
  );

  return $items;
}

/**
 * Run the actual renaming.
 */

