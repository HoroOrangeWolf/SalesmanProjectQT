#include "road.h"

Road::Road()
{

}


Road::~Road(){
    if(this->computedRoad != NULL)
        delete [] this->computedRoad;
}
