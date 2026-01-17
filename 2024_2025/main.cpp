#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Date {
	int day;
	int month;
	int year;
public:
	Date getCurrentDate() {
		return *this;
	}
};

class IRule {
public:
	virtual string apply(string fileName) = 0;
	virtual ~IRule() {}
};

class NormalizeCasing : public IRule {
public:
	string apply(string fileName) {
		string res = "";
		bool newWord = true;
		for (char c : fileName) {
			if (isalpha(c)) {
				if (newWord) {
					newWord = false;
					res += toupper(c);
				}
				else {
					res += tolower(c);
				}
			}
			else {
				newWord = true;
				res += c;
			}
		}
		return res;
	}
};

class RemoveSpecialsCharacter : public IRule {
private:
	string _regex;
public:
	RemoveSpecialsCharacter(string regex = "-_ .") {
		_regex = regex;
	}
	string apply(string fileName) {
		string results = "";
		for (char c : fileName) {
			if (_regex.find(c) == string::npos) {
				results += c;
			}
		}
		return results;
	}
};

class AddDatePrefix : public IRule {
private:
	string formatPattern;
public:
	AddDatePrefix(string pattern = "yyyymmdd_") {
		formatPattern = pattern;
	}
	string padZero(int n, int length) {
		string res = to_string(n);
		while (res.length() < length) {
			res = "0" + res;
		}
		return res;
	}
	string replaceAll(string str, const string& from, const string& to) {
		size_t pos = 0;
		if ((pos = str.find(from, pos)) != string::npos) {
			str.replace(pos, from.length(), to);
			pos += to.length();
		}
		return str;
	}
	string apply(string fileName) {
		/*Date a;
		a = a.getCurrentDate();*/
		int day = 9;
		int month = 7;
		int year = 2025;

		string prefix = formatPattern;
		prefix = replaceAll(prefix, "yyyy", padZero(year, 4));
		prefix = replaceAll(prefix, "mm", padZero(month, 2));
		prefix = replaceAll(prefix, "dd", padZero(day, 2));

		return prefix + fileName;
	}
};

class RenameCVFileUseCase {
private:
	vector<IRule*> ruleChain;
public:
	~RenameCVFileUseCase() {
		for (IRule* x : ruleChain) {
			delete x;
		}
		ruleChain.clear();
	}
	void add(IRule* a) {
		if (a == nullptr) {
			throw exception("Pointer is nullptr");
		}
		ruleChain.push_back(a);
	}
	void readFileRule(const string& nameFileRule) {
		ifstream fi(nameFileRule);
		if (!fi) {
			throw exception("Cannot open the file");
		}
		string line;
		while (getline(fi, line)) {
			size_t spacePos = line.find(' ');
			string type = (spacePos == string::npos) ? line : line.substr(0, spacePos);
			string params = (spacePos == string::npos) ? "" : line.substr(spacePos + 1);

			IRule* tmp = nullptr;
			if (type == "NormalizeCasing") {
				tmp = new NormalizeCasing;
			}
			else if (type == "RemoveSpecialsCharacter") {
				string regex = "";
				size_t pos = params.find('[');
				regex = params.substr(pos + 1);
				regex.pop_back();

				tmp = new RemoveSpecialsCharacter(regex);
			}
			else if (type == "AddDatePrefix") {
				string pattern = "";
				size_t pos = params.find('=');
				pattern = params.substr(pos + 1);

				tmp = new AddDatePrefix(pattern);
			}
			else {
				throw exception("Invalid type");
			}
			ruleChain.push_back(tmp);
		}
	}
	string rename(const string& originalFilename) {
		string res = originalFilename;
		for (IRule* x : ruleChain) {
			res = x->apply(res);
		}
		return res;
	}
};


int main() {
	try {
		RenameCVFileUseCase cvFileRenamer;
		cvFileRenamer.readFileRule("rules.txt");
		string originalFileName = "ho so xin viec_nguyen van a - cv_final.docx";

		string formattedFileName = cvFileRenamer.rename(originalFileName);

		cout << "Original File Name: " << originalFileName << endl;
		cout << "Formatted File Name: " << formattedFileName << endl;
	}
	catch (const exception& ex) {
		cout << "Chuong tring bi loi: " << ex.what() << endl;
	}

	system("pause");
	return 0;
}