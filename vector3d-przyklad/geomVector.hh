#ifndef GEOMVECTOR_HH
#define GEOMVECTOR_HH

/*!
 * \file
 * \brief Contains the definition of the geom::Vector template
 *
 * This template is used to define vectors in a space of any dimention.
 * \author      Bogdan Kreczmer
 * \date        2003.12
 *
 */



#ifdef __GNUG__
#pragma interface
#endif
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <initializer_list>

/*!
 * \file
 * \brief Definition of the vector template with parametric dimention.
 */


namespace geom {

/*!
 * \brief Model of N-dimensional vector
 *
 * This template is a model of N-dimensional vector.
 * \param Type - a type of vector coordinates.
 * \param Size - dimension of vector.
 */
 template<typename Type, unsigned int Size>
 class Vector {

   /*!
    * \brief Width of a field in which a coordinate value is displayed.
    */
   static int _Display_Width;
   /*!
    * \brief Precision of floating numbers to be displayed.
    */
   static int _Display_Precision;
   
    /*!
     *  In this table, values of coordinates are stored.
     */
   Type  _Coord[Size];


    
  protected:

   void RecursiveSetting(unsigned int Idx)
     {
       if (Idx >= Size) return;
       for (; Idx < Size; ++Idx) _Coord[Idx] = 0;
     }
   
   template<typename... Args>
   void RecursiveSetting(unsigned int Idx, Type Val, Args... Tail)
          {
	    if (Idx >= Size) return;
	    _Coord[Idx] = Val;
	    RecursiveSetting(Idx+1, Tail...);	    
	  }
  public:

    /*!
     * \brief All coordiantes are set to zero.
     *
     * All coordinate values are set to zero.
     */
   Vector() { for (Type &Val : _Coord) Val = 0; }

   /*!
    * \brief Coordinate values are set by using a list values
    *
    *  Coordinate values are set by using a list values.
    *  rCoordLst - the list of values used for initialization.
    */
   Vector(const std::initializer_list<Type> &rCoordLst);
   /*!
    * \brief Coordinate values are set by using a variadic list
    *
    *  Coordinate values are set by using a variadic list.
    *  args - the list of values. These values should have a type compatible with Type.
    */
   template<typename... Args>
   Vector(Args... args)
       { RecursiveSetting(0, args...); }
   
    /*!
     *  Access to a coordinate of the vector.
     *  The access is in modification mode.
     *  \param  Ind - index of a vector coordinate.
     *  \pre 0 <= Ind < Size.
     *  \post The reference to the requested coordinate of the vector.
     *  \return The reference to the requested coordinate of the vector.
     */
   Type  &operator [](unsigned int Ind) { assert(Ind < Size); return _Coord[Ind]; }

    /*!
     *  Access to a coordinate of the vector.
     *  The access is in read-only mode.
     *  \param  Ind - index of a vector coordinate.
     *  \pre 0 <= Ind < Size.
     *  \post The requested coordinate of the vector.
     *  \return The requested value of the vector coordinate.
     */
   Type operator [](unsigned int Ind) const { assert(Ind < Size); return _Coord[Ind]; }


    /*! 
     *  Adding two wectors.
     *  \param  V - the second component.
     *  \return  Vector<Type,Size> - an object that contains the sum of two vectors
     *                          i.e. \b *this and \e V.
     */
    Vector<Type,Size>  operator + (Vector<Type,Size> const &V) const;

    /*! 
     *  Adds all coordinates of other vector to coordinates of this vector.
     *  \param  Arg2 - the second arrgument of this operator.
     *  \return *this - reference to this object.
     */
    Vector<Type,Size> &operator += (Vector<Type,Size> const &V);

    /*! 
     * \brief The operation implements a vector difference.
     * 
     *  The operation implements a vector difference. 
     *  \param  V - subtrahend.
     *  \return An object containing the result of the subtraction of two vectors 
     *          i.e. \b *this i \e V.
     */
   Vector<Type,Size>  operator  - (Vector<Type,Size> const &V) const;

