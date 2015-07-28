<?php
/**
 * @file
 * homepins_search.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function homepins_search_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_search_query'
  $field_bases['field_search_query'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_search_query',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
