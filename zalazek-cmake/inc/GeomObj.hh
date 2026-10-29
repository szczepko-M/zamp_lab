#ifndef GEOMOBJ_HH
#define GEOMOBJ_HH



class GeomObj {
    public:
        const std::string GetName() const;
        void SetName(const std:string &Name);
        const Vector3D GetPos_m() const;
        Vector3D UsePos_m();

    private:
        Vector3D _Pos_m;
        std::string _Name;

    
}