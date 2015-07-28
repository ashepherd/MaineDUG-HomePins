<?php
/**
 * @file
 * homepins.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function homepins_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views--exp-pinner-boards'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-pinner-boards',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'pinner/*/boards',
    'roles' => array(),
    'themes' => array(
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Pinner Boards',
    'visibility' => 1,
  );

  $export['views--exp-pinner-pins'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-pinner-pins',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'pinner/*/pins',
    'roles' => array(),
    'themes' => array(
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Pinner Pins',
    'visibility' => 1,
  );

  $export['views--exp-search-search_all'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-search-search_all',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'search',
    'roles' => array(),
    'themes' => array(
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'bootstrap',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Search All',
    'visibility' => 1,
  );

  $export['views--exp-search-search_pinner'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-search-search_pinner',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'search/pinner/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Search Pinner',
    'visibility' => 1,
  );

  return $export;
}
