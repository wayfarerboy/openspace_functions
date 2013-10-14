<?php
class openspace_functions_handler_area_twitter_button_markup extends views_handler_area {
  public function render($empty = false) {
    $output = array();
    $class = $data = '';
    $u = user_load($this->view->args[0]);
    if (count($u->twitter_accounts) > 0) {
      $output[] = t("Sorry, you haven't been invited to an event.");
      // $output[] = l(t('Request an invitation'), 'events/coordinator/request-invitation', array('attributes'=>array('class'=>'invitation')));
    } else {
      $output[] = t('In order to use this site, you need to link with your Twitter account.');
      $output[] = l('<i class="icon-twitter"></i> '.t('Log in with Twitter'), $_GET['q'], array('html'=>true));
      $class = ' no-account';
      $data = ' data-url="'.url('user/'.arg(1).'/edit/twitter').' #twitter-auth-account-form"';
    }
    return '<section class="link-twitter-wrapper'.$class.'"'.$data.'><p>'.implode('</p><p>', $output).'</p></section>';
  }
}
