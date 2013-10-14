<?php

 /**
* @file
* Example rules module to create actions, events, and conditions
*/

/**
 * Implement hook_rules_action_info()

 * Declare any meta data about actions for Rules
 */

function openspace_functions_rules_action_info() {
  $actions = array(
    'openspace_functions_action_hello_world' => array(
      'label' => t('Print Hello World on the page'),
      'group' => t('Rules Example'),
    ),
    'openspace_functions_action_hello_user' => array(
      'label' => t('Print Hello to the logged in user'),
      'group' => t('Rules Example'),
        'parameter' => array(
          'account' => array(
            'type' => 'user',
            'label' => t('User to say hello to'),
          ),
          'element' => array(
            'type' => 'twitter_username',
            'label' => 'Twitter username to search for'
          ),
        ),
      ),
    );
  return $actions;
}

/**
 * The action function for openspace_functions_action_hello_world
 */

function openspace_functions_action_hello_world() {
  drupal_set_message(t('Hello World'));
} 

/** 
 * The action function for openspace_functions_action_hello_user
 */

function openspace_functions_action_hello_user($account) {
  drupal_set_message(t('Hello @username', array('@username' => $account->name)));
}
