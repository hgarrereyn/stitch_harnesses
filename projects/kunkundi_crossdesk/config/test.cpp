#include <iostream>
#include <string>
#include "crossdesk/rd_log.h"
#include "crossdesk/platform.h"
#include "crossdesk/path_manager.h"
#include "crossdesk/display_info.h"

int main() {
  using namespace crossdesk;

  // Initialize logger to a temporary directory inside the container
  InitLogger("/tmp/crossdesk_logs");
  LOG_INFO("CrossDesk mini test starting");

  std::string host = GetHostName();
  LOG_INFO("Hostname: {}", host);
  std::cout << "Hostname: " << host << std::endl;

  PathManager pm("crossdesk-test");
  auto cfg = pm.GetConfigPath();
  auto cache = pm.GetCachePath();
  auto logs = pm.GetLogPath();
  auto certs = pm.GetCertPath();
  pm.CreateDirectories(cfg);
  pm.CreateDirectories(cache);
  pm.CreateDirectories(logs);
  pm.CreateDirectories(certs);
  LOG_INFO("Paths: cfg={}, cache={}, logs={}, certs={}", cfg.string(), cache.string(), logs.string(), certs.string());

  // Use DisplayInfo simple POD-like class
  DisplayInfo d("Main", 0, 0, 1920, 1080);
  std::cout << "Display " << d.name << ": " << d.width << "x" << d.height << std::endl;

  LOG_INFO("CrossDesk mini test finished");
  return 0;
}
