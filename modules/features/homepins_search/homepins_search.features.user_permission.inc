<?php
/**
 * @file
 * homepins_search.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function homepins_search_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create saved_search content'.
  $permissions['create saved_search content'] = array(
    'name' => 'create saved_search content',
    'roles' => array(
      'Pinner' => 'Pinner',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any saved_search content'.
  $permissions['delete any saved_search content'] = array(
    'name' => 'delete any saved_search content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own saved_search content'.
  $permissions['delete own saved_search content'] = array(
    'name' => 'delete own saved_search content',
    'roles' => array(
      'Pinner' => 'Pinner',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any saved_search content'.
  $permissions['edit any saved_search content'] = array(
    'name' => 'edit any saved_search content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own saved_search content'.
  $permissions['edit own saved_search content'] = array(
    'name' => 'edit own saved_search content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
