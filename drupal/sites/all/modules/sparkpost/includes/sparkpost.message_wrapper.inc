<?php

/**
 * @file
 * Message class.
 */

class SparkpostMessageWrapper implements SparkpostMessageWrapperInterface {

  /**
   * @var array
   */
  protected $sparkpostMessage;

  /**
   * @var array
   */
  protected $drupalMessage;

  /**
   * @var \SparkPost\APIResponseException
   */
  protected $apiResponseException;

  /**
   * @var array
   */
  protected $result;

  /**
   * SparkpostMessage constructor.
   */
  public function __construct(array $sparkpost_message, array $drupal_message) {
    $this->sparkpostMessage = $sparkpost_message;
    $this->drupalMessage = $drupal_message;
  }

  /**
   * @param array $drupal_message
   */
  public function setDrupalMessage(array $drupal_message) {
    $this->drupalMessage = $drupal_message;
  }

  /**
   * @param array $sparkpost_message
   */
  public function setSparkpostMessage(array $sparkpost_message) {
    $this->sparkpostMessage = $sparkpost_message;
  }

  /**
   * @param \SparkPost\APIResponseException $apiResponseException
   */
  public function setApiResponseException(\SparkPost\APIResponseException $apiResponseException) {
    $this->apiResponseException = $apiResponseException;
  }

  /**
   * @param array $result
   */
  public function setResult(array $result) {
    $this->result = $result;
  }

  /**
   * @return array
   */
  public function getSparkpostMessage() {
    return $this->sparkpostMessage;
  }

  /**
   * @return array
   */
  public function getDrupalMessage() {
    return $this->drupalMessage;
  }

  /**
   * @return \SparkPost\APIResponseException
   */
  public function getApiResponseException() {
    return $this->apiResponseException;
  }

  /**
   * @return array
   */
  public function getResult() {
    return $this->result;
  }

}
