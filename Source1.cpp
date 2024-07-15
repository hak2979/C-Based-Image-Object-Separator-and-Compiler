#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
using namespace cv;

template<class T1>
class noode
{
private:
public:
	T1 x;
	T1 y;
	noode <T1>* next;
	noode() {}
	noode(T1 v)
	{
		this->x = v;
	}
};
template <class T1>
class Queue
{
public:
	noode <T1>* head;
	noode <T1>* tail;
	Queue()
	{
		head = tail = NULL;
	}
	T1 to(T1 w)
	{
		if (w == 1)
			return head->x;
		else
			return head->y;
	}
	void Dequeue()
	{
		if (head != tail)
		{
			noode<T1>* n = head;
			noode<T1>* temp = head;
			temp = temp->next;
			head->next = temp->next;
			head = temp;
		}
		else
		{
			head = NULL;
		}
	}
	void enqueue(T1 s, T1 w)
	{
		noode<T1>* n = new noode<T1>();
		n->x = s;
		n->y = w;
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
			tail = n;
		}
		else
		{
			tail->next = n;
			n->next = tail->next;
			tail = n;
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
			return 1;
		else
			return 0;
	}
	void print()
	{
		noode<T1>* p = head;
		while (p != tail)
		{
			cout << p->x << "  ";
			p = p->next;
		}
		cout << p->x << endl;
	}
};
int** a(int** aa, int r, int c)
{
	Queue<int>* queue = new Queue<int>();
	int** ww = new int* [r];
	for (int i = 0; i < r; i++)
		ww[i] = new int[c];
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			ww[i][j] = 0;
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (queue->isEmpty() == 0)
			{
				while (queue->isEmpty() == 0)
				{
					// 00 01 02   [i-1][j-1]  [i-1][j]  [i-1][j+1]
					// 10 11 12   [i][j-1]    [i][j]    [i][j+1]
					// 20 21 22   [i+1][j-1]  [i+1][j]  [i+1][j+1]

					ww[queue->to(1)][queue->to(2)] = 1;
					//aa[queue->to(1)][queue->to(2)] = 0;
					int i1 = queue->to(1);
					int j1 = queue->to(2);
					queue->Dequeue();
					if (i1 == 0 && j1 == 0)
					{
						int xp = aa[i1][j1 + 1];
						int rightdd = aa[i1 + 1][j1 + 1];
						int yd = aa[i1 + 1][j1];
						if (xp != 0)
						{
							aa[i1][j1 + 1] = 0;
							queue->enqueue(i1, j1 + 1);
						}
						if (rightdd != 0)
						{
							aa[i1 - 1][j1 + 1] = 0;
							queue->enqueue(i1 - 1, j1 + 1);
						}
						if (yd != 0)
						{
							aa[i1 + 1][j1] = 0;
							queue->enqueue(i1 + 1, j1);
						}
					}
					else if (i1 == 0 && j1 == c - 1)
					{
						int xn = aa[i1][j1 - 1];
						int leftdd = aa[i1 + 1][j1 - 1];
						int yd = aa[i1 + 1][j1];
						if (xn != 0)
						{
							aa[i1][j1 - 1] = 0;
							queue->enqueue(i1, j1 - 1);
						}
						if (leftdd != 0)
						{
							aa[i1 + 1][j1 - 1] = 0;
							queue->enqueue(i1 + 1, j1 - 1);
						}
						if (yd != 0)
						{
							aa[i1 + 1][j1] = 0;
							queue->enqueue(i1 + 1, j1);
						}
					}
					else if (i1 == r - 1 && j1 == 0)
					{
						int yu = aa[i1 - 1][j1];
						int rightdu = aa[i1 - 1][j1 + 1];
						int xp = aa[i1][j1 + 1];
						if (xp != 0)
						{
							aa[i1][j1 + 1] = 0;
							queue->enqueue(i1, j1 + 1);
						}
						if (rightdu != 0)
						{
							aa[i1 - 1][j1 + 1] = 0;
							queue->enqueue(i1 - 1, j1 + 1);
						}
						if (yu != 0)
						{
							aa[i1 - 1][j1] = 0;
							queue->enqueue(i1 - 1, j1);
						}
					}
					else if (i1 == r - 1 && j1 == c - 1)
					{
						int xn = aa[i1][j1 - 1];
						int leftdu = aa[i1 - 1][j1 - 1];
						int yu = aa[i1 - 1][j1];
						if (xn != 0)
						{
							aa[i1][j1 - 1] = 0;
							queue->enqueue(i1, j1 - 1);
						}
						if (leftdu != 0)
						{
							aa[i1 - 1][j1 - 1] = 0;
							queue->enqueue(i1 - 1, j1 - 1);
						}
						if (yu != 0)
						{
							aa[i1 - 1][j1] = 0;
							queue->enqueue(i1 - 1, j1);
						}
					}
					else if (i1 > 0 && j1 > 0 && i1<r-1 && j1<c-1)
					{
						int xp = aa[i1][j1 + 1];
						int xn = aa[i1][j1 - 1];
						int leftdu = aa[i1 - 1][j1 - 1];
						int leftdd = aa[i1 + 1][j1 - 1];
						int rightdu = aa[i1 - 1][j1 + 1];
						int rightdd = aa[i1 + 1][j1 + 1];
						int yu = aa[i1 - 1][j1];
						int yd = aa[i1 + 1][j1];
						if (xp != 0)
						{
							aa[i1][j1 + 1] = 0;
							queue->enqueue(i1, j1 + 1);
						}
						if (xn != 0)
						{
							aa[i1][j1 - 1] = 0;
							queue->enqueue(i1, j1 - 1);
						}
						if (leftdu != 0)
						{
							aa[i1 - 1][j1 - 1] = 0;
							queue->enqueue(i1 - 1, j1 - 1);
						}
						if (leftdd != 0)
						{
							aa[i1 + 1][j1 - 1] = 0;
							queue->enqueue(i1 + 1, j1 - 1);
						}
						if (rightdu != 0)
						{
							aa[i1 - 1][j1 + 1] = 0;
							queue->enqueue(i1 - 1, j1 + 1);
						}
						if (rightdd != 0)
						{
							aa[i1 - 1][j1 + 1] = 0;
							queue->enqueue(i1 - 1, j1 + 1);
						}
						if (yu != 0)
						{
							aa[i1 - 1][j1] = 0;
							queue->enqueue(i1 - 1, j1);
						}
						if (yd != 0)
						{
							aa[i1 + 1][j1] = 0;
							queue->enqueue(i1 + 1, j1);
						}
					}

				}
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						if (ww[i][j] !=0)
							aa[i][j] = 0;
					}
				}
				return ww;
				for (int i = 0; i < r; i++)
					for (int j = 0; j < c; j++)
						ww[i][j] = 0;
				
			}
			else if (aa[i][j] != 0)
			{
				aa[i][j] = 0;
				queue->enqueue(i, j);
			}
		}
	}
}
bool chek(int** a, int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (a[i][j] != 0)
				return 1;
		}
	}
	return 0;
}
int we = 0;
string fun(string ax)
{
	string g = "";
	int index = 0;
	string qq = "C:/Users/Hamza amin khokhar/Desktop/New folder (4)/";
	while (ax[index] != '\0')
	{
		if (ax[index] >= 'a' && ax[index] < 'z' || ax[index] >= 'A' && ax[index] <= 'Z'|| ax[index]>='0' && ax[index]<='9')
			g += ax[index];
		index++;
	}
	ax = g;
	string q = "";
	string fi = "C:/Users/Hamza amin khokhar/Desktop/New folder (4)/Images/Img2.png";
	string fii = "C:/Users/Hamza amin khokhar/Desktop/New folder (4)/Images/Img1.png";
	if (ax == "imagesimg2")
	{
		int si = 0;
		while (ax[si] != '\0')si++;
		ax[0] -= 32;
		ax[6] -= 32;
		string h = "";
		for (int o = 0; o < 6; o++)
		{
			h += ax[o];
		}h += '/';
		for (int o = 6; o < 10; o++)
		{
			h += ax[o];
		}h += ".png";
		qq+= h;
		q = qq;
	}
	else
		q = fii;
	cv::Mat img = cv::imread(q);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	cv::imshow("First OpenCV Application", img);
	cv::moveWindow("First OpenCV Application", 0, 45);
	cv::waitKey(0);
	cv::destroyAllWindows();
	int** aa = new int* [img.rows]; // INITIALIZING AND DECLARING NEW ARRAY OF GIVE BMP
	for (int i = 0; i < img.rows; i++)
		aa[i] = new int[img.cols];
	//.............................................................
	// MAKING CV = NEWIMG
	int x, y, z;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			x = img.at<Vec3b>(i, j)[0];
			y = img.at<Vec3b>(i, j)[1];
			z = img.at<Vec3b>(i, j)[2];
			int g;
			g = (x + y + z);
			g /= 3;
			aa[i][j] = g;
		}
	}
	int** a1 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a1[i] = new int[img.cols];
	int** a2 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a2[i] = new int[img.cols];
	int** a3 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a3[i] = new int[img.cols];
	int** a4 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a4[i] = new int[img.cols];
	int** a5 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a5[i] = new int[img.cols];
	int** a6 = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		a6[i] = new int[img.cols];

	int** ww = new int* [img.rows];
	for (int i = 0; i < img.rows; i++)
		ww[i] = new int[img.cols];
	int no = 0;
	while (chek(aa, img.rows, img.cols) == 1)
	{
		if (no > 5)
			no = 5;
		else
		{

		}
		if (no == 0)
		{
			a1 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a1[i][j];
		}
		else if (no == 1)
		{
			a2 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a2[i][j];
		}
		else if (no == 2)
		{
			a3 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a3[i][j];
		}
		else if (no == 3)
		{
			a4 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a4[i][j];
		}
		else if (no == 4)
		{
			a5 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a5[i][j];
		}
		else if (no == 5)
		{
			a6 = a(aa, img.rows, img.cols);
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.cols; j++)
					ww[i][j] = a6[i][j];
		}
		cv::Mat img1 = cv::imread(q);
		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				if (ww[i][j] != 0)
				{
					img1.at<cv::Vec3b>(i, j)[0] = 255;
					img1.at<cv::Vec3b>(i, j)[1] = 255;
					img1.at<cv::Vec3b>(i, j)[2] = 255;
				}
				else
				{
					img1.at<cv::Vec3b>(i, j)[0] = 0;
					img1.at<cv::Vec3b>(i, j)[1] = 0;
					img1.at<cv::Vec3b>(i, j)[2] = 0;
				}
			}
		}
		cv::namedWindow("out", cv::WINDOW_FULLSCREEN);
		cv::imshow("out", img1);
		cv::moveWindow("out", 0, 45);
		cv::waitKey(0);
		cv::destroyAllWindows();
		string file = "";
		file += "C:/Users/Hamza amin khokhar/Desktop/New folder (4)/Images/";
		char as = we + 48;
		file += as;
		file+=".png";
		cv::imwrite(file,img1);
		we++;
		no++;
	}
	string ma = "";
	char am = no + 48;
	ma += am;
	ma += " ";
	ma+="galaxies";
	return ma;
}
template<typename t>
class Nodee
{
public:
	t data;
	Nodee* next;
	Nodee()
	{
		next = NULL;
	}
};
template<typename t>
class Queue1
{
public:
	Nodee <t>* head;
	Nodee <t>* tail;
	Queue1()
	{
		head = tail = NULL;
	}
	void Dequeue()
	{
		if (head != tail)
		{
			Nodee<t>* n = head;
			Nodee<t>* temp = head;
			temp = temp->next;
			head->next = temp->next;
			head = temp;
		}
		else
		{
			head = NULL;
		}
	}
	void enqueue(t s)
	{
		Nodee<t>* n = new Nodee<t>();
		n->data = s;
		n->next = NULL;
		if (head == NULL)
		{
			head = n;
			tail = n;
		}
		else
		{
			tail->next = n;
			n->next = tail->next;
			tail = n;
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
			return 1;
		else
			return 0;
	}
	void print()
	{
		Nodee<t>* p = head;
		while (p != tail)
		{
			cout << p->x << "  ";
			p = p->next;
		}
		cout << p->x << endl;
	}
};
template<typename t>
class LinkedList {
	Nodee<t>* head;
public:
	LinkedList()
	{
		head = NULL;
	}
	t all()
	{
		t a = "";
		Nodee<t>* ptr = head;
		while (ptr->next != NULL)
		{
			a += ptr->data;
			ptr = ptr->next;
		}
		a += ptr->data;
		head = NULL;
		return a;

	}
	void insert(t data)
	{
		Nodee<t>* ne = new Nodee<t>();
		ne->data = data;
		if (head == NULL)
		{
			head = ne;
		}
		else
		{
			Nodee<t>* ptr = head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = ne;
		}
	}
	t top()
	{
		Nodee<t>* ptr = head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		return ptr->data;
	}
	t deletee()
	{
		int q = 0;
		Nodee<t>* ptr = head;
		t w;
		if (ptr->next != NULL)
		{
			while (ptr->next != NULL)
			{
				q++;
				ptr = ptr->next;
			}
			Nodee<t>* p = head;
			for (int i = 0; i < q - 1; i++)
			{
				p = p->next;
			}
			t e = ptr->data;
			p->next = NULL;
			return e;
		}
		else
		{
			head = NULL;
		}
		return w;
	}
	void print()
	{
		Nodee<t>* ptr = head;
		while (ptr->next != NULL)
		{
			cout << ptr->data << " ";
			ptr = ptr->next;
		}
		cout << ptr->data << endl;
	}
	bool a()
	{
		if (head == NULL)
		{
			return 1;
		}
		else
			return 0;
	}
};
template<typename t>
class Stack {
	LinkedList<t>* link = new LinkedList<t>();
public:
	void push(t a)
	{
		link->insert(a);
	}
	bool che()
	{
		return link->a();
	}
	void pop()
	{
		link->deletee();
	}
	t empty()
	{
		return link->all();
	}
	t top()
	{
		t q = link->top();
		return q;
	}
};
int precedence(string q)
{
	int w = 0;
	if (q == "^" || q == "$")
		w = 3;
	else if (q == "*" || q == "/")
		w = 2;
	else if (q == "+" || q == "-")
		w = 1;
	return w;
}
string postfix(string a, Stack<string>* stac)
{
	string g = "";
	int index = 0;
	string q = "";
	while (a[index] != '\0')
	{
		if (a[index] >= 'a' && a[index] < 'z' || a[index] >= 'A' && a[index] <= 'Z' || (a[index] > 0))
			q += a[index];
		index++;
	}
	index = 0;
	a = q;
	while (a[index] != '\0')
	{
		index++;
	}
	int e = 0;
	for (int i = 0; i < index; i++)
	{
		if (a[i] == ')')
			e++;
		else if (a[i] == '(')
			e++;
	}
	if (e % 2 == 0)
	{
		for (int i = 0; i < index; i++)
		{
			if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9'))
			{
				g += a[i];
			}
			else if (a[i] == '(')
			{
				string aa = "";
				aa += a[i];
				stac->push(aa);
			}
			else if (a[i] == ')')
			{
				while (stac->top() != "(")
				{
					g += stac->top();
					stac->pop();
				}
				stac->pop();
			}
			else
			{
				string aa = "";
				aa += a[i];
				int w = 0;
				if (a[i] == '^' || a[i] == '$')
					w = 3;
				else if (a[i] == '*' || a[i] == '/')
					w = 2;
				else if (a[i] == '+' || a[i] == '-')
					w = 1;
				string qw = "";
				if (stac->che() == 0)
					qw = stac->top();
				int ee = precedence(qw);
				while (ee >= w)
				{
					g += stac->top();
					stac->pop();
					if (stac->che() == 0)
						ee = precedence(stac->top());
					else
						ee = 0;
				}
				stac->push(aa);
			}
		}
		while (stac->che() == 0)
		{
			g += stac->top();
			stac->pop();
		}
		return g;
	}
	else
	{
		return " Invalid Expression ";
	}
}
string prefix(string u, Stack<string>* l)
{
	int w = 0; string h = "";
	while (u[w] != '\0')
		w++;
	int e = 0;
	for (int i = 0; i < w; i++)
	{
		if (u[i] == ')')
			e++;
		else if (u[i] == '(')
			e++;
	}
	if (e % 2 == 0)
	{
		for (int i = w - 1; i >= 0; i--)
		{
			if (u[i] == ')')
			{
				h += '(';
			}
			else if (u[i] == '(')
			{
				h += ')';
			}
			else if (u[i] != ' ')
			{
				h += u[i];
			}
		}
		string y = postfix(h, l);
		w = 0;
		while (y[w] != '\0')
			w++;
		h = "";
		for (int i = w - 1; i >= 0; i--)
		{
			if (y[i] != ' ')
			{
				h += y[i];
			}
		}
		return h;
	}
	else
	{
		return " Invalid Expression ";
	}
}
string infix(string a, Stack<string>* stac)
{
	int i = 0;
	while (a[i] != '\0')i++;
	string qw = "";
	if (a[i - 1] == '^' || a[i - 1] == '+' || a[i - 1] == '*' || a[i - 1] == '-' || a[i - 1] == '/')
	{
		for (int h = 0; h < i; h++)
		{
			if ((a[h] >= 'a' && a[h] <= 'z') || (a[h] >= 'A' && a[h] <= 'Z') || (a[h] >= '0' && a[h] <= '9'))
			{
				string w = "";
				w += a[h];
				stac->push(w);
			}
			else
			{
				string w = "";
				w += a[h];
				string op = stac->top();
				stac->pop();
				if (stac->che() == 0)
				{
					string tp = stac->top();
					stac->pop();
					qw += "( " + tp + w + op + " )";
					stac->push(qw);
					qw = "";
				}
				else
				{
					return " Invalid Expression ";
				}
			}
		}
		qw = stac->top();
		stac->pop();
		return qw;
	}
	else
		return a;
}
void func1(int &fault,int &hit)
{
	int q = 0;
	Queue1<int>* queue = NULL;
	/*for (int i = 0; i < 4; i++)
	{
		queue->enqueue("a");
	}*/
	string start = "|start|", end = "|\\start|";
	string priority = "|priorty|", priority_e = "|\\priorty|";;
	string tab = "|tab|", tab_e = "|\\tab|";
	string para_e = "|\\paragraph|"; string paragraph = "|paragraph|";
	string head = "|head|", head_e = "|\\head|";
	string fil = "Test-1.txt";
	string fil1 = "Test-2.txt";
	string fil2 = "Test-3.txt";
	string fil3 = "Test-4.txt";
	string fil4 = "Test-5.txt";
	string fil5 = "Test-6.txt";
	string fil6 = "Test-7.txt";
	string file = "";
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
			file = fil;
		else if (i == 1)
			file = fil1;
		else if (i == 2)
			file = fil2;
		else if (i == 3)
			file = fil3;
		else if (i == 4)
			file = fil4;
		else if (i == 5)
			file = fil5;
		else if (i == 6)
			file = fil6;
		Stack<string>* stac = new Stack<string>();
		int pr = 0; bool p = 0;
		fstream myfi;
		int c = 0;
		string w = ""; myfi.open(file.c_str());
		string wordre = "";
		ifstream filech;
		filech.open(file.c_str());
		while (filech >> wordre)
		{
			int tag1 = 0;
			bool check1 = 0;
			int yu1 = 0;
			while (wordre[yu1] != '\0')
				yu1++;
			bool c21 = 0;
			string on1 = "";
			string to1 = "";
			int c1 = 0;


			filech.close();
			if (1)
			{
				while (myfi >> w)
				{
					int tag = 0;
					bool check = 0;
					int yu = 0;
					while (w[yu] != '\0')
						yu++;
					bool c2 = 0;
					string on = "";
					string to = "";
					for (int i = 0; i < yu; i++)
					{
						if (c == 2)
						{
							c2 = 1;
							to += w[i];
						}
						else if (w[i] == '|')
						{
							if (c == 0 && i > 0)
							{
								stac->push(on);
								on = "";
							}
							on += w[i];
							c++;
						}
						else
						{
							on += w[i];
						}
					}if (c2 == 0)
					{
						c = 1;
					}
					for (int i = 0; i < c; i++)
					{
						if (i == 0)
						{
							w = on;
						}
						else
						{
							w = to;
						}
						int tag = 0;
						bool check = 0;
						int yu_ = 0;
						while (w[yu_] != '\0')
							yu_++;
						for (int i_ = 0; i_ < yu_; i_++)
						{
							if (w[i_] == '|')
								tag++;
						}
						if (tag == 2)
						{
							check = 1;
						}
						int ee = 0;
						int po = 1;
						if (w == "|start|")
						{
							stac->push(w);
						}
						else if (w == "|priorty|")
						{
							ee = 0;
							myfi >> w;
							while (w != priority_e)
							{
								if (w != " ")
								{
									ee++;
									stac->push(w);
									/*cout << w << " ";*/
								}
								myfi >> w;
							}
							while (ee >= 1)
							{
								int tr;
								string as = stac->top();
								int i = 0;
								while (as[i] != '\0')i++;
								for (int y = 0; y < i - 1; y++)
									po *= 10;
								for (int wq = 0; wq < i; wq++)
								{
									char sa = as[wq];
									tr = sa - 48;
									tr *= po;
									po /= 10;
									pr += tr;
									ee--;
								}
								stac->pop();
								/*stac->pop();*/
							}
						}
						else if (check == 0)
						{
							stac->push(w);
						}
					}
					c = 0;
				}
				q = pr;
				bool b = 0;
				if (queue != NULL)
				{
					Nodee<int>* ptr = queue->head;
					Nodee<int>* ptr3 = queue->head;
					int i1 = 0;
					while (ptr3 != queue->tail)
					{
						i1++;
						ptr3 = ptr3->next;
					}



					for (int ii = 0; ii <= i1; ii++)
					{
						if (pr == ptr->data)
						{
							hit++;
							b = 1;
							break;
						}
						else
							ptr = ptr->next;
					}
				}
				if (b == 0)
				{
					if (queue == NULL)
					{
						queue = new Queue1<int>();
						queue->enqueue(pr);
					}
					else
					{
						int wq = 0;
						Nodee<int>* ptr2 = queue->head;
						while (ptr2 != queue->tail)
						{
							wq++;
							ptr2 = ptr2->next;
						}
						if (wq == 4)
						{
							queue->Dequeue();
							queue->enqueue(pr);
						}
						else
							queue->enqueue(pr);
					}
					fault++;
				}
			/*	std::cout << pr << endl;*/
			}
			else
			{
				/*std::cout << "Syntax" << endl;*/
			}
			/*std::cout << "==================================================================================================================" << endl;*/
			/*int k = 0;
			pr = q;
			Nodee<int>* ptr = queu->head;
			bool e = 0;
			for (int i = 0; i < 4; i++)
			{
				if (ptr->data < pr)
				{
					e = 1;
					break;
				}
				else
				{
					ptr = ptr->next;
					k++;
				}
			}
			Nodee<int>* ptr2 = queu->head;
			Nodee<string>* ptr3 = qu->head;
			int v1, v2, v3, v4; bool e2 = 0;
			string v11, v22, v33, v44;
			if (e)
			{
				if (k == 0)
				{
					e2 = 1;
					v11 = file; v22 = ptr3->data; ptr3 = ptr3->next; v33 = ptr3->data; ptr3 = ptr3->next;  v44 = ptr3->data;
					v1 = pr; v2 = ptr2->data; ptr2 = ptr2->next; v3 = ptr2->data; ptr2 = ptr2->next;  v4 = ptr2->data;
				}
				else if (k == 1)
				{
					e2 = 1;
					v11 = ptr3->data;  v22 = file; ptr3 = ptr3->next;  v33 = ptr3->data; ptr3 = ptr3->next;  v44 = ptr3->data;
					v1 = ptr2->data;  v2 = pr; ptr2 = ptr2->next;  v3 = ptr2->data; ptr2 = ptr2->next;  v4 = ptr2->data;
				}
				else if (k == 2)
				{
					e2 = 1;
					v11 = ptr3->data; ptr3 = ptr3->next;  v22 = ptr3->data; ptr3 = ptr3->next;  v33 = file;  v44 = ptr3->data;
					v1 = ptr2->data; ptr2 = ptr2->next;  v2 = ptr2->data; ptr2 = ptr2->next;  v3 = pr;  v4 = ptr2->data;
				}
				else if (k == 3)
				{
					e2 = 1;
					v11 = ptr3->data; ptr3 = ptr3->next;  v22 = ptr3->data; ptr3 = ptr3->next;  v33 = ptr3->data; ptr3 = ptr3->next;  v44 = file;
					v1 = ptr2->data; ptr2 = ptr2->next;  v2 = ptr2->data; ptr2 = ptr2->next;  v3 = ptr2->data; ptr2 = ptr2->next;  v4 = pr;
				}
				if (e2)
				{
					for (int i = 0; i < 4; i++)
						queu->Dequeue();
					for (int i = 0; i < 4; i++)
						qu->Dequeue();
					queu->enqueue(v1); queu->enqueue(v2); queu->enqueue(v3); queu->enqueue(v4);
					qu->enqueue(v11); qu->enqueue(v22); qu->enqueue(v33); qu->enqueue(v44);
				}
			}*/
		}
	}
		return ;
}
int main()
{

	string start = "|start|", end = "|\\start|";
	string paragraph = "|paragraph|";
	string priority = "|priorty|", priority_e = "|\\priorty|";
	string postfixq = "|post_exp|", postfix_e = "|\\post_exp|";
	string prefixq = "|pre_exp|";
	string solex = "|sol_exp|", solexp_e = "|\\sol_exp|";
	string tab = "|tab|", tab_e = "|\\tab|";
	string para_e = "|\\paragraph|";
	string pre_e = "|\\pre_exp|";
	string head = "|head|", head_e = "|\\head|";
	string src = "|src|", src_e = "|\\src|";
	string fil = "Test-1.txt";
	string fil1 = "Test-2.txt";
	string fil2 = "Test-3.txt";
	string fil3 = "Test-4.txt";
	string fil4 = "Test-5.txt";
	string fil5 = "Test-6.txt";
	string fil6 = "Test-7.txt";
	int hit = 0;
	int fault = 0;
	string file = "";
	Queue1<string>* queu = new Queue1<string>();
	for (int i = 0; i < 4; i++)
		queu->enqueue("0");
	// finding priority
	func1(fault,hit);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
			file = fil;
		else if (i == 1)
			file = fil1;
		else if (i == 2)
			file = fil2;
		else if (i == 3)
			file = fil3;
		else if (i == 4)
			file = fil4;
		else if (i == 5)
			file = fil5;
		else if (i == 6)
			file = fil6;
		Stack<string>* stac = new Stack<string>();
		int pr = 0; bool p = 0;
		string head_ = "";
		string paragraph_ = "";
		fstream myfi;
		int c = 0;
		string w = ""; myfi.open(file.c_str());
		string wordre = "";
		ifstream filech;
		filech.open(file.c_str());
		Stack<string>* tempone = new Stack<string>();
		Stack<string>* temp_two = new Stack<string>();
		int a1ch = 0;
		int a2ch = 0;
		while (filech >> wordre)
		{
			int tag1 = 0;
			bool check1 = 0;
			int yu1 = 0;
			while (wordre[yu1] != '\0')
				yu1++;
			bool c21 = 0;
			string on1 = "";
			string to1 = "";
			int c1 = 0;
			for (int i = 0; i < yu1; i++)
			{
				if (c1 == 2)
				{
					c21 = 1;
					to1 += wordre[i];
				}
				else if (wordre[i] == '|')
				{
					if (c1 == 0 && i > 0)
						on1 = "";
					on1 += wordre[i];
					c1++;
				}
				else
				{
					on1 += wordre[i];
				}
			}
			if (c21 == 0)
			{
				c1 = 0;
				string a1 = "";
				string a2 = "";
				int aao = 0;
				int aat = 0;
				for (int i = yu1 - 1; i >= 0; i--)
				{
					if (c1 == 2)
					{
						aat++;
						c21 = 1;
						a2 += wordre[i];
					}
					else if (wordre[i] == '|')
					{
						if (c1 == 0 && i != yu1 - 1)
							a1 = "";
						aao++;
						a1 += wordre[i];
						c1++;
					}
					else
					{
						aao++;
						a1 += wordre[i];
					}
				}
				if (c21 == 0)
					c1 = 1;
				else
				{
					on1 = ""; c1 = 2;
					to1 = "";
					for (int i = aao - 1; i >= 0; i--)
					{
						on1 += a1[i];
					}
					for (int i = aat - 1; i >= 0; i--)
					{
						to1 += a2[i];
					}
				}
			}
			for (int i = 0; i < c1; i++)
			{
				if (i == 0)
				{
					wordre = on1;
				}
				else
				{
					wordre = to1;
				}
				if (1)
				{
					yu1 = 0;
					while (wordre[yu1] != '\0')
						yu1++;
					int c11 = 0;
					string a1 = "";
					string a2 = "";
					int aao = 0;
					int aat = 0;
					for (int ib = yu1 - 1; ib >= 0; ib--)
					{
						if (c11 == 2)
						{
							aat++;
							c21 = 1;
							a2 += wordre[ib];
						}
						else if (wordre[ib] == '|')
						{
							if (c1 == 0 && i != yu1 - 1)
								a1 = "";
							aao++;
							a1 += wordre[ib];
							c11++;
						}
						else
						{
							aao++;
							a1 += wordre[ib];
						}
					}
					if (c21 == 0)
						c11 = 1;
					else
					{
						on1 = ""; c11 = 2;
						for (int ia = aao - 1; ia >= 0; ia--)
						{
							on1 += a1[ia];
						}
					}
				}
				int tag1 = 0;
				bool check1 = 0;
				int yu_1 = 0;
				while (wordre[yu_1] != '\0')
					yu_1++;
				for (int i_ = 0; i_ < yu_1; i_++)
				{
					if (wordre[i_] == '|')
						tag1++;
				}
				if (tag1 == 2)
				{
					check1 = 1;
				}
				if (check1 == 1)
				{

					if (wordre[1] != '\\')
					{
						a1ch++;
						tempone->push(wordre);
					}
					else
					{
						temp_two->push(wordre);
						a2ch++;
					}
				}
			}
		}
		int* one = new int;
		*one = 0;
		int* two = new int;
		*two = 0;
		bool x = 0;
		string* a1a = new string[a1ch + 1];
		string* a2a = new string[a2ch + 1];
		if (a1ch == a2ch)
		{
			while (tempone->che() == 0)
			{
				a1a[*one] = tempone->top();
				*one = *one + 1;
				tempone->pop();
			}
			while (temp_two->che() == 0)
			{
				a2a[*two] = temp_two->top();
				*two = *two + 1;
				temp_two->pop();
			}
			for (int i = 0; i < a1ch; i++)
			{
				string jk = "";
				jk += a1a[i];
				int tei = 0;
				while (jk[tei] != 0)
					tei++;
				string hh = "";
				for (int g = 0; g < tei; g++)
				{
					if (g == 1)
					{
						hh += "\\";
						hh += jk[g];
					}
					else
					{
						hh += jk[g];
					}

					for (int j = 0; j < a2ch; j++)
					{
						bool s = 0;
						if (hh == a2a[j])
						{
							s = 1;
							x = s;
							a2a[j] = "0";
							break;
						}
						else
						{
							x = 0;
						}
					}
				}
				if (x == 0)
					break;
			}
		}
		else
		{
			x = 0;
		}
		filech.close();
		if (x)
		{
			while (myfi >> w)
			{
				int tag = 0;
				bool check = 0;
				int yu = 0;
				while (w[yu] != '\0')
					yu++;
				bool c2 = 0;
				string on = "";
				string to = "";
				for (int i = 0; i < yu; i++)
				{
					if (c == 2)
					{
						c2 = 1;
						to += w[i];
					}
					else if (w[i] == '|')
					{
						if (c == 0 && i > 0)
						{
							stac->push(on);
							on = "";
						}
						on += w[i];
						c++;
					}
					else
					{
						on += w[i];
					}
				}if (c2 == 0)
				{
					c = 1;
				}
				for (int i = 0; i < c; i++)
				{
					if (i == 0)
					{
						w = on;
					}
					else
					{
						w = to;
					}
					int tag = 0;
					bool check = 0;
					int yu_ = 0;
					while (w[yu_] != '\0')
						yu_++;
					for (int i_ = 0; i_ < yu_; i_++)
					{
						if (w[i_] == '|')
							tag++;
					}
					if (tag == 2)
					{
						check = 1;
					}
					int ee = 0;
					int po = 1;
					if (w == "|start|")
					{
						stac->push(w);
					}
					else if (w == "|priorty|")
					{
						ee = 0;
						myfi >> w;
						while (w != priority_e)
						{
							if (w != " ")
							{
								ee++;
								stac->push(w);
								/*cout << w << " ";*/
							}
							myfi >> w;
						}
						while (ee >= 1)
						{
							int tr;
							string as = stac->top();
							int i = 0;
							while (as[i] != '\0')i++;
							for (int y = 0; y < i - 1; y++)
								po *= 10;
							for (int wq = 0; wq < i; wq++)
							{
								char sa = as[wq];
								tr = sa - 48;
								tr *= po;
								po /= 10;
								pr += tr;
								ee--;
							}
							stac->pop();
							/*stac->pop();*/
						}
					}
					else if (w == head)
					{
						stac->push(w);
					}
					else if (w == head_e)
					{
						string h = "";
						int y = 0;
						Stack<string>* temporary = new Stack<string>();
						while (stac->top() != head)
						{
							y++;
							h = stac->top();
							temporary->push(h);
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < y; i++)
						{
							head_ += temporary->top();
							temporary->pop();
						}
					}
					else if (w == tab)
					{
						if (p == 1)
						{
							int r = 0;
							Stack<string>* temp = new Stack<string>();
							while (stac->top() != paragraph)
							{
								r++;
								temp->push(stac->top());
							}
							for (int i = 0; i < r; i++)
							{
								paragraph_ += " " + temp->top();
								temp->pop();
							}
						}
						stac->push(w);
					}
					else if (w == tab_e)
					{
						string x = "  ";
						while (stac->top() != tab)
						{
							stac->pop();
						}
						stac->pop();
						stac->push(x);
					}
					else if (w == head_e)
					{
						while (stac->top() != head)
						{
							head_ += stac->top();
							stac->pop();
						}
					}
					else if (w == "|\\start|")
					{
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != start)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						for (int i = 0; i < r; i++)
						{
							paragraph_ += " " + temp->top();
							temp->pop();
						}
					}
					else if (w == paragraph)
					{
						stac->push(w);
						p = 1;
					}
					else if (w == para_e)
					{
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != paragraph)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < r; i++)
						{
							paragraph_ += " " + temp->top();
							temp->pop();
						}
						p = 0;
					}
					else if (w == postfixq)
					{
						if (p == 1)
						{
							int r = 0;
							Stack<string>* temp = new Stack<string>();
							while (stac->top() != paragraph)
							{
								r++;
								temp->push(stac->top());
								stac->pop();
							}
							for (int i = 0; i < r; i++)
							{
								paragraph_ += " " + temp->top();
								temp->pop();
							}
						}
						stac->push(w);
					}
					else if (w == postfix_e)
					{
						string h = "";
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != postfixq)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < r; i++)
						{
							if (temp->top() != " ")
							{
								h += temp->top();
							}
							temp->pop();
						}
						paragraph_ += " " + postfix(h, temp);
					}

					else if (w == "|In_exp|")
					{
						if (p == 1)
						{
							int r = 0;
							Stack<string>* temp = new Stack<string>();
							while (stac->top() != paragraph)
							{
								r++;
								temp->push(stac->top());
								stac->pop();
							}
							for (int i = 0; i < r; i++)
							{
								paragraph_ += " " + temp->top();
								temp->pop();
							}
						}
						stac->push(w);
					}
					else if (w == "|\\In_exp|")
					{
						string h = "";
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != "|In_exp|")
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < r; i++)
						{
							if (temp->top() != " ")
							{
								h += temp->top();
							}
							temp->pop();
						}
						paragraph_ += " " + postfix(h, temp);
					}
					else if (w == solex)
					{
						if (p == 1)
						{
							int r = 0;
							Stack<string>* temp = new Stack<string>();
							while (stac->top() != paragraph)
							{
								r++;
								temp->push(stac->top());
								stac->pop();
							}
							for (int i = 0; i < r; i++)
							{
								paragraph_ += " " + temp->top();
								temp->pop();
							}
						}
						stac->push(w);
					}
					else if (w == "|\\sol_exp|")
					{
						string h = "";
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != solex)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < r; i++)
						{
							if (temp->top() != " ")
							{
								h += temp->top();
							}
							temp->pop();
						}
						paragraph_ += " " + infix(h, temp);
					}


					else if (w == prefixq)
					{
						if (p == 1)
						{
							int r = 0;
							Stack<string>* temp = new Stack<string>();
							while (stac->top() != paragraph)
							{
								r++;
								temp->push(stac->top());
								stac->pop();
							}
							for (int i = 0; i < r; i++)
							{
								paragraph_ += " " + temp->top();
								temp->pop();
							}
						}
						stac->push(w);
					}
					else if (w == pre_e)
					{
						string h = "";
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != prefixq)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						stac->pop();
						for (int i = 0; i < r; i++)
						{
							if (temp->top() != " ")
							{
								h += temp->top();
							}
							temp->pop();
						}
						paragraph_ += " " + prefix(h, temp);
					}
					else if (w == src)
					{
					if (p == 1)
					{
						int r = 0;
						Stack<string>* temp = new Stack<string>();
						while (stac->top() != paragraph)
						{
							r++;
							temp->push(stac->top());
							stac->pop();
						}
						for (int i = 0; i < r; i++)
						{
							paragraph_ += " " + temp->top();
							temp->pop();
						}
					}
					stac->push(w);
					}
					else if (w == src_e)
					{
					string h = "";
					int r = 0;
					Stack<string>* temp = new Stack<string>();
					while (stac->top() != src)
					{
						r++;
						temp->push(stac->top());
						stac->pop();
					}
					stac->pop();
					for (int i = 0; i < r; i++)
					{
						if (temp->top() != " ")
						{
							h += temp->top();
						}
						temp->pop();
					}
					paragraph_ += " " + fun(h);
					}
					else if (check == 0)
					{
						stac->push(w);
					}
				}
				c = 0;
			}
			std::cout << head_ << endl;
			std::cout << paragraph_ << endl;
			std::cout << pr << endl;
			string fn = "Output.txt";
			ofstream newfi;
			newfi.open(fn,    ios::app);
			int qq = 0;
			while (head_ [qq] != '\0')
			{
				newfi << head_[qq];
				qq++;
			}
			string e = "\n";
			qq = 0;
			while (e[qq] != '\0')
			{
				newfi << e[qq];
				qq++;
			}
			qq = 0;
			while (paragraph_[qq] != '\0')
			{
				newfi << paragraph_[qq];
				qq++;
			}
			qq = 0;
			while (e[qq] != '\0')
			{
				newfi << e[qq];
				qq++;
			}
			newfi.close();
		}
		else
		{
			std::cout << "Syntax" << endl;
		}
		std::cout << "==================================================================================================================" << endl;
	}
	ofstream newfi;
	newfi.open("Output.txt",ios::app);
	newfi << "Hit   " << hit << " Fault    " << fault << endl;
	//for (int i = 0; i < 4; i++)
	//{
	//	std::cout << queu->head->data;
	//	queu->head = queu->head->next;
	//}
	//while (myfil >> w)
	//{
	//	
	//}	
}