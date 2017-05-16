#include "stdafx.h"
#include "MfcCall.h"
#include<stdlib.h>
#include<string.h>



//status show_node(node *p, CString &str){
//	if (p->next != NULL) show_node(p->next, str);
//	//cout << p->data;
//	CString str_data;
//	str_data.Format(_T("%d"), p->data);
//	str += str_data;
//	return OK;
//}
//
//status show_node(node *p, int point, CString &str){
//	point--;
//	if (p->next != NULL) show_node(p->next, point, str);
//	else{
//		if (point == 0) str += '0';//cout << '0';
//		else if (point>0){
//			//cout << '0' << '.';
//			str += "0.";
//			int i;
//			for (i = 0; i<point; i++)
//				str += '0';
//			//cout << '0';
//		}
//	}
//	if (point == 0) str += '.'; //cout << '.';
//	//cout << p->data;
//	CString str_data;
//	str_data.Format(_T("%d"), p->data);
//	str += str_data;
//	return OK;
//}


char* CString2char(CString data){
	int length = data.GetLength();
	char *ch = (char *)malloc((length+1)*sizeof(char));
	int i;
	for (i = 0; i < length; i++){
		ch[i] = data.GetAt(i);
	}
	ch[i] = '\0';
	return ch;
}

status char2CString(const char *c_str, CString &str){
	str = _T("");
	int len = strlen(c_str);
	int i;
	for (i = 0; i < len; i++){
		str += c_str[i];
	}
	return OK;
}






status show_data(Data d, CString &str){		//显示出来


	char *c_str = Data2char(d);
	if (c_str == NULL){
		str = _T("未定义");
		return ER;
	}
	//str.Format(_T("%s"), "dsd");
	char2CString(c_str, str);

	free(c_str);

	//str = _T("");

	//if (d.symbol == 1)
	//	str += '-';
	//if (d.point == 0)		//是否小数
	//	show_node(d.value->next, str);
	//else
	//	show_node(d.value->next, d.point, str);
	return OK;
}




void fun1(CString &str){
	//str += 'a';
	str = _T("asd");
}
void fun(CString &str){
	Data d1;
	new_data(d1);
	init_data(d1, "-123.4324124432432152355324432432153241234325123432141325324243214123432512345325234");
	show_data(d1, str);
	/*
	CString str1("HockeyBest"), str2=NULL;
	//str1.
	//char a = 'a';
	//CString str4 = "asd";
	CString str3=str2+'a';
	//fun1(str1);
	return str3;*/
}



void calculate(CString data1, Operator op, CString data2, CString &result, int point){

	Data d1, d2, d3;
	new_data(d1);
	new_data(d2);
	new_data(d3);

	char *c_data1 = CString2char(data1);
	char *c_data2 = CString2char(data2);
	init_data(d1, c_data1);
	init_data(d2, c_data2);
	
	if (!((check_error(d1) || op.Compare(_T("根号")) == 0) && check_error(d2))){
		result = _T("输入有误");
		return;
	}
	else{

		if (op.Compare(_T("+")) == 0){
			add_data(d1, d2, d3);
		}
		else if (op.Compare(_T("-")) == 0){
			sub_data(d1, d2, d3);
		}
		else if (op.Compare(_T("*")) == 0){
			mul_data(d1, d2, d3);
		}
		else if (op.Compare(_T("/")) == 0){
			if (equal_0(d2)){
				result = _T("无意义");
				return;
			}
			div_total_data(d1, d2, d3, point);

		}
		else if (op.Compare(_T("exp")) == 0){

			exp_data(d1, d2, d3, point);
			//exp_data1(d1, d2, d3, point);
		}
		else if (op.Compare(_T("%")) == 0){
			//int i;
			//for (i = 0; i < 100000000000;i++)
			if (!mod_data(d1, d2, d3)){
				result = _T("输入有误");
				return;
			}
		}
		else if (op.Compare(_T("根号")) == 0){
			get_sqrt(d2, d3, point);
		}
		else{
			result = _T("输入有误");
			return;
		}
	}

	show_data(d3, result);

	clear_data(d1);
	clear_data(d2);
	clear_data(d3);

	free(c_data1);
	free(c_data2);

}