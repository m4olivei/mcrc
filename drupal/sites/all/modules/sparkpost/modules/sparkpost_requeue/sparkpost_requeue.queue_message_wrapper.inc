<?php

/**
 * @file
 * Class for queued messages.
 */

class SparkpostQueuedMessageWrapper extends SparkpostMessageWrapper implements SparkpostMessageWrapperInterface {

  /**
   * The number of tries we have had with this one.
   *
   * @var int
   */
  protected $retryCount = 0;

  /**
   * Last retry timestamp.
   *
   * @var int
   */
  protected $lastRetry = 0;

  /**
   * SparkpostQueuedMessageWrapper constructor.
   *
   * @param \SparkpostMessageWrapper $message_wrapper
   *   The message wrapper instance. So we can just re-use that.
   */
  public function __construct(SparkpostMessageWrapper $message_wrapper) {
    parent::__construct($message_wrapper->getSparkpostMessage(), $message_wrapper->getDrupalMessage());
    if ($message_wrapper->getResult()) {
      $this->setResult($message_wrapper->getResult());
    }
    if ($message_wrapper->getApiResponseException()) {
      $this->setApiResponseException($message_wrapper->getApiResponseException());
    }
  }

  /**
   * Get the count of retries.
   *
   * @return int
   *   The number of retries we have had.
   */
  public function getRetryCount() {
    return $this->retryCount;
  }

  /**
   * Increment the retry count.
   */
  public function incrementRetryCount() {
    $this->retryCount++;
  }

  /**
   * @return int
   */
  public function getLastRetry() {
    return $this->lastRetry;
  }

  /**
   * @param int $lastRetry
   */
  public function setLastRetry($lastRetry) {
    $this->lastRetry = $lastRetry;
  }

}
