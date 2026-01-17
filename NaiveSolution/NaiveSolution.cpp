#include <iostream>
#include <string>
using namespace std;

// Class giám đốc
class Leader {
public:
	void receiveRequest(string req) {
		cout << "[Giam Doc] Ok, anh da nghe: " << req << endl;
		cout << "[Giam Doc] Duyet luon!" << endl;
	}
};

// Class lập trình viên 
class Developer {
private:
	string _offer;
public:
	Developer(const string& offer) {
		_offer = offer;
	}

	void askDirectly(Leader* sep) {
		sep->receiveRequest(_offer);
	}
};

int main() {
	Leader* OngSep = new Leader();
	Developer DungLe("Em xin sep tang luong len 5k$");

	DungLe.askDirectly(OngSep);

	delete OngSep;

	system("pause");
	return 0;
}




