<?php
/**
 * @file
 * homepins_search.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function homepins_search_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_saved-searches:saved-searches
  $menu_links['main-menu_saved-searches:saved-searches'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'saved-searches',
    'router_path' => 'saved-searches',
    'link_title' => 'Saved Searches',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_saved-searches:saved-searches',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Saved Searches');

  return $menu_links;
}
