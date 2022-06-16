//
// Created by AlexHoring on 2022/6/15.
//

#include "AutomatonLA.h"


AutomatonLA::AutomatonLA() {
    curState = 1;	//1为自动机的起始状态
}
int AutomatonLA::getState() {
    return curState;
}
void AutomatonLA::reset() {
    curState = 1;
}
bool AutomatonLA::machineHalt(char ch) {
    if (curState <= 0) {
        return true;
    }
    //核心步骤：利用状态转移函数类进行自动机状态跳转
    curState = table[curState].getNextState(ch);
    if (curState <= 0) {
        return true;
    } else {
        return false;
    }
}

//几个特殊的字符翻译函数
class TransChar1:public TransChar{
public:
    char operator()(const char ch) const{
        if (isalpha(ch)) {
            return 'A';
        } else if (ch == '0') {
            return '0';
        } else if (isdigit(ch)) {
            return '1';
        } else {
            return ch;
        }
    }
};
class TransChar3:public TransChar{
public:
    char operator()(const char ch) const{
        if (isdigit(ch)) {
            return '0';
        } else if (ch == 'x') {
            return 'X';
        } else {
            return ch;
        }
    }
};
class TransChar5:public TransChar{
public:
    char operator()(const char ch) const{
        if (isdigit(ch)) {
            return '0';
        } else if ((ch >= 'a' && ch <= 'e') || (ch >= 'A' && ch <= 'E')) {
            return 'a';
        } else {
            return ch;
        }
    }
};

//状态转移函数初始化
const array<TransFunc, 23> AutomatonLA::table {
        TransFunc(map<char, int>()),	//0
        TransFunc(map<char, int>{		//1
                {'A',	2},
                {'0',	3},
                {'1',	4},
                {'<',	11},
                {'=',	11},
                {'>',   11},
                {'!',   11},
                {'+',	13},
                {'\'',	15},
                {'\"',	18}
        }, 21, TransChar1()),
        TransFunc(map<char, int>{		//2
                {'A',	2},
                {'0',	2}
        }, -1),
        TransFunc(map<char, int>{		//3
                {'X',	5},
                {'0',	4},
                {'.',	6},
                {'e',	7}
        }, -2, TransChar3()),
        TransFunc(map<char, int>{		//4
                {'0',	4},
                {'.',	6},
                {'e',	7}
        }, -2, TransChar3()),
        TransFunc(map<char, int>{		//5
                {'0',	22},
                {'a',	22}
        }, 0, TransChar5()),
        TransFunc(map<char, int>{		//6
                {'0',	10}
        }),
        TransFunc(map<char, int>{		//7
                {'+',	8},
                {'-',	8},
                {'0',	9}
        }),
        TransFunc(map<char, int>{		//8
                {'0',	9}
        }),
        TransFunc(map<char, int>{		//9
                {'0',	9}
        }, -3),
        TransFunc(map<char, int>{		//10
                {'0',	10},
                {'e',	7}
        }, -3, TransChar3()),
        TransFunc(map<char, int>{		//11
                {'=',	12}
        }, -4),
        TransFunc(map<char, int>(), -4),	//12
        TransFunc(map<char, int>{		//13
                {'+',	14}
        }, -4),
        TransFunc(map<char, int>(), -4),	//14
        TransFunc(map<char, int>(), 16),	//15
        TransFunc(map<char, int>{		//16
                {'\'',	17}
        }),
        TransFunc(map<char, int>(), -5),	//17
        TransFunc(map<char, int>(), 19),	//18
        TransFunc(map<char, int>{		//19
                {'\"',	20}
        }, 19),
        TransFunc(map<char, int>(), -6),	//20
        TransFunc(map<char, int>(), -4),	//21
        TransFunc(map<char, int>{		//22
                {'0',	22},
                {'a',	22},
        }, -2, TransChar5())
};