<?php

/**
 * @file pin_url.pages.inc
 */

/**
 * Form to create a Pin from a website URL.
 */
function pin_url_create_form($form, &$form_state) {
  global $user;

  $step = isset($form_state['storage']['step']) ? $form_state['storage']['step'] : 1;

  // Setup buttons atop of the form for navigation.
  $form['top-nav'] = array(
    '#type' => 'container',
    '#weight' => -99,
  );
  $pin_url_step_classes = array('class' => array('pin-url-step'));
  $form['top-nav']['step-1'] = array(
    '#type' => 'submit',
    '#value' => '1. Website',
    '#attributes' => $pin_url_step_classes,
    '#weight' => 1,
  );
  $form['top-nav']['step-2'] = array(
    '#type' => 'submit',
    '#attributes' => $pin_url_step_classes,
    '#value' => '2. Image',
    '#weight' => 2,
  );
  $form['top-nav']['step-3'] = array(
    '#type' => 'submit',
    '#attributes' => $pin_url_step_classes,
    '#value' => '3. Pin',
    '#weight' => 3,
  );
  // Set the Bootstrap primary button class for the current step.
  $form['top-nav']['step-' . $step]['#attributes']['class'][] = 'btn-primary';

  // Styling for front-end designers.
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'pin_url') . '/pin_url.css',
  );

  // Keep track of the types of submit buttons to show.
  $next_submit = FALSE;
  $previous_submit = FALSE;
  $save_submit = FALSE;

  switch($step) {
    case 1:
      $next_submit = TRUE;

      $website = !empty($form_state['storage']['values'][1]['website']) ? $form_state['storage']['values'][1]['website'] : '';
      $form['website'] = array(
        '#type' => 'textfield',
        '#title' => 'Website',
        '#description' => t('Where do you want to Pin from?'),
        '#required' => TRUE,
        '#default_value' => $website,
        '#weight' => 1,
      );
      break;

    case 2:
      $next_submit = TRUE;
      $previous_submit = TRUE;

      // Show the website URL.
      $website = $form_state['storage']['values']['1']['website'];
      $website_vars = array(
        'title' => t('Website'),
        'value' => l($website, $website, array('attributes' => array('target' => '_blank'))),
      );
      $form['website-markup'] = array(
        '#markup' => theme('pin_url_field', $website_vars),
        '#weight' => 1,
      );

      $images = $form_state['storage']['website_images'];
      if (!empty($images)) {
        $themed_images = array('_none' => t('No Image'));
        foreach($images as $idx => $image_src) {
          $themed_images[$image_src] = pin_url_style_image($image_src);
        }
        $default_image = !empty($form_state['storage']['values'][2]['image']) ? $form_state['storage']['values'][2]['image'] : '_none';
        $form['image'] = array(
          '#type' => 'radios',
          '#title' => t('Image for the Pin'),
          '#options' => $themed_images,
          '#description' => t('Select an image to represent this pin'),
          '#required' => TRUE,
          '#default_value' => $default_image,
          '#weight' => 2,
        );
      }
      else {
        $form['image-notify'] = array(
          '#title' => t('Image for the Pin'),
          '#markup' => 'No images found',
          '#weight' => 2,
        );
      }
      break;

    case 3:
      $previous_submit = TRUE;
      $save_submit = TRUE;

      // Show the website URL.
      $website = $form_state['storage']['values']['1']['website'];
      $website_vars = array(
        'title' => t('Website'),
        'value' => l($website, $website, array('attributes' => array('target' => '_blank'))),
      );
      $form['website-markup'] = array(
        '#markup' => theme('pin_url_field', $website_vars),
        '#weight' => 1,
      );

      if (!empty($form_state['storage']['values'][2]['image'])) {
        $image_src = $form_state['storage']['values'][2]['image'];
        $form['image_to_pin'] = array(
          '#markup' => pin_url_style_image($image_src),
          // Used by pin_url.css CSS file.
          '#prefix' => '<div id="pin-url-image">',
          '#suffix' => '</div>',
          '#weight' => 2,
        );
      }
      else {
        $form['image-markup'] = array(
          '#markup' => '<div class="pin-url-markup">
          <span class="pin-url-markup-title">Image for the Pin</span>:
          <span class="pin-url-markup-value">none</span></div>',
          '#weight' => 2,
        );
      }

      // Get the original Pin node form fields.
      $pin_form = _pin_url_get_pin_form_data();
      //dpm($pin_form);

      $image_upload_location = $pin_form['form']['field_image'][LANGUAGE_NONE][0]['#upload_location'];
      $form['image_upload_location'] = array(
        '#type' => 'hidden',
        '#value' => $image_upload_location,
      );

      // Set the Pin node form fields to this form.
      $form['title'] = $pin_form['form']['title'];
      $form['field_board'] = $pin_form['form']['field_board'];
      $form['field_private'] = $pin_form['form']['field_private'];
      $form['field_description'] = $pin_form['form']['field_description'];
      // Add the node field data to the $form_state['fields'].
      $form_state['field']['field_private'] = $pin_form['form_state']['field']['field_private'];
      $form_state['field']['field_description'] = $pin_form['form_state']['field']['field_description'];
      $form_state['field']['field_board'] = $pin_form['form_state']['field']['field_board'];
      // Weight the Pin node form fields.
      $form['title']['#weight'] = 3;
      $form['field_board']['#weight'] = 4;
      $form['field_private']['#weight'] = 5;
      $form['field_description']['#weight'] = 6;
      // Set the default values.
      $form['title']['#default_value'] = !empty($form_state['storage']['values'][3]['title']) ? $form_state['storage']['values'][3]['title'] : '';
      $form['field_board'][LANGUAGE_NONE]['#default_value'] = !empty($form_state['storage']['values'][3]['field_board'][LANGUAGE_NONE][0]['target_id']) ? $form_state['storage']['values'][3]['field_board'][LANGUAGE_NONE][0]['target_id'] : array();
      $form['field_private'][LANGUAGE_NONE]['#default_value'] = !empty($form_state['storage']['values'][3]['field_private'][LANGUAGE_NONE][0]['value']) ? $form_state['storage']['values'][3]['field_private'][LANGUAGE_NONE][0]['value'] : 0;
      $form['field_description'][LANGUAGE_NONE][0]['value']['#default_value'] = !empty($form_state['storage']['values'][3]['field_description'][LANGUAGE_NONE][0]['value']) ? $form_state['storage']['values'][3]['field_description'][LANGUAGE_NONE][0]['value'] : NULL;

      break;

  }

  $form['buttons'] = array(
    '#type' => 'container',
    '#weight' => 90,
  );
  if ($previous_submit) {
    $form['buttons']['previous'] = array(
      '#type' => 'submit',
      '#value' => 'Previous',
      '#weight' => 99,
      '#attributes' => array('style' => 'float: left'),
    );
  }
  if ($next_submit) {
    $form['buttons']['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#weight' => 100,
      '#attributes' => array('style' => 'float: right'),
    );
  }
  elseif ($save_submit) {
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create'),
      '#weight' => 100,
      '#attributes' => array('style' => 'float: right'),
    );
  }

  //dpm($form, 'form');
  //dpm($form_state, 'form_state');

  return $form;
}

