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

void SRenderText::Draw(sf::RenderWindow& window,AssetStore* assetStore,const CCamera& cameraActor)
{
    for(auto entity : GetSystemEntities())
    {
        const auto textcomp = entity.GetComponent<CTextComponent>();
        const sf::Font* font = assetStore->GetFont(textcomp.AssetID);
        sf::Text text(*font);
        text.setString(textcomp.Text);
        text.setCharacterSize(textcomp.Size);
        text.setFillColor(textcomp.Color);
        if(textcomp.IsFixed)
        {
            text.setPosition(cameraActor.position);
        }
        else
        {
            text.setPosition(textcomp.Position);
        }
        window.draw(text);
    }
}
