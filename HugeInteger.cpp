#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

constexpr size_t MAXN = 128;
class HugeInteger {
private:
	char digits[MAXN];//思路：用数组存储数字，数组的长度为MAXN，数组的每个元素表示一个十进制位
	//数组的第一个元素digits[0]表示最低位，数组的最后一个元素表示最高位
public:
	/*
	* 默认构造函数
	* 
	* 作用：初始化数组digits，使其全部元素为0
	* 
	* 参数：无
	* 
	* 返回值：无
	*/
	HugeInteger() {
		for (int i = 0; i < MAXN; i++) {
			digits[i] = 0;
		}
	}
	/*
	* 构造函数
	* 
	* 作用：初始化数组digits，使其表示输入的字符串
	* 
	* 参数：
	* 
	* str：输入的字符串
	* 
	* 返回值：无
	*/
	HugeInteger(const char* str):HugeInteger() {//这里的this在初始化列表,调用默认构造函数
		string s;
		for (size_t i = 0; str[i]; i++) {
			if (str[i] >= '0' && str[i] <= '9') {//先把字符串中的数字存到s中
				s.push_back(str[i]);
			}
		}
		reverse(s.begin(), s.end());//将s反转，使其从低位到高位
		for (size_t i = 0; i < s.size()&&i<MAXN; i++) {
			digits[i] = s[i] - '0';//将s中的数字转换为数组中的数字
		}
	}
	/*
	* 构造函数
	* 
	* 作用：初始化数组digits，使其表示输入的字符串
	* 
	* 参数：
	* 
	* str：输入的字符串
	* 
	* 返回值：无
	*/
	HugeInteger(const std::string& str):HugeInteger(str.c_str())
		/*这里的this在初始化列表,调用默认构造函数,然后调用const char*,是委托构造函数*/ {}

	/*
	* 构造函数
	* 
	* 作用：初始化数组digits，使其表示输入的整数
	* 
	* 参数：
	* 
	* num：输入的整数
	* 
	* 返回值：无
	*/
	HugeInteger(long long num):HugeInteger() {
		int i = 0;
		while (num != 0) {
			digits[i] = num % 10;
			num /= 10; i++;
		}
	}

	/*
	* 拷贝构造函数
	* 
	* 作用：拷贝构造函数，用于深拷贝
	* 
	* 参数：
	* 
	* num：输入的HugeInteger对象
	* 
	* 返回值：无
	*/
	HugeInteger(const HugeInteger& num)=default;

	/*
	* 重载[]运算符
	* 
	* 作用：返回数组元素的引用
	* 
	* 参数：
	* 
	* i：数组下标
	* 
	* 返回值：数组元素的引用
	* 
	* 注：这里的constexpr是为了编译器优化，使得程序运行效率更高
	*/
	constexpr char& operator[](size_t i) {
		return digits[i];
	}

	/*
	* 重载const[]运算符
	* 
	* 作用：返回数组元素的常量引用
	* 
	* 参数：
	* 
	* i：数组下标
	* 
	* 返回值：数组元素的常量引用
	* 
	* 注：这里的constexpr是为了编译器优化，使得程序运行效率更高
	*/
	constexpr const char& operator[](size_t i) const {
		return digits[i];
	}
	
	/*
	* 重载=运算符
	* 
	* 作用：赋值运算符，用于深拷贝
	* 
	* 参数：
	* 
	* num：输入的HugeInteger对象
	* 
	* 返回值：HugeInteger对象
	*/
	HugeInteger& operator = (const HugeInteger& num)=default;


	/*
	* 重载+运算符
	* 
	* 作用：加法运算符
	* 
	* 参数：
	* 
	* num：输入的HugeInteger对象
	* 
	* 返回值：HugeInteger对象
	*/
	HugeInteger operator + (const HugeInteger& num) const {
		HugeInteger res;
		for (int i = 0; i < MAXN; i++) {//先将每一位相加
			res[i] = digits[i] + num[i];
		}
		for (int i = 0; i < MAXN; i++) {//再将进位相加
			if (res[i] >= 10) {
				if (i + 1 <= MAXN)
				{
					res[i + 1] += res[i] / 10;
				}
				res[i] %= 10;
			}
		}
		return res;
	}

