#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <rocksdb/slice.h>
#include <rocksdb/status.h>
#include <iostream>
#include <string>

int main() {
  // Simple open/put/get close cycle
  rocksdb::Options options;
  options.create_if_missing = true;

  std::string dbpath = "/tmp/rocksdb_fuzz_setup_test";
  // Cleanup any existing DB
  rocksdb::DestroyDB(dbpath, options);

  rocksdb::DB* db = nullptr;
  rocksdb::Status s = rocksdb::DB::Open(options, dbpath, &db);
  if (!s.ok()) {
    std::cerr << "Open failed: " << s.ToString() << std::endl;
    return 1;
  }

  std::string key = "hello";
  std::string value = "world";
  s = db->Put(rocksdb::WriteOptions(), key, value);
  if (!s.ok()) {
    std::cerr << "Put failed: " << s.ToString() << std::endl;
    delete db;
    return 1;
  }

  std::string got;
  s = db->Get(rocksdb::ReadOptions(), key, &got);
  if (!s.ok()) {
    std::cerr << "Get failed: " << s.ToString() << std::endl;
    delete db;
    return 1;
  }

  std::cout << got << std::endl;

  delete db;
  rocksdb::DestroyDB(dbpath, options);
  return 0;
}
