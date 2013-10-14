<?php

/**
 *  A simple system for flushing cache if specific Openspace nodes have been changed
 *  Requires Openspace Functions module
 */
class openspace_functions_plugin_cache extends views_plugin_cache {

  function cache_expire($type) {
    $NEW = false;
    //syslog(LOG_INFO, $this->view->name.' '.$this->view->current_display);
    if (module_exists('openspace_functions')) {
      $args = $this->view->args;
      $options = $this->options;
      $NEW = openspace_functions_ping(
        $options['eid'] == 0 ? 'all' : (isset($args[$options['eid']]) ? $args[$options['eid']] : 'all'),
        $options['qid'] == 0 ? 'all' : (isset($args[$options['qid']]) ? $args[$options['qid']] : 'all'),
        $options['node_type'] == 'All' || $options['node_type'] == 0 ? 'all' : strtolower($options['node_type'])
      );
    }
    return $NEW;
  }

  function cache_set($type) {
    switch ($type) {
      case 'query':
        // Not supported currently, but this is certainly where we'd put it.
        break;
      case 'results':
        $data = array(
          'result' => $this->view->result,
          'total_rows' => isset($this->view->total_rows) ? $this->view->total_rows : 0,
          'current_page' => $this->view->get_current_page(),
        );
        cache_set($this->get_results_key(), $data, $this->table, $this->cache_set_expire($type));
        break;
      case 'output':
        $this->gather_headers();
        $this->storage['output'] = $this->view->display_handler->output;
        cache_set($this->get_output_key(), $this->storage, $this->table, $this->cache_set_expire($type));
        break;
    }
  }

  function cache_get($type) {
    $cutoff = $this->cache_expire($type);
    switch ($type) {
      case 'query':
        // Not supported currently, but this is certainly where we'd put it.
        return FALSE;
      case 'results':
        // Values to set: $view->result, $view->total_rows, $view->execute_time,
        // $view->current_page.
        if ($cache = cache_get($this->get_results_key(), $this->table)) {
          if (!$cutoff || $cache->created > $cutoff) {
            $this->view->result = $cache->data['result'];
            $this->view->total_rows = $cache->data['total_rows'];
            $this->view->set_current_page($cache->data['current_page']);
            $this->view->execute_time = 0;
            return TRUE;
          }
        }
        return FALSE;
      case 'output':
        if ($cache = cache_get($this->get_output_key(), $this->table)) {
          if (!$cutoff || $cache->created > $cutoff) {
            $this->storage = $cache->data;
            $this->view->display_handler->output = $cache->data['output'];
            $this->restore_headers();
            return TRUE;
          }
        }
        return FALSE;
    }
  }

  function summary_title() {
    return t('Openspace ping');
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['eid'] = array('default' => 0);
    $options['qid'] = array('default' => 0);
    $options['node_type'] = array('default' => 0);
    return $options;
  }

  function option_defaults(&$options) {
    $options['eid'] = 0;
    $options['qid'] = 0;
    $options['node_type'] = 'All';
  }

  function options_form(&$form, &$form_state) {
    $options = array(0 => t('All'));
    for ($i = 1; $i <= 10; $i++) {
      $options[$i] = $i;
    }
    
    $form['eid'] = array(
      '#type' => 'select',
      '#title' => t('Event context'),
      '#description' => t('Choose a context argument to use for event nid, otherwise select All to show all values.'),
      '#options' => $options,
      '#default_value' => $this->options['eid'],
    );

    $form['qid'] = array(
      '#type' => 'select',
      '#title' => t('Question context'),
      '#description' => t('Choose a context argument to use for question nid, otherwise select All to show all values.'),
      '#options' => $options,
      '#default_value' => $this->options['qid'],
    );

    $options = node_type_get_names();
    array_unshift($options, t('All'));
    $form['node_type'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#description' => t('Select a content type to compare updated dates.'),
      '#options' => $options,
      '#default_value' => $this->options['node_type'],
    );

  }
}
