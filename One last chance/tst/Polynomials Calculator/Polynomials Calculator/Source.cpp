#include <iostream>
#include <string>
#include <vector>
#include "LinkedPolynomial.h"
#include "Clex.h"
using namespace std;
CLEX stored[100];
int size_stored = 0;

bool check(string s1, string s2) {
	if (s2[0] != '-')
		s2 += '+';
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


void load()
{
	fstream file;
	int i = 0;
	file.open("history.txt");
	while (!file.eof()) {
		file >> stored[i].Eq1 >> stored[i].cc >> stored[i].Eq2 >> stored[i].result;
		i++;
	}
	size_stored = i - 1;
}



void save()
{

	fstream file;
	file.open("history.txt", ios::out);
	for (int i = 0; i <= size_stored; i++) {
		if (stored[i].Eq1 != "just skip it")
			file << stored[i].Eq1 << ' ' << stored[i].cc << ' ' << stored[i].Eq2 << ' ' << stored[i].result << endl;
	}
}

string isValid(string poly) {
	for (int i = 0; i < poly.size(); i++) {
		if (poly[i] == '-' && i == 0)
			continue;
		else if (poly[i] == '+' || poly[i] == '-')
			return " Invalid input..Check the operators & enter the polynomial again: ";
		bool checked[123] = { 0 };
		if(i < poly.size() && poly[i] != '+' && poly[i] != '-') {
			if (isdigit(poly[i])) {
				while (i < poly.size() && isdigit(poly[i])) {
					i++;
					//cout << "  WHY  " << poly[i] << "\n";
				}
			}
			if (i < poly.size() && tolower(poly[i]) >= 'a' && tolower(poly[i]) <= 'z') {
				while (i < poly.size() && tolower(poly[i]) >= 'a' && tolower(poly[i]) <= 'z') {
					if (!checked[poly[i]]) {
						checked[poly[i]] = 1;
						i++;
					}
					else {
						return " Invalid input..Check the repeatition of the characters & enter the polynomial again: ";
					}
				}
			}
			if (i < poly.size() && poly[i] == '^') {
				i++;
				if (i < poly.size() && isdigit(poly[i])) {
					while (i < poly.size() && isdigit(poly[i])) {
						i++;
					}
				}
				else {
					return " Invalid input..Check the exponintials & enter the polynomial again:";
				}
			}
		}

	}
	return "OK";
}

string removeSpaces(string s) {
	string tmp = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != ' ')
			tmp += s[i];
	}
	return tmp;
}

void displayHistory() {
	cout << "\nHere is the history of our lovely calculator:\n";
	for (int i = 0; i < size_stored; i++)
	{
		cout << stored[i].Eq1 << "\n";
		cout << stored[i].cc << "\n";
		cout << stored[i].Eq2 << "\n";
		
		for (int j = 0; j <= max(stored[i].Eq1.size(), stored[i].Eq2.size()); j++)
			cout << '-';
		cout << '\n';
		cout << stored[i].result << "\n\n";
	}
}

int main() {

	system("color FD");
	while (true) {
		system("CLS");
		size_stored = 0;
		load();
		string s1, s2, answer, choice;
		char op;
		bool skip = 0;
		cout << "Enter \"1\" to calculate 2 polynomials or \"2\" to view history: ";
		cin >> choice;
		while (choice != "1" && choice != "2") {
			cout << " Invalid input..Enter only 1 or 2: ";
			cin >> choice;
		}
		if (choice == "2") {
			displayHistory();
		}
		else {
			cout << "\nEnter the 1st polynomial: ";
			cin.clear();
			cin.ignore(10000, '\n');
			getline(cin, s1);
			//cin.clear();
			//cin.ignore(100000, '\n');
			s1 = removeSpaces(s1);
			//cout << "  hi  " << s1 << '\n';
			//cout << " " << s1 << '\n';
			while (isValid(s1) != "OK") {
				cout << isValid(s1);
				
				getline(cin, s1);
				s1 = removeSpaces(s1);
			}
			cout << "\nEnter the oprator: ";
			cin >> op;
			while (op != '+' && op != '-' && op != '*') {
				cout << " Kindly enter +, -, * only: ";
				cin >> op;

			}
			cout << "\nEnter the 2nd polynomial: ";
			cin.clear();
			cin.ignore(10000, '\n');
			getline(cin, s2);
			/*cin.clear();
			cin.ignore(100000, '\n');*/
			s2 = removeSpaces(s2);
			//cout << "  hi  " << s2 << '\n';
			while (isValid(s2) != "OK") {
				cout << isValid(s2);
				
				getline(cin, s2);
				s2 = removeSpaces(s2);
			}
			stored[size_stored].cc = op;
			stored[size_stored].Eq1 = s1;
			stored[size_stored].Eq2 = s2;
			LinkedPolynomial p1, p2, ans;
			p1.Insert(s1);
			p2.Insert(s2);
			s1 = p1.ToStr();
			s2 = p2.ToStr();
			if (s1[0] != '-')
				s1 += '+';
			if (s2[0] != '-')
				s2 += '+';
			for (int i = 0; i < size_stored; i++) {
				if (op == stored[i].cc) {
					if (check(s1, stored[i].Eq1)) {
						//cout << "1 done\n";
						if (check(s2, stored[i].Eq2)) {
							cout << "\nHere is the answer: " << stored[i].result << "\n";
							stored[size_stored].result = stored[i].result;
							stored[i].Eq1 = "just skip it";
							save();
							skip = 1;
							break;
						}
					}
					else if (check(s2, stored[i].Eq1)) {
						//cout << "1 done\n";
						if (check(s1, stored[i].Eq2)) {
							cout << "\nHere is the answer: " << stored[i].result << "\n";
							stored[size_stored].result = stored[i].result;
							stored[i].Eq1 = "just skip it";
							save();
							skip = 1;
							break;
						}
					}
				}

			}
			if (!skip) {
				if (op == '*')
					ans = p1.Multiply(p2);
				else if (op == '+')
					ans = p1.Add(p2);
				else if (op == '-')
					ans = p1.Sub(p2);
				answer = ans.ToStr();
				stored[size_stored].result = answer;
				save();
				cout << "\nHere is the answer: " << answer << '\n';
			}
		}
		cout << "\n\n";
		string final_choice;
		cout << "Enter any value to continue or \"0\" to exit: ";
		cin >> final_choice;
		if (final_choice == "0")
			break;
	}
		
	
		//cout << p1.Check(s1, s2) << endl;;

	return 0;
}