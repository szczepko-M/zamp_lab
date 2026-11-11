#ifndef SET4GEOMOBJECTS_HH
#define SET4GEOMOBJECTS_HH

#include <map>
#include <GeomObj.hh>
#include <string>
#include <memory>

class Set4GeomObjects : public std::map<std::string, std::shared_ptr<GeomObj>> {
    public:
        bool AddGeomObj(const std::string &ObjName);
        std::shared_ptr<GeomObj> FindGeomObj(const std::string &ObjName) const;

};



#endif