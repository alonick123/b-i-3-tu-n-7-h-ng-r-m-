#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#define MAX_equations 10
using namespace std;
using namespace std::chrono;

//khai bao ham so thuc
//---------------------------------------
struct real {  //he so so thuc
	double A, B, C, D, solution;
	int result = 0;
};

int solve(double a, double b);  //ham giai Ax + B = 0
int solve(double a, double b, double c, double d);  //Ax + B = Cx + D
void SolutionReal(real& a, char choice);   //xuat dap an va luu nghiem
void inputRealCoeffecient(double& a, char name);   //nhap he so
void real_Num(real& a, bool& flag, char choice);   //thuc hien cac ham tren


//khai bao ham phan so
//---------------------------------------
struct fraction { //khai bao phan so
	int num, den = 1;  //numerator va denominator
};

struct FractionCoefficient {  //he so phan so
	fraction A, B, C, D, solution;
	int result = 0;
};

int GCD(int a, int b);  //tim uoc chung lon nhat
void simplify(fraction& a);  //rut gon phan so va chuyen dau tru len tu so
fraction CalF(fraction a, fraction b);   //tinh hieu giua 2 phan so
int solve(fraction a, fraction b);  //giai Ax + B = 0
int solve(fraction a, fraction b, fraction c, fraction d);  //giai Ax + B = Cx + D
void SolutionFraction(FractionCoefficient& a, char choice);  //xuat dap an va luu nghiem
void inputCoefficient(fraction& a, char name);  //nhap he so
void Fraction(FractionCoefficient& a, char choice, bool& flag);  //thuc hien cac ham tren


//khai bao so thuc
//----------------------------------------
struct complex {  //so thuc
	double real, img;
};

struct ComplexCoefficient {  //he so so thuc
	complex A, B, C, D, solution;
	int result = 0;
};

int solve(complex a, complex b);
int solve(complex a, complex b, complex c, complex d);
void printComplexSolution(double real, double img);
void ComplexSolution(ComplexCoefficient& a, char choice);
void inputComplex(complex& a, char name);
void Complex(ComplexCoefficient& a, char choice, bool& flag);


//khai bao loai phuong trinh
struct equation {
	char type;
	FractionCoefficient F;
	real R;
	ComplexCoefficient C;
};

void printAllEquations(equation arr[], int i, bool flag);  //in lai toan bo phuong trinh da nhap

int main() {
	auto start = chrono::high_resolution_clock::now();
	char choice; int i = 0; bool flag = false;
	equation arr[MAX_equations];

	cout << "---------------------------------------\n";
	cout << "Giai phuong trinh\n";
	cout << "R. Ax + B = Cx + D tren truong so thuc\n"
		 << "r. Ax + B = 0 tren truong so thuc\n"
		 << "F. Ax + B = Cx + D tren truong phan so\n"
		 << "f. Ax + B = 0 tren truong phan so\n"
		 << "C. Ax + B = Cx + D tren truong so phuc\n"
		 << "c. Ax + B = 0 tren truong so phuc\n";
	cout << "---------------------------------------\n";
	for (i = 0; i < MAX_equations; ++i) {
		//dem gio
		auto end = chrono::high_resolution_clock::now();
		if (duration_cast<seconds>(end - start).count() >= 3600) {
			cout << "Da het 10 phut\n";
			break;
		}

		cout << "\nNhap phuong trinh " << i + 1 << '\n';
		do {
			cout << "Chon loai phuong trinh: "; cin >> choice;
		} while (choice != 'R' && choice != 'r' && choice != 'F' && choice != 'f' && choice != 'C' && choice != 'c');

		switch (choice) {
			case 'R': {
				arr[i].type = 'R';
				real_Num(arr[i].R, flag, choice);
				break;
			}
			case 'r': {
				arr[i].type = 'r';
				real_Num(arr[i].R, flag, choice);
				break;
			}
			case 'F': {
				arr[i].type = 'F';
				Fraction(arr[i].F, choice, flag);
				break;
			}
			case 'f': {
				arr[i].type = 'f';
				Fraction(arr[i].F, choice, flag);
				break;
			}
			case 'C': {
				arr[i].type = 'C';
				Complex(arr[i].C, choice, flag);
				break;
			}
			case 'c': {
				arr[i].type = 'c';
				Complex(arr[i].C, choice, flag);
				break;
			}
		}

		if (flag) break;  //ra tin hieu khong nhap phuong trinh nua
	}

	cout << '\n';
	printAllEquations(arr, i, flag);

	return 0;
}

