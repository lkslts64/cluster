#ifndef ALGORITHMS_PROJECT_OBJECT_H
#define ALGORITHMS_PROJECT_OBJECT_H
#include <string>
using namespace std;
class Object {
private:
    string id;
public:
    Object(string id) {
        this->id = id;
    }
    Object() {}
    string getId() {
        return id;
    }
    void setId(string id) {
        this->id = id;
    }
    virtual void foo() = 0;
};

#endif //ALGORITHMS_PROJECT_OBJECT_H
