#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

constexpr size_t MAXN = 128;
class HugeInteger {
private:
	char digits[MAXN];//˼·��������洢���֣�����ĳ���ΪMAXN�������ÿ��Ԫ�ر�ʾһ��ʮ����λ
	//����ĵ�һ��Ԫ��digits[0]��ʾ���λ����������һ��Ԫ�ر�ʾ���λ
public:
	/*
	* Ĭ�Ϲ��캯��
	* 
	* ���ã���ʼ������digits��ʹ��ȫ��Ԫ��Ϊ0
	* 
	* ��������
	* 
	* ����ֵ����
	*/
	HugeInteger() {
		for (int i = 0; i < MAXN; i++) {
			digits[i] = 0;
		}
	}
	/*
	* ���캯��
	* 
	* ���ã���ʼ������digits��ʹ���ʾ������ַ���
	* 
	* ������
	* 
	* str��������ַ���
	* 
	* ����ֵ����
	*/
	HugeInteger(const char* str):HugeInteger() {//�����this�ڳ�ʼ���б�,����Ĭ�Ϲ��캯��
		string s;
		for (size_t i = 0; str[i]; i++) {
			if (str[i] >= '0' && str[i] <= '9') {//�Ȱ��ַ����е����ִ浽s��
				s.push_back(str[i]);
			}
		}
		reverse(s.begin(), s.end());//��s��ת��ʹ��ӵ�λ����λ
		for (size_t i = 0; i < s.size()&&i<MAXN; i++) {
			digits[i] = s[i] - '0';//��s�е�����ת��Ϊ�����е�����
		}
	}
	/*
	* ���캯��
	* 
	* ���ã���ʼ������digits��ʹ���ʾ������ַ���
	* 
	* ������
	* 
	* str��������ַ���
	* 
	* ����ֵ����
	*/
	HugeInteger(const std::string& str):HugeInteger(str.c_str())
		/*�����this�ڳ�ʼ���б�,����Ĭ�Ϲ��캯��,Ȼ�����const char*,��ί�й��캯��*/ {}

	/*
	* ���캯��
	* 
	* ���ã���ʼ������digits��ʹ���ʾ���������
	* 
	* ������
	* 
	* num�����������
	* 
	* ����ֵ����
	*/
	HugeInteger(long long num):HugeInteger() {
		int i = 0;
		while (num != 0) {
			digits[i] = num % 10;
			num /= 10; i++;
		}
	}

	/*
	* �������캯��
	* 
	* ���ã��������캯�����������
	* 
	* ������
	* 
	* num�������HugeInteger����
	* 
	* ����ֵ����
	*/
	HugeInteger(const HugeInteger& num)=default;

	/*
	* ����[]�����
	* 
	* ���ã���������Ԫ�ص�����
	* 
	* ������
	* 
	* i�������±�
	* 
	* ����ֵ������Ԫ�ص�����
	* 
	* ע�������constexpr��Ϊ�˱������Ż���ʹ�ó�������Ч�ʸ���
	*/
	constexpr char& operator[](size_t i) {
		return digits[i];
	}

	/*
	* ����const[]�����
	* 
	* ���ã���������Ԫ�صĳ�������
	* 
	* ������
	* 
	* i�������±�
	* 
	* ����ֵ������Ԫ�صĳ�������
	* 
	* ע�������constexpr��Ϊ�˱������Ż���ʹ�ó�������Ч�ʸ���
	*/
	constexpr const char& operator[](size_t i) const {
		return digits[i];
	}
	
	/*
	* ����=�����
	* 
	* ���ã���ֵ��������������
	* 
	* ������
	* 
	* num�������HugeInteger����
	* 
	* ����ֵ��HugeInteger����
	*/
	HugeInteger& operator = (const HugeInteger& num)=default;


	/*
	* ����+�����
	* 
	* ���ã��ӷ������
	* 
	* ������
	* 
	* num�������HugeInteger����
	* 
	* ����ֵ��HugeInteger����
	*/
	HugeInteger operator + (const HugeInteger& num) const {
		HugeInteger res;
		for (int i = 0; i < MAXN; i++) {//�Ƚ�ÿһλ���
			res[i] = digits[i] + num[i];
		}
		for (int i = 0; i < MAXN; i++) {//�ٽ���λ���
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
	* ����++�����
	*
	* ���ã�ǰ�üӷ������
	*
	* ������
	*
	* ����ֵ��HugeInteger����
	*
	*/

	HugeInteger& operator++() {
		*this = *this + 1;
		return *this;
	}

	/*
	* ����++�����
	*
	* ���ã����üӷ������
	*
	* ������
	*
	* ����ֵ��HugeInteger����
	*
	*/
	HugeInteger operator++(int) {
		auto res = *this;
		++(*this);
		return res;
	}

	/*
	* ����+=�����
	*
	* ���ã��ӷ���ֵ�����
	*
	* ������
	*
	* num�������HugeInteger����
	*
	* ����ֵ��HugeInteger����
	*/

	HugeInteger& operator+= (const HugeInteger& num) {
		*this = *this + num;
		return *this;
	}
	

	/*
	* ����-�����
	* 
	* ���ã����������
	* 
	* ������
	* 
	* num�������HugeInteger����
	* 
	* ����ֵ��HugeInteger����
	*/
	HugeInteger operator - (const HugeInteger& num) const {
		HugeInteger res;
		for (size_t i = 0; i < MAXN; i++) {//�Ƚ�ÿһλ���
			res[i] = digits[i] - num[i];
		}
		for (size_t i = 0; i < MAXN; i++) {//�ٽ���λ���
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
	* ����--�����
	* 
	* ���ã�ǰ�ü��������
	* 
	* ������
	* 
	* ����ֵ��HugeInteger����
	* 
	*/
	HugeInteger& operator--() {
		*this = *this - 1;
		return *this;
	}

	/*
	* ����--�����
	* 
	* ���ã����ü��������
	* 
	* ������
	* 
	* ����ֵ��HugeInteger��������
	*
	*/
	HugeInteger operator--(int) {
		auto res = *this;
		--(*this);
		return res;
	}

	/*
	* ����-=�����
	* 
	* ���ã�������ֵ�����
	* 
	* ������
	* 
	* num�������HugeInteger����
	* 
	* ����ֵ��HugeInteger��������
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
* ����<<�����
* 
* ���ã���������
* 
* ������
* 
* os�������
* 
* num�������HugeInteger����
* 
* ����ֵ�����������
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