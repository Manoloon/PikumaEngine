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

void SRenderText::Update(AssetStore* assetStore)
{
    // for(auto entity : GetSystemEntities())
    // {
    //     const auto textcomp = entity.GetComponent<CTextComponent>();
    //     const auto font = assetStore->GetFont(textcomp.AssetID);
    //     // setup de font and render the font in the position required and the color.
    //     // is Fixed ? position.x - 0 , sino position.x - camera.x , lo mismo para y.

    // }
}

void SRenderText::Draw(sf::RenderWindow& window,AssetStore* assetStore)
{
        for(auto entity : GetSystemEntities())
    {
        const auto textcomp = entity.GetComponent<CTextComponent>();
        const sf::Font* font = assetStore->GetFont(textcomp.AssetID);
        sf::Text text(*font);
        text.setString(textcomp.Text);
        text.setCharacterSize(24);
        text.setFillColor(textcomp.Color);
        text.setPosition(textcomp.Position);
        window.draw(text);
        // setup de font and render the font in the position required and the color.
        // is Fixed ? position.x - 0 , sino position.x - camera.x , lo mismo para y.
    }
}
