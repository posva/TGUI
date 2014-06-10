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


#ifndef TGUI_TEXT_BOX_HPP
#define TGUI_TEXT_BOX_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Scrollbar;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API TextBox : public Widget, public WidgetBorders
    {
      public:

        typedef SharedWidgetPtr<TextBox> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox(const TextBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~TextBox() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox& operator= (const TextBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual TextBox* clone() override
        {
            return new TextBox(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "TextBox" section with the needed information.
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
        /// \brief Changes the size of the text box.
        ///
        /// This size does not include the borders.
        ///
        /// \param size  The new size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const sf::Vector2f& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the text box.
        ///
        /// This size does not include the borders.
        ///
        /// \return Size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const override
        {
            return sf::Vector2f(m_size);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the full size of the text box.
        ///
        /// This is the size including the borders.
        ///
        /// \return Full size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the text of the text box.
        ///
        /// \param text  New text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Appends some text to the text that was already in the text box.
        ///
        /// \param text  Text that will be added to the text that is already in the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the text of the text box.
        ///
        /// \return  The text that is currently inside the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const
        {
            return m_text;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// \param font  The new font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the text.
        ///
        /// \return  Pointer to the font that is currently being used
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const
        {
            return m_textBeforeSelection.getFont();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the character size of the text.
        ///
        /// \param size  The new text size.
        ///              The minimum text size is 8.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character size of the text.
        ///
        /// \return The current text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_textSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the maximum character limit.
        ///
        /// \param maxChars  The new character limit.
        ///                  Set it to 0 to disable the limit.
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum character limit.
        ///
        /// \return The character limit.
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters() const
        {
            return m_maxChars;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the border width and border height of the text box.
        ///
        /// \param leftBorder    The width of the left border
        /// \param topBorder     The height of the top border
        /// \param rightBorder   The width of the right border
        /// \param bottomBorder  The height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(float leftBorder   = 0,
                                float topBorder    = 0,
                                float rightBorder  = 0,
                                float bottomBorder = 0) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the colors from the text box.
        ///
        /// \param backgroundColor                      The color of the background of the text box.
        /// \param textColor                            The color of the text
        /// \param selectedTextColor                    The color of the text when it is selected
        /// \param selectedTextBackgroundColor          The color of the background of the text that is selected
        /// \param borderColor                          The color of the borders
        /// \param caretColor                           The color of the blinking caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& backgroundColor                      = sf::Color( 50,  50,  50),
                          const sf::Color& textColor                            = sf::Color(  0,   0,   0),
                          const sf::Color& selectedTextColor                    = sf::Color(255, 255, 255),
                          const sf::Color& selectedTextBackgroundColor          = sf::Color( 10, 110, 255),
                          const sf::Color& borderColor                          = sf::Color(  0,   0,   0),
                          const sf::Color& caretColor                           = sf::Color(110, 110, 255));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color that will be used inside the text box.
        ///
        /// \param backgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor)
        {
            m_backgroundColor = backgroundColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the text box.
        ///
        /// \param textColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color of the selected text that will be used inside the text box.
        ///
        /// \param selectedTextColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the text box.
        ///
        /// \param selectedTextBackgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextBackgroundColor(const sf::Color& selectedTextBackgroundColor)
        {
            m_selectedTextBgrColor = selectedTextBackgroundColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the border color that will be used inside the text box.
        ///
        /// \param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor)
        {
            m_borderColor = borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the color that will be used inside the text box for the blinking caret.
        ///
        /// \param caretColor  The color of the blinking caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretColor(const sf::Color& caretColor)
        {
            m_caretColor = caretColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color that is currently being used inside the text box.
        ///
        /// \return The color of the background of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor() const
        {
            return m_backgroundColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the text box.
        ///
        /// \return The text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const
        {
            return m_textBeforeSelection.getColor();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color of the selected text that is currently being used inside the text box.
        ///
        /// \return The selected text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor() const
        {
            return m_textSelection1.getColor();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected text that is currently being used inside the text box.
        ///
        /// \return The background color of the selected text that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextBackgroundColor() const
        {
            return m_selectedTextBgrColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the border color that is currently being used inside the text box.
        ///
        /// \return The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBorderColor() const
        {
            return m_borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the color that is currently being used inside the text box for the blinking caret.
        ///
        /// \return The color of the blinking caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getCaretColor() const
        {
            return m_caretColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the blinking caret to after a specific character.
        ///
        /// \param charactersBeforeCaret  The amount of characters that are before the blinking caret
        ///
        /// Normally you will not need this function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretPosition(unsigned int charactersBeforeCaret);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the scrollbar of the text box.
        ///
        /// \param scrollbarConfigFileFilename  Filename of the config file.
        ///                                     The config file must contain a Scrollbar section with the needed information.
        ///
        /// \return
        ///        - true when the scrollbar was successfully loaded
        ///        - false when the loading of the scrollbar failed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setScrollbar(const std::string& scrollbarConfigFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the scrollbar from the text box (if there is one).
        ///
        /// When there are too many lines to fit in the text box then some lines will be removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief This will change the width of the blinking caret.
        ///
        /// \param width  New width of the caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretWidth(unsigned int width = 2)
        {
            m_caretWidth = width;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the width of the blinking caret.
        ///
        /// \return width  Width of the caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getCaretWidth() const
        {
            return m_caretWidth;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Make the text box read-only or make it writable again
        ///
        /// \param readOnly  Should the text box be read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setReadOnly(bool readOnly = true)
        {
            m_readOnly = readOnly;
        }


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
        virtual bool mouseOnWidget(float x, float y) override;

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
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 Key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused() override;


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
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int findCaretPosition(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when you are selecting text.
        // It will find out which part of the text is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // To keep the drawing as fast as possible, all the calculation are done in front by this function.
        // It is called when the text changes, when scrolling, ...
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateDisplayedText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called by updateDisplayedText and will split the text into five pieces so that the text can
        // be easily drawn.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectionTexts(float maxLineWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When AnimationManager changes the elapsed time then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to TextBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum TextBoxCallbacks
        {
            TextChanged = WidgetCallbacksCount * 1,             ///< Text has changed
            AllTextBoxCallbacks = WidgetCallbacksCount * 2 - 1, ///< All triggers defined in TextBox and its base classes
            TextBoxCallbacksCount = WidgetCallbacksCount * 2
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        // The size of the text box
        sf::Vector2u m_size = sf::Vector2u(360, 200);

        // Some information about the text
        sf::String   m_text;
        sf::String   m_displayedText;
        unsigned int m_textSize = 30;
        unsigned int m_lineHeight = 40;
        unsigned int m_lines = 1;

        // The maximum characters (0 by default, which means no limit)
        unsigned int m_maxChars = 0;

        // What is known about the visible lines?
        unsigned int m_topLine = 1;
        unsigned int m_visibleLines = 1;

        // Information about the selection
        unsigned int m_selChars = 0;
        unsigned int m_selStart = 0;
        unsigned int m_selEnd = 0;

        // Information about the caret
        sf::Vector2u m_caretPosition;
        bool m_caretVisible = true;

        // The color of the blinking caret
        sf::Color m_caretColor;

        // The width in pixels of the blinking caret
        unsigned int m_caretWidth = 2;

        // Should the text be resplit into the five texts?
        bool m_selectionTextsNeedUpdate = true;

        // The colors that are used by the text box
        sf::Color m_backgroundColor;
        sf::Color m_selectedTextBgrColor;
        sf::Color m_borderColor;

        // The sfml Text widgets
        sf::Text m_textBeforeSelection;
        sf::Text m_textSelection1;
        sf::Text m_textSelection2;
        sf::Text m_textAfterSelection1;
        sf::Text m_textAfterSelection2;

        std::vector<float> m_multilineSelectionRectWidth;

        // The scrollbar
        Scrollbar* m_scroll = nullptr;

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        bool m_readOnly = false;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
