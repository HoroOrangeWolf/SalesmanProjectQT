#include "road.h"

Road::Road()
{

}


Road::~Road(){
    delete [] (this->computedRoad);
    delete [] (this->points);
}
