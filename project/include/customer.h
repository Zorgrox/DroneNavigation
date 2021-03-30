/**
 * @file customer.h
 */
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the customer class that holds information about the customer's position.
 *
 * The customer currently does not move (as of iteration 1). It will move in future iterations.
 */

  class Customer : public csci3081::EntityBase
  {
  public:
    /**
   * @brief Constructor: set up a Customer according to the details in the JSON object
   */
    Customer(const picojson::object &obj);

    /**
   *  This function should return the id of the customer
   */
    int GetId() const;

    /**
   *  This function return the name of the customer
   */
    const std::string &GetName();

    /**
   *  This function should return the position of the customer
   */
    const std::vector<float> &GetPosition() const;

    /**
   *  This function should return the direction of the customer
   */
    const std::vector<float> &GetDirection() const;

    /**
   *  This function should return the radius of the customer
   */
    float GetRadius() const;

    /**
   *  This function should return the version of the customer
   */
    int GetVersion() const;

    /**
   *  This function should return a bool denoting whether the customer is dynamic
   */
    bool IsDynamic() const;

  private:
    int id;
    std::string name;
    Vector3D* position;
    Vector3D* direction;
    float radius;
    int version=0;
    bool dynamic=false;
  };

} // namespace csci3081

#endif // CUSTOMER_H_
