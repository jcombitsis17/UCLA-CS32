#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

int getPrecedence(char oper);                       // assigns int value based on operator precedence
char evalPostfix(string& postfix);                  // solves the boolean expression (reduces to 'T' or 'F')
char evalAndOr(char one, char two, char oper);      // evaluates '&' and '|' operators
void shortenInfix(string& infix);                   // gets rid of blank spaces in infix string
bool isValid(string infix);                         // checks that # of () match, # operands > # operators
bool validParenth(char c, string infix, int index); // checks for correct implementation/order of ()

int evaluate(string infix, string& postfix, bool& result)
{
    shortenInfix(infix);    // get rid of blanks
    if (!isValid(infix))
        return 1;
    stack<char> charStack;
    string pf = "";
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        switch (c)
        {
            case ' ':   // do nothing for blank space
                break;
            case 'T':   // add to postfix string
            case 'F':
                if (i != 0)
                    if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')')
                        return 1;
                if (i != infix.size() - 1)
                    if (infix[i + 1] != '&' && infix[i + 1] != '|' && infix[i + 1] != ')')
                        return 1;
                pf += c;
                break;
            case '(':   // push onto stack
                if (!validParenth(c, infix, i + 1))
                    return 1;
                charStack.push(c);
                break;
            case ')':   // add everything until '(' to postfix string
                if (!validParenth(c, infix, i - 1))
                    return 1;
                while (charStack.top() != '(')
                {
                    pf += charStack.top();
                    charStack.pop();
                }
                charStack.pop();
                break;
            case '!':
                if (i != 0)
                    if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')')
                        return 1;
                if (i != infix.size() - 1)
                    if (infix[i + 1] == '&' || infix[i + 1] == '|' || infix[i + 1] == ')')
                        return 1;
                while ( !charStack.empty() && charStack.top() != '(' &&
                       getPrecedence(c) <= getPrecedence(charStack.top()) )
                {
                    pf += charStack.top();
                    charStack.pop();
                }
                charStack.push(c);
                break;
            case '&':
            case '|':
                if (i != 0)
                    if (infix[i - 1] == '&' || infix[i - 1] == '|' || infix[i - 1] == '!')
                        return 1;
                if (i != infix.size() - 1)
                    if (infix[i + 1] == '&' || infix[i + 1] == '|')
                        return 1;
                while ( !charStack.empty() && charStack.top() != '(' &&
                        getPrecedence(c) <= getPrecedence(charStack.top()) )
                {
                    pf += charStack.top();
                    charStack.pop();
                }
                charStack.push(c);
                break;
            default:
                return 1;
        }
    }
    
    while (!charStack.empty())
    {
        pf += charStack.top();
        charStack.pop();
    }
    
    postfix = pf;
    
    if (evalPostfix(pf) == 'T')
        result = true;
    else
        result = false;
    
    return 0;
}

int getPrecedence(char oper)
{
    switch (oper)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return -1;
    }
}

char evalPostfix(string& postfix)
{
    stack<char> pfStack;
    char operand1, operand2, result;
    for (int i = 0; i < postfix.size(); i++)
    {
        char c = postfix[i];
        if (c == 'T' || c == 'F')
            pfStack.push(c);
        else
        {
            if (c == '!')       // case for '!'
            {
                operand1 = pfStack.top();
                pfStack.pop();
                if (operand1 == 'T')
                    result = 'F';
                else
                    result = 'T';
            }
            else                // case for '&', '|'
            {
                operand2 = pfStack.top();
                pfStack.pop();
                operand1 = pfStack.top();
                pfStack.pop();
                result = evalAndOr(operand1, operand2, c);
            }
            
            pfStack.push(result);
        }
    }
    return pfStack.top();
}

char evalAndOr(char one, char two, char oper)    // evaluate for & and |
{
    if (oper == '&')
    {
        if (one == 'T' && two == 'T')
            return 'T';
        else
            return 'F';
    }
    
    else    // '|'
    {
        if (one == 'F' && two == 'F')
            return 'F';
        else
            return 'T';
    }
}

void shortenInfix(string& infix)
{
    string temp = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
        {
            temp += infix[i];
        }
    }
    /*string temp2 = "";
    for (int j = 0; j < temp1.size(); j++)
    {
        if (temp1[j] == '!')
        {
            if (temp1[j + 1] == 'T')
                temp2 += 'F';
            if (temp1[j + 1] == 'F')
                temp2 += 'T';
            j++;
        }
        else
        {
            temp2 += temp1[j];
        }
    }*/
    infix = temp;
}

bool validParenth(char c, string infix, int index)
{
    if (c == '(')
    {
        for (int i = index; i < infix.size(); i++)
        {
            if (infix[i] == ')')
                return true;
        }
    }
    else    // ')'
    {
        for (int i = index; i >= 0; i--)
        {
            if (infix[i] == '(')
                return true;
        }
    }
    return false;
}

bool isValid(string infix)
{
    int operandCount = 0;
    int operatorCount = 0;
    int openP = 0;
    int closeP = 0;
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        switch (c)
        {
            case 'T':
            case 'F':
                operandCount++;
                break;
            case '&':
            case '|':
                operatorCount++;
                break;
            case '(':
                openP++;
                break;
            case ')':
                closeP++;
                break;
            default:
                break;
        }
    }
    
    if (operandCount <= operatorCount || openP != closeP || operandCount == 0)
        return false;
    if (operatorCount == 0 && operandCount > 1)
        return false;
    return true;
}

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    
    assert(evaluate(" T & ( F ) ", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("T&!    F", pf, answer) == 0 && pf == "TF!&" && answer);
    assert(evaluate("!((F|(T)))", pf, answer) == 0 && pf == "FT|!" && !answer);
    assert(evaluate("!F|T", pf, answer) == 0 && pf == "F!T|" && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && pf == "TFF&|" && answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0  && pf == "TFTT&|F|!&!!FT&F&!|" && answer);
    cerr << "All tests passed!" << endl;
}
