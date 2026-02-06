#include <iostream>
#include "tensorflow/lite/logger.h"
#include "tensorflow/lite/minimal_logging.h"

int main() {
  // Ensure logs are visible
  tflite::LoggerOptions::SetMinimumLogSeverity(tflite::TFLITE_LOG_VERBOSE);
  TFLITE_LOG_PROD(tflite::TFLITE_LOG_INFO, "Hello from TFLite minimal logging: %d", 123);
  TFLITE_LOG_PROD_ONCE(tflite::TFLITE_LOG_WARNING, "This warning logs only once");
  // Also exercise the debug macro (may be compiled out in release)
  TFLITE_LOG(tflite::TFLITE_LOG_VERBOSE, "Verbose log: %s", "ok");
  std::cout << "Ran minimal logging test" << std::endl;
  return 0;
}