//truong so thuc
//---------------------------------------
int solve(double a, double b) { //giai Ax + B = 0
	if (!a && b) return 0; //khong co nghiem
	return 1; //co 1 nghiem
}

int solve(double a, double b, double c, double d) { //giai Ax + B = Cx + D
	if (!(a - c) && (b - d)) return 0; //khong co nghiem
	if (!(a - c) && !(b - d)) return -1;  //co vo so nghiem
	return 1; //co 1 nghiem
}

void SolutionReal(real& a, char choice) {
	if (choice == 'R') {
		int Result = solve(a.A, a.B, a.C, a.D);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case -1: {
				a.result = -1;
				cout << "Phuong trinh vo so nghiem\n"; break;
			}

			case 1: {
				a.result = 1;
				cout << "Phuong trinh co 1 nghiem: " << setprecision(3) << (a.D - a.B) / (a.A - a.C) << '\n';
				a.solution = (a.D - a.B) / (a.A - a.C);
			}
		}
	}
	else {
		int Result = solve(a.A, a.B);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case 1: {
				a.result = 1;
				cout << "Phuong trinh co 1 nghiem: " << setprecision(3) << -a.B / a.A << '\n';
				a.solution = -a.B / a.A;
			}
		}
	}
}

void inputRealCoeffecient(double& a, char name) {
	cout << "Nhap he so " << name << ": "; cin >> a;
}

void real_Num(real& a, bool& flag, char choice) {
	//nhap he so
	inputRealCoeffecient(a.A, 'A');
	inputRealCoeffecient(a.B, 'B');
	if (choice == 'R') {
		inputRealCoeffecient(a.C, 'C');
		inputRealCoeffecient(a.D, 'D');
	}
	//kiem tra he so
	if (choice == 'r') {
		if (!a.A && !a.B) {
			flag = true;
			return;
		}
	}
	else {
		if (!a.A && !a.B && !a.C && !a.D) {
			flag = true;
			return;
		}
	}
	cout << '\n';
	SolutionReal(a, choice);
}


//ham giai phan so
//--------------------------------------------
int GCD(int a, int b) {
	a = abs(a); b = abs(b); int r = 0;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void simplify(fraction& a) {
	int gcd = GCD(a.num, a.den);  //rut gon phan so
	a.num /= gcd;
	a.den /= gcd;

	if (a.den < 0) {  // chuyen dau tru len tu so
		a.num = -a.num;
		a.den = -a.den;
	}
}

fraction CalF(fraction a, fraction b) {  // ham tinh hieu 2 phan so
	fraction c;
	c.num = a.num * b.den - a.den * b.num;
	c.den = a.den * b.den;
	simplify(c);
	return c;
}

int solve(fraction a, fraction b) {  //ham giai Ax + B = 0
	if (!a.num && b.num) return 0;  //khong co nghiem
	return 1;  //co 1 nghiem
}

int solve(fraction a, fraction b, fraction c, fraction d) { //ham giai Ax + B = Cx + D
	if ((double(a.num) / a.den) == (double(c.num) / c.den) && (double(b.num) / b.den) == (double(d.num) / d.den)) return -1;  //vo so nghiem
	a = CalF(a, c); b = CalF(b, d);
	if (!a.num && b.num) return 0;  //khong co nghiem
	return 1;  //co 1 nghiem
}

void SolutionFraction(FractionCoefficient& a, char choice) {  //ham giai phuong trinh va luu ket qua
	int Result = 0;
	if (choice == 'F') {
		Result = solve(a.A, a.B, a.C, a.D);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case -1: {
				cout << "Phuong trinh co vo so nghiem\n";
				a.result = -1;
				break;
			}

			case 1: {
				fraction A = CalF(a.A, a.C); fraction B = CalF(a.B, a.D);
				fraction sol = { -B.num * A.den, A.num * B.den };
				simplify(sol);
				cout << "Phuong trinh co 1 nghiem: " << sol.num << "/" << sol.den << '\n';
				a.result = 1;
				a.solution = sol;
			}
		}
	}
	else {
		Result = solve(a.A, a.B);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case 1: {
				fraction sol = { -a.B.num * a.A.den, a.A.num * a.B.den };
				simplify(sol);
				cout << "Phuong trinh co 1 nghiem: " << sol.num << "/" << sol.den << '\n';
				a.result = 1;
				a.solution = sol;
			}
		}
	}
}

