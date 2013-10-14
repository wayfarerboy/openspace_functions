<?php

class openspace_functions_plugin_access extends views_plugin_access {
  function summary_title() {
    return t('Access if invited participant');
  }

  function access($account) {
    return openspace_functions_access_participant($account);
  }

  function get_access_callback() {
    return array('openspace_functions_access_participant', array());
  }
}
