#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
#pragma once
class Node {
public:
	int Factor;
	int Exponent[123];
	string Terms_Char;
	Node *Next;
	Node();
	void Cutting(string);
	~Node();
};
class LinkedPolynomial
{

public:
	Node *Head;
	Node *Tail;
	LinkedPolynomial();
	string ToStr();
	void Insert(string);
	void Insert(Node*term);
	void create(string);
	bool Check(string s1, string s2); //checks if the current node from the other polynomial already exists or not
	void Handle(); //operations on the same polynomial
	LinkedPolynomial Add(LinkedPolynomial LP);
	LinkedPolynomial Sub(LinkedPolynomial LP);
	LinkedPolynomial Multiply(LinkedPolynomial LP);
	~LinkedPolynomial();
};