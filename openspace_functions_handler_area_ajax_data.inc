<?php
class openspace_functions_handler_area_ajax_data extends views_handler_area {
  public function render($empty = false) {
    if (isset($this->view->args)) {
      $args = $this->view->args;
      $url = $this->view->get_url();
      if (is_array($args) && count($args) > 0) {
        $eid = $this->view->args[0];
        if (isset($this->view->exposed_input) && is_array($this->view->exposed_input)) {
          $url .= '?'.drupal_http_build_query($this->view->exposed_input);
        }
        return sprintf('<div class="ajax-data" data-eid="%d" data-timestamp="%d" data-url="/%s .view-id-%s.view-display-id-%s .view-content"></div>', $eid, openspace_functions_get_last_event_timestamp($eid), $url, $this->view->name, $this->view->current_display);
      }
    }
    return '';
  }
}
