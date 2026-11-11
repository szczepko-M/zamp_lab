#ifndef GEOMOBJ_HH
#define GEOMOBJ_HH

#include <string>
#include "g3dVector.hh"

class GeomObj {
    private:
        g3d::Vector _Pos_m;
        std::string _Name;


    public:
        GeomObj(const std::string &Name, g3d::Vector Pos_m);
        
        std::string GetName() const;
        void SetName(const std::string &Name);
        g3d::Vector GetPos_m() const;
        g3d::Vector UsePos_m();

    
};

#endif