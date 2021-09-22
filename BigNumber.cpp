#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <complex>

using namespace std;
typedef complex<double> Z;
const double PI(acos(-1.0));

void inputmode(int &mode);
void chosemode(int mode,string a, string b, vector<int> &c);
void addition(string a, string b, vector<int> &c);
void subtraction(string a, string b, vector<int> &c);
void multiplication(string a, string b, vector<int> &c);
void changeform(string a,string b,int *A,int *B);
void changeform(string a, string b, vector<int> *A, vector<int> *B);
void FFT(Z *a, int n, int t);
void changeform(string a, string b, Z A[], Z B[]);

int main(){
    string inputA, inputB;
    vector<int>  outputC;
    int countmode=6;
    while(countmode!=0){
        inputmode(countmode);
        if(countmode!=0){
            switch(countmode){
                case 1:
                    cout << "----Now for Addition----"<<endl;
                        cout << "a= ";
                        cin >> inputA;
                        cout << "b=";
                        cin >> inputB;
                        addition(inputA, inputB, outputC);
                        break;
                case 2:
                    cout << "----Now for Subtraction----" << endl;
                        cout << "a= ";
                        cin >> inputA;
                        cout << "b=";
                        cin >> inputB;
                        subtraction(inputA, inputB, outputC);
                        break;
                case 3:
                    cout << "----Now for Subtraction----" << endl;
                        cout << "a= ";
                        cin >> inputA;
                        cout << "b=";
                        cin >> inputB;
                        multiplication(inputA, inputB, outputC);
                        break;
                default:
                    cout << "Error! Please try again" << endl;
                    break;
            }
            cout << "Result:";
            while (!outputC.empty())
            {
                cout << outputC.back();
                outputC.pop_back();
            }
        cout << endl;
        }
    }
    cout << "Good bye!";
    return 0;
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
    int space = a.length() + b.length() - 1;
    int n = 0;
    int num = pow(2, n);
    while(num<space){
        num = pow(2, n);
        n++;
    }
    if(num>space){
        space = pow(2, n);
    }
    shark = new Z[space]();
    bebe = new Z[space]();
    gura = new int[space]();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    changeform(a, b, shark, bebe);
    FFT(shark, space, 1);
    FFT(bebe, space, 1);
    for (int i = 0;i<space;i++)
        shark[i] *= bebe[i];
    FFT(shark, space, -1);
    for (int i = 0;i<space;++i){
        gura[i] = (int)(shark[i].real() + 0.5);
    }
    for (int i = 0; i < space; ++i){
        gura[i + 1] += gura[i] / 10;
        gura[i] %= 10;
        c.push_back(gura[i]);
    }
    delete[] shark;
    delete[] gura;
    delete[] bebe;
}

void FFT(Z* a, int n, int t) {
  bit_reverse_swap(a, n);
  for (int i = 2; i <= n; i <<= 1) {
    Z wi(cos(2.0 * t * PI / i), sin(2.0 * t *PI / i));
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
