#include "stdafx.h"
#include "KBInput.h"
#include <cctype>


KBInput::KBInput() {
	W = 'W';
	A = 'A';
	S = 'S';
	D = 'D';
	Q = 'Q';
	E = 'E';
	w = 'w';
	a = 'a';
	s = 's';
	d = 'd';
	q = 'q';
	e = 'e';
}

void KBInput::BindKey(char key, const std::string& action)
{
	int aux = inputData[action];
	switch (aux)
	{
	case 0:
		D = toupper(key);
		d = tolower(key);
		break;
	case 1:
		A = toupper(key);
		a = tolower(key);
		break;
	case 2:
		Q = toupper(key);
		q = tolower(key);
		break;
		break;
	case 3:
		E = toupper(key);
		e = tolower(key);
		break;
	case 4:
		S = toupper(key);
		s = tolower(key);
		break;
	case 5:
		W = toupper(key);
		w = tolower(key);
		break;
	default:
		break;
	}
}