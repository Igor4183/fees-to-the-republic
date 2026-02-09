#include <bits/stdc++.h>

using digit = uint64_t;

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

  friend big_integer operator+(const big_integer &a, const big_integer &b);
  friend big_integer operator-(const big_integer &a, const big_integer &b);

  big_integer &operator+=(const big_integer &b) { return *this = *this + b; }
  big_integer &operator-=(const big_integer &b) { return *this = *this - b; }

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

big_integer add(const big_integer &a, const big_integer &b) {
  __uint128_t rem = 0;
  const size_t sz1 = a.digits.size(), sz2 = b.digits.size();
  std::vector<digit> arr;
  arr.reserve(std::max(sz1, sz2) + 1);
  for (int i = 0; i < std::min(sz1, sz2); i++) {
    rem = rem + a.digits[i] + b.digits[i];
    arr.push_back(rem & std::numeric_limits<digit>::max());
    rem >>= 64;
  }

  for (int i = std::min(sz1, sz2); i < std::max(sz1, sz2); i++) {
    if (i < sz1)
      rem = rem + a.digits[i];
    else
      rem = rem + b.digits[i];

    arr.push_back(rem & std::numeric_limits<digit>::max());
    rem >>= 64;
  }
  if (rem != 0)
    arr.push_back(rem);

  big_integer res;
  res.digits = std::move(arr);
  res.compact();
  return res;
}
big_integer sub(const big_integer &a, const big_integer &b) {
  big_integer ta = a, tb = b;
  bool sign = 0;
  ta.sign = 0;
  tb.sign = 0;
  if (ta < tb) {
    sign = 1;
    std::swap(ta, tb);
  }

  const size_t sz1 = ta.digits.size(), sz2 = tb.digits.size();
  std::vector<digit> arr;
  arr.reserve(sz1);

  unsigned __int128 borrow = 0;
  for (size_t i = 0; i < sz1; i++) {
    unsigned __int128 ai = ta.digits[i];
    unsigned __int128 bi = (i < sz2 ? tb.digits[i] : 0);
    unsigned __int128 tmp = ai;
    unsigned __int128 need = bi + borrow;
    unsigned __int128 diff;
    if (tmp >= need) {
      diff = tmp - need;
      borrow = 0;
    } else {
      diff = ((__uint128_t(1) << 64) + tmp) - need;
      borrow = 1;
    }
    arr.push_back(static_cast<digit>(diff & std::numeric_limits<digit>::max()));
  }

  big_integer res;
  res.digits = std::move(arr);
  res.sign = sign;
  res.compact();
  return res;
}

big_integer operator+(const big_integer &a, const big_integer &b) {
  if (a.digits.empty())
    return b;
  if (b.digits.empty())
    return a;

  if (!a.sign and !b.sign)
    return add(a, b);
  if (a.sign and b.sign) {
    big_integer res = add(a, b);
    res.sign = 1;
    return res;
  }

  if (!a.sign and b.sign)
    return sub(a, b);
  return sub(b, a);
}

big_integer operator-(const big_integer &a, const big_integer &b) {
  if (a.digits.empty()) {
    big_integer res = b;
    res.sign = 1 - b.sign;
    return res;
  }
  if (b.digits.empty())
    return a;

  if (!a.sign and !b.sign)
    return sub(a, b);
  if (a.sign and b.sign)
    return sub(b, a);

  if (!a.sign and b.sign)
    return add(a, b);
  big_integer res = add(a, b);
  res.sign = 1;
  return res;
}

using namespace std;

int main() {
  vector<big_integer> a(2);
  for (int i = 0; i < 2; i++) {
    int sign, n;
    cin >> sign >> n;
    vector<uint64_t> d(n);
    for (int j = 0; j < n; j++)
      cin >> d[j];
    a[i].sign = sign;
    a[i].digits = d;
    a[i].compact();
  }
  char op;
  cin >> op;
  if (op == '-')
    a[1].sign = 1 - a[1].sign;

  big_integer res = a[0] + a[1];
  cout << res.sign << ' ';
  cout << res.digits.size() << ' ';
  for (auto now : res.digits)
    cout << now << ' ';
}