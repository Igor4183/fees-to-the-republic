#include <bits/stdc++.h>

struct big_integer {
  using digit = uint64_t;
  std::vector<digit> digits;
  bool sign = false;

  big_integer() = default;

  template <class T>
    requires std::convertible_to<T, digit> && std::is_signed_v<T>
  big_integer(T num) {
    sign = num < 0;
    digits.push_back(abs(num));
    this->compact();
  }

  template <class T>
    requires std::convertible_to<T, digit> && std::is_unsigned_v<T>
  big_integer(T num) {
    digits.push_back(num);
    this->compact();
  }

  big_integer &compact() {
    while (!digits.empty() and digits.back() == 0)
      digits.pop_back();
    if (digits.empty())
      sign = false;
    return *this;
  }
};

std::string to_string(const big_integer &num) {
  if (num.digits.empty())
    return "0";
  std::string str = std::to_string(num.digits[0]);
  if (num.sign)
    return "-" + str;
  return str;
}

std::ostream &operator<<(std::ostream &os, const big_integer &num) {
  os << to_string(num);
  return os;
}

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  out << "[";
  for (auto &val : v) {
    out << val << ", ";
  }
  out << "]";
  return out;
}

template <class T, class U>
void RequireEqual(const T &a, const U &b, std::string message = "Not equal") {
  if (a != b) {
    std::ostringstream ss;
    ss << message << ": " << a << " != " << b;
    throw std::runtime_error(ss.str());
  }
  return;
}

void Test(std::string name, std::function<void()> test) {
  try {
    test();
  } catch (std::exception &e) {
    std::cout << "Test " << name << " failed:\n" << e.what() << std::endl;
    return;
  } catch (...) {
    std::cout << "Test " << name << " failed:\n"
              << "Unknown error" << std::endl;
    return;
  }

  std::cout << "Test " << name << " passed" << std::endl;
}

int main() {
  Test("Constructor Default", [] {
    {
      big_integer a;
      RequireEqual(
          to_string(a), "0",
          "to_string of default constructed big_integer should be zero");
    }
  });
  Test("Constructor Int32", [] {
    {
      big_integer a(0);
      RequireEqual(
          to_string(a), "0",
          "to_string of default constructed big_integer should be zero");
      RequireEqual(a.digits, std::vector<big_integer::digit>{},
                   "constructed of zero should has no digits");
    }
    {
      big_integer a(153456);
      RequireEqual(to_string(a), "153456", "Positive");
    }

    {
      big_integer a(-34563);
      RequireEqual(to_string(a), "-34563", "Negative");
    }
  });
  Test("Constructor Int64", [] {
    {
      big_integer a(3456786543245);
      RequireEqual(to_string(a), "3456786543245", "Positive");
    }
    {
      big_integer a(-3456786543245);
      RequireEqual(to_string(a), "-3456786543245", "Negative");
    }
  });
  Test("Constructor Uint64", [] {
    {
      big_integer a(0ull);
      RequireEqual(
          to_string(a), "0",
          "to_string of default constructed big_integer should be zero");
      RequireEqual(a.digits, std::vector<big_integer::digit>{},
                   "constructed of zero should has no digits");
    }
    {
      big_integer a(static_cast<uint64_t>(-1));
      RequireEqual(to_string(a), to_string(static_cast<uint64_t>(-1)),
                   "Should has no '-'");
    }
  });
  Test("Constructor_Char", [] {
    big_integer a('0');
    RequireEqual(to_string(a), "48", "Positive");
  });
  Test("Constructor Floating point", [] {
    {
      big_integer a(0.5);
      RequireEqual(to_string(a), "0", "Positive");
    }

    {
      big_integer a(-12.95);
      RequireEqual(to_string(a), "-12", "Negative");
    }
  });
  Test("Constructor Copy", [] {
    big_integer a(-1337);
    {
      big_integer b(a);
      RequireEqual(to_string(b), to_string(a), "Should copy");
    }
    RequireEqual(to_string(a), "-1337", "Should exist after deletion of copy");
  });
  Test("Operator Copy", [] {
    big_integer a(-1337);
    {
      auto b = a;
      RequireEqual(to_string(b), to_string(a), "Should copy");
    }
    RequireEqual(to_string(a), "-1337", "Should exist after deletion of copy");
  });
  Test("Constructor Move", [] {
    big_integer a(-1337);
    {
      big_integer b(std::move(a));
      RequireEqual(to_string(b), "-1337", "Should move");
      RequireEqual(to_string(a), "0", "Should be moved");
    }
    RequireEqual(to_string(a), "0", "Should still be moved");
  });
  Test("Operator Move", [] {
    big_integer a(-1337);
    {
      big_integer b = std::move(a);
      RequireEqual(to_string(b), "-1337", "Should move");
      RequireEqual(to_string(a), "0", "Should be moved");
    }
    RequireEqual(to_string(a), "0", "Should still be moved");
  });
}