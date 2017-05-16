#ifndef CALULATOR_H
#define CALULATOR_H

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef int status;
#define OK 1;
#define ER 0;

#define L 0;
#define R 1;

typedef int Elemtype;


//enum { ADD, SUB, MUL, DIV};




typedef struct node{ //结点
	Elemtype data;
	node * next;
}node;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct{			//队列
	node * front;
	node * rear;
}Queue;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct{			//栈
	node * front;
	node * rear;
}Stack;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct Binode{ //二叉树的二叉链表
	Elemtype data;
	Binode * lchild;
	Binode * rchild;
}Binode, *Bitree;

//////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct{
	node * value;
	int len;
	int symbol;
	int point;
}Data;						//数


status sub_abs_data(Data d1, Data d2, Data &d3);

status set_point(Data &d);

bool equal_0(Data d);

status new_data(Data &d);

status clear_data(Data &d);



status init_data(Data &d, char *str);

status init_data(Data &d);

status is_float(double n);

status init_data(Data &d, double n);


status set_point(Data &d);

status set_point(Data &d, int n);

status show_data(Data d);

status copy_data(Data d1, Data &d2);
status copy_point_data(Data d1, Data &d2);

status copy_int_data(Data d1, Data &d2);

int is_equal(Data d1, Data d2);


status add_abs_data(Data d1, Data d2, Data &d3);



status add_data(Data d1, Data d2, Data &d3);



status compare_abs_data(Data d1, Data d2, int &e);

status compare_data(Data d1, Data d2, int &e);

status plus_data(Data d1, Data &d2, bool clearHead);

status sub_abs_data(Data d1, Data d2, Data &d3);

status sub_data(Data d1, Data d2, Data &d3);

status mul_nom_abs_node(node *p1, Elemtype nom, node *&p2, Elemtype attach, int &len);

status mul_nom_abs_data(Data d1, Elemtype nom, int exp, Data &d2);

status mul_data_by_order(Data d1, Data d2, Data &d3);

status mul_data(Data d1, Data d2, Data &d3);

status div_total_data(Data d1, Data d2, Data &d3, int point);


status mod_data(Data d1, Data d2, Data &d3);


status exp_data(Data d1, Data d2, Data &d3, int point);


status exp_data1(Data d1, Data d2, Data &d3, int point);


float InvSqrt(float x);

int is_equal1(Data d1, Data d2);
status get_sqrt(Data d1, Data &d2, int point);


status get_pi(Data &d1, int point);


/////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_sort(Elemtype a[], int n);

bool equal_0(Data d);

char* Data2char(Data d);



#endif