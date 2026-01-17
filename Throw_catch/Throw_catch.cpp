#include <iostream>
#include <string>
using namespace std;

class LegacyBankingSystem {
private:
    string _nameBank;
public:
    LegacyBankingSystem(const string& s) {
        _nameBank = s;
    }
    string getXmlRate() {
        return "<rate><currency>USD</currency><value>25000</value></rate>";
    }
};

class FrontendApp {
private:
    string _appName;
public:
    FrontendApp(const string& s) {
        _appName = s;
    }
    void showRateInfo(LegacyBankingSystem* a) {
        string xmlData = a->getXmlRate();
        string val = "0";
        string openTag = "<value>";
        string closeTag = "</value>";

        size_t startPos = xmlData.find(openTag);
        size_t endPos = xmlData.find(closeTag);

        if (startPos != string::npos && endPos != string::npos) {
            startPos += openTag.length();
            val = xmlData.substr(startPos, endPos - startPos);
        }

        cout << "Display JSON: { \"rate\": " << val << " }" << endl;
    }
};

int main() {
    FrontendApp* app = new FrontendApp("Foody");
    LegacyBankingSystem* bank = new LegacyBankingSystem("Crack Bank");

    app->showRateInfo(bank);

    delete app;
    delete bank;
    return 0;
}