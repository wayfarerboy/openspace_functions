<?php

class openspace_functions_plugin_twitter_access extends views_plugin_access {
  function summary_title() {
    return t('Access if user has linked Twitter account');
  }

  function access($account) {
    return openspace_functions_twitter_access($account);
  }

  function get_access_callback() {
    return array('openspace_functions_twitter_access', array());
  }
}
