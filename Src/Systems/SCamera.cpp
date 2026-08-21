#include "SCamera.h"
#include "Logger.h"

SCamera::SCamera()
{
    RequireComponent<CCamera>();
    RequireComponent<CTransform>();
}

void SCamera::BeginPlay(const Registry* registry)
{
    CameraTarget = registry->GetEntityByTag(TargetID);
}

void SCamera::Update()
{
    const auto &transform = CameraTarget->GetComponent<CTransform>();
  
    auto camera = &CameraTarget->GetComponent<CCamera>(); 
    camera->position = transform.position;
    Logger::Info("Camera at position " + std::to_string(camera->position.x) + " : " + std::to_string(camera->position.y));
    const float HalfCameraWidth = CameraTarget->GetComponent<CCamera>().viewSize.x / 2.f;
    const float HalfCameraHeight = CameraTarget->GetComponent<CCamera>().viewSize.y / 2.f;
    camera->position.x = std::clamp(camera->position.x, HalfCameraWidth, Game::mapWidth - HalfCameraWidth);
    camera->position.y = std::clamp(camera->position.y, HalfCameraHeight, Game::mapHeight - HalfCameraHeight);
}
