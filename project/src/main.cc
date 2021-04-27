#include <EntityProject/project_settings.h>
#include <EntityProject/web_scene_viewer.h>
#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/graph.h>
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_console_logger.h>

#include <cmath>
#include <iostream>

using namespace csci3081;
using namespace entity_project;

int main(int argc, char**argv) {
  std::cout << "Usage: ./build/web-app 8081 web scenes/scene.json" << std::endl;

  if (argc > 3) {
    int port = std::atoi(argv[1]);
    std::string webDir(argv[2]);
    std::string scene(argv[3]);

    IEntitySystem* entitySystem = GetEntitySystem("default");
    IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(entitySystem);

    // Create and set the graph
    if (deliverySystem) {
      OSMGraphParser parser;
      const IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
      deliverySystem->SetGraph(graph);
    }

    // Create the web scene viewer
    WebSceneViewer viewer(port, webDir, scene);
    viewer.SetEntitySystem(entitySystem);

    // Add observers
    entity_project::EntityConsoleLogger logger;
    if (deliverySystem) {
      deliverySystem->AddObserver(&logger);
      deliverySystem->AddObserver(&viewer);
    }

    // Run the simulation
    while (viewer.Run()) {}
    delete entitySystem;
  }

  return 0;
}
