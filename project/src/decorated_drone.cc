
#include "decorated_drone.h"

namespace csci3081 {

DecoratedDrone::DecoratedDrone(const picojson::object &obj) {

}

DecoratedDrone::DecoratedDrone( Drone* original_drone) {
    decorated_drone = original_drone;
    details_ = decorated_drone->GetDetails();
}

int DecoratedDrone::GetId() const
{
    return decorated_drone->GetId();
}

void DecoratedDrone::AddGraphPath(const IGraph* newgraph)
{
	decorated_drone->AddGraphPath(newgraph);
}


const std::string& DecoratedDrone::GetName()
{
	return decorated_drone->GetName();
}

const Battery* DecoratedDrone::GetBattery()
{
	return decorated_drone->GetBattery();
}

const std::vector<float>& DecoratedDrone::GetPosition() const
{
	return decorated_drone->GetPosition();
}

const std::vector<float>& DecoratedDrone::GetDirection() const
{
	return decorated_drone->GetDirection();
}

float DecoratedDrone::GetSpeed() 
{
	return decorated_drone->GetSpeed();
}

void DecoratedDrone::SetDirection(std::vector<float> newDirection) {
	decorated_drone->SetDirection(newDirection);
}

void DecoratedDrone::SetPosition(std::vector<float> newPosition) {
	decorated_drone->SetPosition(newPosition);
}

float DecoratedDrone::GetRadius() const
{
	return decorated_drone->GetRadius();
}

int DecoratedDrone::GetVersion() const
{
	return decorated_drone->GetVersion();
}

bool DecoratedDrone::IsDynamic() const
{
	return decorated_drone->IsDynamic();
}

Package* DecoratedDrone::GetCurPackage() 
{
	return decorated_drone->GetCurPackage();
}

void DecoratedDrone::UpdateCurPackage() 
{
	decorated_drone->UpdateCurPackage();
}

const bool DecoratedDrone::GetIsCarryingPackage() const
{
	return decorated_drone->GetIsCarryingPackage();
}

void DecoratedDrone::SetIsCarryingPackage(bool newIsCarryingPackage)
{
	decorated_drone->SetIsCarryingPackage(newIsCarryingPackage);
} 

const bool DecoratedDrone::GetOnTheWayToPickUpPackage() const
{
	return decorated_drone->GetOnTheWayToPickUpPackage();
}

void DecoratedDrone::SetOnTheWayToPickUpPackage(bool newOnTheWay)
{
	decorated_drone->SetOnTheWayToPickUpPackage(newOnTheWay);
}

const bool DecoratedDrone::GetOnTheWayToDropOffPackage() const
{
	return decorated_drone->GetOnTheWayToDropOffPackage();
}

void DecoratedDrone::SetOnTheWayToDropOffPackage(bool newOnWay)
{
	decorated_drone->SetOnTheWayToDropOffPackage(newOnWay);
}

void DecoratedDrone::UpdateBatteryCharge(float decrAmount)
{
	decorated_drone->UpdateBatteryCharge(decrAmount);
}

void DecoratedDrone::UpdateDronePosition(float dt, std::vector<IEntityObserver *> &observers)
{
	decorated_drone->UpdateDronePosition(dt, observers);
}

void DecoratedDrone::UpdateDroneVelocity(std::vector<float> & newVelocity)
{
	decorated_drone->UpdateDroneVelocity(newVelocity);
}

void DecoratedDrone::Update(const IGraph *graph, std::vector<IEntityObserver *> &observers, float dt)
{
	picojson::object& drone_obj = const_cast<picojson::object&>(decorated_drone->GetDetails());
	std::cout << "made to decorated update for drone\n";
	
	decorated_drone->Update(graph, observers, dt);
	std::cout << "madehere 1 \n";
	
	
	//change color based on batt life
	float maxcharge = decorated_drone->GetBattery()->GetMaxCharge();
	float charge = decorated_drone->GetBattery()->GetCurrentCharge();
	std::cout << maxcharge << " / " << charge << std::endl;
	float ratio = (charge / maxcharge);
	std::cout << ratio << std::endl;
	//std::cout << charge << std::endl;
	int colorStep = ratio * 15;
	colorStep = 15 - colorStep;
	std::cout << colorStep << std::endl;
	int red, green, blue;
	switch (colorStep)
	{
		case 0:
			red = 32;
			green = 255;
			blue = 4;
			break;
		case 1:
			red = 66;
			green = 255;
			blue = 14;
			break;
		case 2:
			red = 97;
			green = 255;
			blue = 21;
			break;
		case 3:
			red = 126;
			green = 255;
			blue = 25;
			break;
		case 4:
			red = 153;
			green = 255;
			blue = 25;
			break;
		case 5:
			red = 179;
			green = 255;
			blue = 21;
			break;
		case 6:
			red = 203;
			green = 255;
			blue = 14;
			break;
		case 7:
			red = 227;
			green = 255;
			blue = 4;
			break;
		case 8:
			red = 243;
			green = 247;
			blue = 0;
			break;
		case 9:
			red = 255;
			green = 235;
			blue = 6;
			break;
		case 10:
			red = 255;
			green = 211;
			blue = 18;
			break;
		case 11:
			red = 255;
			green = 186;
			blue = 26;
			break;
		case 12:
			red = 255;
			green = 160;
			blue = 31;
			break;
		case 13:
			red = 255;
			green = 160;
			blue = 31;
			break;
		case 14:
			red = 255;
			green = 103;
			blue = 29;
			break;
		case 15:
			red = 255;
			green = 71;
			blue = 22;
			break;
		default:
			red = 255;
			green = 71;
			blue = 22;
	}
	/*
	red = 255 - (255 * ratio);
	green = 255 * ratio;
	//green = 20;
	blue = 100;*/
	std::cout << "\n" << red << ", " << green << ", " << blue << std::endl;
	int temp = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	std::cout << std::hex;
	std::cout << "\n" << temp << "\n";
	std::cout << std::dec;
	//temp = temp + ((charge) * 0x010000) - (charge * 0x000100 );
	float hexnum = temp;
	
	JsonHelper::AddFloatToJsonObject(drone_obj, "color", hexnum);
	
	picojson::object obj7 = JsonHelper::CreateJsonObject();
	
	JsonHelper::AddStringToJsonObject(obj7, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj7, "value", "updateDetails");
	
	JsonHelper::AddObjectToJsonObject(obj7, "details", drone_obj);
	
	picojson::value val7 = JsonHelper::ConvertPicojsonObjectToValue(obj7);
	for (IEntityObserver *obs : observers) 
	{
		const IEntity *temp_drone = dynamic_cast<IEntity*>(decorated_drone);
		obs->OnEvent(val7, *temp_drone);
	}
	
	
}

bool DecoratedDrone::CheckReadyToPickUp()
{
	return decorated_drone->CheckReadyToPickUp();
}

bool DecoratedDrone::CheckReadyToDropOff()
{
	return decorated_drone->CheckReadyToDropOff();
}

void DecoratedDrone::PickUpPackage()
{
	decorated_drone->PickUpPackage();
}

void DecoratedDrone::DropOffPackage()
{
	decorated_drone->DropOffPackage();
}

void DecoratedDrone::CalculateAndUpdateDroneDirection(std::vector<float>& nextPosition)
{
	decorated_drone->CalculateAndUpdateDroneDirection(nextPosition);
}

void DecoratedDrone::AddAssignedPackage(Package& newPackage)
{
	AddAssignedPackage(newPackage);
}

int DecoratedDrone::GetNumAssignedPackages()
{
	return decorated_drone->GetNumAssignedPackages();
}

void DecoratedDrone::SetNewCurRoute(std::vector<std::vector<float>>& newCurRoute)
{
	decorated_drone->SetNewCurRoute(newCurRoute);
}

int DecoratedDrone::GetCurRouteLength()
{
	return decorated_drone->GetCurRouteLength();
}
int DecoratedDrone::GetCurRouteNextIndex()
{
	return decorated_drone->GetCurRouteNextIndex();
}

void DecoratedDrone::IncrementCurRouteNextIndex()
{
	decorated_drone->IncrementCurRouteNextIndex();
}

void DecoratedDrone::SetFlightBehavior(std::vector<float> pos, std::vector<float> target, const IGraph* newGraph)
{
	decorated_drone->SetFlightBehavior( pos, target, newGraph);
}

void DecoratedDrone::ChooseFlightStrategy()
{
	decorated_drone->ChooseFlightStrategy();
}

std::vector<Package*> DecoratedDrone::GetRemainingAssignedPackages()
{
	return decorated_drone->GetRemainingAssignedPackages();
}

void DecoratedDrone::SetFlightStrategyIndex(int index, bool allowChange)
{
	decorated_drone->SetFlightStrategyIndex( index, allowChange);
}
}

