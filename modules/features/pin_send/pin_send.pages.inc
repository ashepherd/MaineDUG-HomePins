<?php

/**
 * @file pin_send.pages.inc
 *
 */

/**
 * Send a Pin Page.
 */
function pin_send_page() {
  // STEP 1: Include the Recommended Pins View.
  $html = '<h2 id="recommended-title">Recommended Pins</h2>';
  $html .= views_embed_view('recommended_pins' , 'default');

  $html .= '<hr/>';

  // STEP 2: Include the pin_send custom form.
  $form = drupal_get_form('pin_send_form');
  $html .= drupal_render($form);

  return $html;
}

/**
 * Form for sending Pins to people.
 */
function pin_send_form($form, &$form_state) {

  $form['recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient\'s Email Address'),
    '#size' => 50,
    '#required' => TRUE,
    '#description' => t('The email address you want to send a Pin'),
    '#weight' => 1,
  );

  $form['send'] = array(
    '#type' => 'submit',
    '#value' => 'Send',
    '#attributes' => array('class' => array('btn-primary')),
    '#weight' => 99,
  );

  $form['select-pins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pins to Send'),
    '#weight' => 2,
    '#prefix' => '<div id="select-pins-section">',
    '#suffix' => '</div>',
  );

  // STEP 2: #ajax - Add another Pin to send
  $form['select-pins']['add-pin'] = array(
    '#type' => 'button',
    '#value' => t('Add Another Pin'),
    '#weight' => -1,
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => '_pin_send_add_pin',
      'wrapper' => 'select-pins-section',
      'effect' => 'fade',
    ),
  );

  // How many Pins to send.
  $pin_count = 1;

  //Try out static function!!!- Adam.
  // Get an array of Pins only once for performance.
  if (!isset($form_state['storage']['pins'])) {
    $form_state['storage']['pins'] = _pin_send_pin_options();
  }
  $select_a_pin = $form_state['storage']['pins'];

  // STEP 2a: Use the pin count set in the $form_state['storage']['pin-count'].

  // Make sure at least one pin textfield is displayed.
  if (!isset($form_state['storage']['pin-count'])) {
    $form_state['storage']['pin-count'] = $pin_count;
  }
  else {
    $pin_count = $form_state['storage']['pin-count'];
  }


  // For each Pin count
  for($a = 0; $a < $pin_count; $a++) {
    $pin_id = 'pin-' . $a;
    $form['select-pins'][$pin_id] = array(
      '#type' => 'select',
      '#title' => t('Select a Pin'),
      '#options' => $select_a_pin,
      '#weight' => $a,
    );
  }

  // Make sure my styles work even if form validation fails.
  //$form['#after_build'][] = '_pin_send_after_build';

  return $form;
}

/**
 * AJAX callback for adding pins to the message.
 */
function _pin_send_add_pin(&$form, &$form_state) {
  $form_state['storage']['pin-count'] += 1;
  $form = drupal_rebuild_form($form['#form_id'], $form_state, $form);
  return $form['select-pins'];
}

/**
 * Pin send validation handler.
 */
function pin_send_form_validate($form, &$form_state) {
  $email = $form_state['values']['recipient'];
  if (!valid_email_address($email)) {
    form_set_error('recipient', t('The email address %email is invalid', array('%email' => $email)));
  }
}

/**
 * Add styles to a form, etc.
 */
function _pin_send_after_build($form, &$form_state) {
  $form['recipient']['#suffix'] = 'This text will rule them all!';

  //This line works even after validation fails.
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'pin_send') . '/pin_send.css',
  );

  return $form;
}

/**
 * Pin send submit handler.
 */
function pin_send_form_submit($form, &$form_state) {
  drupal_set_message(t('Pins have been sent.'));
}

/**
 * Get a list of Pins as an options array.
 *
* @param string $string
 *   The user's query.
 */
function _pin_send_pin_options() {
  return db_query("SELECT nid, title FROM {node} WHERE type = 'pin' AND status = 1")->fetchAllKeyed();
}
