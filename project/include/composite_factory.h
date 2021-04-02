/**
 *@file composite_factory.h
 */
#ifndef COMPOSITE_FACTORY_H
#define COMPOSITE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_factory.h>

namespace csci3081
{

  /*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
 * @brief The composite factory houses the different factories that create the different entities.
 *
 * This class can be used to add factories and create entities, for each of the entity types.
 *
 * See the documentation for IEntityFactory for more information
 */
  class CompositeFactory : public IEntityFactory
  {
  public:
    /**
   *  @brief Constructor: set up the composite factory with one factory for each entity.
   */
    CompositeFactory();
    /**
   *  @brief: Destructor: delete each entityfactory in the factories vector.
   */
    ~CompositeFactory();
  /**
   *  This function creates a new entity, based on the type of object passed in. Technically, we loop over the entities' factories CreateEntity functions here.
   */
    IEntity *CreateEntity(const picojson::object &val);
  /**
   *  This function adds a factory to the factories member attribute vector.
   */
    void AddFactory(IEntityFactory& factory);

  private:
    std::vector<IEntityFactory*> factories;
    std::vector<std::string> types_list{"drone", "robot", "customer", "package"};
  };

} // namespace csci3081

#endif // COMPOSITE_FACTORY_H
