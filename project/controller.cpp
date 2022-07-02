#include "controller.hpp"
#include "core/application.hpp"
using namespace engine;
using namespace core;
using namespace events;
using namespace math;
using namespace components;

// 1: roughness / metalness showcase
// 2: global illumination scene
#define SCENE 2


namespace
{
    const vec3 kUp{0, 1, 0};
    const vec3 kDown{0, -1, 0};
    const vec3 kLeft{-1, 0, 0};
    const vec3 kRight{1, 0, 0};
    const vec3 kForward{0, 0, 1};
    const vec3 kBackwards{0, 0, -1};
    render::Material &UpdateMaterial(render::Material &mat,
                                     vec3 albedo = vec3{0.3f},
                                     vec3 inF0 = vec3{0.04f},
                                     vec3 emission = vec3{0.0f},
                                     float roughness = 1,
                                     float metalness = 1,
                                     bool casts_shadow = true)
    {
        mat.albedo = albedo;
        mat.F0 = lerp(inF0, mat.albedo, mat.metalness);
        mat.emission = emission;
        mat.roughness = roughness;
        mat.metalness = metalness;
        mat.casts_shadow = casts_shadow;

        return mat;
    }

    Transform &UpdateTransform(entt::registry &registry, entt::entity e,
                               vec3 position = vec3{0},
                               vec3 scale = vec3{1},
                               quat rotation = quat{1, 0, 0, 0})
    {
        Transform &t = registry.get_or_emplace<Transform>(e);
        t.position = position;
        t.scale = scale;
        t.rotation = rotation;
        t.UpdateMatrices();
        return t;
    }
    SceneMesh &AddCubeComponent(entt::registry &registry, entt::entity e)
    {
        return registry.emplace<SceneMesh>(e, render::kCubeMesh);
    }
    SceneSphere &AddSphereComponent(entt::registry &registry, entt::entity e)
    {
        return registry.emplace<SceneSphere>(e);
    }
    PointLight &AddPointLight(entt::registry &registry, entt::entity e, vec3 color = vec3{1, 1, 1}, float power = 1e6f)
    {
        PointLight &point_light = registry.get_or_emplace<PointLight>(e);
        point_light.color = color;
        point_light.power = power;
        return point_light;
    }

    SpotLight &AddSpotLight(entt::registry &registry, entt::entity e,
                            vec3 color = vec3{1, 1, 1},
                            float cut_off = radians(45.0F),
                            vec3 direction = vec3{0, -1, 0}, 
                            float power = 1e6f)
    {
        SpotLight &spot = registry.get_or_emplace<SpotLight>(e);
        spot.direction = direction;
        spot.color = color;
        spot.cut_off = cut_off;
        spot.power = power;
        return spot;
    }