    /*! 
     *  \brief The operation implements a vector difference.
     *
     *  The operation implements a vector difference. The result is saved
     *  in \p this object.
     *  \param  V - subtrahend.
     *  \return *this -  reference to this object and its contain
     *                   the result of the operation.
     */
   Vector<Type,Size> &operator -= (Vector<Type,Size> const &V);

     /*!
      * Implementation of the vector product.
      * \param     V - second product factor. 
      * \return  An object that contains the product vector of
      *                           \b *this and \e V.
      */
   Vector<Type,Size>  operator  * (Vector<Type,Size> const &V) const;

     /*!
      * Operator implementuje iloczyn wektorowy. 
      * \param     V - drugi czynnik iloczynu.
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              produktem iloczynu wektorowego \b *this i \e V.
      */
   Vector<Type,Size> &operator *= (Vector<Type,Size> const &V); 

     /*!
      * Multiplying the vector by a number 
      * \param     L - a number which is the second factor.
      * \retval  An object which is the product of
      *                            \b *this and the number \e L.
      */
   Vector<Type,Size>  operator  * (Type L) const;

     /*!
      * Operator implementuje iloczyn wektora przez liczbê.
      * \param     L - drugi czynnik iloczynu (liczba).
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              produktem iloczynem \b *this i liczby \e L.
      */
   Vector<Type,Size> &operator *= (Type L);

     /*!
      * Operator implementuje iloraz wektora przez liczbê.
      * \param     L - dzielnik wektora (liczba).
      * \retval  Vector<Type,Size>  - obiekt bêd±cy ilorazem
      *                            \b *this (wektor) / \e L (liczba).
      */
   Vector<Type,Size>  operator  / (Type L) const;

     /*!
      * Operator implementuje iloraz wektora przez liczbê.
      * \param     L - dzielnik wektora (liczba).
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              ilorazem \b *this i liczby \e L.
      */
   Vector<Type,Size> &operator /= (Type L);


   /*!
    * \brief Multiplies each corresponding coordinate of both vectors.
    */
   Vector<Type,Size>& SetResult_ParallelMultiply(const Vector<Type,Size> &Arg2);   
   /*!
    * \brief Multiplies each corresponding coordinate of both vectors.
    */
   Vector<Type,Size> ParallelMultiply(const Vector<Type,Size> &Arg2) const;

   /*!
    * \brief The square root of each coordinate is computed.
    *
    *  The square root of each coordinate is computed.
    *  \pre The values of vector coordinates must be greater than or equal to zero.
    *
    *  \return The reference to this object which contains the result of the operation.
    */
   Vector<Type,Size>& SetResult_ParallelSqrt()
        {  for (Type &rCrd : _Coord ) { assert(rCrd >= 0); rCrd = sqrt(rCrd); }; return *this; }
   
   
   /*!
    * \brief The square root of each coordinate is computed.
    *
    *  The square root of each coordinate is computed.
    *  \pre The values of vector coordinates must be greater than or equal to zero.
    *
    *  \return The result vector of containing computed square roots
    *          for each vector coordinate.
    */
   Vector<Type,Size> ParallelSqrt() const
        { Vector Vec_Result = *this;  return Vec_Result.SetResult_ParallelSqrt(); }


   /*!
    * \brief Divide each corresponding coordinate of both vectors.
    */
   Vector<Type,Size> ParallelDivide(const Vector<Type,Size> &Arg2) const;
   
   /*!
    * \brief Divide each corresponding coordinate of both vectors.
    *        The result is set to the invoking object.
    */
   Vector<Type,Size> & SetResult_ParallelDivide(const Vector<Type,Size> &Arg2);

   /*!
    * \brief It is checked if there is any coordinate value which is greater
    *        than a value delivered by the parameter.
    */
   bool AnyAbsCoord_GreaterThan(double Val) const;
     /*!
      * \brief  The scalar product of two vectors
      *
      * Implementation of the scalar product of two vectors.
      * \param[in] V - the second factor of the scalar product. 
      * \return The value which is the scalar product of vectors \b *this and \e V.
      */
   Type  operator & (Vector<Type,Size> const &V) const;      // skalar product


