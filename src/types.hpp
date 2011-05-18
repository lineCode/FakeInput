#ifndef FI_TYPES_HPP
#define FI_TYPES_HPP

namespace FakeInput
{
    /** Mouse button which can be pressed or released */
    enum MouseButton {
        Mouse_Left,
        Mouse_Middle,
        Mouse_Right
    };

    /** Predefined common US keyboard layout key types */
    enum KeyType {
        Key_NoKey = -1,

        Key_A, Key_B, Key_C, Key_D, Key_E, Key_F,
        Key_G, Key_H, Key_I, Key_J, Key_K, Key_L,
        Key_M, Key_N, Key_O, Key_P, Key_Q, Key_R,
        Key_S, Key_T, Key_U, Key_V, Key_W, Key_X,
        Key_Y, Key_Z, 

        Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,

        Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6, Key_F7, Key_F8,
        Key_F9, Key_F10, Key_F11, Key_F12, Key_F13, Key_F14, Key_F15, Key_F16,
        Key_F17, Key_F18, Key_F19, Key_F20, Key_F21, Key_F22, Key_F23, Key_F24,

        Key_Escape,
        Key_Space,
        Key_Return,
        Key_Backspace,
        Key_Tab,
        
        Key_Shift_L,
        Key_Shift_R,
        Key_Control_L,
        Key_Control_R,
        Key_Alt_L,
        Key_Alt_R,
        Key_Win_L,
        Key_Win_R,
        Key_Apps,

        Key_CapsLock,
        Key_NumLock,
        Key_ScrollLock,

        Key_PrintScreen,
        Key_Pause,

        Key_Insert,
        Key_Delete,
        Key_PageUP,
        Key_PageDown,
        Key_Home,
        Key_End,

        Key_Left,
        Key_Right,
        Key_Up,
        Key_Down,

        Key_Numpad0,
        Key_Numpad1,
        Key_Numpad2,
        Key_Numpad3,
        Key_Numpad4,
        Key_Numpad5,
        Key_Numpad6,
        Key_Numpad7,
        Key_Numpad8,
        Key_Numpad9,

        Key_NumpadAdd,
        Key_NumpadSubtract,
        Key_NumpadMultiply,
        Key_NumpadDivide,
        Key_NumpadDecimal,
        Key_NumpadEnter
    };
}

#endif