#include "my_string_view.hpp"

namespace msv = my_string_view_namespace;
int main() {
  msv::my_string_view<char> sv("Hello, world!");
  std::cout << sv.data() << std::endl;
  std::cout << sv.size() << std::endl;
  std::cout << sv[7] << std::endl;
  std::cout << sv.find('o') << std::endl;
  msv::my_string_view<char> str1("Hello");
  msv::my_string_view<char> str2("World");
  // check fo equals
  if (str1 == str2) {
    std::cout << "The strings are equal" << std::endl;
  } else {
    std::cout << "The strings are not equal" << std::endl;
  }
  // comparing strings
  if (str1 < str2) {
      std::cout << "The string 2 are greater than string 1" << std::endl;
  } else {
      std::cout << "The string 1 are greater than string 2" << std::endl;
  }
  //msv::find
  msv::my_string_view<char> str("Hello, world!");

  int index = str.find('o');
  if (index != msv::my_string_view<char>::npos) {
    std::cout << "The character 'o' is found at index " << index << std::endl;
  } else {
    std::cout << "The character 'o' is not found" << std::endl;
  }
  //sub string view find
  msv::my_string_view svf("Hello world", 13);

  msv::string_view substring("world", 5);
  auto pos = sv.find(substring);

  if (pos != msv::string_view::npos) {
    std::cout << "The substring was found at position: " << pos << std::endl;
  } else {
    std::cout << "The substring was not found in the string" << std::endl;
  }

  // Using the substr operation
  size_t substrPos = 5;
  size_t substrCount = 5;
  msv::my_string_view<char> subview = str.substr(substrPos, substrCount);
  std::cout << "Substring view: " << subview.data() << std::endl;

  //copy
  msv::my_string_view cpsv1("Hello");
  msv::my_string_view cpsv2("World");

  std::cout << "Before copying:" << std::endl;
  std::cout << "sv1: " << cpsv1.data() << std::endl;
  std::cout << "sv2: " << cpsv2.data() << std::endl;

  cpsv1 = cpsv2;

  std::cout << "After copying:" << std::endl;
  std::cout << "sv1: " << cpsv1.data() << std::endl;
  std::cout << "sv2: " << cpsv2.data() << std::endl;
  //swap
  msv::my_string_view cwptrv1("hello");
  msv::my_string_view cwptrv2("world");
  cwptrv1.swap(cwptrv2);

  std::cout << "After swap:" << std::endl;
  std::cout << "sv1: " << cwptrv1.data() << std::endl;
  std::cout << "sv2: " << cwptrv2.data() << std::endl;
  // is string equals(bool)
  msv::my_string_view<char> sv2("Hello, world!");
  std::cout << "string are equal(1): "<< (sv == sv2) << std::endl; // Output: 1 (true)

  msv::my_string_view<char> s;
  [[maybe_unused]] msv::my_string_view<char> view(s);
  //  range-based for loop to iterate
  std::cout << "Characters in the view:" << std::endl;
  for (char it : sv2) {
    std::cout << it;
  }
  std::cout << std::endl;
  //rfind for symbol
  msv::my_string_view ssv("Hello, World!");
  char ch = 'o';
  size_t last_index = sv.rfind(ch);
  //rfind for substring
  msv::my_string_view strv("Hello, World!");
  msv::my_string_view pattern("W");
  std::cout << "rfind result: " << strv.rfind(pattern) << std::endl;

  if (last_index != msv::string_view::npos) {
    std::cout << "Last occurrence of '" << ch << "' is at index: " << last_index << std::endl;
  } else {
    std::cout << "Character '" << ch << "' not found in the string." << std::endl;
  }

  //find_of
  //find_firts
  size_t found_first = sv.find_first_of("aeiou");
  if (found_first != msv::string_view::npos) {
    std::cout << "First occurrence of any vowel: " << found_first << std::endl;
  } else {
    std::cout << "No vowel found" << std::endl;
  }

  // find_last
  size_t found_last = sv.find_last_of("aeiou");
  if (found_last != msv::string_view::npos) {
    std::cout << "Last occurrence of any vowel: " << found_last << std::endl;
  } else {
    std::cout << "No vowel found" << std::endl;
  }

  //contains
  msv::string_view myView("Hello, World!");

  // check if the string contains the character 'o'
  bool containsO = myView.contains('o');
  std::cout << containsO << std::endl;

  // check if the string contains the character 'x'
  bool containsX = myView.contains('x');
  std::cout << containsX << std::endl;

  msv::my_string_view strView("    hello world    ");
  std::cout << "original string: " << strView.data() << "" << std::endl;
  //strip method
  msv::my_string_view stripString = strView.strip();
  std::cout << "stripped string: " << stripString.data() << "" << std::endl;
  //reverse iterator
  msv::string_view svRev("Hello");
  std::cout << "Original string view: " << svRev.data() << std::endl;
  std::cout << "Reversed string view: ";
  for (auto it = svRev.rbegin(); it != svRev.rend(); ++it) {
    std::cout << *it;
  }

  return 0;
}
