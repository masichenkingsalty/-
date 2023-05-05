#include"../../stack/stack.h"
#include<map>
#include<iostream>
#include<cmath>
using namespace std;
map <char, int> myoptr;
int flag=1;
int maxn=10000;
#define N_OPTR 20 //���������
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
    /*              |-------------------- �� ǰ �� �� �� --------------------| */
    /*              +      -      *      /      ^      !      s      c      l      g      (      )     \0 */
    /* --  + */    {'>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* |   - */    {'>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* ջ  * */    {'>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* ��  / */    {'>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* ��  ^ */    {'>',   '>',   '>',   '>',   '>',   '<',   '<',   '<',   '<',   '<',   '<',   '>',   '>' },
    /* ��  ! */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   s */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   c */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   l */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* |   g */    {'>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '>',   '<',   '>',   '>' },
    /* ��  ( */    {'<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ' },
    /* |   ) */    {' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ' },
    /* -- \0 */    {'<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '=' }

};

//�ж��Ƿ�Ϊ���� 
bool isdigit(char c) {
    if (c <= '9' && c >= '0')
        return true;
    else return false;
}


//�Ӽ��˳��ȵĶ�Ԫ���� 
double calcu(double number1, char c, double number2)
{
    double result = 0;
    switch (c) {
    case '+': result = number1 + number2; break;
    case '-': result = number1 - number2; break;
    case '*': result = number1 * number2; break;
    case '/': if (number2 == 0) { cout << "��������" << endl; exit(-1); } result = number1 / number2; break;
    case '^': result = pow(number1, number2); break;
    default: cout << "��������" << endl; exit(-1);
    }
    return result;
}



//�׳�ȡ�����ȵ�һԪ���� 
double calcu(char c, double number)
{
    double result = 0;
    switch (c) {
    case '!':
        if (number != int(number)) {
            cout << "��������" << endl;
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



//��ȡ���� 
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
    if (*S == '.') //С����ȡ  
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

double evaluate(char* S) { //�ԣ����޳��׿ո�ģ����ʽ S ��ֵ  
    Stack<double> opnd; Stack<char> optr; //������ջ�������ջ  
    optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ 
    while (!optr.empty()) { //�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ� 
        if (isdigit(*S)) { //����ǰ�ַ�Ϊ����������  

            readNumber(S, opnd);  //���������  

        }
        else //����ǰ�ַ�Ϊ���������  

            switch (priority(optr.top(), *S)) { //������ջ�������֮�����ȼ��ߵͷֱ��� 
            case '<': //ջ����������ȼ�����ʱ 
                optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ 
                break;
            case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ 
                optr.pop(); S++; //�����Ų�������һ���ַ� 
                break;
            case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ 
                if (optr.top() == '(')
                {
                    optr.push(*S);
                    S++;
                }
                else {
                    char op = optr.pop();  //ջ���������ջ��������RPNĩβ  
                    if ('!' == op || 's' == op || 'l' == op || 'g' == op || 'c' == op) //������һԪ����� 
                        opnd.push(calcu(op, opnd.pop())); //��ȡһ������������������ջ 

                    else
                    { //������������Ԫ������� 
                        double opnd2 = opnd.pop(), opnd1 = opnd.pop(); //ȡ����ǰ������
                        opnd.push(calcu(opnd1, op, opnd2)); //ʵʩ��Ԫ���㣬�����ջ
                    }
                }
            }
                    break;
            default: cout << "��������" << endl; exit(-1); //���﷨���󣬲�������ֱ���˳�
            }//switch
    }//while
    return opnd.pop(); //�������������ļ�����
}




int main()
{
    
    // �� myoptr ��ֵ 
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
    cout<<"��ѧ�����滻:"<<endl; 
    cout<<"sin-->s"<<endl;
    cout<<"cos-->c"<<endl;
    cout<<"ln-->l"<<endl;
    cout<<"log10-->g"<<endl;
    cout<<"���������ʽ��:"<<endl; 
    scanf("%s", &S);
    double result = evaluate(S);

    if (flag == 0) {
        cout << "ʽ����Ч" << endl;
    }
    else {
        cout << result << endl;
    }
    return 0;
}
