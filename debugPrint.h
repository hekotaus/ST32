#pragma once
#include <stdint.h>

// if you comment-out this line, serial logging will be removed from the program (see user guide for details)
#define debugP
#ifdef debugP

  #define dbSerial Serial

  void DebPrintData(const char *data, int len, const char *units);
  void DebPrintChar(const char ch);
  void DebPrintInt(const int val);
  void DebPrintHex8(const uint8_t val);
  void DebPrintHex16(const uint16_t val);
  void DebPrintHex32(const uint32_t val);
  void DebPrintHex64(const uint64_t val);
  void DebPrintCStr(const char *sVal);
  //void DebPrintStr(const char *sVal);
#if 1
    void DebPrintParamChar(const char *nam, const char ch, const char *units);
    void DebPrintParamStr(const char *nam, const char *sVal, const char *units);
    void DebPrintParamInt(const char *nam, const int val, const char *units);
    void DebPrintParamInt64(const char *nam, const long long int val, const char *units);
    void DebPrintParamHex(const char *nam, const int val, const char *units);
    void DebPrintParamHex16(const char *nam, const uint16_t val, const char *units);
    void DebPrintParamHex8(const char *nam, const uint8_t val, const char *units);
#else
  void DebPrintParamChar(const std::string &nam, const char ch, const std::string &units);
  void DebPrintParamStr(const std::string &nam, const std::string &sVal, const std::string &units);

  void DebPrintParamInt(const std::string &nam, const int val, const std::string &units);
  void DebPrintParamHex(const std::string &nam, const int val, const std::string &units);
#endif

#else
  #define DebPrint(x) 
  #define DebPrintln(x) 

  #define DebPrintHex(x) 
  #define DebPrintlnHex(x) 

  #define DebPrintBin(x) 
  #define DebPrintlnBin(x)

  #define DebPrintParam(x,y,z)
  #define DebPrintParamHex(x,y,z)

#endif