    /*!
     *  Dokonuje porównania dwóch wektorów.
     *  \retval  true - je¶li odpowiadaj±ce sk³adowej s± sobie równe
     *              w sensie funkcji sgn (patrz \link sgn.hh sgn.hh \endlink).
     *              pozwala to uwzglêdniæ (przynajmniej czê¶ciowo) b³êdy
     *              obliczeñ,
     *  \retval  false - w przypadku przeciwnym.
     */
   bool  operator == (Vector<Type,Size> const &);



    /*!
     *  \brief Length of this vector is computed.
     *
     * Length of this vector is computed.
     * \return A value of vector length is returned.
     */
    Type Length() const;

    /*!
     *  Zmienia znak wszystkich sk³adowych wektora na przeciwny.
     *  \return\b *this - zwraca referencjê do samego siebie.
     */
    Vector<Type,Size> &SetResult_Inverse() { for (Type &rCrd : _Coord ) rCrd = -rCrd; return *this; }



    /*!
     * \brief Each coordinate value is squared.
     *
     *  Each coordinate value is squared.
     *  \return The reference to this object is returned.
     */
    Vector<Type,Size>& SetResult_Pow2() { for (Type &rCrd : _Coord ) rCrd *= rCrd; return *this; }
    /*!
     * \brief Each coordinate value is squared.
     *
     *  Each coordinate value is squared.
     *  \return The reference to this object is returned.
     */
    Vector<Type,Size> Pow2() const { Vector Vec_Result = *this; return Vec_Result.SetResult_Pow2(); }

    /*!
     * \brief All coordinates are set to zero.
     *
     *  All coordinates are set to zero.
     *  \post
     *    The value of each coordinate is equal to zero.
     */
    void SetZero() { for (Type &Crd : _Coord ) Crd = 0;  }


    /*!
     * Sprawdza czy dany wektor jest wektorem zerowym. Przyjmuje
     * siê, ¿e pole ma warto¶æ 0 je¶li funkcja sgn zwróci warto¶æ 0.
     * Wspomniana funkcja uwzglêdnia b³êdy obliczeñ zdefiniowane
     * poprzez sta³± ERROR_LEVEL.
     * \return true - je¶li sgn zwróci dla wszystkich pól zero,
     * \return false - w przypadku przeciwnym.
     */
    bool IsZero() const  { for (Type Crd : _Coord ) if (Crd) return false;  return true; }


    /*!
     * Sprawdza czy wspó³rzêdna \e x znajduje siê wewn±trz przedzia³u.
     * \param x_min - dolny kraniec przedzia³u.
     * \param x_max - górny kraniec przedzia³u.
     * \return true - je¶li warto¶æ pola \e _x jest wewn±trz przedzia³u
     *               (\e x_min, \e x_max).
     * \return false - w przypadku przeciwnym.
     */
   bool IsInside(unsigned int Ind, Type x_min, Type x_max) const
     { return (x_min < _Coord[Ind]) && (_Coord[Ind] < x_max);}

    /*!
     * Sprawdza czy dany punkty jest wewn±trz prostopad³o¶cianu.
     * Zak³ada siê, ¿e ¶cianki prostopad³o¶cianu s± równoleg³e do jednej
     * z p³aszczyzn kartezjañskiego uk³adu wspó³rzêdnych OXY.
     * \param Min - zawiera wspó³rzêdne wierzcho³ka, którego sk³adowe
     *              maj± minimalne warto¶ci spo¶ród sk³adowych tego 
     *              samego typu wszystkich wierzcho³ków
     *              tego prostopad³o¶cianu.
     * \param Max - zawiera wspó³rzêdne wierzcho³ka, którego sk³adowe
     *              maj± maksymalne warto¶ci spo¶ród sk³adowych tego 
     *              samego typu wszystkich wierzcho³ków
     *              tego prostopad³o¶cianu.
     *              prostopad³o¶cianu.
     * \return  true  - je¶li punkt jest wewn±trz prostopad³o¶cianu.
     * \return  false - w przypadku przeciwnym.
     */
   bool IsInside(Vector<Type,Size> const &Min, Vector<Type,Size> Max) const;

    /*!
     * \brief This vector is normalized.
     *
     * The method normlizes length of the vector.
     * After this operation the length is equal to 1.
     */
   void Normalize() 
     { Type d = Length(); for (Type &Crd : _Coord) Crd /= d; }


