/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
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


#include <TGUI/TGUI.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
/*
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void addCallback(Callback& callback)
    {
        TGUI_UNUSED_PARAM(callback);
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void unfocus(OBJECT* object)
    {
        TGUI_UNUSED_PARAM(object);
    }
*/
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    OBJECT::OBJECT() :
    callbackID (0),
    m_Visible    (true),
    m_Loaded     (false),
    m_ObjectPhase(0),
    m_Parent     (NULL),
    m_MouseHover (false),
    m_MouseDown  (false),
    m_ObjectID   (0),
    m_Focused    (false),
    m_AllowFocus (false)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    OBJECT::OBJECT(const OBJECT& copy) :
    callbackID   (copy.callbackID),
    m_Visible    (copy.m_Visible),
    m_Loaded     (copy.m_Loaded),
    m_ObjectPhase(copy.m_ObjectPhase),
    m_Parent     (copy.m_Parent),
    m_MouseHover (false),
    m_MouseDown  (false),
    m_ObjectID   (0),
    m_Focused    (false),
    m_AllowFocus (copy.m_AllowFocus),
    m_ObjectType (copy.m_ObjectType)
    {
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    OBJECT::~OBJECT()
    {
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    OBJECT& OBJECT::operator= (const OBJECT& right)
    {
        // Make sure it is not the same object
        if (this != &right)
        {
            callbackID    = right.callbackID;
            m_Visible     = right.m_Visible;
            m_Loaded      = right.m_Loaded;
            m_ObjectPhase = right.m_ObjectPhase;
            m_Parent      = right.m_Parent;
            m_MouseHover  = false;
            m_MouseDown   = false;
            m_ObjectID    = 0;
            m_Focused     = false;
            m_AllowFocus  = right.m_AllowFocus;
            m_ObjectType  = right.m_ObjectType;
        }
        
        return *this;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::show()
    {
        m_Visible = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::hide()
    {
        m_Visible = false;

        // We needed to override our parent's function to change the mouse button state.
        // If we don't do this then we might redraw the wrong image when the object becomes visible again.
        m_MouseHover = false;
        m_MouseDown = false;

        // If the object is focused then it must be unfocused
        m_Parent->unfocus(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool OBJECT::isVisible()
    {
        return m_Visible;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool OBJECT::isLoaded()
    {
        return m_Loaded;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    unsigned int OBJECT::getObjectID()
    {
        return m_ObjectID;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void OBJECT::moveToFront()
    {
        m_Parent->moveObjectToFront(this);
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void OBJECT::moveToBack()
    {
        m_Parent->moveObjectToBack(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::extractPhases(std::string phases)
    {
        std::string::size_type commaPos;

      NextPhase:

        // Search for the next comma
        commaPos = phases.find(',', 0);

        // Check if there was a comma
        if (commaPos != std::string::npos)
        {
            // Get the next phase
            std::string SinglePhase = phases.substr(0, commaPos);

            // Store the phase
            if (SinglePhase.compare("hover") == 0)
                m_ObjectPhase |= objectPhase::hover;
            else if (SinglePhase.compare("focus") == 0)
                m_ObjectPhase |= objectPhase::focused;
            else if (SinglePhase.compare("down") == 0)
                m_ObjectPhase |= objectPhase::mouseDown;

            // Remove this phase from the string
            phases.erase(0, commaPos+1);

            goto NextPhase;
        }
        else // There was no comma
        {
            // Store the phase
            if (phases.compare("hover") == 0)
                m_ObjectPhase |= objectPhase::hover;
            else if (phases.compare("focus") == 0)
                m_ObjectPhase |= objectPhase::focused;
            else if (phases.compare("down") == 0)
                m_ObjectPhase |= objectPhase::mouseDown;

            return;
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool OBJECT::isFocused()
    {
        return m_Focused;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ObjectTypes OBJECT::getObjectType()
    {
        return m_ObjectType;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool OBJECT::mouseOnObject(float x, float y)
    {
        TGUI_UNUSED_PARAM(x);
        TGUI_UNUSED_PARAM(y);

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::leftMousePressed(float x, float y)
    {
        TGUI_UNUSED_PARAM(x);
        TGUI_UNUSED_PARAM(y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::leftMouseReleased(float x, float y)
    {
        TGUI_UNUSED_PARAM(x);
        TGUI_UNUSED_PARAM(y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::mouseMoved(float x, float y)
    {
        TGUI_UNUSED_PARAM(x);
        TGUI_UNUSED_PARAM(y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::keyPressed(sf::Keyboard::Key key)
    {
        TGUI_UNUSED_PARAM(key);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::textEntered(char key)
    {
        TGUI_UNUSED_PARAM(key);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::objectFocused()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::objectUnfocused()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::mouseNotOnObject()
    {
        m_MouseHover = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void OBJECT::mouseNoLongerDown()
    {
        m_MouseDown = false;
    }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	OBJECT_BORDERS::OBJECT_BORDERS() :
	m_LeftBorder  (0),
	m_TopBorder   (0),
	m_RightBorder (0),
	m_BottomBorder(0)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color extractColor(std::string string)
    {
        int red;
        int green;
        int blue;
        int alpha = 255;

        // Make sure that the line isn't empty
        if (string.empty() == false)
        {
            // The first and last character have to be brackets
            if ((string[0] == '(') && (string[string.length()-1] == ')'))
            {
                // Remove the brackets
                string.erase(0, 1);
                string.erase(string.length()-1);

                // Search for the first comma
                std::string::size_type commaPos = string.find(',');
                if (commaPos != std::string::npos)
                {
                    // Get the red value and delete this part of the string
                    red = atoi(string.substr(0, commaPos).c_str());
                    string.erase(0, commaPos+1);

                    // Search for the second comma
                    commaPos = string.find(',');
                    if (commaPos != std::string::npos)
                    {
                        // Get the green value and delete this part of the string
                        green = atoi(string.substr(0, commaPos).c_str());
                        string.erase(0, commaPos+1);

                        // Search for the third comma (optional)
                        commaPos = string.find(',');
                        if (commaPos != std::string::npos)
                        {
                            // Get the blue value and delete this part of the string
                            blue = atoi(string.substr(0, commaPos).c_str());
                            string.erase(0, commaPos+1);

                            // Get the alpha value
                            alpha = atoi(string.c_str());
                        }
                        else // No alpha value was passed
                        {
                            // Get the blue value
                            blue = atoi(string.substr(0, commaPos).c_str());
                        }

                        // All values have to be unsigned chars
                        return sf::Color(static_cast <unsigned char> (red),
                                         static_cast <unsigned char> (green),
                                         static_cast <unsigned char> (blue),
                                         static_cast <unsigned char> (alpha));
                    }
                }
            }
        }

        // If you pass here then something is wrong about the line, the color will be black
        return sf::Color::Black;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool extractVector2f(std::string string, Vector2f& vector)
    {
        // Make sure that the string isn't empty
        if (string.empty() == false)
        {
            // The first and last character have to be brackets
            if ((string[0] == '(') && (string[string.length()-1] == ')'))
            {
                // Remove the brackets
                string.erase(0, 1);
                string.erase(string.length()-1);

                // Search for the first comma
                std::string::size_type commaPos = string.find(',');
                if (commaPos != std::string::npos)
                {
                    // Get the x value and delete this part of the string
                    vector.x = static_cast<float>(atof(string.substr(0, commaPos).c_str()));
                    string.erase(0, commaPos+1);

                    // Get the y value
                    vector.y = static_cast<float>(atof(string.c_str()));

                    return true;
                }
            }
        }

        // If you pass here then something is wrong with the string
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool extractVector4u(std::string string, Vector4u& vector)
    {
        // Make sure that the line isn't empty
        if (string.empty() == false)
        {
            // The first and last character have to be brackets
            if ((string[0] == '(') && (string[string.length()-1] == ')'))
            {
                // Remove the brackets
                string.erase(0, 1);
                string.erase(string.length()-1);

                // Search for the first comma
                std::string::size_type commaPos = string.find(',');
                if (commaPos != std::string::npos)
                {
                    // Get the first value and delete this part of the string
                    vector.x1 = atoi(string.substr(0, commaPos).c_str());
                    string.erase(0, commaPos+1);

                    // Search for the second comma
                    commaPos = string.find(',');
                    if (commaPos != std::string::npos)
                    {
                        // Get the second value and delete this part of the string
                        vector.x2 = atoi(string.substr(0, commaPos).c_str());
                        string.erase(0, commaPos+1);

                        // Search for the third comma
                        commaPos = string.find(',');
                        if (commaPos != std::string::npos)
                        {
                            // Get the third value and delete this part of the string
                            vector.x3 = atoi(string.substr(0, commaPos).c_str());
                            string.erase(0, commaPos+1);

                            // Get the fourth value
                            vector.x4 = atoi(string.c_str());

                            return true;
                        }
                    }
                }
            }
        }

        // If you pass here then something is wrong with the string
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////