void inputCoefficient(fraction& a, char name) {  //nhap he so
	cout << "Nhap he so " << name << '\n';
	cout << "Nhap tu so: "; cin >> a.num;
	if (a.num) {
		do {
			cout << "Nhap mau so: "; cin >> a.den;
		} while (!a.den);
	}
	simplify(a);
}

void Fraction(FractionCoefficient& a, char choice, bool& flag) {
	inputCoefficient(a.A, 'A');
	inputCoefficient(a.B, 'B');
	if (choice == 'F') {
		inputCoefficient(a.C, 'C');
		inputCoefficient(a.D, 'D');
	}

	//kiem tra he so de xem co bang 0 het hay khong
	if (choice == 'F') {
		if (!a.A.num && !a.B.num && !a.C.num && !a.D.num) {
			flag = true;
			return;
		}
	}
	else {
		if (!a.A.num && !a.B.num) {
			flag = true;
			return;
		}
	}

	//giai phuong trinh
	SolutionFraction(a, choice);
}


//giai so phuc
//---------------------------------
int solve(complex a, complex b) { //giai phuong trinh Ax + B = 0
	if (!a.real && !a.img) {
		if (b.real || b.img) return 0;  //khong co nghiem
	}
	return 1;  //co 1 nghiem
}

int solve(complex a, complex b, complex c, complex d) {  //giai phuong trinh Ax + B = Cx + D
	complex t1 = { 0,0 }, t2 = { 0,0 };
	t1.real = a.real - c.real;
	t1.img = a.img - c.img;
	t2.real = b.real - d.real;
	t2.img = b.img - d.img;
	if (!t1.real && !t1.img) {
		if (!t2.real && !t2.img) return -1;  //vo so nghiem
		return 0;  //khong co nghiem
	}
	return 1;  //co 1 nghiem
}

void printComplexSolution(double real, double img) {  //in dap an
	if (!real && !img)
	{
		cout << "Phuong trinh co nghiem: 0\n";
	}
	else if (!real) {
		cout << setprecision(2) << "Phuong trinh co nghiem: " << img << "i\n";
	}
	else if (!img) {
		cout << setprecision(2) << "Phuong trinh co nghiem: " << real << '\n';
	}
	else {
		cout << setprecision(2) << "Phuong trinh co nghiem: " << real << " + " << img << "i\n";
	}
}

void ComplexSolution(ComplexCoefficient& a, char choice) {  //ham giai phuong trinh
	if (choice == 'C') {
		int Result = solve(a.A, a.B, a.C, a.D);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case -1: {
				cout << "Phuong trinh vo so nghiem\n";
				a.result = -1;
				break;
			}

			case 1: {
				a.result = 1;
				complex t1 = { 0,0 }, t2 = { 0,0 };
				t1.real = a.A.real - a.C.real;
				t1.img = a.A.img - a.C.img;
				t2.real = a.B.real - a.D.real;
				t2.img = a.B.img - a.D.img;

				//tinh toan nghiem
				a.solution.real = -(t2.real * t1.real + t2.img * t1.img) / (t1.real * t1.real + t1.img * t1.img);
				a.solution.img = -(t1.real * t2.img - t1.img * t2.real) / (t1.real * t1.real + t1.img * t1.img);
				//xuat nghiem
				printComplexSolution(a.solution.real, a.solution.img);
			}
		}
	}
	else {
		int Result = solve(a.A, a.B);
		switch (Result) {
			case 0: cout << "Phuong trinh vo nghiem\n"; break;

			case 1: {
				a.result = 1;

				//tinh toan nghiem
				a.solution.real = (a.A.real * -a.B.real + a.A.img * -a.B.img) / (a.A.real * a.A.real + a.A.img * a.A.img);
				a.solution.img = (-a.A.real * a.B.img + a.A.img * a.B.real) / (a.A.real * a.A.real + a.A.img * a.A.img);
				//xuat nghiem
				printComplexSolution(a.solution.real, a.solution.img);
			}
		}
	}
}

