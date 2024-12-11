#include<iostream>
#include<istream>
#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <cassert>
#include<vector>
#include<math.h>
#include <exception>
#include <cctype>
#include <random>
#include "expression_evaluator.h"
using namespace std;

void check(const string &arr, double assertvalue)//检查运算的正确性
{
    evaluator a(arr);
    const double EPS = 1e-9;//浮点数的精度问题
    assert( abs( a.calculate() - assertvalue ) <= EPS);
    std::cout << arr << "=" << assertvalue << std::endl;
    a.empty();
}

void testException(const string &arr)//测试异常类
{
    evaluator b(arr);
    //处理异常
    try 
    {
        b.calculate();
    } catch (const std::exception& e) 
    {
        std::cerr << arr << " is " << e.what();
    }
}

void checkall()
{   
    check("1+(9/3-1*2)*2", 3);//10以内正整数的四则混合运算
    check("100+(9000/30-10*15)*2", 400);//多位正整数的四则混合运算
    check("2147483647",2147483647);//接近INT_MAX
    check("3.3+(12/2.5-2.3)*1.2", 6.3);//正小数的四则混合运算
    check("1.66665+5.443*2.666",16.177688);//多位小数,double的运算精度问题
    check("-1+(-9/-3--1*-2)*-2", -3);//负数的四则混合运算
    check("-12+(-45/15-1*-12)*-20", -192);
    check("-2147483648",-2147483648);//接近INT_MIN

    check("1--1", 2);//1--1是合法的
    check("-1+1", 0);//以负数开头
    check("2*(-1.25)+-1.2", -3.7);//负小数
    check("-12.6*3.6/(-1.2)+-12.5*-2.4", 67.8);

    check("1+(1+(1+(1+(1))))", 5);//多重括号
    check("-1+(-1+(-1+(-1+(-1))))", -5);

    check("1e2+10", 110);//正数科学计数法
    check("1E+2+10", 110);
    check("3300e-2+1",34);
    check("1e1", 10);
    check("1E-9",1e-9);//测试接近0的数
    check("1e-10+0.01",0.0100000001);//仅支持有限位小数

    check("-1E2+100",0);//负数科学计数法
    check("-1e+2+100",0);
    check("-15e-2+0.75",0.6);
    check("-1e1", -10);

    check(" 1    +    1   ",2);//空格合法
}

void testall()
{
    testException("1+(1+1))");
    std::cout << "右括号不匹配!" << std::endl;//右括号不匹配
    testException("2+((1+1)");//左括号不匹配
    std::cout << "左括号不匹配!" << std::endl;

    testException("1+*1");
    std::cout << "运算符连续使用!" << std::endl;//运算符连续使用
    testException("1-/1");
    std::cout << "运算符连续使用!" << std::endl;
    testException("1*/1");
    std::cout << "运算符连续使用!" << std::endl;

    testException("*1+2");
    std::cout << "表达式以运算符开头!" << std::endl;//表达式以运算符开头
    testException("1+1/");
    std::cout << "表达式以运算符结尾!" << std::endl;//表达式以运算符结尾

    testException("1/0");
    std::cout << "除数是0!" << std::endl;//除数是0
    testException("1++1");
    std::cout << "1++1是不合法的!" << std::endl;//1++1是不合法的

    testException("1e*1");
    std::cout << "错误的科学计数法!" << std::endl;//错误的科学计数法
    testException("1ee1");
    std::cout << "错误的科学计数法!" << std::endl;
    testException("1e+1e");
    std::cout << "错误的科学计数法!" << std::endl; 
}

double generateRandomNumber() //生成随机数
{
    static random_device seed;
    static mt19937 rnd(seed());
    uniform_real_distribution<> range1(-100, 100); //范围为 -100 到 100
    return range1(rnd);
}


char generateRandomOperator() //随机生成运算符
{
    vector<char> ops = {'+', '-', '*', '/'};
    static random_device seed;
    static mt19937 rnd(seed());
    uniform_int_distribution<> range2(0, ops.size() - 1);
    return ops[range2(rnd)];
}


string generateExpression() //随机生成表达式
{   
    static random_device seed;
    static mt19937 rnd(seed());
    uniform_int_distribution<> range3(1,5);//控制循环个数
    uniform_int_distribution<> range4(1,2);//控制是否有括号
    string expression;//表达式
    double randomnumber;//随机数
    int flag=0;//控制括号的临时变量
    for(int i = range3(rnd); i >= 0; --i)
    {
        double randomnumber = generateRandomNumber();//生成随机数
        char operator1 = generateRandomOperator();//生成随机运算符
        expression += to_string(randomnumber) + " " + operator1 + " ";
        if (range4(rnd) % 2 == 0) //随机生成括号
        { 
            expression += "(";
            ++flag;//记录左括号个数
            continue;
        }
        if (flag > 0)//存在左括号
        {
            randomnumber = generateRandomNumber();
            expression += to_string(randomnumber);
            expression += ")";//补上右括号
            operator1 = generateRandomOperator();
            expression += operator1;
            --flag;
        }
    }
    randomnumber = generateRandomNumber();
    expression += to_string(randomnumber);//补上最后的数字
    while(flag > 0)//补上缺少的右括号
    {
        expression += ")";
        --flag;
    }
    return expression;
}

void testRandom()//测试随机生成的数据
{
    string arr;
    for(int i = 0; i < 20; ++i)//生成20个随机表达式
    {
        arr = generateExpression();
        evaluator d(arr);
        try 
        {
            d.calculate();
            std::cout << arr << " = " << d.calculate() << std::endl;
        } catch (const std::exception& e) 
        {
            std::cerr << arr << " is " << e.what() << std::endl;//非法表达式输出ILLEGAL
        }
        d.empty();
        arr.clear();
    }
    
}
int main(){
    std::cout << "输入四则运算表达式得到运算结果，输入test测试测试样例" << std::endl;
    std::cout << "请输入(exit退出）：";
    string arr;//输入的表达式
    getline(std::cin,arr);//读取整行
    while(arr != "exit")//exit退出
    {
        if(arr == "test")//测试
        {
            std::cout << "下面是合法的表达式测试样例：" << std::endl;
            checkall();//合法的表达式测试样例
            std::cout << "下面是非法的表达式测试样例：" << std::endl;
            testall();//非法的表达式测试样例
            std::cout << "下面是随机表达式测试样例：" << std::endl;
            testRandom();//测试随机数据
            std::cout << "测试结束！" << std::endl;
        }
        else
        {
            evaluator c(arr);
            try 
            {
                c.calculate();
                std::cout << arr << " = " << c.calculate() << std::endl;
            } catch (const std::exception& e) 
            {
                std::cerr << e.what() << std::endl;//非法表达式输出ILLEGAL
            }
        }
        std::cout << "请继续输入(exit退出)：";
        getline(std::cin,arr);//读取整行
    }
}