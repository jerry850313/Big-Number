#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <complex>

using namespace std;
typedef complex<double> Z;
const double PI = 3.141592653;

void inputmode(int &mode);
void inputnum(string &a,string &b);
void chosemode(int mode,string a, string b, vector<int> &c);
void addition(string a, string b, vector<int> &c);
void subtraction(string a, string b, vector<int> &c);
void multiplication(string a, string b, vector<int> &c);
void changeform(string a,string b,int *A,int *B);
void FFT(Z *a, int n, int t);
void changeform(string a, string b, Z *A[], Z *B[]);
void bit_reverse_swap(Z *a, int n);

int main(){
    string inputA, inputB;
    vector<int>  outputC,temp;
    int countmode=6;
    int mode = 0;
    while(countmode!=0){
        inputmode(countmode);
        if(countmode!=0){
            chosemode(countmode,inputA, inputB, outputC);
            cout << "Result:";
            temp.assign(outputC.begin(), outputC.end());
            while (!temp.empty()){
            	if(temp.back()==0){
            		mode=1;
				}else{
					mode=0;
				}                	
				temp.pop_back();
            }
            if(mode==0){
            	while (!outputC.empty()){
                	cout << outputC.back();
                	outputC.pop_back();
            		}
				}else{
					cout << 0;
				}
			}
        cout << endl;
        }
    cout << "Good bye!";
    return 0;
}

void chosemode(int mode,string a, string b, vector<int> &c){
    switch(mode){
                case 1:
                    cout << "----Now for Addition----"<<endl;
                    inputnum(a, b);
                    addition(a,b,c);
                    break;
                case 2:
                    cout << "----Now for Subtraction----" << endl;
                    inputnum(a,b);
                    subtraction(a,b,c);
                    break;
                case 3:
                    cout << "----Now for Subtraction----" << endl;
                    inputnum(a,b);
                    multiplication(a,b,c);
                    break;
                default:
                    cout << "Error! Please try again" << endl;
                    break;
            }
}

void inputmode(int &mode){
    cout << "----Welcome to big number calculator----" << endl
         << "Please choose the function" << endl
         << "1.Addition" << endl
         << "2.Subtraction" << endl
         << "3.Multiplication" << endl
         << "0.Exit" << endl
         << "--------------------------" <<endl;
    cin >> mode;
}

void inputnum(string &a,string &b){
    cout << "a= ";
    cin >> a;
    cout << "b=";
    cin >> b;
}

void changeform(string a,string b,int *A,int *B){
    for (int timeA = 0;timeA<a.length();timeA++)
        A[timeA] = a[timeA]-'0';
    for (int timeB = 0;timeB<b.length();timeB++)
        B[timeB] = b[timeB]-'0';
}

void changeform(string a,string b,Z *A,Z *B){
    for (int timeA = 0;timeA<a.length();timeA++)
        A[timeA] = Z(a[timeA] - '0');
    for (int timeB = 0;timeB<b.length();timeB++)
        B[timeB] = Z(b[timeB] - '0');
}

void addition(string a, string b, vector<int> &c){
    int *shark, *bebe;
    int space = max(a.length(), b.length());
    shark = new int[space+1]();
    bebe = new int[space+1]();
    int sum = 0;
    int carry = 0;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    changeform(a, b, shark, bebe);
    for (int time = 0;time<space;time++){
        sum = shark[time] + bebe[time] + carry;
        carry = sum / 10;
        c.push_back(sum % 10);
    }
    delete[] shark;
    delete[] bebe;
}

void subtraction(string a, string b, vector<int> &c){
    int *shark, *bebe;
    int space = max(a.length(), b.length());
    shark = new int[space]();
    bebe = new int[space]();
    int delta = 0;
    int borrow = 0;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    changeform(a, b, shark, bebe);
    for (int time = 0;time<space;time++){
        delta = shark[time] - bebe[time] - borrow;
        if(delta<0){
            delta += 10;
            borrow = 1;
        }else
            borrow = 0;
        c.push_back(delta);
    }
    if(borrow!=0){
        c.push_back(borrow);
    }
    delete[] shark;
    delete[] bebe;
}
void multiplication(string a, string b, vector<int> &c){
    Z *shark, *bebe;
    int *gura;
    int space = a.length() + b.length();
    int num = 1;
    while(num<space){
        num *= 2;
    }
    space = num;
    shark = new Z[space]();
    bebe = new Z[space]();
    gura = new int[space]();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    changeform(a, b, shark, bebe);
    FFT(shark, space, 1);
    FFT(bebe, space, 1);
    for (int i = 0;i<space;++i)
        shark[i] *= bebe[i];
    FFT(shark, space, -1);
    for (int i = 0;i<space;++i){
        gura[i] = (int)(shark[i].real() + 0.5);
    }
    int carry=0;
    int i = 0;
    for (; i < a.length() + b.length()-1; i++){
        gura[i] += carry;
        carry = gura[i] / 10;
        gura[i] %= 10;
        c.push_back(gura[i]);
    }
    if( gura[i]!=0)
        c.push_back(gura[i]);
    delete[] shark;
    delete[] gura;
    delete[] bebe;
}

void FFT(Z* a, int n, int t) {
  bit_reverse_swap(a, n);
  for (int i = 2; i <= n; i <<= 1) {
    Z wi(cos(2.0 * t * PI / i), sin(2.0 * t * PI / i));
    for (int j = 0; j < n; j += i) {
      Z w(1);
      for (int k = j, h = i >> 1; k < j + h; ++k) {
        Z t = w * a[k + h], u = a[k];
        a[k] = u + t;
        a[k + h] = u - t;
        w *= wi;
      }
    }
  }
  if (t == -1) {
    for (int i = 0; i < n; ++i) {
      a[i] /= n;
    }
  }
}

void bit_reverse_swap(Z* a, int n) {
  for (int i = 1, j = n >> 1, k; i < n - 1; ++i) {
    if (i < j) swap(a[i], a[j]);
    for (k = n >> 1; j >= k; j -= k, k >>= 1)
      ;
    j += k;
  }
}
