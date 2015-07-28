<?php

/**
 * @file pin_url.pages.inc
 */

/**
 * Form to create a Pin from a URL.
 */
function pin_url_create_form($form, &$form_state) {

  $form['website'] = array(
    '#type' => 'textfield',
    '#title' => 'Website',
    '#description' => t('Where do you want to Pin from?'),
    '#size' => '60',
    '#weight' => 1,
  );

  $form['website-next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
    '#weight' => 99,
  );

  //dpm($form, 'form');
  //dpm($form_state, 'form_state');

  return $form;
}

/**
 * Validation handler for creating a Pin from a URL.
 */
function pin_url_create_form_validate($form, &$form_state) {
  $website = $form_state['values']['website'];
  if (!valid_url($website, TRUE)) {
    form_set_error('website', 'Please specify a valid URL.');
  }
}

/**
 * Submit handler for creating a Pin from a URL.
 */
function pin_url_create_form_submit($form, &$form_state) {
  $website = $form_state['values']['website'];
}

/**
 * Parse a URL for images.
 *
 * @param string $html_url
 *   The URL to parse
 *
 * @return array
 *   Array of images found in the URL's HTML
 */
function pin_url_parse($html_url) {

  $html = file_get_contents($html_url);

  $doc = new DOMDocument();
  @$doc->loadHTML($html);

  $tags = $doc->getElementsByTagName('img');

  $image_urls = array();

  foreach ($tags as $tag) {
    $image = $tag->getAttribute('src');
    $check = parse_url($src);
    if (empty($check['host']) && empty($check['scheme'])) {
      $image = $url . $src;
    }

    // Check if it's an image.
    $valid = FALSE;
    $url_headers = get_headers($image, 1);
    if(!empty($url_headers['Content-Type'])){
      $type = strtolower($url_headers['Content-Type']);
      $valid = !empty($type) || strrpos($type, 'image', -strlen($type)) !== FALSE;
    }

    // Keep it, if valid.
    if ($valid) {

      $image_urls[] = $image;
    }
  }
  return $img;
}

/**
 * Theme array of iamge urls.
 *
 * @param array $images
 *   Array of image URLs
 *
 * @return array
 *   Themed image URLs.
 */
function pin_url_style_images($images) {

  $attrs = array('class' => 'some-img');
  foreach($images as $idx => $image_src) {
    $images[$idx] = theme_image(array('path' => $image_src, 'attributes' => $attrs));
  }

  return $images;
}
