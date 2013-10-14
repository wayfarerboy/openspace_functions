<?php
class openspace_functions_handler_area_timer_markup extends views_handler_area {
  public function render($empty = false) {
    return '<div class="timer-wrapper"><div class="pie spinner"></div><div class="pie filler"></div><div class="mask"></div></div>';
  }
}
