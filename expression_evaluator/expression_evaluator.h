#include<iostream>
#include<stack>
#include<cstdlib>
#include<string>
#include<vector>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;
// /// 临时性的异常类
// class UnderflowException { };
// class IllegalArgumentException { };
// class ArrayIndexOutOfBoundsException { };
// class IteratorOutOfBoundsException { };
// class IteratorMismatchException { };
// class IteratorUninitializedException { };
class evaluator
{
private:
    string expression;//传入的表达式
    stack<double> numbers;//数字栈
    stack<char> operators;//运算符栈
    string numberstr;//临时变量存单个数字
public:
    evaluator(const string &s): expression(s)
    {
        operators.push('#');
    } //构造函数

    ~evaluator(){}//析构函数

    void empty()//清空evaluator
    {
        expression.clear();
        while (!numbers.empty()) 
        {
            numbers.pop();
        }
        while (!operators.empty()) 
        {
            operators.pop();
        }
        numberstr.clear();
    }

    double operatorvalue(const char &s)//给运算符赋值区分优先级
    {
        switch (s)
        {
            case '(':return 0;
            case '+': case '-': return 1;
            case '*': case '/': return 2;
            case ')':return 3;
            case '#':return -1;//栈底
            default:throw std::invalid_argument("ILLEGAL! ");
        }
    }

    double operate(double a, double b,char s) //做两个数之间的四则运算
    {
        switch (s)
        {
            case '+': return a+b;
            case '-': return b-a;
            case '*': return a*b;
            case '/': 
            {
                if (a == 0) 
                    throw invalid_argument("ILLEGAL! ");
                return b/a;
            }
        }
        throw invalid_argument("ILLEGAL! ");//传入的不是四则运算符，非法
    }

    void function()//执行数字栈顶部2个数字的运算操作
    {
        if (numbers.size() < 2) 
            throw invalid_argument("ILLEGAL! ");
        double a=numbers.top();//栈顶第一个数字
        numbers.pop();
        double b=numbers.top();//栈顶第二个数字
        numbers.pop();
        double result = operate(a,b,operators.top());//运算
        numbers.push(result);//运算结果入栈
        operators.pop();//运算符出栈
    }

    void pushnumbers() //数字入栈
    {
        if(!numberstr.empty())
        {
            double num = stod(numberstr);//stod函数把string类型转换成double
            numbers.push(num);
            numberstr.clear();
        }
    }
    
    void removeSpaces() //移除空格
    {
        expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    }

    double calculate()//计算结果
    {
        removeSpaces();//移除空格
        std::istringstream iss(expression);
        char ch;
        if(expression[0] == '-')//开头是负号
            numbers.push(0);
        while(iss >> ch)
        {   
            if(isdigit(ch) || ch == '.')// 提取数字存放在numberstr中
                numberstr += ch;
            else if(ch == 'e' || ch == 'E')//科学计数法
            {
                numberstr += ch;
                iss >> ch;
                if(isdigit(ch) || (operatorvalue(ch) == 1 && isdigit(iss.peek())))//科学计数法的格式是否正确
                    numberstr += ch;
                else 
                    throw invalid_argument("ILLEGAL! ");
            }
            else//运算符入栈
            {   
                pushnumbers();//数字入栈
                if(ch == ')')//右括号的情况
                {   
                    while(operators.top() != '(')
                    {
                        function();
                    }
                    operators.pop();
                }
                else if(ch == '(')//左括号
                {
                    operators.push(ch);
                    // if(iss.peek() == '-')
                    //     numbers.push(0);
                }
                else if(operatorvalue(ch) > operatorvalue(operators.top()))
                {
                    operators.push(ch);
                }
                else if (operatorvalue(ch) <= operatorvalue(operators.top()))//把优先级高的符号弹出进行运算
                {   
                    do{
                        function();
                    }while(operatorvalue(ch) <= operatorvalue(operators.top()));
                    operators.push(ch);
                }
                if(iss.peek() == '-' && (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '('))//实现负数
                {
                    iss.ignore(1);//跳过负号
                    numberstr += '-';
                }
            }
        }
        pushnumbers();//将表达式末尾的数字入栈
        while(operatorvalue(operators.top()) != -1) //表达式遍历结束，进行最后的运算清空栈
        {
            function();
        }
        if(!numbers.empty()) 
            return numbers.top();
        else
            throw invalid_argument("ILLEGAL! ");
    }
};