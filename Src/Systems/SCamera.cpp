#include "SCamera.h"
#include "Logger.h"

SCamera::SCamera()
{
    RequireComponent<CCamera>();
    RequireComponent<CTransform>();
}

void SCamera::BeginPlay(const Registry *registry)
{
    CameraTarget = registry->GetEntityByTag(TargetID);
    if (CameraTarget == std::nullopt)
    {
        Logger::Error("SCamera: CameraTarget is nullptr");
        return;
    }
    Logger::Info("SCamera::BeginPlay -> TargetID: " + TargetID + " EntityID: " + std::to_string(CameraTarget->GetId()));
}

void SCamera::Update()
{
    const auto &transform = CameraTarget->GetComponent<CTransform>();
    auto camera = &CameraTarget->GetComponent<CCamera>();
    camera->position = transform.position;
    const float HalfCameraWidth = camera->viewSize.x / 2.f;
    const float HalfCameraHeight = camera->viewSize.y / 2.f;
    camera->position.x = std::clamp(camera->position.x, HalfCameraWidth, Game::mapWidth - HalfCameraWidth);
    camera->position.y = std::clamp(camera->position.y, HalfCameraHeight, Game::mapHeight - HalfCameraHeight);
}
