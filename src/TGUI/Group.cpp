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

// Many functions inside the Group struct look at each other but use different types of objects.
// These defines will avoid that there are too many copies of the code and thus will keep my code shorter.

#define TGUI_GROUP_ADD_FUNCTION(StructName) \
StructName* Group::add##StructName(const std::string objectName) \
{ \
    StructName* new##StructName = new StructName(); \
    new##StructName->m_Parent = this; \
    m_EventManager.addObject(new##StructName); \
  \
    m_Objects.push_back(new##StructName); \
    m_ObjName.push_back(objectName); \
  \
    return new##StructName; \
}

#define TGUI_GROUP_ADD_FUNCTION_WITH_FONT(StructName) \
StructName* Group::add##StructName(const std::string objectName) \
{ \
    StructName* new##StructName = new StructName(); \
    new##StructName->m_Parent = this; \
    new##StructName->setTextFont(globalFont); \
    m_EventManager.addObject(new##StructName); \
  \
    m_Objects.push_back(new##StructName); \
    m_ObjName.push_back(objectName); \
  \
    return new##StructName; \
}

#define TGUI_GROUP_COPY_FUNCTION_BY_NAME(StructName, EnumName, GroupName) \
StructName* Group::copy##StructName(const std::string oldObjectName, const std::string newObjectName) \
{ \
    for (unsigned int i=0; i<m_ObjName.size(); ++i) \
    { \
        if ((m_Objects[i]->m_ObjectType == EnumName) && (m_ObjName[i].compare(oldObjectName) == 0)) \
            return copyObject(static_cast<StructName*>(m_Objects[i]), newObjectName); \
    } \
  \
    return &m_Empty##StructName; \
}

#define TGUI_GROUP_GET_FUNCTION(StructName, EnumName, GroupName) \
StructName* Group::get##StructName(const std::string objectName) \
{ \
    for (unsigned int i=0; i<m_ObjName.size(); ++i) \
    { \
        if ((m_Objects[i]->m_ObjectType == EnumName) && (m_ObjName[i].compare(objectName) == 0)) \
            return static_cast<StructName*>(m_Objects[i]); \
    } \
  \
    return &m_Empty##StructName; \
}

#define TGUI_GROUP_REMOVE_OBJECT(EnumName) \
if (m_Objects[i]->m_ObjectType == EnumName) \
{ \
    m_EventManager.removeObject(m_Objects[i]->getObjectID()); \
    delete m_Objects[i]; \
    m_Objects.erase(m_Objects.begin() + i); \
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Label       Group::m_EmptyLabel;
    Picture     Group::m_EmptyPicture;
    Button      Group::m_EmptyButton;
    Checkbox    Group::m_EmptyCheckbox;
    RadioButton Group::m_EmptyRadioButton;
    EditBox     Group::m_EmptyEditBox;
    Slider      Group::m_EmptySlider;
    Scrollbar   Group::m_EmptyScrollbar;
    Listbox     Group::m_EmptyListbox;
    LoadingBar  Group::m_EmptyLoadingBar;
    Panel       Group::m_EmptyPanel;
    ComboBox    Group::m_EmptyComboBox;
    TextBox     Group::m_EmptyTextBox;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Group::Group()
    {
        globalFont = sf::Font::getDefaultFont();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Group::Group(const Group& copy) :
    globalFont(copy.globalFont)
    {
        // Copy all the objects
        for (unsigned int i=0; i<copy.m_Objects.size(); ++i)
        {
            if (copy.m_Objects[i]->m_ObjectType == picture)
                copyObject(static_cast<Picture*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == button)
                copyObject(static_cast<Button*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == checkbox)
                copyObject(static_cast<Checkbox*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == radioButton)
                copyObject(static_cast<RadioButton*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == label)
                copyObject(static_cast<Label*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == editBox)
                copyObject(static_cast<EditBox*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == listbox)
                copyObject(static_cast<Listbox*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == comboBox)
                copyObject(static_cast<ComboBox*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == slider)
                copyObject(static_cast<Slider*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == scrollbar)
                copyObject(static_cast<Scrollbar*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == loadingBar)
                copyObject(static_cast<LoadingBar*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == textBox)
                copyObject(static_cast<TextBox*>(copy.m_Objects[i]));
            if (copy.m_Objects[i]->m_ObjectType == panel)
                copyObject(static_cast<Panel*>(copy.m_Objects[i]));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Group::~Group()
    {
        removeAllObjects();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Group& Group::operator= (const Group& right)
    {
        // Make sure it is not the same object
        if (this != &right)
        {
            // Copy the font
            globalFont = right.globalFont;

            // Copy all the objects
            for (unsigned int i=0; i<right.m_Objects.size(); ++i)
            {
                if (right.m_Objects[i]->m_ObjectType == picture)
                    copyObject(static_cast<Picture*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == button)
                    copyObject(static_cast<Button*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == checkbox)
                    copyObject(static_cast<Checkbox*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == radioButton)
                    copyObject(static_cast<RadioButton*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == label)
                    copyObject(static_cast<Label*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == editBox)
                    copyObject(static_cast<EditBox*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == listbox)
                    copyObject(static_cast<Listbox*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == comboBox)
                    copyObject(static_cast<ComboBox*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == slider)
                    copyObject(static_cast<Slider*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == scrollbar)
                    copyObject(static_cast<Scrollbar*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == loadingBar)
                    copyObject(static_cast<LoadingBar*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == textBox)
                    copyObject(static_cast<TextBox*>(right.m_Objects[i]));
                if (right.m_Objects[i]->m_ObjectType == panel)
                    copyObject(static_cast<Panel*>(right.m_Objects[i]));
            }
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EditBox* Group::addEditBox(const std::string objectName)
    {
        EditBox* newEditBox = new EditBox();
        newEditBox->m_Parent = this;
        newEditBox->setTextFont(globalFont);
        m_EventManager.addObject(newEditBox);
//        m_AnimationManager.addObject(newEditBox);

        m_Objects.push_back(newEditBox);
        m_ObjName.push_back(objectName);

        return newEditBox;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Panel* Group::addPanel(const std::string objectName)
    {
        Panel* newPanel = new Panel();
        newPanel->m_Parent = this;
        newPanel->globalFont = globalFont;
        m_EventManager.addObject(newPanel);

        m_Objects.push_back(newPanel);
        m_ObjName.push_back(objectName);

        return newPanel;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_GROUP_ADD_FUNCTION (Picture)
    TGUI_GROUP_ADD_FUNCTION (Slider)
    TGUI_GROUP_ADD_FUNCTION (Scrollbar)
    TGUI_GROUP_ADD_FUNCTION (LoadingBar)

    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (Label)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (Button)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (Checkbox)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (RadioButton)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (Listbox)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (ComboBox)
    TGUI_GROUP_ADD_FUNCTION_WITH_FONT (TextBox)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_GROUP_GET_FUNCTION (Label,       label,       m_Labels)
    TGUI_GROUP_GET_FUNCTION (Picture,     picture,     m_Pictures)
    TGUI_GROUP_GET_FUNCTION (Button,      button,      m_Buttons)
    TGUI_GROUP_GET_FUNCTION (Checkbox,    checkbox,    m_Checkboxes)
    TGUI_GROUP_GET_FUNCTION (RadioButton, radioButton, m_RadioButtons)
    TGUI_GROUP_GET_FUNCTION (EditBox,     editBox,     m_EditBoxes)
    TGUI_GROUP_GET_FUNCTION (Slider,      slider,      m_Sliders)
    TGUI_GROUP_GET_FUNCTION (Scrollbar,   scrollbar,   m_Scrollbars)
    TGUI_GROUP_GET_FUNCTION (Listbox,     listbox,     m_Listboxes)
    TGUI_GROUP_GET_FUNCTION (LoadingBar,  loadingBar,  m_LoadingBars)
    TGUI_GROUP_GET_FUNCTION (Panel,       panel,       m_Panels)
    TGUI_GROUP_GET_FUNCTION (ComboBox,    comboBox,    m_ComboBoxes)
    TGUI_GROUP_GET_FUNCTION (TextBox,     textBox,     m_TextBoxes)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<OBJECT*>& Group::getObjects()
    {
        return m_Objects;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    T* Group::copyObject(T* oldObject, const std::string newObjectName)
    {
        T* newObject = new T(*oldObject);
        m_EventManager.addObject(newObject);

        m_Objects.push_back(newObject);
        m_ObjName.push_back(newObjectName);

        return newObject;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Label,       label,       m_Labels)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Picture,     picture,     m_Pictures)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Button,      button,      m_Buttons)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Checkbox,    checkbox,    m_Checkboxes)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (RadioButton, radioButton, m_RadioButtons)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (EditBox,     editBox,     m_EditBoxes)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Slider,      slider,      m_Sliders)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Scrollbar,   scrollbar,   m_Scrollbars)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Listbox,     listbox,     m_Listboxes)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (LoadingBar,  loadingBar,  m_LoadingBars)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (Panel,       panel,       m_Panels)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (ComboBox,    comboBox,    m_ComboBoxes)
    TGUI_GROUP_COPY_FUNCTION_BY_NAME (TextBox,     textBox,     m_TextBoxes)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::removeObject(const std::string objectName)
    {
        // Loop through every object
        for (unsigned int i=0; i<m_ObjName.size(); ++i)
        {
            // Check if the name matches
            if (m_ObjName[i].compare(objectName) == 0)
            {
                // remove the object
                if (m_Objects[i]->m_ObjectType == editBox)
                {
                    m_EventManager.removeObject(m_Objects[i]->getObjectID());
//                    m_AnimationManager.removeObject(static_cast<EditBox*>(m_Objects[i]));
                    delete m_Objects[i];
                    m_Objects.erase(m_Objects.begin() + i);
                }
                else TGUI_GROUP_REMOVE_OBJECT(label)
                else TGUI_GROUP_REMOVE_OBJECT(picture)
                else TGUI_GROUP_REMOVE_OBJECT(button)
                else TGUI_GROUP_REMOVE_OBJECT(checkbox)
                else TGUI_GROUP_REMOVE_OBJECT(radioButton)
                else TGUI_GROUP_REMOVE_OBJECT(slider)
                else TGUI_GROUP_REMOVE_OBJECT(scrollbar)
                else TGUI_GROUP_REMOVE_OBJECT(listbox)
                else TGUI_GROUP_REMOVE_OBJECT(loadingBar)
                else TGUI_GROUP_REMOVE_OBJECT(panel)
                else TGUI_GROUP_REMOVE_OBJECT(comboBox)
                else TGUI_GROUP_REMOVE_OBJECT(textBox)

                // Also emove the name it from the list
                m_ObjName.erase(m_ObjName.begin() + i);

                break;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::removeAllObjects()
    {
        // Remove all the objects from the event and animation manager
        m_EventManager.removeAllObjects();
//        m_AnimationManager.removeAllObjects();

        // Delete all objects
        for (unsigned int i=0; i<m_Objects.size(); ++i)
            delete m_Objects[i];

        // Clear the lists
        m_Objects.clear();
        m_ObjName.clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::uncheckRadioButtons()
    {
        // Loop through all radio buttons and uncheck them
        for (unsigned int i=0; i<m_Objects.size(); ++i)
        {
            if (m_Objects[i]->m_ObjectType == radioButton)
                static_cast<RadioButton*>(m_Objects[i])->m_Checked = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::focus(OBJECT* object)
    {
        m_EventManager.setFocus(object->getObjectID());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::unfocus(OBJECT* object)
    {
        m_EventManager.unfocusObject(object);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::moveObjectToFront(OBJECT* object)
    {
        m_EventManager.moveObjectToFront(object);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::moveObjectToBack(OBJECT* object)
    {
        m_EventManager.moveObjectToBack(object);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::updateTime(const sf::Time& elapsedTime)
    {
        m_EventManager.updateTime(elapsedTime);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Group::drawObjectGroup(sf::RenderTarget* target, const sf::RenderStates& states) const
    {
        unsigned int objectID = 0;
        unsigned int highestID = TGUI_MAX_OBJECTS;
        unsigned int lowestID = 0;

        for (unsigned int i=0; i<m_Objects.size(); ++i)
        {
            // Loop through all objects
            for (unsigned int j=0; j<m_Objects.size(); ++j)
            {
                // Check if the visible object has a higher id
                if ((m_Objects[j]->isVisible()) && (m_Objects[j]->m_ObjectID > lowestID))
                {
                    // Make sure that the object id is the smallest
                    if (m_Objects[j]->m_ObjectID < highestID)
                    {
                        // Remember the new highers id
                        highestID = m_Objects[j]->m_ObjectID;

                        // Remember the object that has to be drawn
                        objectID = j;
                    }
                }
            }

            // Draw the object if it is allowed
            if (lowestID < m_Objects[objectID]->m_ObjectID)
                target->draw(*m_Objects[objectID], states);

            // Remember the new lowest id
            lowestID = m_Objects[objectID]->m_ObjectID;

            // Reset the highest id
            highestID = TGUI_MAX_OBJECTS;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
