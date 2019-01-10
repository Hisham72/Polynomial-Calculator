#include "LinkedPolynomial.h"
Node::Node() {
	Next = NULL;
	Factor = 1;
	Terms_Char = "";
	for (char i = 'a'; i <= 'z'; i++) {
		Exponent[i] = 1;
	}
}
void Node::Cutting(string s) {
	string tmpS = "";
	char tmpCH;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '-' && i == 0) {
			Factor *= -1;
			continue;
		}
		if (s[i] == '+')
			continue;
		if (isdigit(s[i])) {
			while (i < s.size() && isdigit(s[i])) {
				tmpS += s[i];
				i++;
			}
			Factor *= stoi(tmpS);
			tmpS = "";
		}
		if (i < s.size() && tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z') {
			while (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z')
			{
				Terms_Char += s[i];
				i++;
			}
			i--;
		}
		else if (i < s.size()) {
			tmpCH = s[i - 1];
			i++;
			tmpS = "";
			while (i < s.size() && isdigit(s[i])) {
				tmpS += s[i];
				i++;
			}
			i--;
			Exponent[tmpCH] = stoi(tmpS);
			tmpS = "";
		}

	}
}
Node::~Node() 
{
}


LinkedPolynomial::LinkedPolynomial()
{
	Head = Tail = NULL;

}

bool LinkedPolynomial::Check(string s1, string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < s1.size(); i++) {
			if (s1.find(s2[i]) == -1) {
				return false;
			}
		}
		return true;
	}
}

void LinkedPolynomial::Handle() {
	Node *currentN = Head, *prev = Head, *nextN;
	bool isEqual = 1;
	string tmp;
	while (currentN != NULL)
	{
		nextN = currentN->Next;
		prev = currentN;
		while (nextN != NULL)
		{
			isEqual = 1;
			if (Check(currentN->Terms_Char, nextN->Terms_Char)) {
				for (auto i : currentN->Terms_Char) {
					if (currentN->Exponent[i] != nextN->Exponent[i]) {
						isEqual = 0;
						break;
					}
				}
			}
			else {
				isEqual = 0;
			}
			if (isEqual) {
				currentN->Factor += nextN->Factor;
				prev->Next = nextN->Next;
				delete nextN;
			}
			else {
				prev = nextN;
			}
			nextN = prev->Next;

		}
		currentN = currentN->Next;
	}
}

void LinkedPolynomial::create(string s) {
	Node *newNode = new Node();
	newNode->Cutting(s);
	if (Head == NULL) {
		Head = Tail = newNode;
	}
	else {
		Tail->Next = newNode;
		Tail = newNode;
	}
}

void LinkedPolynomial::Insert(string s) {
	string tmp = "";
	for (int i = 0; i < s.size(); i++) {
		if (i == 0 || (s[i] != '+' && s[i] != '-'))
			tmp += s[i];
		else {
			create(tmp);
			tmp = "";
			tmp += s[i];
		}
	}
	create(tmp);
	Handle();
}

void LinkedPolynomial::Insert(Node *term) {
	if (Head == NULL) {
		Head = Tail = term;
	}
	else {
		Tail->Next = term;
		Tail = term;
	}
}

LinkedPolynomial LinkedPolynomial::Add(LinkedPolynomial LP) {
	LinkedPolynomial newP;
	Node *tmp = Head;
	while (tmp != NULL) {
		newP.Insert(tmp);
		tmp = tmp->Next;
	}
	tmp = LP.Head;
	while (tmp != NULL) {
		newP.Insert(tmp);
		tmp = tmp->Next;
	}
	newP.Handle();
	return newP;
}
string LinkedPolynomial::ToStr() {
	string s = "";
	Node *tmp = Head;
	while (tmp != NULL)
	{
		if (tmp->Factor != 0) {
			if (tmp->Factor != 0) {
				//if (tmp != Head)
					//s += ' ';
				if (tmp->Factor >= 0 && tmp != Head)
					s += "+";
				if (tmp->Factor != 1) {
					if (tmp->Factor == -1) {
						s += '-';
						//if (tmp != Head)
							//s += ' ';
					}
					else {
						stringstream ss; string x;
						ss << tmp->Factor;
						ss >> x;
						/*if (x[0] == '-' && tmp != Head) {
							x.insert(1, 1, ' ');
						}*/
						s += x;
					}
				}
			}

			for (int i = 0; i < tmp->Terms_Char.size(); i++) {
				s += tmp->Terms_Char[i];
				if (tmp->Exponent[tmp->Terms_Char[i]] > 1) {
					s += '^';
					s += tmp->Exponent[tmp->Terms_Char[i]] + '0';
				}
			}
		}
		tmp = tmp->Next;
	}
	return s;
}
LinkedPolynomial LinkedPolynomial::Sub(LinkedPolynomial LP) {
	LinkedPolynomial newP;
	Node *tmp = Head;
	while (tmp != NULL) {
		newP.Insert(tmp);
		tmp = tmp->Next;
	}
	tmp = LP.Head;
	while (tmp != NULL) {
		tmp->Factor *= -1;
		newP.Insert(tmp);
		tmp = tmp->Next;
	}
	newP.Handle();
	return newP;
}

LinkedPolynomial LinkedPolynomial::Multiply(LinkedPolynomial LP) {
	LinkedPolynomial newP;
	Node *tmp1 = Head, *tmp2 = LP.Head;
	while (tmp1 != NULL) {
		tmp2 = LP.Head;
		while (tmp2 != NULL) {
			Node *newNode = new Node();
			newNode->Factor *= tmp1->Factor * tmp2->Factor;
			newNode->Terms_Char = tmp1->Terms_Char;
			for (int i = 0; i < tmp1->Terms_Char.size(); i++) {
				newNode->Exponent[tmp1->Terms_Char[i]] = tmp1->Exponent[tmp1->Terms_Char[i]];
			}
			for (int i = 0; i < tmp2->Terms_Char.size(); i++) {
				if (newNode->Terms_Char.find(tmp2->Terms_Char[i]) != -1) {
					newNode->Exponent[tmp2->Terms_Char[i]] += tmp2->Exponent[tmp2->Terms_Char[i]];
				}
				else {
					newNode->Terms_Char += tmp2->Terms_Char[i];
					newNode->Exponent[tmp2->Terms_Char[i]] = tmp2->Exponent[tmp2->Terms_Char[i]];
				}
			}
			newP.Insert(newNode);
			tmp2 = tmp2->Next;
		}
		tmp1 = tmp1->Next;
	}
	newP.Handle();
	return newP;
}

LinkedPolynomial::~LinkedPolynomial()
{
}
