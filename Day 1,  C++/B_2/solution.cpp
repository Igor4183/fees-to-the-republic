#include <bits/stdc++.h>

struct big_integer {
  using digit = uint64_t;
  std::vector<digit> digits;
  bool sign = false;

  big_integer() = default;

  template <class T>
    requires std::convertible_to<T, digit> && std::is_signed_v<T>
  big_integer(T num) {
    long long val = num;
    if (val < 0) {
      sign = true;
      val *= -1;
    }
    digits.push_back(val);
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

std::strong_ordering operator<=>(const big_integer &a, const big_integer &b) {
  if (a.digits.empty() and b.digits.empty())
    return std::strong_ordering::equal;
  if (a.digits.empty() and !b.digits.empty())
    return (b.sign ? std::strong_ordering::greater
                   : std::strong_ordering::less);
  if (!a.digits.empty() and b.digits.empty())
    return (a.sign ? std::strong_ordering::less
                   : std::strong_ordering::greater);

  if (a.sign ^ b.sign)
    return (a.sign ? std::strong_ordering::less
                   : std::strong_ordering::greater);

  // a.sign == b.sign
  const size_t sz1 = a.digits.size(), sz2 = b.digits.size();
  if (sz1 > sz2)
    return (a.sign ? std::strong_ordering::less
                   : std::strong_ordering::greater);
  if (sz1 < sz2)
    return (a.sign ? std::strong_ordering::greater
                   : std::strong_ordering::less);

  // sz1 == sz2
  for (int i = sz1 - 1; i >= 0; i--) {
    if (a.digits[i] < b.digits[i])
      return (a.sign ? std::strong_ordering::greater
                     : std::strong_ordering::less);
    else if (a.digits[i] > b.digits[i])
      return (a.sign ? std::strong_ordering::less
                     : std::strong_ordering::greater);
  }

  return std::strong_ordering::equal;
}

bool operator==(const big_integer &a, const big_integer &b) {
  return (a <=> b) == std::strong_ordering::equal;
}

std::string to_string(const big_integer &num) {
  if (num.digits.empty())
    return "0";

  std::string str = "";
  for (int i = num.digits.size() - 1; i >= 0; i--)
    str += std::to_string(num.digits[i]);

  if (num.sign)
    return "-" + str;
  return str;
}

std::ostream &operator<<(std::ostream &os, const big_integer &num) {
  os << to_string(num);
  return os;
}

using namespace std;

int main() {
  vector<big_integer> a(2);
  for (int i = 0; i < 2; i++) {
    int sign, n;
    cin >> sign >> n;
    vector<uint64_t> d(n);
    for (int j = n - 1; j >= 0; j--)
      cin >> d[j];
    a[i].sign = sign;
    a[i].digits = d;
  }
  if (a[0] == a[1])
    cout << "equal";
  else if (a[0] < a[1])
    cout << "less";
  else
    cout << "greater";
}