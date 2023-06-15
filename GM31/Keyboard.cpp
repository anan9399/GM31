
#include "main.h"
#include "Keyboard.h"


BYTE Keyboard::m_OldKeyState[256];
BYTE Keyboard::m_KeyState[256];


void Keyboard::Init()
{

	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);

}

void Keyboard::Uninit()
{


}

void Keyboard::Update()
{

	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);

}

bool Keyboard::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Keyboard::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}
