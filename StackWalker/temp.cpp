#include <iostream>
#include <string>
#include "StackWalker.h"

class MyStackWalker : public StackWalker
{
private:
    std::string trace;
    int stack = 0;
protected:
    virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName){}
    virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion){}
    virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr){}
    virtual void OnOutput(LPCSTR szText) {
        if(++stack > 2 ){
            trace.append(szText);
        }
    }

public:
    MyStackWalker() : StackWalker(0) {}
    std::string GetCallStack(){
        stack = 0;
        trace = "";
        ShowCallstack();
        return trace;
    }
};
std::string stacktrace(){
    static MyStackWalker sw;
    return sw.GetCallStack();
}

void f2(){
    std::cout << stacktrace();
}

void f1(){
    f2();
}

int main(int argc, char **argv){
    std::cout << "Stack Trace:\n";
    f1();
    return 1;
}