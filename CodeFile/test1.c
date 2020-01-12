//
// Created by HkingAuditore on 2019/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//读取单个字符
int ReadSingleChar(char *_input) {
    scanf("%c", _input);
//	 //输入字符是否为数字
    if ((*_input - '0') >= 0 && (*_input - '0') <= 9) {
        return 0;
    } else {
        if (((*_input == '(') || (*_input == ')'))) {
            return 1;
        } else {
            if ((*_input == '+') || (*_input == '-') || (*_input == '*') || (*_input == '/')) {
                return 2;
            } else {
                if (*_input == '\n') {
                    return 3;
                }
            }
        }
    }
    return 4;
}

//连接多个字符
int ReadChar2Action(Stack *_stack) {
    char input;
    int judge = ReadSingleChar(&input);
    switch (judge) {
        case 0:
            return (input - '0');
        case 1:
            if(input == '('){
                Push(_stack, -1);
                return -1;
            }else{
                Push(_stack,-2);
                return -1;
            }

        case 2:
            Push(_stack, input);
//            printf("2--*--IN:%d\n",input);
            return -2;
        default:
            return -3;
    }
}





int Add(int _a,int _b){
    printf("\n%d + %d = %d\n",_a,_b,_a+_b);
    return _a+_b;
}
int Minus(int _a,int _b){
    printf("\n%d - %d = %d\n",_a,_b,_a-_b);
    return _a-_b;
}
int Multiply(int _a,int _b){
    printf("\n%d * %d = %d\n",_a,_b,_a*_b);
    return _a*_b;
}
int Divide(int _a,int _b){
    printf("\n%d / %d = %d\n",_a,_b,_a/_b);
    return _a/_b;
}
int Calculator(int _a,int _b,int _func){
    switch (_func){
        case '+':
            return Add(_a,_b);
        case '-':
            return Minus(_a,_b);
        case '*':
            return Multiply(_a,_b);
        case '/':
            return Divide(_a,_b);
        default:
            return -1;
    }

}

//去掉所有乘号
void GetNonBracketMultiplyResult(Stack* _stack){
    Stack* tempSaver = (Stack*)malloc(sizeof(Stack));
    GenerateStack(tempSaver);
    while (!IsEmptyStack(*_stack)){
        int temp = Pop(_stack);
        if((temp == '*')||(temp == '/')){
            int tempNext = Pop(_stack);
            int tempResult = Calculator(Pop(tempSaver),tempNext,temp);
            Push(tempSaver,tempResult);
//            printf("\n Get temp result:%d\n",tempResult);
            continue;
        }
        Push(tempSaver,temp);
    }
//    把tempSaver给回去，这里变回顺序
//    free(_stack);
    *_stack = *tempSaver;
}

//合并加减结果
int GetNonBracketResult(Stack* _stack){
//    把乘除号算出来，这里变回顺序
    GetNonBracketMultiplyResult(_stack);
    Stack* tempSaver = (Stack*)malloc(sizeof(Stack));
    GenerateStack(tempSaver);
    int temp = 0;
    while (!IsEmptyStack(*_stack)){
        temp = Pop(_stack);
//        printf("   now pop a %d\n",temp);
//        printf("\n   temp = %d\n",temp);
        if((temp == '+')||(temp == '-')){
            int tempNext = Pop(_stack);
            Push(tempSaver,Calculator(tempNext,Pop(tempSaver),temp));
            continue;
        }
        Push(tempSaver,temp);
    }
//    printf("\n GETRESULT : Sum a %d\n",temp);
    return Pop(tempSaver);
}

int GetBracketResult(Stack* _stack){
    Stack tempSaver;
    GenerateStack(&tempSaver);
    int temp;
//    处理嵌套括号,把括号里的结果放入一个新的栈，保证新栈内不存在任何括号
    while ((temp = Pop(_stack)) != -1){
        if(temp == -2){
            Push(&tempSaver,GetBracketResult(_stack));
            continue;
        }
        Push(&tempSaver,temp);
    }
//    计算新栈中的结果(逆序）
    return GetNonBracketResult(&tempSaver);
}
//读取
int Read(Stack *_stack) {
    char read;
    int tempNum = 0;
    while ((read = ReadChar2Action(_stack)) != -3) {
        if (read >= 0) {
            tempNum = 10 * tempNum + read;
        } else {
            if (tempNum) {
                int temp = Pop(_stack);
                Push(_stack, tempNum);
                Push(_stack, temp);
            }
//            printf("IN:%d\n",tempNum);
            tempNum = 0;
        }
    }
    if (tempNum)
        Push(_stack, tempNum);
    return 0;
}
//输出
int WriteDefault(Stack *_stack) {
    while (!IsEmptyStack(*_stack)) {
        printf("%d ", Pop(_stack));
    }
}

int GetResult(Stack *_stack){
    Stack tempSaver;
    GenerateStack(&tempSaver);
    int temp;
//    printf("OUTSIDE!\n");
    while (!IsEmptyStack(*_stack)){
//        printf("IN!\n");
        temp = Pop(_stack);
        if((temp == -2)||(temp == -1)){
            Push(&tempSaver,GetBracketResult(_stack));
            continue;
        }
        Push(&tempSaver,temp);
    }
//    WriteDefault(&tempSaver);
   return GetNonBracketResult(&tempSaver);
}
int main() {
    Stack saver;
    GenerateStack(&saver);
    printf("Input it\n");
    Read(&saver);
//    WriteDefault(&saver);
    printf("\nresult is :%d\n", GetResult(&saver));
//     getchar();
}