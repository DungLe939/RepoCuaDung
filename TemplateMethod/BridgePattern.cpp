#include <iostream>
#include <string>
using namespace std;

class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int v) = 0;
    virtual ~Device() {}
};

class TV : public Device {
private:
    int volume = 50;
    bool isOn = false;
public:
    void turnOn() override {
        isOn = true;
        cout << "TV is ON" << endl;
    }
    void turnOff() override {
        isOn = false;
        cout << "TV is OFF" << endl;
    }
    void setVolume(int v) override {
        volume = v;
        cout << "TV volume: " << volume << endl;
    }
    int getVolume() override { return volume; }
};

class Radio : public Device {
private:
    int volume = 30;
    bool isOn = false;
public:
    void turnOn() override {
        isOn = true;
        cout << "Radio is ON" << endl;
    }
    void turnOff() override {
        isOn = false;
        cout << "Radio is OFF" << endl;
    }
    void setVolume(int v) override {
        volume = v;
        cout << "Radio volume: " << volume << endl;
    }
    int getVolume() override { return volume; }
};

// Bridge pattern

// Abstract bridge
class Remote {
protected:
    Device* device; 
public:
    Remote(Device* dev) : device(dev) {}

    virtual void power() {
        cout << "Power button pressed" << endl;
    }
    virtual void volumeUp() {
        device->setVolume(device->getVolume() + 10);
    }
    virtual void volumeDown() {
        device->setVolume(device->getVolume() - 10);
    }
    virtual ~Remote() {}
};

class AdvancedRemote : public Remote {
public:
    AdvancedRemote(Device* dev) : Remote(dev) {}

    void mute() {
        device->setVolume(0);
        cout << "Muted!" << endl;
    }

    void turboVolume() {
        device->setVolume(100);
        cout << "TURBO MODE!" << endl;
    }
};

int main() {

    // Tạo các thiết bị
    TV tv;
    Radio radio;

    // Remote cơ bản điều khiển TV
    cout << "=== Basic Remote + TV ===" << endl;
    Remote* remote1 = new Remote(&tv);
    remote1->power();
    remote1->volumeUp();

    // Remote nâng cao điều khiển Radio
    cout << "\n=== Advanced Remote + Radio ===" << endl;
    AdvancedRemote* remote2 = new AdvancedRemote(&radio);
    remote2->volumeUp();
    remote2->mute();

    // Remote nâng cao điều khiển TV
    cout << "\n=== Advanced Remote + TV ===" << endl;
    AdvancedRemote* remote3 = new AdvancedRemote(&tv);
    remote3->turboVolume();

    delete remote1;
    delete remote2;
    delete remote3;

    system("pause");
    return 0;
}