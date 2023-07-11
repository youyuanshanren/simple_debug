/************************************************************************
 * @copyright
 * **********************************************************************
 * @brief
 * @file    debug_message.h
 * @author  yongliang.wang (youyuanshanren@163.com)
 * @version 0.0.1
 * @date    2023-04-21 17:24
 * **********************************************************************
 * @remarks
 ************************************************************************/
#pragma once

#include <sys/syscall.h>
#include <unistd.h>

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <thread>

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

#ifndef FILE_BASE_NAME_
#    define FILE_BASE_NAME_ \
        (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#endif

enum DebugLevel
{
    Debug_Level_None = 0,  // Level_Emergency no used

    Debug_Level_Fatal,
    Debug_Level_Critica,
    Debug_Level_Error,
    Debug_Level_Warning,
    Debug_Level_Notice,
    Debug_Level_Info,
    Debug_Level_Debug,
    Debug_Level_Trace,

    Debug_Level_All,
};

__attribute__((unused)) static DebugLevel g_debugLevel = Debug_Level_All;

__attribute__((unused)) static const char* GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);

    const size_t buffsize = 32;
    thread_local char buffer[buffsize] = {0};
    strftime(buffer, buffsize, "%F %T", now_tm);

    const uint32_t coefficient = 1000;
    std::chrono::milliseconds ms;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(
             now.time_since_epoch()) %
         coefficient;

    const size_t buffsize2 = 64;
    thread_local char buffer2[buffsize2] = {0};
    snprintf(buffer2, buffsize2, "%s:%03ld", buffer, ms.count());
    return buffer2;
}

#ifndef PROJECT_NAME
#    define PROJECT_NAME "Mid"
#endif

#define SET_LEVEL(v)      \
    do                    \
    {                     \
        g_debugLevel = v; \
    }                     \
    while (0)

#define PRINT_HEAD(color, type)                                                \
    {                                                                          \
        printf(" " color "[%s][" PROJECT_NAME "][" type                        \
               "][%ld][%s:%d][%s]:" RESET,                                     \
               GetTimestamp(), syscall(SYS_gettid), FILE_BASE_NAME_, __LINE__, \
               __FUNCTION__);                                                  \
    }

#define PRINT_BODY(format, ...)             \
    {                                       \
        printf(format "\n", ##__VA_ARGS__); \
    }

#define cCout(s)                \
    {                           \
        std::cout << s << "\n"; \
    }

//===================================================================================
#if defined(NO_MSG)
#    define bFatal(format, ...)
#    define bCritica(format, ...)
#    define bError(format, ...)
#    define bWarning(format, ...)
#    define bNotice(format, ...)
#    define bInfo(format, ...)
#    define bDebug(format, ...)
#    define bTrace(format, ...)
//==============
#    define bTest
//==============
#    define cFatal(s)
#    define cCritica(s)
#    define cError(s)
#    define cWarning(s)
#    define cNotice(s)
#    define cInfo(s)
#    define cDebug(s)
#    define cTrace(s)
//==============
#else
#    define bFatal(format, ...)                                        \
        if (Debug_Level_Fatal <= g_debugLevel)                         \
        {                                                              \
            PRINT_HEAD(BOLDRED, "F") PRINT_BODY(format, ##__VA_ARGS__) \
        }

#    define bCritica(format, ...)                                          \
        if (Debug_Level_Critica <= g_debugLevel)                           \
        {                                                                  \
            PRINT_HEAD(BOLDMAGENTA, "C") PRINT_BODY(format, ##__VA_ARGS__) \
        }

#    define bError(format, ...)                                        \
        if (Debug_Level_Error <= g_debugLevel)                         \
        {                                                              \
            PRINT_HEAD(BOLDRED, "E") PRINT_BODY(format, ##__VA_ARGS__) \
        }

#    define bWarning(format, ...)                                         \
        if (Debug_Level_Warning <= g_debugLevel)                          \
        {                                                                 \
            PRINT_HEAD(BOLDYELLOW, "W") PRINT_BODY(format, ##__VA_ARGS__) \
        }

#    define bNotice(format, ...)                \
        if (Debug_Level_Notice <= g_debugLevel) \
        {                                       \
        }                                       \
        PRINT_HEAD(BOLDBLUE, "N") PRINT_BODY(format, ##__VA_ARGS__)

#    define bInfo(format, ...)                                          \
        if (Debug_Level_Info <= g_debugLevel)                           \
        {                                                               \
            PRINT_HEAD(BOLDBLUE, "I") PRINT_BODY(format, ##__VA_ARGS__) \
        }

#    define bDebug(format, ...)                \
        if (Debug_Level_Debug <= g_debugLevel) \
        {                                      \
        }                                      \
        PRINT_HEAD(BOLDGREEN, "D") PRINT_BODY(format, ##__VA_ARGS__)

#    define bTrace(format, ...)                                     \
        if (Debug_Level_Trace <= g_debugLevel)                      \
        {                                                           \
            PRINT_HEAD(BLUE, "T") PRINT_BODY(format, ##__VA_ARGS__) \
        }

//==============
#    define bTest(format, ...)                 \
        if (Debug_Level_Trace <= g_debugLevel) \
        {                                      \
            PRINT_HEAD(BLUE, "T")              \
        }

//==============
#    define cFatal(s)                          \
        if (Debug_Level_Fatal <= g_debugLevel) \
        {                                      \
            PRINT_HEAD(BOLDRED, "F") cCout(s)  \
        }

#    define cCritica(s)                           \
        if (Debug_Level_Critica <= g_debugLevel)  \
        {                                         \
            PRINT_HEAD(BOLDMAGENTA, "C") cCout(s) \
        }

#    define cError(s)                          \
        if (Debug_Level_Error <= g_debugLevel) \
        {                                      \
            PRINT_HEAD(BOLDRED, "E") cCout(s)  \
        }

#    define cWarning(s)                          \
        if (Debug_Level_Warning <= g_debugLevel) \
        {                                        \
            PRINT_HEAD(BOLDYELLOW, "W") cCout(s) \
        }

#    define cNotice(s)                          \
        if (Debug_Level_Notice <= g_debugLevel) \
        {                                       \
            PRINT_HEAD(BOLDBLUE, "N") cCout(s)  \
        }

#    define cInfo(s)                           \
        if (Debug_Level_Info <= g_debugLevel)  \
        {                                      \
            PRINT_HEAD(BOLDBLUE, "I") cCout(s) \
        }

#    define cDebug(s)                           \
        if (Debug_Level_Debug <= g_debugLevel)  \
        {                                       \
            PRINT_HEAD(BOLDGREEN, "D") cCout(s) \
        }

#    define cTrace(s)                          \
        if (Debug_Level_Trace <= g_debugLevel) \
        {                                      \
            PRINT_HEAD(BLUE, "T") cCout(s)     \
        }

#endif
//===================================================================================
