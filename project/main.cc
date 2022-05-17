#include "pch.hpp"

#include "controller.hpp"
#include "core/application.hpp"
#include "components/sphere.hpp"

using namespace engine;
using namespace components;

// the entry point for any Windows program
INT WINAPI wWinMain(HINSTANCE instance, HINSTANCE prev_instance, PWSTR cmd_line,
                    int cmd_show)
{
    WNDCLASSEXW wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

    // create the window and use the result as the handle
    auto bmwindow = std::make_shared<BitmapWindow>(
        wc, NULL,
        L"WindowClass1",                  // name of the window class
        L"Our First Windowed Program",    // title of the window
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // window style
        kWindowPosition,                  // position of the window
        kWindowResolution,                // window size
        nullptr,                          // we have no parent window, nullptr
        nullptr,                          // we aren't using menus, nullptr
        instance,                         // application handle
        nullptr);                         // used with multiple windows, nullptr
    // display the window on the screen
    ShowWindow(bmwindow->handle(), cmd_show);

    
    auto scene = std::make_shared<Scene>();
    entt::registry& registry = scene->registry;

    entt::entity sphere = registry.create();
    registry.emplace<Sphere>(sphere);
    Transform& sphere_transform = registry.emplace<Transform>(sphere);
    sphere_transform.position = math::vec3{ 0,-1,-2 };
    sphere_transform.scale = math::vec3{ 0.5f };

    entt::entity point_light_entity = registry.create();
    
    PointLight &point_light = registry.emplace<PointLight>(point_light_entity);
    Transform &pl_transform = registry.emplace<Transform>(point_light_entity);
    pl_transform.position = math::vec3 {0,-0.25f,0};
    point_light.color = math::vec3{ 0.5f,0.0f,0.5f };
    point_light.ambient_intensity = 0.2f;
    point_light.diffuse_intensity = 0.3f;
    point_light.specular_intensity = 0.1f;
    point_light.attenuation = PointLight::Attenuation
    {
        .constant = 1.0f,
        .linear = 0.7f,
        .quadratic = 0.44f
    };

    DirectionalLight directional_light;
    directional_light.direction = math::normalize(math::vec3{ 0,-1, 0 });
    directional_light.color = math::vec3{ 1,1,0.7f };
    directional_light.ambient_intensity = 0.2f;
    directional_light.diffuse_intensity = 0.3f;
    directional_light.specular_intensity = 0.1f;

    auto controller = std::make_shared<Controller>(*bmwindow, scene);

    registry.emplace<DirectionalLight>(registry.create(), directional_light);
 //   math::Intersection nearest;
 //   math::Ray ray;
 //   nearest.reset();
  //  auto group = registry.group<Transform, IIntersectable>();
  // for(auto entity: group)
 //  {
 //      //group.get<IIntersectable>(entity)->CheckIntersection(nearest, ray);
 //  }

    
    Application::Init();

    bmwindow->SetEventCallback(Application::event_function());
    

    Application &application = Application::Get();
    application.AddLayer(controller);
    application.Run();
    PostQuitMessage(0);
    return 0;
}