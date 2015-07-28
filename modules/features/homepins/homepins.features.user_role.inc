<?php
/**
 * @file
 * homepins.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function homepins_user_default_roles() {
  $roles = array();

  // Exported role: Pinner.
  $roles['Pinner'] = array(
    'name' => 'Pinner',
    'weight' => 3,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
