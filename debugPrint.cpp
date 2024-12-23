#include "debugPrint.h"

#ifdef debugP
#include <cstdio>
#include <cstring>
//#include "hwversion.h"
#include "ST32Stream.h"
extern Stream &Serial;

void DebPrintData(const char *data, int len, const char *units) {
	//for (int i = 0; i < len; ++i)
	//	Serial.write_ch(data[i]);
	Serial.write_block(data, len);
	DebPrintCStr(units);
}

//void DebPrintStr(const std::string &sVal) {
//    for (size_t i  = 0; i < sVal.size(); i++)
//        Serial.write(sVal[i]);
//}

void DebPrintCStr(const char *sVal) {
	if (sVal == nullptr) return;
	Serial.write_block(sVal, (uint16_t)strlen(sVal));
}

void DebPrintChar(const char ch) {
	Serial.write_ch(ch);
}

void DebPrintInt(const int val) {
	char sVal[20];
	sprintf(sVal, "%d", val);
    DebPrintCStr(sVal);
}

void DebPrintHex8(const uint8_t val) {
	char sVal[20];
	sprintf(sVal, "0x%02X", val);
    DebPrintCStr(sVal);
}

void DebPrintHex16(const uint16_t val) {
	char sVal[20];
	sprintf(sVal, "0x%04X", val);
    DebPrintCStr(sVal);
}

void DebPrintHex32(const uint32_t val) {
	char sVal[20];
	sprintf(sVal, "0x%08X", val);
    DebPrintCStr(sVal);
}

void DebPrintHex64(const uint64_t val) {
	char sVal[20];
	sprintf(sVal, "0x%016X", val);
    DebPrintCStr(sVal);
}

void DebPrintParamChar(const char *nam, const char ch, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
	    DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	Serial.write_ch(ch);
    DebPrintCStr(units);
}

void DebPrintParamStr(const char *nam, const char *sVal, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
	    DebPrintCStr(nam);
        Serial.write_ch('=');
	}
    DebPrintCStr(sVal);
    DebPrintCStr(units);
}
#if 0
void DebPrintParamChar(const std::string &nam, const char ch, const std::string &units) {
	if (nam != "") {
	    DebPrintStr(nam);
        Serial.write('=');
	}
	Serial.write(ch);
    DebPrintStr(units);
}
void DebPrintParamStr(const std::string &nam, const std::string &sVal, const std::string &units) {
	if (nam != "") {
	    DebPrintStr(nam);
        Serial.write('=');
	}
    DebPrintStr(sVal);
    DebPrintStr(units);
}

void DebPrintParamInt(const std::string &nam, const int val, const std::string &units) {
	if (nam != "") {
	    DebPrintStr(nam);
        Serial.write('=');
	}
    std::stringstream ss;
    ss << val;
    std::string sVal = ss.str();
    DebPrintStr(sVal);
    DebPrintStr(units);
};

void DebPrintParamHex(const std::string &nam, const int val, const std::string &units) {
	if (nam != "") {
	    DebPrintStr(nam);
        Serial.write('=');
	}
    std::stringstream ss;
    ss << "0x" << std::hex << val;
    std::string sVal = ss.str();
    DebPrintStr(sVal);
    DebPrintStr(units);
};

#else

void DebPrintParamHex(const char *nam, const int val, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
		DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	char sVal[40];
	sprintf(sVal, "0x%08X", val);
    //std::stringstream ss;
    //ss << "0x" << std::hex << val;
    //std::string sVal = ss.str();
    DebPrintCStr(sVal);
    DebPrintCStr(units);
}

void DebPrintParamHex8(const char *nam, const uint8_t val, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
		DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	char sVal[10];
	sprintf(sVal, "0x%02X", val);
    //std::stringstream ss;
    //ss << "0x" << std::hex << val;
    //std::string sVal = ss.str();
    DebPrintCStr(sVal);
    DebPrintCStr(units);
}

void DebPrintParamHex16(const char *nam, const uint16_t val, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
		DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	char sVal[10];
	sprintf(sVal, "0x%04X", val);
    //std::stringstream ss;
    //ss << "0x" << std::hex << val;
    //std::string sVal = ss.str();
    DebPrintCStr(sVal);
    DebPrintCStr(units);
}

void DebPrintParamInt(const char *nam, const int val, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
		DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	char sVal[40];
	sprintf(sVal, "%d", val);
    //std::stringstream ss;
    //ss << "0x" << std::hex << val;
    //std::string sVal = ss.str();
    DebPrintCStr(sVal);
    DebPrintCStr(units);
};

void DebPrintParamInt64(const char *nam, const long long int val, const char *units) {
	if (nam == nullptr) return;
	if (nam[0] != 0) {
		DebPrintCStr(nam);
        Serial.write_ch('=');
	}
	char sVal[40];
	//sprintf(sVal, "%d%u", val >> 32, val & 0xffffffff);
	sprintf(sVal, "%d", (int)val);
    //std::stringstream ss;
    //ss << "0x" << std::hex << val;
    //std::string sVal = ss.str();
    DebPrintCStr(sVal);
    DebPrintCStr(units);
};

#endif


#endif
