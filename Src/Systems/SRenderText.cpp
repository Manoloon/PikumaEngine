#include "SRenderText.h"
#include "../ECS/AssetStore.h"
#include "../Components/Components.h"

SRenderText::SRenderText()
{
    RequireComponent<CTextComponent>();
}

void SRenderText::Initialize(AssetStore* assetStore)
{
    // TODO : podriamos evitar mucho loop en tick
}

void SRenderText::Draw(sf::RenderWindow& window,AssetStore* assetStore, sf::RectangleShape& cameraActor)
{
    for(auto entity : GetSystemEntities())
    {
        const auto textcomp = entity.GetComponent<CTextComponent>();
        const sf::Font* font = assetStore->GetFont(textcomp.AssetID);
        sf::Text text(*font);
        text.setString(textcomp.Text);
        text.setCharacterSize(24);
        text.setFillColor(textcomp.Color);
        if(textcomp.IsFixed)
        {
            text.setPosition(textcomp.Position);
        }
        else
        {
            sf::Vector2f pos = {textcomp.Position - cameraActor.getPosition()};
            text.setPosition(pos);
        }
        window.draw(text);
        // setup de font and render the font in the position required and the color.
        // is Fixed ? position.x - 0 , sino position.x - camera.x , lo mismo para y.
    }
}