    /*!
     * \brief Inverts the values of each coordinate.
     */
    Vector InvertCoords() const;
   
   
   /*!
    * \brief The new value of the field width is set.
    *
    *  The new value of the display field width is set.
    *  In this kind of fields, vector coordinate values are displayed.
    *  \param[in] Width - the new value of display field width.
    */   
   static void SetDisplayWidth(int Width) { _Display_Width = Width; }
   /*!
    * \brief Default width is set.
    */
   static void ResetDisplayWidth() { _Display_Width = -1; }
   /*!
    * \brief The display field width is accessed.
    */
   static int GetDisplayWidth() { return _Display_Width; }

   /*!
    * \brief The new value of the precision of floating numbers is set.
    *
    *  The new value of the display precision of floating numbers is set.
    *  \param[in] Prec - the new value of display precisoin of floatin numbers.
    */   
   static void SetDisplayPrecision(int Precision) { _Display_Precision = Precision; }
   /*!
    * \brief The display field precision is accessed.
    */
   static int GetDisplayPrecision() { return _Display_Precision; }

 };

 
 template<typename Type, unsigned int Size>
 int Vector<Type,Size>::_Display_Width = -1;


 template<typename Type, unsigned int Size>
 int Vector<Type,Size>::_Display_Precision = 2;


 template <typename Type, unsigned int Size>
 Vector<Type,Size>::Vector(const std::initializer_list<Type> &rCoordLst)
 {
  assert(rCoordLst.size() <= Size);
  int Ind = -1;
  for (double Crd_i : rCoordLst) _Coord[++Ind] = Crd_i;
  for (++Ind; Ind < static_cast<int>(Size); ++Ind) _Coord[Ind] = 0;
 }



  
 template<typename Type, unsigned int Size>
 inline
 bool Vector<Type,Size>::IsInside(Vector<Type,Size> const &Min, Vector<Type,Size> Max) const
 {
   for (unsigned Ind = 0; Ind < Size; ++Ind) {
     if (!IsInside(Ind,Min[Ind],Max[Ind])) return false;
   }
   return true;
 }




/*!
 * Multiplies each corresponding coordinate of both vectors.
 * \param[in] Arg2 - multiplier, the second argument of multiplication.
 * \return The reference to this object which contains
 *         the result of parallel multiplication of both vectors.
 */
 template<typename Type, unsigned int Size>  
 Vector<Type,Size> & Vector<Type,Size>::SetResult_ParallelMultiply(const Vector<Type,Size> &Arg2)
 {
   for (unsigned Ind = 0; Ind < Size; ++Ind) { (*this)[Ind] *= Arg2[Ind]; }
   return *this;
 }
 
  

/*!
 * Multiplies each corresponding coordinate of both vectors.
 * \param[in] Arg2 - multiplier, the second argument of multiplication.
 * \return The result of parallel multiplication of both vectors.
 */
 template<typename Type, unsigned int Size>  
 Vector<Type,Size> Vector<Type,Size>::ParallelMultiply(const Vector<Type,Size> &Arg2) const
 {
   Vector<Type,Size> V_Res = *this;
   return V_Res.SetResult_ParallelMultiply(Arg2);
 }



  



/*!
 * Divide each corresponding coordinate of both vectors.
 * \param[in] Arg2 - divider, the second argument for division.
 * \return The result of parallel multiplication of both vectors.
 */
 template<typename Type, unsigned int Size>  
 Vector<Type,Size> Vector<Type,Size>::ParallelDivide(const Vector<Type,Size> &Arg2) const
 {
   Vector<Type,Size> V_Res = *this;
   return V_Res.SetResult_ParallelDivide(Arg2);
 }


/*!
 * Divide each corresponding coordinate of both vectors.
 * The result is set to the invoking object.
 * \param[in] Arg2 - divider, the second argument for division.
 *
 */
 template<typename Type, unsigned int Size>  
 Vector<Type,Size>& Vector<Type,Size>::SetResult_ParallelDivide(const Vector<Type,Size> &Arg2)
 {
   for (unsigned Ind = 0; Ind < Size; ++Ind) {
     assert(Arg2[Ind] != 0);
     (*this)[Ind] /= Arg2[Ind];
   }
   return *this;
 }


