#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <climits>

using namespace std;

typedef vector<int>::iterator ITR;

struct BigInt {
  static const int WIDTH = 1;
  static const int BASE = 10;  // 10 ^ WIDTH
  vector<int> digits;

  BigInt() {}
  BigInt(long long num) { *this=num; }
  BigInt(const string &str) { *this=str; }

  BigInt operator = (long long num) {
    digits.clear();
    do {
      digits.push_back(num % BASE);
      num /= BASE;
    } while (num>0);
    return *this;
  }

  BigInt operator = (const string &numstr) {
    digits.clear();
    int digitCount = numstr.size()/WIDTH;
    digits.reserve(digitCount);
    for(int s=digitCount-1; s>=0; s--) {
      digits.push_back(numstr[s]-'0');
    }
    return *this;
  }

  void clear() {
    digits.clear();
  }

  int placeCount() const {
    return digits.size();
  }

  int getIntAt(unsigned pos) const {
    return pos >= digits.size() ? 0 : digits[pos];
  }

  void putIntAt(unsigned pos, int v) {
    for(int i=placeCount(); i <= pos; i++) {
      digits.push_back(0);
    }
    unsigned prevPos = pos + 1;
    if (v >= 0) {
      digits[pos] = v % BASE;
      if (int carry = v / BASE > 0) {
        putIntAt(prevPos, carry + getIntAt(prevPos));
      }
    } else {
      int borrowed = ((-1 * v) - 1) / BASE + 1;
      digits[pos] = v + borrowed * BASE;
      putIntAt(prevPos, getIntAt(prevPos) - borrowed);
    }
  }

  BigInt negtive() const {
    BigInt result;
    for(int i=0; i < placeCount(); i++) {
      result.digits.push_back(getIntAt(i) * -1);
    }
    return result;
  }

  BigInt operator + (const BigInt &other) {
    BigInt result;
    for(int i = 0; i < max(digits.size(), other.digits.size()); i++) {
      result.putIntAt(i, getIntAt(i) + other.getIntAt(i) + result.getIntAt(i));
    }
    return result;
  }

  BigInt operator += (const BigInt &other) {
    *this = *this + other;
    return *this;
  }

  BigInt operator - (const BigInt &other) {
    return *this + other.negtive();
  }

  BigInt operator * (const BigInt &other) {
    BigInt result;
    for(int j = 0; j < other.placeCount(); j++) {
      BigInt placeResult;
      for (int i = 0; i < placeCount(); i++) {
        BigInt stepResult;
        stepResult.putIntAt(i + j, (getIntAt(i) * other.getIntAt(j)));
        placeResult += stepResult;
      }
      result += placeResult;
    }
    return result;
  }

  BigInt& removeLeadingZeros() {
    for(vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); it++) {
      if(*it==0) digits.pop_back();
      else break;
    }
    return *this;
  }

  bool isZero() const {
    for(int i = 0; i < placeCount(); i++) {
      if(getIntAt(i) != 0) return false;
    }
    return true;
  }

  bool operator < (const BigInt &other) const {
    if(placeCount()!=other.placeCount()) return placeCount()<other.placeCount();
    for(int i=0; i < placeCount(); i++) {
      if(getIntAt(i) != other.getIntAt(i)) return getIntAt(i) < other.getIntAt(i);
    }
    return false; // equal
  }

  bool operator > (const BigInt &other) const {
    return other < *this;
  }

  bool operator == (const BigInt &other) const {
    if(isZero() && other.isZero()) return true;
    return !(other < *this) && !(*this < other);
  }

  const string toString() const {
    string result="";
    bool nonLeadingZero = false;
    for(int i = placeCount()-1; i >= 0; i--) {
      int v = getIntAt(i);
      if( v!=0 ) {
        nonLeadingZero = true;
        result += to_string(v);
      } else {
        if(nonLeadingZero) result += '0'; // '0' * WIDTH
      }
    }
    if(result.empty()) result = "0";
    return result;
  }

};

ostream& operator << (ostream& out, const BigInt& x) {
  out << x.toString();
  return out;
}

istream& operator >> (istream& ins, BigInt& x) {
  string s;
  if( ! (ins >> s) ) return ins;
  x = s;
  return ins;
}

void test() {

  BigInt i("12345");
  assert(i.getIntAt(2)==3);
  i.putIntAt(5, 6);
  assert(i.toString()=="612345");
  i.putIntAt(8, 6);
  assert(i.toString()=="600612345");
  i.putIntAt(8, 12);
  assert(i.toString()=="1200612345");

  assert(BigInt("000") == BigInt("0"));

  i = "999";
  i.putIntAt(0, 10);
  assert(i.toString()=="1000");

  i = "1000";
  i.putIntAt(0, -1);
  assert(i.toString()=="999");

  i = "999";
  i.putIntAt(0, -10);
  assert(i.toString() == "980");

  assert(BigInt("2") + BigInt("18") == BigInt("20"));
  assert(BigInt("9") + BigInt("9")== BigInt("18"));
  assert(BigInt("123") + BigInt("456") == BigInt("579"));
  assert(BigInt("60") + BigInt("480") == BigInt("540"));

  assert(BigInt("456") - BigInt("123") == BigInt("333"));


  assert(BigInt("1") * BigInt("0") == BigInt("0"));
  assert(BigInt("1") * BigInt("1") == BigInt("1"));
  assert(BigInt("10") * BigInt("2") == BigInt("20"));
  assert(BigInt("100") * BigInt("0") == BigInt("0"));
  assert(BigInt("1") * BigInt("10") == BigInt("10"));
  assert(BigInt("123") * BigInt("11") == BigInt("1353"));
  assert(BigInt("12") * BigInt("9") == BigInt("108"));
  assert(BigInt("12") * BigInt("45") == BigInt("540"));
  assert(BigInt("123") * BigInt("456") == BigInt("56088"));

  cout << "all pass" << endl;
}

int main() {
  test();
  return 0;
}
