#include <iostream>
#include <string>
using namespace std;
class IDocument {
public:
    virtual ~IDocument() = default;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void read() = 0;
};
class RealDocument : public IDocument {
private:
    string filename;
    bool isOpen;
public:
    RealDocument(const string& filename) : filename(filename), isOpen(false) {
        cout << "Loading document: " << filename << endl;
    }
    void open() override {
        if (!isOpen) {
            cout << "Opening document: " << filename << endl;
            isOpen = true;
        }
    }
    void close() override {
        if (isOpen) {
            cout << "Closing document: " << filename << endl;
            isOpen = false;
        }
    }
    void read() override {
        if (isOpen) {
            cout << "Reading document: " << filename << endl;
        }
        else {
            cout << "Document is not open." << endl;
        }
    }
};
class DocumentProxy : public IDocument {
private:
    string filename;
    RealDocument* realDocument;

public:
    DocumentProxy(const string& filename) : filename(filename), realDocument(nullptr) {}
    ~DocumentProxy() {
        delete realDocument;
    }
    void open() override {
        if (!realDocument) {
            realDocument = new RealDocument(filename);
        }
        realDocument->open();
    }
    void close() override {
        if (realDocument) {
            realDocument->close();
        }
    }
    void read() override {
        if (!realDocument) {
            realDocument = new RealDocument(filename);
        }
        realDocument->read();
    }
};
void client(IDocument& document) {
    document.open();
    document.read();
    document.close();
}
int main()
{
    DocumentProxy proxyDoc("DZ.txt");
    client(proxyDoc);
}

