#include "decorated_entity.h"

namespace csci3081 {


DecoratedEntity::DecoratedEntity( EntityBase* original_entity) {
    decorated_entity = original_entity;
    details_ = original_entity->GetDetails();
}

int DecoratedEntity::GetId() const {
	return decorated_entity->GetId();
}

const std::string& DecoratedEntity::GetName() {
	return decorated_entity->GetName();
}
    
const std::vector<float>& DecoratedEntity::GetPosition() const {
	return decorated_entity->GetPosition();
}
    
const std::vector<float>& DecoratedEntity::GetDirection() const {
	return decorated_entity->GetDirection();
}

int DecoratedEntity::GetVersion() const {
	return decorated_entity->GetVersion();
}
    
bool DecoratedEntity::IsDynamic() const {
	return decorated_entity->IsDynamic();
}
    
float DecoratedEntity::GetRadius() const {
	return decorated_entity->GetRadius();
}

void DecoratedEntity::Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt)
{
	picojson::object& entity_obj = const_cast<picojson::object&>(decorated_entity->GetDetails());

	
	//if a drone treat as drone, else if a robot treat as robot
	//to retrieve battery data
	float charge, maxCharge;
	std::string name = decorated_entity->GetName();
	if (name[0] == 'd') {
	//casts the entity as drone to get it's battery
	maxCharge = dynamic_cast<Drone*>(decorated_entity)->GetBattery()->GetMaxCharge();
	charge = dynamic_cast<Drone*>(decorated_entity)->GetBattery()->GetCurrentCharge();
	}
	else if (name[0] == 'r') {
	Robot* decorated_robot = dynamic_cast<Robot*>(decorated_entity);

	maxCharge = decorated_robot->GetBattery()->GetMaxCharge();
	charge = decorated_robot->GetBattery()->GetCurrentCharge();
	}
	
	//calculate intended color from battery charge
	float ratio = charge / maxCharge;

	//colorstep will go from 1 to 15 as the ratio of the battery charge decreases to 0
	int colorStep = ratio * 15;
	colorStep = 15 - colorStep;

	int temp;
	switch (colorStep)
	{
		case 0:
		  temp = 268705;
		  break;
		case 1:
		  temp = 268705;
		  break;
		case 2:
		  temp = 388708;
		  break;
		case 3:
		  temp = 498710;
		  break;
		case 4:
		  temp = 599910;
		  break;
		case 5:
		  temp = 709908;
		  break;
		case 6:
		  temp = 799905;
		  break;
		case 7:
		  temp = 889900;
		  break;
		case 8:
		  temp = 949600;
		  break;
		case 9:
		  temp = 879102;
		  break;
		case 10:
		  temp = 878107;
		  break;
		case 11:
		  temp = 877210;
		  break;
		case 12:
		  temp = 996212;
		  break;
		case 13:
		  temp = 995212;
		  break;
		case 14:
		  temp = 874011;
		  break;
		case 15:
		  temp = 872809;
		  break;
		default:
		  temp = 872809;
		  
	}
	//convert num to indicate color to a float
	float colornum = temp;

	//send color data to entity details as well as observers
	JsonHelper::AddFloatToJsonObject(entity_obj, "color", colornum);

	picojson::object obj7 = JsonHelper::CreateJsonObject();

	JsonHelper::AddStringToJsonObject(obj7, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj7, "value", "updateDetails");

	JsonHelper::AddObjectToJsonObject(obj7, "details", entity_obj);

	picojson::value val7 = JsonHelper::ConvertPicojsonObjectToValue(obj7);
	for (IEntityObserver *obs : observers)
	{
		const IEntity *temp_entity = dynamic_cast<IEntity*>(decorated_entity);
		obs->OnEvent(val7, *temp_entity);
	}

	//finally, call the entity's actual update function
	details_ = entity_obj;
	decorated_entity->Update(graph, observers, dt);
}

}
