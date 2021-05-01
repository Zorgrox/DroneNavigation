/**
 * @file package.h
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>
#include <string>
#include "vector3d.h"
#include "customer.h"

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief This is the package class that will be delivered to customers.
 *
 * This class will be used to hold all of the details about the package.
 */

  class Package : public csci3081::EntityBase
  {
  public:
    /**
   * @brief Constructor: set up a Package according to the details in the JSON object
   * @param obj the picojson object that sets details for the package
   */
    Package(const picojson::object &obj);

    /**
   *  Destructor: Package
   */
    ~Package();

    /**
   *  This function should return the id of the package
   */
    int GetId() const;

    /**
   *  This function is unused for a package, but is inherited from EntityBase
   */
    void Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt);

    /**
   *  This function should set the id of the package
   * @param ID the id
   */
    void SetId(int ID);

    /**
   *  This function return the name of the package
   */
    const std::string &GetName();

    /**
   *  This function should return the position of the package
   */
    const std::vector<float> &GetPosition() const;

    /**
   *  This function should set the position of the package
   * @param newPosition the new position
   */
    void SetPosition(std::vector<float>& newPosition);

    /**
   *  This function should return the direction of the package
   */
    const std::vector<float> &GetDirection() const;

    /**
    *  This function should set the package's velocity
    * @param newVelocity the new velocity to be set
    */
    void SetVelocity(std::vector<float> &newVelocity);

    /**
   *  This function should return the radius of the package
   */
    float GetRadius() const;

    /**
   *  This function should return the version of the package
   */
    int GetVersion() const;

    /**
   *  This function should return a bool denoting whether the package is dynamic
   */
    bool IsDynamic() const;

    /**
   *  This function should return the package's intended customer
   */
    Customer* GetCustomer();

    /**
   *  This function should set the package's intended customer
   * @param newCustomer the new customer
   */
    void SetCustomer(Customer& newCustomer);

    /**
   *  This function should return the package's intended destination
   */
    const std::vector<float> GetDestination() const;

    /**
   *  This function should return the package's weight
   */
    float GetWeight();

  private:
    std::string name;
    Vector3D* position;
    Vector3D* direction;
    float radius;
    int version = 0;
    bool dynamic = true;

    Customer* customer;
    std::vector<float> destination;
    float weight;
  };

} // namespace csci3081

#endif // PACKAGE_H_