void inputComplex(complex& a, char name) {  //ham nhap he so phuc
	cout << "Nhap he so " << name << " \n";
	cout << "Nhap phan thuc: "; cin >> a.real;
	cout << "Nhap phan ao: "; cin >> a.img;
}

void Complex(ComplexCoefficient& a, char choice, bool& flag) {  //ham xu ly so phuc
	//nhap he so
	inputComplex(a.A, 'A');
	inputComplex(a.B, 'B');
	if (choice == 'C') {
		inputComplex(a.C, 'C');
		inputComplex(a.D, 'D');
	}

	//kiem tra he so
	if (choice == 'C') {
		if (!(a.A.real) && !(a.A.img) && !(a.B.real) && !(a.B.img) && !(a.C.real) && !(a.C.img) && !(a.D.real) && !(a.D.img)) {
			flag = true;
			return;
		}
	}
	else {
		if (!(a.A.real) && !(a.A.img) && !(a.B.real) && !(a.B.img)) {
			flag = true;
			return;
		}
	}

	//tao bien phu roi gan ham solve
	ComplexSolution(a, choice);
}

void printAllEquations(equation arr[], int i, bool flag) {  //in lai toan bo phuong trinh da nhap
	if (flag) i--;
	for (int j = 0; j <= i; ++j) {
		switch (arr[j].type) {  //kiem tra loai phuong trinh, xuat ket qua tuong ung
			case 'R': {
				cout << "Phuong trinh (" << arr[j].R.A << ")x + (" << arr[j].R.B << ") = (" << arr[j].R.C << ")x + (" << arr[j].R.D << ") ";
				switch (arr[j].R.result) {
					case 0: cout << " vo nghiem\n"; break;
					case -1: cout << " co vo so nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].R.solution << '\n';
				}
				break;
			}
			case 'r': {
				cout << "Phuong trinh (" << arr[j].R.A << ")x + (" << arr[j].R.B << ") = 0 ";
				switch (arr[j].R.result) {
					case 0: cout << " vo nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].R.solution << '\n';
				}
				break;
			}
			case 'F': {
				cout << "Phuong trinh (" << arr[j].F.A.num << "/" << arr[j].F.A.den << ")x + (" 
					 << arr[j].F.B.num << "/" << arr[j].F.B.den << ") =  ("
					 << arr[j].F.C.num << "/" << arr[j].F.C.den << ")x + ("
					 << arr[j].F.D.num << "/" << arr[j].F.D.den << ") ";
				switch (arr[j].F.result) {
					case 0: cout << " vo nghiem\n"; break;
					case -1: cout << " co vo so nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].F.solution.num << "/" << arr[j].F.solution.den << '\n';
				}
				break;
			}
			case 'f': {
				cout << "Phuong trinh (" << arr[j].F.A.num << "/" << arr[j].F.A.den << ")x + ("
					 << arr[j].F.B.num << "/" << arr[j].F.B.den << ") = 0";
				switch (arr[j].F.result) {
					case 0: cout << " vo nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].F.solution.num << "/" << arr[j].F.solution.den << '\n';
				}
				break;
			}
			case 'C': {
				cout << "Phuong trinh (" << arr[j].C.A.real << " + " << arr[j].C.A.img << ")x + ("
					<< arr[j].C.B.real << " + " << arr[j].C.B.img << ") =  ("
					<< arr[j].C.C.real << " + " << arr[j].C.C.img << ")x + ("
					<< arr[j].C.D.real << " + " << arr[j].C.D.img << ") ";
				switch (arr[j].C.result) {
					case 0: cout << " vo nghiem\n"; break;
					case -1: cout << " co vo so nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].C.solution.real << " + " << arr[j].C.solution.img << '\n';
				}
				break;
			}
			case 'c': {
				cout << "Phuong trinh (" << arr[j].C.A.real << " + " << arr[j].C.A.img << ")x + ("
					<< arr[j].C.B.real << " + " << arr[j].C.B.img << ") = 0 ";
				switch (arr[j].C.result) {
					case 0: cout << " vo nghiem\n"; break;
					case 1: cout << " co 1 nghiem: " << arr[j].C.solution.real << " + " << arr[j].C.solution.img << '\n';
				}
			}
		}
	}
}