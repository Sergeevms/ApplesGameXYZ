#include "Utility.h"

namespace ApplesGame
{

    void DrawTexts(sf::RenderWindow& window, std::vector<sf::Text*> const & texts, Position2D position, RelativeOrigin relativeOrigin,
        Alignment alignment, Orientation orientation, float spacing)
    {
        sf::FloatRect totalRect;

        for (auto item = texts.begin(); item != texts.end(); ++item)
        {
            sf::FloatRect itemRect = (*item)->getGlobalBounds();
            if (orientation == Orientation::Vertical)
            {
                totalRect.width = std::max(totalRect.width, itemRect.width);
                totalRect.height += itemRect.height + (item != texts.end() - 1) ? spacing : 0.f;
            }
            else
            {
                totalRect.width += itemRect.height + (item != texts.end() - 1) ? spacing : 0.f;
                totalRect.height = std::max(totalRect.height, itemRect.height);
            }
        }

        totalRect.left = position.x - relativeOrigin.x * totalRect.width;
        totalRect.top = position.y - relativeOrigin.y * totalRect.height;
        sf::Vector2f currentPosition = { totalRect.left, totalRect.top };

        for (auto item = texts.begin(); item != texts.end(); ++item)
        {
            sf::FloatRect itemRect = (*item)->getGlobalBounds();
            RelativeOrigin itemOrigin;

            if (orientation == Orientation::Vertical)
            {
                itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                itemOrigin.y = 0.f;
                currentPosition.x = totalRect.left + itemOrigin.x * totalRect.width;
            }
            else
            {
                itemOrigin.x = 0.f;
                itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                currentPosition.y = totalRect.top + itemOrigin.y * totalRect.height;
            }

            SetOriginByRelative(*(*item), itemOrigin);
            (*item)->setPosition(currentPosition);
            window.draw(**item);

            if (orientation == Orientation::Vertical)
            {
                currentPosition.y += itemRect.height + spacing;
            }
            else
            {
                currentPosition.x += itemRect.width + spacing;
            }
        }
    }
}