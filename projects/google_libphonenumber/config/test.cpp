#include <iostream>
#include <string>
#include <phonenumbers/phonenumberutil.h>
#include <phonenumbers/asyoutypeformatter.h>

using namespace i18n::phonenumbers;

int main() {
  PhoneNumberUtil* util = PhoneNumberUtil::GetInstance();
  const std::string input = "044 668 18 00";
  PhoneNumber number;
  auto status = util->Parse(input, "CH", &number);
  if (status != PhoneNumberUtil::NO_PARSING_ERROR) {
    std::cout << "Parse failed: " << status << "\n";
    return 0;
  }
  std::string e164;
  util->Format(number, PhoneNumberUtil::E164, &e164);
  std::cout << "E164: " << e164 << "\n";

  std::unique_ptr<AsYouTypeFormatter> fmt(util->GetAsYouTypeFormatter("US"));
  std::string seq = "6502530000";
  std::string out;
  for (char c : seq) {
    out = fmt->InputDigit(c, &out);
  }
  std::cout << "AsYouType US sample: " << out << "\n";
  return 0;
}
