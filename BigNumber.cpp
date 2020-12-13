#include <iostream>
#include <vector>
#include <string.h>
#include <tuple>
#include <algorithm>
#include <sstream>

class Calculator{
public:
	static int function;
	static std::string InputA;
	static std::string InputB;
	static std::string OutputC;
	static void Computing();
	static void Work();
	static void Print();
	static std::vector<char> Str2Vec(std::string String);
	static std::vector<char> Complement(std::vector<char> Vector);
	static std::tuple<std::vector<char>,std::vector<char>> Align(
		std::vector<char> Vector0,
		std::vector<char> Vector1);
	static std::vector<char> ADDER();
	static std::vector<char> SUB();
	static std::vector<char> MUL();
};

class Adder{
public:
	std::tuple<char,char> ADDER_Unit(char A,char B,char Cin);
	std::tuple<std::vector<char>,char> ADDER(
		char Cin,
		std::vector<char> Input0,
		std::vector<char> Input1);
};

class Multiplexer : public Adder{
public:
	std::tuple<char,char> MUL_Unit(char A,char B,char Cin);
	std::vector<char> Multiplexer_OneDigit(
		std::vector<char> Input0,
		char Input1);
};

int Calculator::function=0;
std::string Calculator::InputA="";
std::string Calculator::InputB="";
std::string Calculator::OutputC="";

int main(){
	Calculator::Work();
	return 0;
}

void Calculator::Work(){
	while(1){
		std::cout << "Please choose the function\n";
		std::cout << "1 Addition\n";
		std::cout << "2 Subtraction\n";
		std::cout << "3 Multiplication\n";
		std::cout << "0 Exit\n";
		std::cin >> function;
		switch(function){
			case 0:{
				std::cout << "Good bye!\n";
				return;
			}
			case 1: case 2: case 3:
				break;
			default:{
				std::cout << "Error! Please try again.\n";
				continue;
			}
		}
		std::cout << "Enter the Number\n";
		std::cout << "a=";
		std::cin >> InputA;
		std::cout << "b=";
		std::cin >> InputB;
		Calculator::Computing();
		std::cout << "Result=";
		std::cout << OutputC << std::endl;
	}
	return;
}

void Calculator::Computing(){
	std::vector<char> v;
	std::ostringstream out;
	switch(function){
		case 1:{
			v=Calculator::ADDER();
			break;
		}
		case 2:{
			v=Calculator::SUB();
			break;
		}
		case 3:{
			v=Calculator::MUL();
			break;
		}
		default:
			break;
		}
    for (char c: v) {
        out << c;
    }
    OutputC=out.str();
	return;
}

std::vector<char> Calculator::ADDER(){
	Adder A;
	std::vector<char> S;
	std::vector<char> InputA_;
	std::vector<char> InputB_;
	char Cout;
	S.clear();
	std::tie(InputA_,InputB_)=Calculator::Align(
		Calculator::Str2Vec(InputA),
		Calculator::Str2Vec(InputB));
	std::tie(S,Cout)=A.ADDER(
		'0',
		InputA_,
		InputB_);
	if(Cout!=0)
		S.push_back(Cout);
	std::reverse(S.begin(),S.end());
	return S;
}

std::vector<char> Calculator::SUB(){
	Adder A;
	std::vector<char> S;
	std::vector<char> InputA_;
	std::vector<char> InputB_;
	char Cout;
	S.clear();
	InputA_.clear();
	InputB_.clear();
	std::tie(InputA_,InputB_)=Calculator::Align(
		Calculator::Str2Vec(InputA),
		Calculator::Str2Vec(InputB));
	std::tie(S,Cout)=A.ADDER(
		'1',
		InputA_,
		Calculator::Complement(InputB_)
		);
	if(Cout=='0'){
		std::vector<char> One(S.size(),'0');
		S=Calculator::Complement(S);
		std::tie(S,Cout)=A.ADDER('1',S,One);
		Cout='-';
		S.push_back(Cout);
	}
	std::reverse(S.begin(),S.end());
	return S;
}

std::vector<char> Calculator::MUL(){
	Multiplexer m;
	std::vector<char> Sum;
	std::vector<char> v;
	std::vector<char> Input0=Calculator::Str2Vec(InputA);
	std::vector<char> Input1=Calculator::Str2Vec(InputB);
	v.clear();
	Sum.clear();
	char Cout;
	for(size_t i=0;i<Input1.size();i++){
		std::vector<char> Temp;
		Temp.clear();
		for(size_t j=0;j<i;j++)
			Temp.push_back('0');
		v=m.Multiplexer_OneDigit(
			Input0,
			Input1[i]);
		std::copy(
			v.begin(),
			v.end(),
			back_inserter(Temp));
		std::tie(Sum,Temp)=Calculator::Align(
			Sum,
			Temp);
		std::tie(Sum,Cout)=m.ADDER(
		'0',
		Sum,
		Temp);
		if(Cout!='0')
			Sum.push_back(Cout);
	}
	std::reverse(Sum.begin(),Sum.end());
	return Sum;
}

std::vector<char> Calculator::Complement(std::vector<char> Vector){
	std::vector<char> Result;
	Result.clear();
	for(size_t i=0;i<Vector.size();i++){
		Result.push_back((9-(Vector[i]-'0'))+'0');
	}
	return Result;
}

std::vector<char> Calculator::Str2Vec(std::string String){
	std::vector<char> v(String.rbegin(),String.rend());
	return v;
}

std::tuple<std::vector<char>,std::vector<char>> Calculator::Align(
		std::vector<char> Vector0,
		std::vector<char> Vector1){
	int diff=0;
	if(Vector0.size()>=Vector1.size()){
		diff=Vector0.size()-Vector1.size();
		for(size_t i=0;i<diff;i++){
			Vector1.push_back('0');
		}
	}else{
		diff=Vector1.size()-Vector0.size();
		for(size_t i=0;i<diff;i++){
			Vector0.push_back('0');
		}
	}
	return std::make_tuple(Vector0,Vector1);
}

std::tuple<char,char> Adder::ADDER_Unit(char A,char B,char Cin){
	return std::make_tuple((((A-'0')+(B-'0')+(Cin-'0'))/10)+'0',
		(((A-'0')+(B-'0')+(Cin-'0'))%10)+'0');
}

std::tuple<std::vector<char>,char> Adder::ADDER(
		char Cin,
		std::vector<char> Input0,
		std::vector<char> Input1){
	char C=Cin;
	char Cout;
	char S;
	std::vector<char> Output;
	Output.clear();
	if(Input0.size()!=Input1.size())
		std::cout << "error!\n";
	for(size_t i=0;i<std::max(Input0.size(),Input1.size());i++){
		std::tie(C,S)=ADDER_Unit(Input0[i],Input1[i],C);
		Output.push_back(S);
	}
	Cout=C;
	return std::make_tuple(Output,Cout);
}

std::tuple<char,char> Multiplexer::MUL_Unit(char A,char B,char Cin){
	return std::make_tuple((((A-'0')*(B-'0')+(Cin-'0'))/10)+'0',
		(((A-'0')*(B-'0')+(Cin-'0'))%10)+'0');
}

std::vector<char> Multiplexer::Multiplexer_OneDigit(
	std::vector<char> Input0,
	char Input1){
	std::vector<char> Output;
	Output.clear();
	char Cin='0';
	char S;
	for(size_t i=0;i<Input0.size();i++){
		std::tie(Cin,S)=MUL_Unit(Input0[i],Input1,Cin);
		Output.push_back(S);
	}
	if(Cin!='0')
		Output.push_back(Cin);
	return Output;
}