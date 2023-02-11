#pragma once

#include <iostream>
#include <stdlib.h>

namespace sb
{
    #ifdef DEBUG_COMMANDS
        #define LOG_INFO(...)      std::cout<<"\ninfo: "<<##__VA_ARGS__<<'\n'
        #define LOG_WARN(...)      std::cout<<"\nwarning: "<<##__VA_ARGS__<<'\n'
        #define LOG_ERROR(...)     std::cout<<"\nerror: "<<##__VA_ARGS__<<'\n'
    #else
        #define LOG_INFO(...)       
        #define LOG_WARN(...)       
        #define LOG_ERROR(...) 
    #endif
}