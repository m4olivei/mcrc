<?php

/**
 * @file
 * Message class.
 */

/**
 * Interface SparkpostMessageWrapperInterface.
 */
interface SparkpostMessageWrapperInterface {
  /**
   * @return array
   */
  public function getSparkpostMessage();

  /**
   * @return array
   */
  public function getDrupalMessage();

  /**
   * @return \SparkPost\APIResponseException
   */
  public function getApiResponseException();

  /**
   * @return array
   */
  public function getResult();

  /**
   * @param array
   */
  public function setSparkpostMessage(array $sparkpost_message);

  /**
   * @param array
   */
  public function setDrupalMessage(array $drupal_message);

  /**
   * @param array $result
   */
  public function setResult(array $result);

  /**
   * @param \SparkPost\APIResponseException $apiResponseException
   */
  public function setApiResponseException(\SparkPost\APIResponseException $apiResponseException);
}
