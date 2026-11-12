#ifndef GEOMOBJECT_HH
#define GEOMOBJECT_HH

#include <string>
#include "g3dVector.hh"

class GeomObject {
    private:
        g3d::Vector _Pos_m;
        g3d::Vector _RotAng_deg;
        std::string _Name;


    public:
        GeomObject() = default;
        explicit GeomObject(const std::string& Name,
            const g3d::Vector& RotAng_deg = g3d::Vector(),
            const g3d::Vector& Pos_m = g3d::Vector());
        
        const std::string& GetName() const {return _Name;};
        void SetName(const std::string& Name) {_Name = Name;};
        const g3d::Vector& GetPos_m() const {return _Pos_m;};
        g3d::Vector& UsePos_m() {return _Pos_m;};
        // zrobić dwie fukcje setrot i userot
    
};

#endif