    DirectionalLight &AddDirLight(entt::registry &registry, entt::entity e,
                                  vec3 color = vec3{1, 1, 1},
                                  vec3 direction = vec3{0, -1, 0},
                                  float power = 1.0f)
    {
        DirectionalLight &dir = registry.get_or_emplace<DirectionalLight>(e);
        dir.direction = direction;
        dir.color = color;
        dir.power = power;
        return dir;
    }
} // namespace
void Controller::InitScene()
{
    UpdateMaterial(scene_->floor.material, vec3{0.3f}, vec3{0.04f}, vec3{0}, 1.0f, 1, true);
    scene_->floor.transform.reset();
    scene_->floor.plane.update_plane(vec3{0, 0, 1}, vec3{1, 0, 0});
    scene_->floor.transform.position = vec3{0, -2, 0};
    scene_->floor.transform.UpdateMatrices();
    entt::registry &registry = scene_->registry;

    /*     entt::entity directional_light = registry.create();
        DirectionalLight &directional_light_v = registry.emplace<DirectionalLight>(directional_light);
        directional_light_v.direction = normalize(vec3{0, -1, -1});
        directional_light_v.color = vec3{0.1f};  */
    /*
         tick_layer->funcs.push_back(
            [&time_from_start_, &directional_light_v](float delta_time)
            {
                directional_light_v.direction = normalize(vec3{
                    sin(time_from_start_),
                    cos(time_from_start_),
                    0 });
            });   */
#if SCENE == 1
    vec3 a{1,0,0};
    for (int j = 0; j < 7; j++)
        for (int i = 0; i < 7; i++)
        {
            entt::entity sphere = registry.create();
            UpdateTransform(registry, sphere, vec3{i, j, 0}, vec3{0.5f});
            float r = lerp(0.001f, 1.0f, static_cast<float>(i) /  7.0f);
            float m = lerp(0.0f, 1.0f, static_cast<float>(j) / 7.0f);
            UpdateMaterial(AddSphereComponent(registry, sphere).material, a, vec3{0.04f}, vec3{0.0f}, r, m);
        }
    entt::entity main_light = registry.create();
    UpdateTransform(registry, main_light, vec3{4,4,-10}, vec3{1.0f});
    AddPointLight(registry, main_light, vec3{1.0f, 1.0f, 1.0f}, 50);
    UpdateMaterial(AddSphereComponent(registry, main_light).material, vec3{0}, vec3{0.04f}, vec3{1.0f} * 50, 1, 0, false);
#elif SCENE == 2
    auto gen_cube = [this, &registry](vec3 coords, vec3 scale, vec3 color, quat rotation = quat(), float roughness = 1, float metalness = 0){
        entt::entity cube = registry.create();
        UpdateTransform(registry, cube, coords, scale, rotation);
        UpdateMaterial(AddCubeComponent(registry, cube).material(), color, vec3{0.04f}, vec3{0.0f}, roughness, metalness);
    };
    gen_cube(vec3{-2,1,0},vec3{2}, vec3{1,0,0});
    gen_cube(vec3{0,-1,0}, vec3{2}, vec3{1});
    gen_cube(vec3{0,3,0}, vec3{2}, vec3{1});
    gen_cube(vec3{0,1,2}, vec3{2}, vec3{1});
    gen_cube(vec3{2,1,0}, vec3{2}, vec3{0,1,0});
    gen_cube(vec3{-0.25f,0.25f,-0.25f}, vec3{0.5f}, vec3{1}, quat(), 1, 0);
    gen_cube(vec3{0.5f,0.625f,0.0f}, vec3{0.45f, 1.25f, 0.45f}, vec3{1}, quat{1, 0, -radians(30.0f), 0});
    
    entt::entity spot_light = registry.create();
    UpdateTransform(registry, spot_light, vec3{0,1,0}, vec3{0.01f});
    UpdateMaterial(AddSphereComponent(registry, spot_light).material, vec3{0}, vec3{0.04f}, vec3{1.0f} * 50, 1, 0, false);
    AddSpotLight(registry, spot_light, vec3{1.0f, 1.0f, 1.0f}, radians(45.0f), normalize(vec3{-1,1,1}), 5e5f);
    camera_controller_.SetWorldOffset(vec3{0,0.95f,-3.6f});
/*     entt::entity main_light = registry.create();
    UpdateTransform(registry, main_light, vec3{0,1,0}, vec3{0.01f});
    AddPointLight(registry, main_light, vec3{1.0f, 1.0f, 1.0f}, 5e3f);
    UpdateMaterial(AddSphereComponent(registry, main_light).material, vec3{0}, vec3{0.04f}, vec3{1.0f} * 5e3f, 1, 0, false); */
#endif
    
    //entt::entity main_light = registry.create();
   // UpdateTransform(registry, main_light, vec3{3, 2.5f, -3}, vec3{0.5f});
    // color times power of the light
  //  AddPointLight(registry, main_light, vec3{1.0f, 1.0f, 1.0f} * 50.0f);
  // UpdateMaterial(AddSphereComponent(registry, main_light).material, vec3{0}, vec3{1.0f, 1.0f, 1.0f}, 0, 0, false);
}
void Controller::InitInput()
{
    auto update_bitmap = [this](float, Input::KeySeq const &seq, uint32_t count)
    {
        if (count == UINT32_MAX) return;
        int32_t offset = (seq[0] == 'P') ? -1 : 1;
        window_.resolution_scale() += offset;
        rclamp(window_.resolution_scale(), 1, 128);
        window_.OnScaleChanged();
    };
    input_.AddTickKeyCallback({'P'}, update_bitmap, false);
    input_.AddTickKeyCallback({'L'}, update_bitmap, false);

    auto adjust_exposure = [this](float dt, Input::KeySeq const &seq, uint32_t)
    {
        float offset = ((seq[0] == Key::KEY_PLUS || seq[0] == Key::KEY_NUMPAD_PLUS)) ? 0.5f : -0.5f;
        scene_->exposure += offset * dt;
        OutputDebugStringA(("Exposure value: " + std::to_string(scene_->exposure) + "\n").c_str());
    };
    input_.AddTickKeyCallback({Key::KEY_PLUS}, adjust_exposure, true);
    input_.AddTickKeyCallback({Key::KEY_MINUS}, adjust_exposure, true);
    input_.AddTickKeyCallback({Key::KEY_NUMPAD_PLUS}, adjust_exposure, true);
    input_.AddTickKeyCallback({Key::KEY_NUMPAD_MINUS}, adjust_exposure, true);

    auto reflect_switch = [this](float, Input::KeySeq const &, uint32_t count)
    {
        if (count == UINT32_MAX) return;
        scene_->reflections_on = !scene_->reflections_on;
    };
    input_.AddTickKeyCallback({Key::KEY_R}, reflect_switch, false);
    auto gi_switch = [this](float, Input::KeySeq const &, uint32_t count)
    {
        if (count == UINT32_MAX) return;
        scene_->UpdateScene();
        scene_->global_illumination_on = !scene_->global_illumination_on;
    };
    input_.AddTickKeyCallback({Key::KEY_G}, gi_switch, false);
}