/**
 * Validation handler for creating a Pin from a URL.
 */
function pin_url_create_form_validate($form, &$form_state) {

  // Figure out what step we are on.
  $step = isset($form_state['storage']['step']) ? $form_state['storage']['step'] : 1;
  switch($step){
    case 1:
      $website = $form_state['values']['website'];
      if (!valid_url($website, TRUE)) {
        form_set_error('website', 'Please specify a valid website URL.');
        // Do not continue on because the URL isn't valid.
        return;
      }

      // Get the images from the website, if any.
      // Do this now, because you ONLY want to perform this task
      // after submitting step #1, anfd not on refreshes of 'Previous' clicks.
      $form_state['storage']['website_images'] = pin_url_parse($website);
      break;

    case 2:

      break;

    case 3:

      break;
  }
}

/**
 * Submit handler for creating a Pin from a URL.
 */
function pin_url_create_form_submit($form, &$form_state) {

  if (!isset($form_state['storage']['step'])) {
    $form_state['storage']['step'] = 1;
  }

  // The current step.
  $step = $form_state['storage']['step'];
  $form_state['storage']['values'][$step] = $form_state['values'];

  // Move on to the next step.
  if ($form_state['clicked_button']['#id'] == 'edit-next') {
    $form_state['storage']['step'] = $step + 1;
  }
  // Go back to the previous step.
  else if ($form_state['clicked_button']['#id'] == 'edit-previous') {
    $form_state['storage']['step'] = $step - 1;
  }
  else if ($form_state['clicked_button']['#id'] == 'edit-submit') {
    //dpm($form_state, 'form state');
    //dpm($form, 'form');
    // Save the data.
    $data = array(
      'website' => $form_state['storage']['values'][1]['website'],
      'image' => $form_state['storage']['values'][2]['image'],
      'image_upload_location' => $form_state['storage']['values'][3]['image_upload_location'],
      'title' => $form_state['storage']['values'][3]['title'],
      'board' => $form_state['storage']['values'][3]['field_board'][LANGUAGE_NONE][0]['target_id'],
      'private' => $form_state['storage']['values'][3]['field_private'][LANGUAGE_NONE][0]['value'],
      'notes' => $form_state['storage']['values'][3]['field_description'][LANGUAGE_NONE][0]['value'],
    );
    $node = _pin_url_create_pin($data);
    if( $node && isset($node->nid) ){
      unset ($form_state['storage']);
      drupal_goto('node/' . $node->nid);
    }
  }
  else {
    // Go to a step.
    switch($form_state['clicked_button']['#id']){
      case 'edit-step-1':
        $form_state['storage']['step'] = 1;
        break;

      case 'edit-step-2':
        $form_state['storage']['step'] = 2;
        break;

      case 'edit-step-3':
        $form_state['storage']['step'] = 3;
        break;
    }
  }

  // In some instances where there are more than 2 steps,
  // the 'form_build_id' gets lost???
  if (isset($form_state['storage']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['storage']['form_build_id'];
  }
  $form_state['storage']['form_build_id'] = $form_state['values']['form_build_id'];

  // We didn't save a new Pin, so rebuild the form.
  $form_state['rebuild'] = TRUE;
}

/**
 * Create a Pin node.
 *
 * @param array $data
 *   Necessary data from the pin_from_url form.
 *
 * @return object
 */
function _pin_url_create_pin($data) {

  // Get a stub Pin node.
  $node = _homepins_stub_node('pin');
  $pin = entity_metadata_wrapper('node', $node);

  $title = $data['title'];
  $url = $data['website'];
  $image = $data['image'];
  $image_upload_location = $data['image_upload_location'];
  $board = $data['board'];
  $private = $data['private'];
  $notes = $data['notes'];

  // Set the Pin fields.
  $pin->title = $title;
  $pin->field_url = array('url' => $url);
  $pin->field_board = $board;
  $pin->field_private = $private;
  if (!empty($notes)) {
    $pin->field_description = $notes;
  }

  if ('_none' != $image) {
    // Get a filename for the image.
    $uri  =  $image_upload_location . '/' . drupal_basename($image);;
    // Save the image URL as a file.
    $new_file = system_retrieve_file($image, $uri, TRUE, FILE_EXISTS_RENAME);
    if($new_file) {
      $pin->field_image = (array)$new_file;
    }
    else {
      drupal_set_message('error', t('Could not save the Pin\'s image @image', array('@image' => $image)));
    }
  }
  // Save the Pin node.
  $pin->save();

  return $node;
}

/**
 * Get a Pin node form.
 */
function _pin_url_get_pin_form_data() {

  $pin_node = new stdClass();
  $pin_node->type = 'pin';
  node_object_prepare( $pin_node );
  // Load the required include file.
  module_load_include('inc', 'node', 'node.pages');

  // Calling drupal_get_form() renders the node title field.
  $pin_form = drupal_get_form('pin_node_form', $pin_node);

  // Remove '#value', it blocks the $form_state['values']['title'] from setting.
  unset($pin_form['title']['#value']);

  // Add the missing node form title field.
  $form = array(
    'title' => $pin_form['title'],
  );

  $form_state = array();
  // Create the entity form fields.
  field_attach_form('node', $pin_node, $form, $form_state);

  return array(
    'form' => $form,
    'form_state' => $form_state,
  );
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
    $check = parse_url($image);
    if (empty($check['host']) && empty($check['scheme'])) {
      $image = $html_url . $image;
    }

    // Check if it's an image.
    $valid = FALSE;
    $url_headers = get_headers($image, 1);
    if (!empty($url_headers['Content-Type'])) {
      $type = strtolower($url_headers['Content-Type']);
      // Does the media type start with 'image/'.
      $valid = !empty($type) || strrpos($type, 'image/', -strlen($type)) !== FALSE;
    }

    // Keep it, if valid.
    if ($valid) {
      $image_urls[] = $image;
    }
  }
  return $image_urls;
}

/**
 * Generate HTML for an image.
 *
 * @param array $image_src
 *   Absolute image URL
 *
 * @return array
 *   Themed image HTML
 */
function pin_url_style_image($image_src) {

  $attrs = array('class' => 'pin-url-image');
  return theme_image(array('path' => $image_src, 'attributes' => $attrs));
}
