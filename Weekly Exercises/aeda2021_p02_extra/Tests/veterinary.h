#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>
using namespace std;

class Veterinary {
    string name;
    long codOrder;
public:
    /**
     * Class Veterinary constructor
     * @param nome - Veterinary name
     * @param cod - Veterinary codOrder
     */
    Veterinary(string nome, int cod);
    /**
     *
     * @return Class member name
     */
    string getName() const;
    /**
     *
     * @return Class member codOrder
     */
    long getCode() const;
    /**
     *
     * @return string with info concerning the name and codOrder
     */
    string getInfo() const;
};


#endif /* SRC_VETERINARY_H_ */