	/*
	* 重载++运算符
	*
	* 作用：前置加法运算符
	*
	* 参数：
	*
	* 返回值：HugeInteger对象
	*
	*/

	HugeInteger& operator++() {
		*this = *this + 1;
		return *this;
	}

	/*
	* 重载++运算符
	*
	* 作用：后置加法运算符
	*
	* 参数：
	*
	* 返回值：HugeInteger对象
	*
	*/
	HugeInteger operator++(int) {
		auto res = *this;
		++(*this);
		return res;
	}

	/*
	* 重载+=运算符
	*
	* 作用：加法赋值运算符
	*
	* 参数：
	*
	* num：输入的HugeInteger对象
	*
	* 返回值：HugeInteger对象
	*/

	HugeInteger& operator+= (const HugeInteger& num) {
		*this = *this + num;
		return *this;
	}
	

	/*
	* 重载-运算符
	* 
	* 作用：减法运算符
	* 
	* 参数：
	* 
	* num：输入的HugeInteger对象
	* 
	* 返回值：HugeInteger对象
	*/
	HugeInteger operator - (const HugeInteger& num) const {
		HugeInteger res;
		for (size_t i = 0; i < MAXN; i++) {//先将每一位相减
			res[i] = digits[i] - num[i];
		}
		for (size_t i = 0; i < MAXN; i++) {//再将借位相减
			if (res[i] < 0) {
				if (i + 1 <= MAXN) {
					res[i + 1] -= 1;
				}
				res[i] += 10;
			}
		}
		return res;
	}

	/*
	* 重载--运算符
	* 
	* 作用：前置减法运算符
	* 
	* 参数：
	* 
	* 返回值：HugeInteger对象
	* 
	*/
	HugeInteger& operator--() {
		*this = *this - 1;
		return *this;
	}

	/*
	* 重载--运算符
	* 
	* 作用：后置减法运算符
	* 
	* 参数：
	* 
	* 返回值：HugeInteger对象引用
	*
	*/
	HugeInteger operator--(int) {
		auto res = *this;
		--(*this);
		return res;
	}

	/*
	* 重载-=运算符
	* 
	* 作用：减法赋值运算符
	* 
	* 参数：
	* 
	* num：输入的HugeInteger对象
	* 
	* 返回值：HugeInteger对象引用
	* 
	*/
	HugeInteger& operator-= (const HugeInteger& num) {
		*this = *this - num;
		return *this;
	}


	operator std::string() {
		std::string res;
		bool flag = false;
		for (int i = MAXN - 1; i >= 0; i--) {
			if (digits[i] != 0) {
				flag = true;
			}
			if (flag) {
				res.push_back(digits[i] + '0');
			}
		}
		return res;
	}
};
/*
* 重载<<运算符
* 
* 作用：输出运算符
* 
* 参数：
* 
* os：输出流
* 
* num：输入的HugeInteger对象
* 
* 返回值：输出流引用
*/
ostream& operator << (ostream& os, const HugeInteger& num) {
	bool flag = false;
	for (int i = MAXN - 1; i >= 0; i--) {
		if (num[i] != 0) {
			flag = true;
		}
		if (flag) {
			os << int(num[i]);
		}
	}
	
	return flag?os:os<<0;
	
}
int main() {
	HugeInteger a="11451c4";
	cout << a << endl;
	HugeInteger b =1919810;
	cout << b << endl;
	HugeInteger c = a + b;
	cout << c << endl;
	cout<<114514+1919810<<endl;


	HugeInteger d = 999999;
	cout << d << endl;
	d+=2;
	cout << d << endl<<endl;

	HugeInteger e = 1000005;
	cout << e << endl;
	e-=1;
	cout << e << endl<<endl;

	std::string SS = e;
	cout << SS << endl;
	return 0;
}