﻿#include "Log.h"
#if defined(WIN32)
#include <windows.h>
#endif
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <string.h>

using namespace std;

LogHook Log::m_gNormalLogHook = nullptr;
LogHook Log::m_gDebugHook = nullptr;
LogHook Log::m_gWarnningHook = nullptr;
LogHook Log::m_gErrHook = nullptr;

std::string Log::GetLogStr(const char * _pLog,va_list *_pVaList)
{
    std::string szLog = "";
    va_list args;
    try {
        va_copy(args,*_pVaList);
        int sLogSize = vsnprintf(nullptr,0,_pLog,args);
        char * pLogTemp = new char[(size_t)(sLogSize + 1)];
        memset(pLogTemp,0,(size_t)(sLogSize+1));
        va_copy(args,*_pVaList);
        vsprintf(pLogTemp,_pLog,args);
        szLog = pLogTemp;
        delete[] pLogTemp;
    } catch (...) {
    }
    return szLog;
}

void Log::Normal(const char* pLog, ...)
{
	va_list args;
	va_start(args, pLog);
    std::string szLog = GetLogStr(pLog,&args);
    printf("%s",szLog.c_str());
    va_end(args);
    if(m_gNormalLogHook != nullptr)
    {
        m_gNormalLogHook(szLog);
    }
}

void Log::Warnning(const char* pLog, ...)
{
    std::string szLog = "";
    va_list args;
    va_start(args, pLog);
#if defined(WIN32)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    szLog = GetLogStr(pLog,&args);
    printf("%s",szLog.c_str());
    va_end(args);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else //if defined(UNIX)
    szLog = GetLogStr(pLog,&args);
    printf("\033[33m%s\033[0m",szLog.c_str());
#endif
    va_end(args);
    if(m_gWarnningHook != nullptr)
    {
        m_gWarnningHook(szLog);
    }
}

void Log::Error(const char* pLog, int iErrcode, ...)
{
    string szLog = "";
    string szError = string("ERROR : ") + string(pLog);
    if(iErrcode != 0)
        szError += string(", Error Code ") + to_string(iErrcode) + string(":") + strerror(iErrcode) + string("\r\n");
    va_list args;
    va_start(args, iErrcode);
#if defined(WIN32)
    //设置红 色字体，并输出
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED );
    szLog = GetLogStr(szError.c_str(),&args);
    printf("%s",szLog.c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else //if defined(UNIX)
    szLog = GetLogStr(szError.c_str(),&args);
    printf("\033[31m%s\033[0m",szLog.c_str());
#endif
    va_end(args);
    if(m_gErrHook != nullptr)
    {
        m_gErrHook(szLog);
    }
}

void Log::Debug(const char* pLog, ...)
{
#if defined(DEBUG)
    std::string szLog = "";
    va_list args;
    va_start(args, pLog);
#if defined(WIN32)
    //设置绿色字体，并输出
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN);
    szLog = GetLogStr(pLog,&args);
    printf("%s",szLog.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else //if defined(UNIX)
    szLog = GetLogStr(pLog,&args);
    printf("\033[32m%s\033[0m",szLog.c_str());
#endif
    va_end(args);
    if(m_gDebugHook != nullptr)
    {
        m_gDebugHook(szLog);
    }
#endif
}
