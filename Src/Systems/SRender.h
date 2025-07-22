//
// Created by Manoloon on 22/06/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include <algorithm>
#include "../ECS/AssetStore.h"
#include <SFML/Graphics.hpp>

class SRender : public System
{
public:
    SRender();
    static bool CompareByIndex(const Entity &a,const Entity &b);
  /**
  * \brief Gets the LoginSession object for the provided accountId, and creates one if necessary.
  * \param loginSessionId The AccountId for this login session.
  * \return The login session for that accountId.
  * \remarks If a new login session is created, then LoginSessions.AfterKeyAdded is raised.</remarks>
  */
    void Update(sf::RenderWindow& window,const std::unique_ptr<AssetStore>& assetStore,
                                    const sf::RectangleShape& camera) const;
    /*
    void Draw(sf::RenderWindow& window)
    {
        window.draw(spr)
    }*/
};
