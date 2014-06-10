/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_TEXTURE_HPP
#define TGUI_TEXTURE_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/Transformable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// TODO: Add documentation to functions

namespace tgui
{
    class TextureData;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class Texture : public sf::Transformable, public sf::Drawable
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture() {}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture(const Texture& copy);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ~Texture();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture& operator=(const Texture& right);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setTexture(TextureData& data, const sf::IntRect& middleRect);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        TextureData* getData() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setSize(const sf::Vector2f& size);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f getSize() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f getImageSize() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setColor(const sf::Color& color);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setTextureRect(const sf::FloatRect& textureRect);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bool isTransparentPixel(float x, float y) const;


    private:
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void updateVertices();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        enum ScalingType
        {
            Normal,
            Horizontal,
            Vertical,
            NineSliceScaling
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:
        TextureData* m_data = nullptr;
        std::vector<sf::Vertex> m_vertices;

        sf::Vector2f  m_size;
        sf::IntRect   m_middleRect;
        sf::FloatRect m_textureRect;

        ScalingType   m_scalingType = Normal;

        float m_rotation = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXTURE_HPP