 template<typename Type, unsigned int Size>
 inline
 Type Vector<Type,Size>::Length() const
 {
   return sqrt(*this & *this);
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator += (Vector<Type,Size> const &rArg2)
 {
   for (unsigned int Ind = 0; Ind < Size; ++Ind) _Coord[Ind] += rArg2[Ind];
   return *this;
 }
  

 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator + (Vector const &rArg2) const
 {
   Vector<Type,Size>  Vec_Sum(*this);
   return Vec_Sum += rArg2;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator -= (Vector<Type,Size> const & Arg2)
 {
   for (unsigned int Ind = 0; Ind < Size; ++Ind) _Coord[Ind] -= Arg2[Ind];
   return *this;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator - (Vector<Type,Size>  const &rArg2) const
 {
   Vector<Type,Size>  Vec_Res(*this);  
   return Vec_Res -= rArg2;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator *= (Type Digit)
 {
   for (Type &rCrd : _Coord ) rCrd *= Digit;
   return *this;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator * (Type Digit) const
 {
   Vector<Type,Size>  Vec_Res(*this);
   return Vec_Res *= Digit;  
 }



 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator /= (Type Digit)
 {
   assert(Digit != 0);
   for (Type &rCrd : _Coord ) rCrd /= Digit;
   return *this;
 }
  

 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator / (Type Digit) const
 {
   Vector<Type,Size>  Vec_Res(*this);
   return Vec_Res /= Digit;    
 }


 template<typename Type, unsigned int Size>
 inline
 bool Vector<Type,Size>::operator == (Vector<Type,Size> const &rArg2)
 {
   for (unsigned int Idx = 0; Idx < Size; ++Idx) if (_Coord[Idx] != rArg2[Idx]) return false;
   return true;
 }


 template<typename Type, unsigned int Size>
 inline
 Type Vector<Type,Size>::operator & (Vector<Type,Size> const &rVec) const
 {
   Type Res = 0;
   for (unsigned int Idx = 0; Idx < Size; ++Idx) Res += _Coord[Idx] * rVec[Idx];  
   return Res;
 }



  /*!
   * It is checked if there is any coordinate value which is greater
   * than a value delivered by the parameter \e Val.
   * \param Val - a value which is compared with coordines of this object.
   * \retval true - there is a value of vector coordinates which is greater than \e Val.
   * \retval otherwise.
   */
  template<typename Type, unsigned int Size>
  bool Vector<Type,Size>::AnyAbsCoord_GreaterThan(double Val) const
  {
    for (double Crd_i : _Coord) if (fabs(Crd_i) > Val) return true;
    return false;
  }


  /*!
   * Inverts the values of each coordinate.
   * \return A vector whose coordinate values are the reciprocal of
   *         the coordinates values of \b *this
   */
  template<typename Type, unsigned int Size>  
  Vector<Type,Size>  Vector<Type,Size>::InvertCoords() const
  {
    Vector Vec_Result = *this;
    for (double &Crd_i : Vec_Result._Coord) {
      assert( Crd_i != 0 );
      Crd_i = 1/Crd_i;
    }
    return Vec_Result;
  }

  
}



/*!
 *  It displayes coordinates of the vector
 *  \param ostrm - output stream,
 *  \param V - the vector whose coordinates should be displayed.
 */
template<typename Type, unsigned int Size>
inline
std::ostream & operator << ( std::ostream &OStrm, const geom::Vector<Type,Size> &V)
{
  int  Width = geom::Vector<Type,Size>::GetDisplayWidth();
  int  OldPrec = OStrm.precision();

  OStrm.precision(geom::Vector<Type,Size>::GetDisplayPrecision());
  OStrm << "(" << std::setw(Width > -1 ? Width : 0) << V[0];
   for (unsigned int Ind = 1; Ind < Size; ++Ind) {
     OStrm << ", " << std::setw(Width > -1 ? Width : 0) << V[Ind];
   }
   OStrm << ")";
   OStrm.precision(OldPrec);
   return OStrm;
}



#endif
