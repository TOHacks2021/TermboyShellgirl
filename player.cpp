#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Entity {
    public:
        virtual ~Entity ();
        virtual draw();
    protected:
        Entity ();
    private:
        int x, y;
};

Entity::~Entity() {}
Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
}