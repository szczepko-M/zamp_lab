#include "Set4GeomObjects.hh"

#include <iostream>
#include <stdexcept>

using namespace std;

bool Set4GeomObjects::AddGeomObj(const std::string &ObjName){
    shared_ptr<GeomObj> pObj;

    try {
        pObj = make_shared<GeomObj>(ObjName);
    }
    catch (const exception &e){
        cerr << "!!!" << e.what() << endl;
        return false;
    }

    if(find(pObj->GetName()) != end()){
        cerr << "!!! Obiekt \"" << pObj->GetName()
            << "\" już istnieje" << endl;
        return false;
    }

    (*this)[pObj->GetName()] = pObj;
    return true;
}

std::shared_ptr<GeomObj> Set4GeomObjects::FindGeomObj(const std::string &ObjName) const {
    const_iterator it = find(ObjName);

    if(it == end()){
        return shared_ptr<GeomObj>();
    }

    return it->second;
}