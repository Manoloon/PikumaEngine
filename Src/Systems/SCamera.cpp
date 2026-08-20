#include "SCamera.h"
#include "Logger.h"

SCamera::SCamera()
{
    RequireComponent<CCamera>();
    RequireComponent<CTransform>();
}

void SCamera::BeginPlay()
{
    const auto locEntities = GetSystemEntities();
    Logger::Info("SCamera entities: " + std::to_string(locEntities.size()));
    for (const auto& entity : GetSystemEntities())
    {
        Logger::Info("Camera entity found");
        PlayerCamera = &entity.GetComponent<CCamera>();
        break;
    }
}

void SCamera::Update(sf::Time DeltaTime)
{
    for (const auto &entity : GetSystemEntities())
    {
        const auto &transform = entity.GetComponent<CTransform>();

        PlayerCamera->position = transform.position;

        PlayerCamera->position.x = std::clamp(PlayerCamera->position.x, PlayerCamera->size.x/2.f, Game::mapWidth - PlayerCamera->size.x/2.f);
        PlayerCamera->position.y = std::clamp(PlayerCamera->position.y, PlayerCamera->size.y/2.f, Game::mapHeight - PlayerCamera->size.y/2.f);
        break;
    }
}

const CCamera *SCamera::GetCamera() const
{
    return PlayerCamera;
}
