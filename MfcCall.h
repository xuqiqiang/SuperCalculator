#ifndef MFC_CALL_H
#define MFC_CALL_H

#include "Calculator.h"

typedef CString Operator;

status show_data(Data d, CString &str);

status check_error(Data d);



char* CString2char(CString data);

void calculate(CString data1, Operator op, CString data2, CString &result, int point);


#endif