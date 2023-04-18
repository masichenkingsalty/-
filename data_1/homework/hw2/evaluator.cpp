#include"../../stack/stack.h"
#include<map>
#include<iostream>
#include<cmath>
using namespace std;
map <char, int> myoptr;
int flag=1;
int maxn=10000;
#define N_OPTR 20 //运算符总数
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
    /*              |-------------------- 当 前 运 算 符 --------------------| */
    /*              +      -      *      /      ^      !      s      c      l      g      (      )     \0 */
    /* --  + */    {'>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* |   - */    {'>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* 栈  * */    {'>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* 顶  / */    {'>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* 运  ^ */    {'>',   '>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* 算  ! */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   s */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   c */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   l */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   g */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* 符  ( */    {'<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ' },
    /* |   ) */    {' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ' },
    /* -- \0 */    {'<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '=' }

};

//判断是否为数字 
bool isdigit(char c) {
    if (c <= '9' && c >= '0')
        return true;
    else return false;
}


//加减乘除等的二元计算 
double calcu(double number1, char c, double number2)
{
    double result = 0;
    switch (c) {
    case '+': result = number1 + number2; break;
    case '-': result = number1 - number2; break;
    case '*': result = number1 * number2; break;
    case '/': if (number2 == 0) { cout << "错误输入" << endl; exit(-1); } result = number1 / number2; break;
    case '^': result = pow(number1, number2); break;
    default: cout << "错误输入" << endl; exit(-1);
    }
    return result;
}



//阶乘取对数等的一元计算 
double calcu(char c, double number)
{
    double result = 0;
    switch (c) {
    case '!':
        if (number != int(number)) {
            cout << "错误输入" << endl;
            exit(-1);
        }
        else {
            result = 1;
            int n = result;
            for (int i = 2; i <= number; i++) {
                result = result * i;
            }
        } break;
    case 's': result = sin(number); break;

    case 'c': result = cos(number); break;

    case 'l': result = log(number); break;

    case 'g': result = log10(number); break;

    default: exit(-1);
    }


    return result;
}



//读取数据 
void readNumber(char*& S, Stack<double>& opnd)
{
    int cnt = 1;
    int temp;
    int xiaocnt = 0;
    double result;
    double xiao = 0;
    temp = (*S) - '0';
    result = temp * 1.0;
    S++;
    while (isdigit(*S)) {
        temp = *S - '0';
        result = result * 10 + temp * 1.0;
        S++;
        cnt++;
    }
    if (*S == '.') //小数读取  
    {
        cnt++;
        S++;
        while (isdigit(*S)) {
            xiaocnt++;
            temp = *S - '0';
            xiao = xiao * 10 + temp * 1.0;
            S++;
            cnt++;
        }
    }
    result = result + xiao * 1.0 / pow(10, xiaocnt);
    opnd.push(result);
}
char priority(char optr1, char optr2)
{
    int x1 = myoptr[optr1], x2 = myoptr[optr2];
    return pri[x1][x2];
}

double evaluate(char* S) { //对（已剔除白空格的）表达式 S 求值  
    Stack<double> opnd; Stack<char> optr; //运算数栈、运算符栈  
    optr.push('\0'); //尾哨兵'\0'也作为头哨兵首先入栈 
    while (!optr.empty()) { //在运算符栈非空之前，逐个处理表达式中各字符 
        if (isdigit(*S)) { //若当前字符为操作数，则  

            readNumber(S, opnd);  //读入操作数  

        }
        else //若当前字符为运算符，则  

            switch (priority(optr.top(), *S)) { //视其与栈顶运算符之间优先级高低分别处理 
            case '<': //栈顶运算符优先级更低时 
                optr.push(*S); S++; //计算推迟，当前运算符进栈 
                break;
            case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时 
                optr.pop(); S++; //脱括号并接收下一个字符 
                break;
            case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈 
                if (optr.top() == '(')
                {
                    optr.push(*S);
                    S++;
                }
                else {
                    char op = optr.pop();  //栈顶运算符出栈并续接至RPN末尾  
                    if ('!' == op || 's' == op || 'l' == op || 'g' == op || 'c' == op) //若属于一元运算符 
                        opnd.push(calcu(op, opnd.pop())); //则取一个操作数，计算结果入栈 

                    else
                    { //对于其它（二元）运算符 
                        double opnd2 = opnd.pop(), opnd1 = opnd.pop(); //取出后、前操作数
                        opnd.push(calcu(opnd1, op, opnd2)); //实施二元计算，结果入栈
                    }
                }
            }
                    break;
            default: cout << "错误输入" << endl; exit(-1); //逢语法错误，不做处理直接退出
            }//switch
    }//while
    return opnd.pop(); //弹出并返回最后的计算结果
}




int main()
{
    
    // 给 myoptr 赋值 
    myoptr.insert(pair<char, int>('+', 0));
    myoptr.insert(pair<char, int>('-', 1));
    myoptr.insert(pair<char, int>('*', 2));
    myoptr.insert(pair<char, int>('/', 3));
    myoptr.insert(pair<char, int>('^', 4));
    myoptr.insert(pair<char, int>('!', 5));
    myoptr.insert(pair<char, int>('s', 6));
    myoptr.insert(pair<char, int>('c', 7));
    myoptr.insert(pair<char, int>('l', 8));
    myoptr.insert(pair<char, int>('g', 9));
    myoptr.insert(pair<char, int>('(', 10));
    myoptr.insert(pair<char, int>(')', 11));
    myoptr.insert(pair<char, int>('\0', 12));

    char S[maxn];
    cout<<"数学函数替换:"<<endl; 
    cout<<"sin-->s"<<endl;
    cout<<"cos-->c"<<endl;
    cout<<"ln-->l"<<endl;
    cout<<"log10-->g"<<endl;
    cout<<"请输入计算式子:"<<endl; 
    scanf("%s", &S);
    double result = evaluate(S);

    if (flag == 0) {
        cout << "式子无效" << endl;
    }
    else {
        cout << result << endl;
    }
    return 0;
}
