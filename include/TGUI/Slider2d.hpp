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


#ifndef TGUI_SLIDER2D_HPP
#define TGUI_SLIDER2D_HPP


#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Slider2d : public ClickableWidget
    {
      public:

        typedef SharedWidgetPtr<Slider2d> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Slider2d();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Slider2d() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Slider2d* clone() override
        {
            return new Slider2d(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "Slider2d" section with the needed information.
        /// \throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const
        {
            return m_loadedConfigFile;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the slider.
        ///
        /// \param width  The new size of the slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const sf::Vector2f& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a minimum value.
        ///
        /// \param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is (-1, -1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(const sf::Vector2f& minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a maximum value.
        ///
        /// \param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is (1, 1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(const sf::Vector2f& maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the current value.
        ///
        /// \param value  The new value
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(const sf::Vector2f& value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the minimum value.
        ///
        /// \return The current minimum value
        ///
        /// The default minimum value (-1, -1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMinimum() const
        {
            return m_minimum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum value.
        ///
        /// \return The current maximum value
        ///
        /// The default maximum value (1, 1).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMaximum() const
        {
            return m_maximum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the current value.
        ///
        /// \return The current value
        ///
        /// The default value is (0, 0).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getValue() const
        {
            return m_value;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change whether the thumb size changes when you change the size of the slider.
        ///
        /// \param fixedSize  If true then the size of the thumb doesn't change when calling setSize
        ///
        /// When \a fixedSize is set to false then the thumb will change size together with the slider.
        /// So if the slider is two times bigger than the loaded image, the thumb will also be two times bigger as its image.
        /// When \a fixedSize is set to true then the size of the thumb will always stay the same as the loaded image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFixedThumbSize(bool fixedSize)
        {
            m_fixedThumbSize = fixedSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns whether the thumb size changes when you change the size of the slider.
        ///
        /// \return whether the thumb size changes when you change the size of the slider
        ///
        /// \see setFixedThumbSize
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getFixedThumbSize() const
        {
            return m_fixedThumbSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Decide whether or not the thumb will jump back to the center when the mouse is released.
        ///
        /// \param autoCenterThumb  Place the thumb in the center on mouse release?
        ///
        /// This behavior is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void enableThumbCenter(bool autoCenterThumb);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places the thumb back in the center.
        ///
        /// When enableThumbCenter(true) was called then this will happen automatically when the mouse is released.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void centerThumb();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void getProperty(std::string property, std::string& value) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Slider2d.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum Slider2dCallbacks
        {
            ValueChanged = ClickableWidgetCallbacksCount * 1,             ///< Value changed (slider moved)
            ThumbReturnedToCenter = ClickableWidgetCallbacksCount * 2,    ///< Thumb returned to center
            AllSlider2dCallbacks = ClickableWidgetCallbacksCount * 4 - 1, ///< All triggers defined in Slider2d and its base classes
            Slider2dCallbacksCount = ClickableWidgetCallbacksCount * 4
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        sf::Vector2f m_minimum = sf::Vector2f(-1, -1);
        sf::Vector2f m_maximum = sf::Vector2f(1, 1);
        sf::Vector2f m_value = sf::Vector2f(0, 0);

        bool m_returnThumbToCenter = false;
        bool m_fixedThumbSize = true;

        Texture m_textureThumbNormal;
        Texture m_textureThumbHover;
        Texture m_textureTrackNormal;
        Texture m_textureTrackHover;

        bool m_separateHoverImage = false;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SLIDER2D_HPP
