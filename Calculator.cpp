#include "stdafx.h"
#include "Calculator.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//队列
status init_Queue(Queue &q){			//初始化
	q.front = (node*)malloc(sizeof(node));
	//q.rear = (node*)malloc(sizeof(node));
	//if (!q.front || !q.rear)return ER;
	if (!q.front)return ER;
	q.front->next = NULL;
	q.rear = q.front;
	return OK;
}

status isempty_Queue(Queue q){			//是否为空
	return q.rear == q.front;
}

status goin_Queue(Queue &q, Elemtype a){			//入队
	node *p = (node*)malloc(sizeof(node));
	if (!p)return ER;
	p->data = a;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
	return OK;
}

status goout_Queue(Queue &q, Elemtype &a){			//出队
	if (q.front == q.rear) return ER;
	node *p = q.front->next;
	q.front->next = p->next;
	if (p == q.rear) q.rear = q.front;
	a = p->data;
	free(p);
	return OK;
}

status free_Queue(Queue &q){			//出队
	if (q.front == q.rear) return ER;
	node *p = q.front->next;
	while (p != NULL){
		q.front->next = p->next;
		if (p == q.rear) q.rear = q.front;
		free(p);
		p = q.front->next;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//栈
status init_Stack(Stack &s){			//初始化
	s.front = (node*)malloc(sizeof(node));
	s.rear = (node*)malloc(sizeof(node));
	if (!s.front || !s.rear)return ER;
	s.front->next = NULL;
	s.rear = s.front;
	return OK;
}

status isempty_Stack(Stack s){			//是否为空
	return s.rear == s.front;
}

status Gettop(Stack s, Elemtype &a){			//站顶元素
	if (s.front == s.rear) return ER;
	a = s.front->next->data;
	return OK;
}

status Push(Stack &s, Elemtype a){		//
	s.front->data = a;
	node *p = (node*)malloc(sizeof(node));
	if (!p)return ER;
	p->next = s.front;
	s.front = p;
	return OK;
}

status Pop(Stack &s, Elemtype &a){			//
	if (s.front == s.rear) return ER;
	node *p = s.front->next;
	s.front->next = p->next;
	if (p == s.rear) s.rear = s.front;
	a = p->data;
	free(p);

	return OK;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//二叉树的二叉链表
status init_Binode(Bitree &t){
	t = (Binode*)malloc(sizeof(Binode));
	if (!t)return ER;
	t->lchild = NULL;
	t->rchild = NULL;
	return OK;
}

status init_Binode(Bitree &t, Elemtype data){
	t = (Binode*)malloc(sizeof(Binode));
	if (!t)return ER;
	t->data = data;
	t->lchild = NULL;
	t->rchild = NULL;
	return OK;
}

status insert_Binode(Binode *n, Elemtype data, int direct){
	Binode* m = (Binode*)malloc(sizeof(Binode));
	if (!m)return ER;
	m->data = data;
	m->lchild = NULL;
	m->rchild = NULL;
	if (direct == 0) n->lchild = m;
	else n->rchild = m;
	return OK;
}

status create_Binode(Bitree &t, Elemtype a[], int len){
	Bitree * b = (Bitree*)malloc((len + 1)*sizeof(Bitree));
	if (!b)return ER;
	int i;
	for (i = 1; i <= len; i++){
		b[i] = (Binode*)malloc(sizeof(Binode));
		if (!b[i])return ER;
	}

	for (i = len; i >= 1; i--){
		if (a[i - 1] != 0){
			b[i]->data = a[i - 1];
			if (2 * i <= len)b[i]->lchild = b[2 * i];
			else b[i]->lchild = NULL;
			if (2 * i + 1 <= len)b[i]->rchild = b[2 * i + 1];
			else b[i]->rchild = NULL;
		}
		else{
			b[i] = NULL;
		}
	}
	t = b[1];

	return OK;
}

int get_height_Binode(Bitree t){
	if (!t) return 0;
	else{
		int hl = get_height_Binode(t->lchild);
		int hr = get_height_Binode(t->rchild);
		if (hl>hr) return hl + 1;
		else return hr + 1;
	}
}

void visit_Binode(Bitree t){
	if (t){
		cout << t->data << ' ';
		visit_Binode(t->lchild);
		visit_Binode(t->rchild);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//test
void Queue_test(){
	Queue q;
	init_Queue(q);

	int i;
	int N;
	Elemtype data;
	cout << "输入要存储的数组长度:";
	cin >> N;

	cout << "输入数组:";
	for (i = 0; i<N; i++){
		cin >> data;
		goin_Queue(q, data);
	}
	cout << "队列的输出结果:";
	while (!isempty_Queue(q)){
		goout_Queue(q, data);
		cout << data << ' ';
	}
	cout << endl;
}

int getpriority(char c, int d){
	if (c == '#') return 0;
	if (d == 0){
		if (c == '(') return 1;
		else if (c == '+' || c == '-') return 3;
		else if (c == '*' || c == '/') return 5;
		else if (c == ')') return 6;
	}
	else{
		if (c == '(') return 6;
		if (c == '+' || c == '-') return 2;
		if (c == '*' || c == '/') return 4;
		else if (c == ')') return 1;
	}
	return 0;
}

void calculate(){				//四则混合运算
	char a[100];
	cin >> a;

	int i;
	for (i = 0; a[i] != '\0'; i++);
	a[i] = '#';
	a[i + 1] = '\0';

	char b[100];
	int p = 0;

	i = 0;

	Stack s;
	init_Stack(s);
	Push(s, '#');

	Elemtype e;
	int priority1, priority2;

	while (!isempty_Stack(s)){
		if (a[i] >= '0'&&a[i] <= '9'){
			b[p++] = a[i++];
		}
		else{
			Gettop(s, e);
			priority1 = getpriority(e, 0);
			priority2 = getpriority(a[i], 1);
			if (priority1<priority2){
				Push(s, a[i]);
				i++;
			}
			else if (priority1 == priority2){
				Pop(s, e);
				i++;
			}
			else{
				Pop(s, e);
				b[p++] = e;
			}
		}
	}

	b[p] = '\0';
	cout << b << endl;
	///////////////////////////////////
	Elemtype d;
	for (i = 0; b[i] != '\0'; i++){
		if (b[i] >= '0'&&b[i] <= '9'){
			Push(s, b[i] - '0');
		}
		else{
			switch (b[i]){
			case '+':
				Pop(s, e);
				Pop(s, d);
				Push(s, d + e);
				break;
			case '-':
				Pop(s, e);
				Pop(s, d);
				Push(s, d - e);
				break;
			case '*':
				Pop(s, e);
				Pop(s, d);
				Push(s, d*e);
				break;
			case '/':
				Pop(s, e);
				Pop(s, d);
				Push(s, d / e);
				break;
			}
		}
	}

	Pop(s, e);
	int result = e;
	cout << result;


}

void Stack_test(){
	Stack s;
	Elemtype a;
	init_Stack(s);

	int i;
	int N;
	cout << "输入要存储的数组长度:";
	cin >> N;
	Elemtype data;
	cout << "输入数组:";
	for (i = 0; i<N; i++){
		cin >> data;
		Push(s, data);
	}

	cout << "栈的输出结果:";
	while (!isempty_Stack(s)){
		Pop(s, a);
		cout << a << ' ';
	}
	cout << endl;
}

void Binode_test(){
	Bitree t = NULL;

	int i;

	int N;
	cout << "输入二叉树的结点数:";
	cin >> N;
	Elemtype data[20];
	cout << "输入结点数值（0为空结点）:";

	for (i = 0; i<N; i++)
		cin >> data[i];


	create_Binode(t, data, N);

	cout << "二叉树的先序遍历序列:";
	visit_Binode(t);
	cout << endl;

	cout << "二叉树的高度为:" << get_height_Binode(t) << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//数


status new_data(Data &d){
	d.value = NULL;
	return OK;
}

status clear_node(node *&value){
	node *free_node;
	while (value != NULL){
		free_node = value;
		value = value->next;
		free(free_node);
	}
	return OK;
}

status clear_data(Data &d){
	clear_node(d.value);
	//d.value = NULL;
	return OK;
}



status init_data(Data &d, char *str){
	/*node *free_node;
	while(d.value!=NULL){
	free_node=d.value;
	d.value=d.value->next;
	free(free_node);
	}*/
	clear_data(d);

	if (str[0] == '\0'){
		return ER;
	}

	int i, len, bit = -1, pointsum = 0;
	if (str[0] == '.') return ER;
	for (i = 0; str[i] != '\0'; i++){				//检查字符串，标记小数点
		if (!(str[i] >= '0'&&str[i] <= '9' || str[i] == '-'&&i == 0 ||
			str[i] == '.'&&str[i - 1] >= '0'&&str[i - 1] <= '9'&&str[i + 1] >= '0'&&str[i + 1] <= '9'))
			return ER;

		if (str[i] == '.'){
			if (pointsum >= 1) return ER;
			bit = i;
			pointsum++;
		}
	}
	len = i;

	if (pointsum == 1)				//是否小数
		d.point = len - bit - 1;
	else
		d.point = 0;

	if (str[0] == '-')				//是否负数
		d.symbol = 1;
	else
		d.symbol = 0;

	for (i = d.symbol; i<len - 1 && (str[i] == '0' || str[i] == '.'); i++);	//消去前面的0，最后一个数要保留
	if (bit<i)
		d.len = len - i;
	else
		d.len = len - i - 1;

	node *p = (node *)malloc(sizeof(node));
	p->next = NULL;
	node *q;
	for (; i<len; i++){
		if (i != bit){
			p->data = str[i] - '0';
			q = (node *)malloc(sizeof(node));
			q->next = p;
			p = q;
		}
	}
	d.value = p;


	set_point(d);

	return OK;
}

status init_data(Data &d){
	/*node *q;
	while(d.value!=NULL){
	q=d.value;
	d.value=d.value->next;
	free(q);
	}*/
	clear_data(d);

	d.len = 1;
	d.symbol = 0;
	d.point = 0;
	d.value = (node *)malloc(sizeof(node));
	node *p = (node *)malloc(sizeof(node));
	p->data = 0;
	p->next = NULL;
	d.value->next = p;
	return OK;
}

status is_float(double n){
	return n>(int)n;
}

status init_data(Data &d, double n){

	clear_data(d);

	if (!is_float(n) && n >= 0 && n<9){
		d.len = 1;
		d.symbol = 0;
		d.point = 0;
		d.value = (node *)malloc(sizeof(node));
		node *p = (node *)malloc(sizeof(node));
		p->data = n;
		p->next = NULL;
		d.value->next = p;
		return OK;
	}
	else{
		d.symbol = !(n >= 0);

		d.value = (node *)malloc(sizeof(node));


		if (n<0) n = -n;

		int point = 0;
		while (is_float(n)){
			n *= 10;
			point++;
		}

		d.point = point;

		int m = n;
		node *p = d.value;
		node *q;

		d.len = 0;
		while (m>0){
			q = (node *)malloc(sizeof(node));
			q->data = m % 10;
			m /= 10;
			p->next = q;
			p = q;
			d.len++;
		}
		p->next = NULL;

	}

	return OK;
}


status set_point(Data &d){
	if (d.point == 0 || d.value == NULL) return ER;

	if (d.point > 0 && equal_0(d)){
		//init_data(d);
		d.len = 1;
		d.point = 0;
		d.symbol = 0;
		node *p = d.value->next->next;
		while (p != NULL){
			node *q = p;
			p = p->next;
			free(q);
		}
		d.value->next->next = NULL;
		return OK;
	}

	node *p;
	while (d.value->next != NULL && d.value->next->data == 0 && d.point>0){
		p = d.value->next;
		d.value->next = d.value->next->next;
		d.point--;
		d.len--;
		free(p);
	}

	//if (d.value->next != NULL)
	return OK;
}

status set_point(Data &d, int n){
	if (n <= d.point) return ER;
	int i;
	node *p;
	for (i = 0; i<n - d.point; i++){
		p = (node *)malloc(sizeof(node));
		p->data = 0;
		p->next = d.value->next;
		d.value->next = p;
	}
	d.len += n - d.point;
	d.point = n;
	return OK;
}

status show_node(node *p){
	if (p->next != NULL) show_node(p->next);
	cout << p->data;
	return OK;
}

status show_node(node *p, int point){
	point--;
	if (p->next != NULL) show_node(p->next, point);
	else{
		if (point == 0) cout << '0';
		else if (point>0){
			cout << '0' << '.';
			int i;
			for (i = 0; i<point; i++)
				cout << '0';
		}
	}
	if (point == 0) cout << '.';
	cout << p->data;
	return OK;
}

status show_data(Data d){		//显示出来

	if (d.value == NULL || d.value->next == NULL){
		cout << "未定义";
		return ER;
	}

	if (d.symbol == 1)
		cout << '-';
	if (d.point == 0)		//是否小数
		show_node(d.value->next);
	else
		show_node(d.value->next, d.point);
	return OK;
}

status copy_data(Data d1, Data &d2){			//d2=d1

	node *free_node = d2.value;//

	d2.len = d1.len;
	d2.symbol = d1.symbol;
	d2.point = d1.point;
	d2.value = (node *)malloc(sizeof(node));
	node *p1 = d1.value->next;
	node *p2 = d2.value;
	node *q;
	while (p1 != NULL){
		q = (node *)malloc(sizeof(node));
		q->data = p1->data;
		p2->next = q;
		p2 = q;
		p1 = p1->next;
	}
	p2->next = NULL;

	clear_node(free_node);//

	return OK;
}

status copy_point_data(Data d1, Data &d2){			//d1->d2
	d2.len = d1.len;
	d2.point = d1.point;
	d2.symbol = d1.symbol;

	if (d2.value != d1.value){

		clear_data(d2);
		d2.value = d1.value;
	}

	return OK;
}

status copy_int_data(Data d1, Data &d2){			//d2=(int)d1

	if (d1.point >= d1.len){
		init_data(d2);
		return OK;
	}
	node *q = d1.value;

	int i;
	for (i = 0; i < d1.point; i++){
		q = q->next;
	}

	node *p = (node *)malloc(sizeof(node));
	node *new_value = p;

	d2.len = 0;
	while (q->next != NULL){
		p->next = (node *)malloc(sizeof(node));
		p->next->data = q->next->data;
		p = p->next;

		d2.len++;

		q = q->next;
	}

	p->next = NULL;

	d2.point = 0;
	d2.symbol = d1.symbol;

	clear_data(d2);
	d2.value = new_value;

	return OK;
}

int is_equal(Data d1, Data d2){			//d1是否等于d2
	if (d1.len != d2.len) return 0;
	if (d1.symbol != d2.symbol) return 0;
	if (d1.point != d2.point) return 0;
	node *p1 = d1.value->next;
	node *p2 = d2.value->next;
	while (p1 != NULL&&p2 != NULL&&p1->data == p2->data){
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 != NULL || p2 != NULL) return 0;
	return 1;
}

status add_node(node *p1, node *p2, node * &p3, Elemtype attach, int &len){
	Elemtype e = attach;
	if (e == 0 && p1 == NULL&&p2 == NULL) { p3 = NULL; return OK; }
	if (p1 != NULL) { e += p1->data; p1 = p1->next; }
	if (p2 != NULL) { e += p2->data; p2 = p2->next; }

	//if (e == 0 && p1 == NULL&&p2 == NULL) { p3 = NULL; return OK; }
	p3 = (node *)malloc(sizeof(node));
	p3->data = e % 10;
	node *p4;
	add_node(p1, p2, p4, e / 10, ++len);
	p3->next = p4;

	return OK;
}


status add_abs_data(Data d1, Data d2, Data &d3){	//d3=|d1|+|d2|

	node *free_node = d3.value;//为什么要在最后才清理，因为可能出现d3就是d1或d2的情况

	if (d1.point>d2.point) set_point(d2, d1.point);
	else if (d1.point<d2.point) set_point(d1, d2.point);
	node *p;
	d3.len = 0;
	add_node(d1.value->next, d2.value->next, p, 0, d3.len);
	d3.value = (node *)malloc(sizeof(node));
	d3.value->next = p;
	d3.symbol = 0;
	d3.point = d1.point;
	set_point(d1);
	set_point(d2);
	set_point(d3);

	clear_node(free_node);//

	return OK;
}



status add_data(Data d1, Data d2, Data &d3){			//d1+d2=d3
	if (d1.symbol == 0 && d2.symbol == 0){
		add_abs_data(d1, d2, d3);
	}
	else if (d1.symbol == 0 && d2.symbol == 1){
		sub_abs_data(d1, d2, d3);
	}
	else if (d1.symbol == 1 && d2.symbol == 0){
		sub_abs_data(d2, d1, d3);
	}
	else{
		add_abs_data(d1, d2, d3);
		d3.symbol = 1;
	}
	return OK;
}

status compare_node(node *p1, node *p2, int &e){
	if (p1 == NULL || p2 == NULL){
		e = 0;
		return ER;
	}
	compare_node(p1->next, p2->next, e);
	if (e == 0){
		if (p1->data>p2->data) e = 1;
		else if (p1->data<p2->data) e = 2;
		else e = 0;
	}
	return OK;
}


status compare_abs_data(Data d1, Data d2, int &e){		//比较绝对值大小
	if (d1.len == 0 && d2.len>0) e = 2;
	else if (d1.len>0 && d2.len == 0) e = 1;
	else if (d1.len == 0 && d2.len == 0) e = 0;
	else{
		if (d1.point>d2.point) set_point(d2, d1.point);
		else if (d1.point<d2.point) set_point(d1, d2.point);
		if (d1.len>d2.len) e = 1;
		else if (d1.len<d2.len) e = 2;
		else compare_node(d1.value->next, d2.value->next, e);
		set_point(d1);
		set_point(d2);
	}
	return OK;
}

status compare_data(Data d1, Data d2, int &e){		//比较大小
	if (d1.symbol == 0 && d2.symbol == 1) e = 1;
	else if (d1.symbol == 1 && d2.symbol == 0) e = 2;
	else if (d1.symbol == 0 && d2.symbol == 0){
		compare_abs_data(d1, d2, e);
	}
	else{
		compare_abs_data(d1, d2, e);
		e = (3 - e) % 3;
	}
	return OK;
}

/*
status plus_node(node *p1, node *&p2, int &len){
if (p1 != NULL){
p2 = (node *)malloc(sizeof(node));
p2->data = 9 - p1->data;
len++;
if (!plus_node(p1->next, p2->next, len)){
if (p2->data == 0){
free(p2);
p2 = NULL;
len--;
return ER;
}
}
}
else{
p2 = NULL;
return ER;
}
return OK;
}

status plus_data(Data d1, Data &d2){			//求补码

node *free_node = d2.value;//为什么要在最后才清理，因为可能出现d2就是d1的情况

d2.len = 0;
d2.symbol = d1.symbol;
d2.point = 0;
d2.value = (node *)malloc(sizeof(node));
plus_node(d1.value->next, d2.value->next, d2.len);
Data d3;
new_data(d3);
init_data(d3, 1);
add_abs_data(d2, d3, d2);
d2.point = d1.point;
set_point(d2);

clear_data(d3);
clear_node(free_node);//

return OK;
}

status sub_abs_data(Data d1, Data d2, Data &d3){
//clear_data(d3);
int e;
Data d4;
new_data(d4);
compare_abs_data(d1, d2, e);
if (e == 0) init_data(d3);
else if (e == 1){

plus_data(d1, d4);
add_abs_data(d2, d4, d4);
plus_data(d4, d4);

clear_data(d3);

d3.symbol = 0;
d3.len = d4.len;
d3.point = d4.point;
d3.value = d4.value;


}
else if (e == 2){
plus_data(d2, d4);
add_abs_data(d1, d4, d4);
plus_data(d4, d4);

clear_data(d3);

d3.symbol = 1;
d3.len = d4.len;
d3.point = d4.point;
d3.value = d4.value;
}
return OK;
}*/

status plus_node(node *p1, node *&p2, int &len, bool clearHead){
	if (p1 != NULL){
		p2 = (node *)malloc(sizeof(node));
		p2->data = 9 - p1->data;
		len++;


		if (!plus_node(p1->next, p2->next, len, clearHead)){

			if (clearHead){
				if (p2->data == 0){
					free(p2);
					p2 = NULL;
					len--;
					return ER;
				}
			}
		}
	}
	else{
		p2 = NULL;
		return ER;
	}
	return OK;
}

status plus_data(Data d1, Data &d2, bool clearHead){			//求补码

	node *free_node = d2.value;//为什么要在最后才清理，因为可能出现d2就是d1的情况

	d2.len = 0;
	d2.symbol = d1.symbol;
	d2.point = 0;
	d2.value = (node *)malloc(sizeof(node));
	plus_node(d1.value->next, d2.value->next, d2.len, clearHead);
	Data d3;
	new_data(d3);
	init_data(d3, 1);
	add_abs_data(d2, d3, d2);
	d2.point = d1.point;
	set_point(d2);

	clear_data(d3);
	clear_node(free_node);//

	return OK;
}

status sub_abs_data(Data d1, Data d2, Data &d3){
	//clear_data(d3);
	int e;
	Data d4;
	new_data(d4);
	compare_abs_data(d1, d2, e);
	if (e == 0) init_data(d3);
	else if (e == 1){

		plus_data(d1, d4, FALSE);
		add_abs_data(d2, d4, d4);
		plus_data(d4, d4, TRUE);

		clear_data(d3);

		d3.symbol = 0;
		d3.len = d4.len;
		d3.point = d4.point;
		d3.value = d4.value;


	}
	else if (e == 2){
		plus_data(d2, d4, FALSE);
		add_abs_data(d1, d4, d4);
		plus_data(d4, d4, TRUE);

		clear_data(d3);

		d3.symbol = 1;
		d3.len = d4.len;
		d3.point = d4.point;
		d3.value = d4.value;
	}
	return OK;
}

status sub_data(Data d1, Data d2, Data &d3){				//d1-d2=d3
	if (d1.symbol == 0 && d2.symbol == 0){
		sub_abs_data(d1, d2, d3);
	}
	else if (d1.symbol == 0 && d2.symbol == 1){
		add_abs_data(d1, d2, d3);
	}
	else if (d1.symbol == 1 && d2.symbol == 0){
		add_abs_data(d1, d2, d3);
		d3.symbol = 1;
	}
	else{
		sub_abs_data(d2, d1, d3);
	}
	return OK;
}

status mul_nom_abs_node(node *p1, Elemtype nom, node *&p2, Elemtype attach, int &len){
	//p2=(node *)malloc(sizeof(node));
	if (p1 == NULL&&attach == 0)
		p2 = NULL;
	else{
		Elemtype e = attach;
		p2 = (node *)malloc(sizeof(node));

		if (p1 != NULL){
			e += p1->data*nom;
			mul_nom_abs_node(p1->next, nom, p2->next, e / 10, ++len);
		}
		else{
			//p2->next=(node *)malloc(sizeof(node));
			p2->next = NULL;
			len++;
		}
		p2->data = e % 10;
	}
	return OK;
}

status mul_nom_abs_data(Data d1, Elemtype nom, int exp, Data &d2){		//d2=d1*nom*10^exp
	if (equal_0(d1) || nom == 0){
		init_data(d2);
	}
	else{


		node *new_value;

		d2.symbol = d1.symbol;
		d2.point = d1.point;
		new_value = (node *)malloc(sizeof(node));
		d2.len = 0;
		mul_nom_abs_node(d1.value->next, nom, new_value->next, 0, d2.len);

		if (exp > 0){
			node *p;
			int i;
			for (i = 0; i < exp; i++){
				p = (node *)malloc(sizeof(node));
				p->data = 0;
				p->next = new_value->next;//d2.value->next;
				new_value->next = p;
			}
			d2.len += exp;

		}
		else{
			d2.point += -exp;
		}


		clear_data(d2);
		d2.value = new_value;
		set_point(d2);

	}
	return OK;
}

status mul_data_by_order(Data d1, Data d2, Data &d3){					//d1*d2=d3



	if (equal_0(d1) || equal_0(d2)){
		init_data(d3);
		return OK;
	}


	Data d4;
	new_data(d4);

	Data d5;
	new_data(d5);
	init_data(d5);

	int exp = -d1.point;

	node *p = d1.value->next;


	while (p != NULL){
		mul_nom_abs_data(d2, p->data, exp++, d4);
		add_data(d5, d4, d5);
		p = p->next;
	}
	d3.len = d5.len;
	d3.symbol = (d1.symbol + d2.symbol) % 2;
	d3.point = d5.point;

	clear_data(d3);
	d3.value = d5.value;
	set_point(d3);

	clear_data(d4);
	return OK;
}

status mul_data(Data d1, Data d2, Data &d3){					//d1*d2=d3
	if (d1.len <= d2.len)
		return mul_data_by_order(d1, d2, d3);
	else
		return mul_data_by_order(d2, d1, d3);
}

status div_total_data(Data d1, Data d2, Data &d3, int point){			//d1/d2=d3

	Data d5, d6, d7;
	new_data(d5);
	new_data(d6);
	new_data(d7);
	mul_nom_abs_data(d1, 1, point + d2.point, d5);
	mul_nom_abs_data(d2, 1, d2.point, d6);

	init_data(d3);

	set_point(d5);
	set_point(d6);

	d5.symbol = 0;
	d6.symbol = 0;
	int n, i;
	Data d4;
	new_data(d4);
	int e = 0;
	for (n = 0; e < 2; n++){
		mul_nom_abs_data(d6, 1, n, d4);
		compare_abs_data(d5, d4, e);
	}
	n -= 2;



	while (n >= 0){
		mul_nom_abs_data(d6, 1, n, d4);
		e = 1;
		if (d5.symbol == 1) break;
		for (i = 1; e < 2; i++){
			mul_nom_abs_data(d4, i, 0, d7);
			compare_abs_data(d5, d7, e);
		}
		i -= 2;
		mul_nom_abs_data(d4, i, 0, d7);
		sub_abs_data(d5, d7, d5);
		init_data(d7, i);
		mul_nom_abs_data(d7, 1, n, d7);
		add_abs_data(d3, d7, d3);
		n--;
	}

	if (!equal_0(d3)){

		d3.symbol = (d1.symbol + d2.symbol) % 2;
		d3.point = point;
		set_point(d3);

	}


	clear_data(d4);
	clear_data(d5);
	clear_data(d6);
	clear_data(d7);

	return OK;
}


status mod_data(Data d1, Data d2, Data &d3){			//d1%d2=d3
	if (d1.point>0 || d2.point>0
		|| d1.symbol == 1 || d2.symbol == 1
		|| equal_0(d2)){
		clear_data(d3);
		return ER;
	}

	Data d4, d5, d6;
	new_data(d4);
	new_data(d5);
	new_data(d6);
	copy_data(d1, d4);

	int i, n, e = 0;
	for (n = 0; e < 2; n++){
		mul_nom_abs_data(d2, 1, n, d5);
		compare_abs_data(d4, d5, e);
	}

	n -= 2;

	while (n >= 0){
		mul_nom_abs_data(d2, 1, n, d5);
		e = 1;
		for (i = 1; e < 2; i++){
			mul_nom_abs_data(d5, i, 0, d6);
			compare_abs_data(d4, d6, e);
		}
		i -= 2;
		mul_nom_abs_data(d5, i, 0, d6);
		sub_abs_data(d4, d6, d4);
		n--;
	}

	clear_data(d3);
	d3.value = d4.value;
	d3.len = d4.len;
	d3.point = 0;
	d3.symbol = 0;

	clear_data(d5);
	clear_data(d6);
	return OK;
}


status exp_data(Data d1, Data d2, Data &d3, int point){			//d1^d2=d3
	if (d2.point>0){
		clear_data(d3);
		return ER;
	}

	if (equal_0(d2)){
		init_data(d3, 1);
		return OK;
	}

	Data d4;	//
	new_data(d4);

	Data data_1;
	new_data(data_1);
	init_data(data_1, 1);

	Data data_2;
	new_data(data_2);
	init_data(data_2, 2);

	if (d2.symbol == 1){	//若指数为负数
		div_total_data(data_1, d1, d4, point);	//求倒数
	}
	else{
		copy_data(d1, d4);
	}


	int e = 0;

	///////////////////////////////////////////////
	Queue q;
	init_Queue(q);

	Data d5;
	new_data(d5);
	copy_data(d2, d5);
	d5.symbol = 0;

	int exp_2 = 0;
	while (!equal_0(d5)){
		if (d5.value->next->data % 2 == 1){
			goin_Queue(q, exp_2);
		}

		exp_2++;

		mul_nom_abs_data(d5, 5, -1, d5);
		copy_int_data(d5, d5);
	}

	Data d6;
	new_data(d6);
	init_data(d6, 1);

	int i = 0, exp;
	while (!isempty_Queue(q)){
		goout_Queue(q, exp);
		for (; i < exp; i++){
			mul_data(d4, d4, d4);
		}

		mul_data(d6, d4, d6);
	}


	copy_point_data(d6, d3);
	clear_data(d4);
	clear_data(d5);
	clear_data(data_1);
	clear_data(data_2);

	return OK;
}


status exp_data1(Data d1, Data d2, Data &d3, int point){			//d1^d2=d3
	if (d2.point>0){
		clear_data(d3);
		return ER;
	}

	if (equal_0(d2)){
		init_data(d3, 1);
		return OK;
	}

	Data data_1;
	new_data(data_1);
	init_data(data_1, 1);

	Data new_d1;
	new_data(new_d1);

	if (d2.symbol == 1){	//若指数为负数
		div_total_data(data_1, d1, new_d1, point);	//求倒数
	}
	else{
		copy_data(d1, new_d1);
	}



	Data d4, d5;
	new_data(d4);
	new_data(d5);
	init_data(d4, 1);
	init_data(d5, 1);




	int e = 2;
	compare_data(d4, d2, e);
	while (e == 2){
		mul_data(new_d1, d5, d5);
		compare_data(d4, d2, e);

		add_data(d4, data_1, d4);
	}

	copy_point_data(d5, d3);


	clear_data(data_1);
	clear_data(new_d1);
	clear_data(d4);
}


float InvSqrt(float x){
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1); // 计算第一个近似根
	x = *(float*)&i;
	x = x*(1.5f - xhalf*x*x); // 牛顿迭代法
	return x;
}


int is_equal1(Data d1, Data d2){			//d1是否等于d2
	if (d1.point > d2.point)
		set_point(d2, d1.point);
	else if (d1.point < d2.point)
		set_point(d1, d2.point);

	if (d1.len != d2.len || d1.symbol != d2.symbol){
		set_point(d1);
		set_point(d2);
		return 0;
	}
	node *p1 = d1.value->next;
	node *p2 = d2.value->next;

	/*if (p1 != NULL&&p2 != NULL){
	p1 = p1->next;
	p2 = p2->next;

	p1 = p1->next;
	p2 = p2->next;
	p1 = p1->next;
	p2 = p2->next;
	}*/

	/*int tip = d1.len*0.35;
	while (tip-- > 0){
	p1 = p1->next;
	p2 = p2->next;
	}*/

	if (d1.len > 3){
		p1 = p1->next;
		p2 = p2->next;
	}

	while (p1 != NULL&&p2 != NULL&&p1->data == p2->data){
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 != NULL || p2 != NULL){
		set_point(d1);
		set_point(d2);
		return 0;
	}

	set_point(d1);
	set_point(d2);
	return 1;
}

status get_sqrt(Data d1, Data &d2, int point){			//sqrt(d1)=d2
	//int point=25;
	Data d3, d4, d5;				//d3=2 d4=a/x

	new_data(d3);
	new_data(d4);
	new_data(d5);

	init_data(d3, 2);
	div_total_data(d1, d3, d2, point);
	do{
		copy_data(d2, d5);
		div_total_data(d1, d2, d4, point);
		add_data(d2, d4, d2);
		div_total_data(d2, d3, d2, point);
	} while (!is_equal1(d2, d5));

	/*init_data(d4, 2);

	while (!is_equal(d2, d4)){
	add_data(d2, d4, d2);
	div_total_data(d2, d3, d2, point);
	div_total_data(d1, d2, d4, point);
	}*/
	////////////////////////////////////////////////////
	clear_data(d3);
	clear_data(d4);
	clear_data(d5);

	return OK;
}

/*
double get_sqrt(double a){
double x=a/2;
int i;
for(i=0;i<100;i++)
x=(x+a/x)/2;
return x;
}*/

status get_pi(Data &d1, int point){
	Data d2, d3, data_1, data_2, data_4;

	new_data(d2);
	new_data(d3);
	new_data(data_1);
	new_data(data_2);
	new_data(data_4);

	init_data(d1, 1);
	init_data(d2, 1);
	init_data(data_1, 1);
	init_data(data_2, 2);
	init_data(data_4, 4);
	int i = 1;
	while (d2.len <= 1){
		add_data(d2, data_2, d2);
		div_total_data(data_1, d2, d3, point);
		if (i++ % 2 == 0)
			add_data(d1, d3, d1);
		else
			sub_data(d1, d3, d1);
	}

	mul_data(d1, data_4, d1);

	clear_data(d2);
	clear_data(d3);
	clear_data(data_1);
	clear_data(data_2);
	clear_data(data_4);

	return OK;
}
/*
double get_pi(){
double i,j=-1,pi=1;
int k=1;
while (fabs(i)>(1e-6))
{
k=k+2;
i=j/k;
pi+=i;
j=-j;
}
pi=pi*4;
return pi;
}*/

void test_data1(){
	Data d1, d2, d3;
	init_data(d1, "1000.9123");//3482947914872914720148934710483925791348913483959134893471948357392481957");
	init_data(d2, "3.23");//45832581035730589327593583295793589257238758");

	//plus_data(d1,d3);
	//mul_nom_abs_data(d1,1,d1.point,d3);
	/*
	int e;
	compare_abs_data(d1,d2,e);

	cout<<' '<<e;*/
	//plus_data(d2,d3);
	//sub_abs_data(d1,d2,d3);
	//mul_nom_abs_data(d1,2,1,d3);
	//cout<<d3.len;
	div_total_data(d1, d2, d3, 15);
	//mul_data(d1,d2,d3);
	//set_point(d1,3);
	//set_point(d1);
	//add_abs_data(d1,d2,d3);
	show_data(d3);
	//cout<<d1.len;

}

void test_data(){
	Data d1, d2, d3;



	char str1[10000], str2[10000];
	char c;
	cout << "================================================================================" << endl;
	cout << "-----------------------------------超级计算器-----------------------------------" << endl;
	cout << "================================================================================" << endl;
	while (1){

		cout << "请输入第一个数:";
		cin >> str1;
		if (!init_data(d1, str1))
			cout << "输入有误!" << endl;
		else{
			cout << "请输入运算符:";
			cin >> c;
			if (!(c == '+' || c == '-' || c == '*' || c == '/'))
				cout << "输入有误!" << endl;
			else{
				cout << "请输入第二个数:";
				cin >> str2;
				if (!init_data(d2, str2))
					cout << "输入有误!" << endl;
				else{

					cout << "运算结果:";
					switch (c){
					case '+':add_data(d1, d2, d3); show_data(d3); cout << endl; break;
					case '-':sub_data(d1, d2, d3); show_data(d3); cout << endl; break;
					case '*':mul_data(d1, d2, d3); show_data(d3); cout << endl; break;
					case '/':div_total_data(d1, d2, d3, 15); show_data(d3); cout << endl; break;
					}
				}

			}
		}

		cout << "--------------------------------------------------------------------------------" << endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_sort(Elemtype a[], int n){	//插入排序
	int i, j, k, p;
	for (i = 1; i<n; i++){
		p = a[i];
		for (j = 0; j<i&&a[j]<p; j++);
		for (k = i; k>j; k--)
			a[k] = a[k - 1];
		a[j] = p;
	}
}

void test_sort(){
	Elemtype a[7] = { 12, 61, 25, 43, 19, 37, 48 };
	insert_sort(a, 7);
	int i;
	for (i = 0; i<7; i++)
		cout << a[i] << ' ';
	cout << endl;
}

bool equal_0(Data d){

	if (d.value != NULL){
		node *p = d.value->next;
		while (p != NULL){
			if (p->data != 0)
				return FALSE;
			p = p->next;
		}
		return TRUE;
	}

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////


void add_char(char *str, char c){
	int len = strlen(str);
	str[len] = c;
	str[len + 1] = '\0';
}

char int2char(int n){
	return n + 48;
}



status show_node(node *p, char *c_str){
	if (p->next != NULL) show_node(p->next, c_str);
	//cout << p->data;

	add_char(c_str, int2char(p->data));
	return OK;
}

status show_node(node *p, int point, char *c_str){
	point--;
	if (p->next != NULL) show_node(p->next, point, c_str);
	else{
		if (point == 0) add_char(c_str, '0'); //str += '0';//cout << '0';
		else if (point>0){
			//cout << '0' << '.';
			//str += "0.";
			add_char(c_str, '0');
			add_char(c_str, '.');
			int i;
			for (i = 0; i<point; i++)
				add_char(c_str, '0');
			//cout << '0';
		}
	}
	if (point == 0) add_char(c_str, '.');//cout << '.';
	//cout << p->data;
	add_char(c_str, int2char(p->data));
	return OK;
}

char* Data2char(Data d){
	if (d.value == NULL || d.value->next == NULL){
		return NULL;
	}

	int length;
	if (d.point < d.len){
		length = d.len + 4;
	}
	else{
		length = d.point + 5;
	}

	char *c_str = (char *)malloc(length * sizeof(char));
	c_str[0] = '\0';

	if (d.symbol == 1)
		add_char(c_str, '-');
	if (d.point == 0)		//是否小数
		show_node(d.value->next, c_str);
	else
		show_node(d.value->next, d.point, c_str);
	return c_str;
}

