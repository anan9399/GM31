#pragma once

//TODO do not receive msg when kill forcus
// GetKeyboardState( m_KeyState );
class Keyboard
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

public:
	//Keyboard();
	static void Init();
	static void Uninit();
	static void Update();
	static void Reset();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

};
