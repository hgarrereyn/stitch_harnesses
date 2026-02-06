#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/slice.h>
#include <leveldb/iterator.h>
#include <leveldb/write_batch.h>
#include <iostream>
#include <string>
#include <memory>

int main() {
  // Prepare DB options
  leveldb::Options options;
  options.create_if_missing = true;

  // Open a temporary database under /tmp
  const std::string kDBPath = "/tmp/leveldb_fuzz_setup_test";

  leveldb::DB* db = nullptr;
  leveldb::Status status = leveldb::DB::Open(options, kDBPath, &db);
  if (!status.ok()) {
    std::cerr << "Open failed: " << status.ToString() << std::endl;
    return 1;
  }

  // Basic Put/Get
  std::string key = "hello";
  std::string value = "world";
  status = db->Put(leveldb::WriteOptions(), key, value);
  if (!status.ok()) { std::cerr << "Put failed\n"; delete db; return 1; }

  std::string got;
  status = db->Get(leveldb::ReadOptions(), key, &got);
  if (!status.ok() || got != value) { std::cerr << "Get failed\n"; delete db; return 1; }

  // Iterate
  std::unique_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));
  it->SeekToFirst();
  while (it->Valid()) {
    // Touch data to ensure iterator is usable
    (void)it->key();
    (void)it->value();
    it->Next();
  }

  // Cleanup and close
  delete db;
  std::cout << "LevelDB test OK" << std::endl;
  return 0;
}