Controller::Controller(BitmapWindow &window,
                       std::shared_ptr<Scene> scene,
                       CameraController const &cam) : camera_controller_(cam), scene_(scene), window_(window)
{
    InitScene();
    InitInput();
}

void Controller::OnEvent(Event &event)
{
    if (event.in_category(EventCategoryApplication))
    {
        if (event.type() == EventType::AppUpdate)
        {
            window_.PeekOSMessages();
            input_.OnEvent(event);
        }
        else if (event.type() == EventType::AppTick)
        {
            auto const &ate = static_cast<AppTickEvent &>(event);
            input_.OnEvent(event); // process input callbacks
            Tick(ate.delta_time());
            time_from_start_ += ate.delta_time();
            for (auto const &func : update_callbacks_)
            {
                func(ate.delta_time());
            }
            input_.flush();
        }
        else if (event.type() == EventType::AppRender)
        {
            if(!scene_->global_illumination_on)
            {
                scene_->UpdateScene();
            }
            scene_->Draw(camera_controller_.camera(), window_, executor);
        }
        else if (event.type() == EventType::WindowResize)
        {
            camera_controller_.UpdateProjectionMatrix();
            OutputDebugStringA("asd");
        }
        else if (event.type() == EventType::WindowClose)
        {
            Application::Exit();
        }
    }
    else if (event.in_category(EventCategoryInput))
    {
        input_.OnEvent(event);
        if (!event.in_category(EventCategoryMouse))
        {
            return;
        }
        if (event.type() == EventType::MouseButtonPressed)
        {
            auto const &mbpe = static_cast<MouseButtonPressedEvent &>(event);
            if (mbpe.mouse_button() == 1)
            {
                Ray ray = PixelRaycast(vec2{mbpe.coordinates()});
                Intersection intersection;
                intersection.reset();
                std::optional<entt::entity> entity = scene_->GetIntersectedEntity(intersection, ray);
                if (entity.has_value())
                {
                    selected_object_ = &scene_->registry.get<components::Transform>(entity.value());
                    selected_object_distance_ = intersection.t;
                    selected_object_offset_ = selected_object_->position - ray.PointAtParameter(intersection.t);
                    rb_saved_mouse_position_ = mbpe.coordinates();
                }
                else
                {
                    selected_object_ = nullptr;
                    selected_object_distance_ = 0;
                }
            }
            else if (mbpe.mouse_button() == 0)
            {
                lb_saved_mouse_position_ = mbpe.coordinates();
            }
        }
    }
}

