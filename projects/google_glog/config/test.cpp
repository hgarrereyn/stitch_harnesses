#include <glog/logging.h>
#include <iostream>

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;  // Avoid creating log files
  LOG(INFO) << "glog test: Hello from glog!";
  LOG(WARNING) << "This is a warning";
  LOG(ERROR) << "This is an error";
  // Basic checks
  if (google::NUM_SEVERITIES <= 0) {
    std::cerr << "Unexpected severities" << std::endl;
    return 1;
  }
  google::ShutdownGoogleLogging();
  return 0;
}
