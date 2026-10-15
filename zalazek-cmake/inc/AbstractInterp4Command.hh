#ifndef ABSTRACTINTERP4COMMAND_HH
#define ABSTRACTINTERP4COMMAND_HH

/*!
 * \file 
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractInterp4Command
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractInterp4Command.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

 /*!
  * \brief Definiuje interfejs interpretera polecenia.
  *
  * Definiuje interfejs interpretera polecenia udostępnianego
  * przez daną wtyczkę.
  */
  class AbstractInterp4Command {
   public:

    virtual ~AbstractInterp4Command() {}
    
    /*!
     * \brief Wyświetla składnię polecenia
     */
     virtual void PrintSyntax() const = 0;
  };


#endif
