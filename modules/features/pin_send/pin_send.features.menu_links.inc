<?php
/**
 * @file
 * pin_send.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pin_send_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_send-a-pin:send-pin
  $menu_links['main-menu_send-a-pin:send-pin'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'send-pin',
    'router_path' => 'send-pin',
    'link_title' => 'Send a Pin',
    'options' => array(
      'attributes' => array(
        'title' => 'Send a Pin to someone else',
      ),
      'identifier' => 'main-menu_send-a-pin:send-pin',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Send a Pin');

  return $menu_links;
}
