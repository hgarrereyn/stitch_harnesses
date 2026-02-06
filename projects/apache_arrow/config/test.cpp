#include <arrow/api.h>
#include <iostream>

int main() {
  arrow::Int32Builder builder;
  if (!builder.Append(1).ok()) return 1;
  if (!builder.AppendNull().ok()) return 1;
  if (!builder.Append(3).ok()) return 1;
  std::shared_ptr<arrow::Array> array;
  auto st = builder.Finish(&array);
  if (!st.ok()) {
    std::cerr << "Finish failed: " << st.ToString() << std::endl;
    return 1;
  }
  std::cout << "Array length: " << array->length() << " type: " << array->type()->ToString() << std::endl;
  return 0;
}