void Controller::Tick(float delta_time)
{
    if (input_.rbutton_down() && selected_object_)
    {
        Ray a = PixelRaycast(vec2{rb_saved_mouse_position_});
        Ray b = PixelRaycast(vec2{input_.mouse_position()});
        rb_saved_mouse_position_ = input_.mouse_position();

        vec3 obj_offset = b.PointAtParameter(selected_object_distance_);

        selected_object_->position = selected_object_offset_ + obj_offset;
        selected_object_->UpdateMatrices();
    }
    if (input_.mouse_scrolled())
    {
        if (selected_object_ && input_.rbutton_down())
        {
            selected_object_->scale *= vec3{powf(math::clamp(1 + delta_time / 120 * input_.scroll_delta(), 0.5f, 1.5f), 0.5f)};
            rclamp(selected_object_->scale, 0.1f, std::numeric_limits<float>::max());
        }
        else
        {
            camera_controller_.camera().fovy_ -= delta_time / 120 * radians(45.0f) * input_.scroll_delta();
            rclamp(camera_controller_.camera().fovy_, radians(0.01f), radians(89.9f));
            camera_controller_.UpdateProjectionMatrix();
        }
    }

    engine::core::math::vec3 offset{0};
    // process movement
    if (input_.key_state('W'))
    {
        offset += kForward;
    }
    if (input_.key_state('S'))
    {
        offset += kBackwards;
    }
    if (input_.key_state('A'))
    {
        offset += kLeft;
    }
    if (input_.key_state('D'))
    {
        offset += kRight;
    }
    if (input_.key_state(VK_CONTROL))
    {
        offset += kDown;
    }
    if (input_.key_state(VK_SPACE))
    {
        offset += kUp;
    }

    float roll = 0;
    float yaw = 0;
    float pitch = 0;
    // process camera rotation
    if (camera_controller_.roll_enabled())
    {
        if (input_.key_state('Q'))
        {
            roll -= roll_speed_;
        }
        if (input_.key_state('E'))
        {
            roll += roll_speed_;
        }
    }
    else
    {
        if (input_.key_state('Q'))
        {
            offset += kDown;
        }
        if (input_.key_state('E'))
        {
            offset += kUp;
        }
    }
    if (input_.lbutton_down())
    {
        vec2 t{lb_saved_mouse_position_ - input_.mouse_position()};
        t = t / window_.window_size();
        t *= sensivity_;
        t *= camera_controller_.camera().fovy_;
        yaw = t.x;
        pitch = t.y;
    }
    if (!(roll == 0 && pitch == 0 && yaw == 0))
    {
        camera_controller_.AddRelativeAngles(delta_time * roll, delta_time * pitch, delta_time * yaw);
        scene_->global_illumination_on = false;
    }
    if (squared_length(offset) != 0)
    {
        camera_controller_.AddRelativeOffset(move_speed_ * offset * delta_time * (input_.key_state(Key::KEY_SHIFT) ? 5.0f : 1.0f));
        scene_->global_illumination_on = false;
    }
    camera_controller_.UpdateMatrices();
}