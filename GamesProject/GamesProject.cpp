﻿#include "stdafx.h"

const int _SIZE_X = 30, _SIZE_Y = 30, _COUNT_B = 100;

int mass[_SIZE_X * _SIZE_Y] = { 0 };

int _init_pole(int mass[], int size_x, int size_y, int count_b);

using namespace std;

int main() {
	setlocale(LC_ALL, ".866");
	return 0;
}

template <class T>
T size_mass(T x, T y) {
	return x * y;
}

int _inc_ver(int ver, int _max) {
	return (ver >= _max) ? (_max) : (++ver);
}

int _dec_ver(int ver, int _min = 0) {
	return (ver <= _min) ? (_min) : (--ver);
}

int _get_index_pole(int current, int _size_p, int _size_r, int index = 1) {
	switch (index) {
	case 1: return (current - _size_r > -1) ? (current - _size_r) : (current);
	case 2:
	case 8: {
		int _current = _get_index_pole(current, _size_p, _size_r);
		if (_current != current) {
			int __current;
			if (index == 8) __current = _get_index_pole(_current, _size_p, _size_r, 7);
			else __current = _get_index_pole(_current, _size_p, _size_r, 3);
			return (__current != _current) ? (__current) : (current);
		}
		else return current;
	}
	case 3: return ((current + 1 < _size_p) && ((current + 1) % _size_r)) ? (current + 1) : (current);
	case 4:
	case 6: {
		int _current = _get_index_pole(current, _size_p, _size_r, 5);
		if (_current != current) {
			int __current;
			if (index == 6) __current = _get_index_pole(_current, _size_p, _size_r, 7);
			else __current = _get_index_pole(_current, _size_p, _size_r, 3);
			return (__current != _current) ? (__current) : (current);
		}
		else return current;
	}
	case 5: return (current + _size_r < _size_p) ? (current + _size_r) : (current);
	case 7: return ((current - 1 > -1) && (current % _size_r)) ? (current - 1) : (current);
	default: return current;
	}
}

int _init_pole(int mass[], int size_x, int size_y) {
	for (unsigned int i = 0; i < size_mass<unsigned int>(size_x, size_y); i++)
		for (int j = 1; j < 9; j++)
			if (mass[i] != -1) {
				int index = _get_index_pole(i, size_mass<int>(size_x, size_y), size_y, j);
				if (index != static_cast<int>(i) && mass[index] == -1) mass[i]++;
			}
	return 0;
}

int _init_pole(int mass[], int size_x, int size_y, int count_b) {
	srand((unsigned int)mass);
	int _count = count_b, ver = 1;
	for (unsigned int i = 0; i < size_mass<unsigned int>(size_x, size_y); i++) {
		int c_ver = size_mass<unsigned int>(size_x, size_y) / _count;
		if (mass[i] != -1) {
			if (rand() % c_ver < ver) {
				mass[i] = -1;
				ver = 0;
				_count--;
			}
			else ver = _inc_ver(ver, c_ver - 2);
		}
		else  ver = _dec_ver(ver);
		if (!_count) return _init_pole(mass, size_x, size_y);
	}
	return _init_pole(mass, size_x, size_y, _count);
}

/****************************************************************************************
*       Работа с колодой                                                                *
****************************************************************************************/

/***************************************************************************
*                       Объявление констант                                *
***************************************************************************/

const int _CARD_CH = 3, _CARD_BB = 4, _CARD_TR = 5, _CARD_PK = 6;       // Константы мастей карт

const int _CARD_S[4] = { _CARD_CH, _CARD_BB, _CARD_TR, _CARD_PK };

const int   _CARD_0 = 0x30, _CARD_1 = 0x31, _CARD_2 = 0x32, _CARD_3 = 0x33, _CARD_4 = 0x34,
            _CARD_5 = 0x35, _CARD_6 = 0x36, _CARD_7 = 0x37, _CARD_8 = 0x38, _CARD_9 = 0x39,
            _CARD_V = 0x78, _CARD_D = 0x84, _CARD_K = 0x8A, _CARD_T = 0x92;

const int _CARD_M[13] = {
	_CARD_2, _CARD_3, _CARD_4, _CARD_5,
	_CARD_6, _CARD_7, _CARD_8, _CARD_9,
	_CARD_0,
	_CARD_V, _CARD_D, _CARD_K, _CARD_T };

const int _CARD_W = 5, _CARD_H = 4;

const int _SHIRT_CARDS = 0xB0;

const int _LR_O_BORDER = 0xB3, _TB_O_BORDER = 0xC4, _LT_O_BORDER = 0xDA, _LB_O_BORDER = 0xC0, _RT_O_BORDER = 0xBF, _RB_O_BORDER = 0xD9;

const int _LR_D_BORDER = 0xBA, _TB_D_BORDER = 0xCD, _LT_D_BORDER = 0xC9, _LB_D_BORDER = 0xC8, _RT_D_BORDER = 0xBB, _RB_D_BORDER = 0xBC;

int mass_card[_CARD_W * _CARD_H] = {
	_LT_O_BORDER, _TB_O_BORDER, _TB_O_BORDER, _TB_O_BORDER, _RT_O_BORDER,           // Примитив закрытой карты 176 - рубашка                    ┌───┐    ┌───┐    ┌───┐
	_LR_O_BORDER, _SHIRT_CARDS, _SHIRT_CARDS, _SHIRT_CARDS, _LR_O_BORDER,           // Позиция 6 - символ 32, позиция 8 - масть карты           │░░░│    │  ♣│    │  ♥│
	_LR_O_BORDER, _SHIRT_CARDS, _SHIRT_CARDS, _SHIRT_CARDS, _LR_O_BORDER,           // Позиция 8 - символ _CARD_1, если достоинство карты 10    │░░░│    │7  │    │10 │
                                                                                    // позиция 9 - достоинство карты, позиция 10 - символ 32    └───┘    └───┘    └───┘
    _LB_O_BORDER, _TB_O_BORDER, _TB_O_BORDER, _TB_O_BORDER, _RB_O_BORDER };

int mass_card_s[_CARD_W * _CARD_H] = {
	_LT_D_BORDER, _TB_D_BORDER, _TB_D_BORDER, _TB_D_BORDER, _RT_D_BORDER,           // Примитив закрытой выделенной карты
	_LR_D_BORDER, _SHIRT_CARDS, _SHIRT_CARDS, _SHIRT_CARDS, _LR_D_BORDER,
	_LR_D_BORDER, _SHIRT_CARDS, _SHIRT_CARDS, _SHIRT_CARDS, _LR_D_BORDER,
	_LB_D_BORDER, _TB_D_BORDER, _TB_D_BORDER, _TB_D_BORDER, _RB_D_BORDER };

const int _COUNT_USER_MACHINE = 1, _MAX_USER_MACHINE = 6, _ROW_USERS = 2;

const int _COUNT_PACK = 4, _COUNT_CARD = 52;

const int _TABLE_W = 60, _TABLE_H = 20;

const int _TABLE_USER_W = _TABLE_W / _MAX_USER_MACHINE * _ROW_USERS, _TABLE_USER_H = _TABLE_H / 4;

const int _TABLE_USER_BANK_W = _TABLE_USER_W / 2 - 2, _TABLE_USER_BANK_H = _TABLE_USER_H - 2;

const int _TABLE_MENU_W = _TABLE_W, _TABLE_MENU_H =  _TABLE_H / 4;

const int _TABLE_CROUPIER_W = _TABLE_W / 3, _TABLE_CROUPIER_H =  _TABLE_H / 4;

const int _TABLE_POLE_W = _TABLE_W / 3 * 2, _TABLE_POLE_H =  _TABLE_H / 4;

const int _MENU_BUTTON_W = 10, _MENU_BUTTON_H = 3;

const int _COUNT_MENU_BUTTON = _TABLE_MENU_W / _MENU_BUTTON_W;

const char _TABLE_GROUND_C = 0x20;

const int _MAX_RAUND = 5;

const int _START_USERS_BANKS = 1000;

int _mass_cards[_COUNT_CARD * _COUNT_PACK] = { 0 };

/***************************************************************************
*                       Функционал                                         *
***************************************************************************/

int _create_table_border(char mass[_TABLE_H][_TABLE_W], int _size_w = _TABLE_W, int _size_h = _TABLE_H);

int _create_table_border(char **mass, int _size_w, int _size_h);

int _create_table_croupier(char **mass, int _size_w, int _size_h);

int _create_table_menu(char **mass, int _size_w, int _size_h);

int _create_table_menu_button(char **mass, int _size_w, int _size_h, int _button_count = _COUNT_MENU_BUTTON, int _num = 0);

int _create_table_pole(char **mass, int _size_w, int _size_h);

int _create_table_pole_card(char **mass, int _size_w, int _size_h, int _card_count = 0, int _num = 0);

int _create_table_users(char **mass, int _size_w, int _size_h);

int _create_table_users_card(char **mass, int _size_w, int _size_h, int _card_count = 0, int _num = 0);

int _get_card(int _num, char *_color, char *_value);

inline int _get_color(int _num, char *color);

int &_get_count_user();

int _get_count_card_pole();

int _get_count_card_user();

int _get_current_card(int _index = 1);

int _get_pole_card(int _index);

int &_get_raund();

inline int _get_value(int _num, char *value);

int &_is_current_cardA();

int &_is_current_cardB();

int &_is_current_money();

int &_is_current_user();

bool &_is_open_card();

int &_is_pole_card_1();

int &_is_pole_card_2();

int &_is_pole_card_3();

int &_is_pole_card_4();

int &_is_pole_card_5();

bool &_is_select_card();

int _next_card();

int _rand_to(int _max);

int _set_current_user(int _id, bool _get = false);

int _set_pole_card(int _card);

int _sorted_package(int mass[], int _count = 36, int _count_pack = 1);

int _refresh_user_info(int user_id, int cardA, int cardB, bool open, bool _get = false);

inline int &_card_size() {
	static int _size = 0, _back = 0;
	if (_size % 4) _size = _back;
	else _back = _size;
	return _size;
}

int _create_card(char *ch, int _row = 1, bool _open = false, bool _select = false) {
	if (_row < 1 || _row > _CARD_H) return -1;
	const int row = _row - 1;
	for (int i = 0; i < _CARD_W; i++) {
		if (_select) ch[i] = mass_card[row * _CARD_W + i];
		else ch[i] = mass_card_s[row * _CARD_W + i];
		if ((i > 0) && (i < _CARD_W - 1) && _open) ch[i] = _TABLE_GROUND_C;
	}
	return 0;
}

int _create_card(char *ch, int card, int _row = 1, bool _open = false, bool _select = false) {
	int res = _create_card(ch, _row, _open, _select);
	if (_row == 2) return _get_color(card, ch + (_CARD_W - 2));
	if (_row == _CARD_H - 1) return _get_value(card, ch + 1);
	return res;
}

int _clear_table(char mass[_TABLE_H][_TABLE_W], int _size_w, int _size_h) {
	if (!_create_table_border(mass, _size_w, _size_h))
		for (int i = 1; i < _size_h - 1; i++)
			for (int j = 1; j < _size_w - 1; j++)
                mass[i][j] = _TABLE_GROUND_C;
	else return -1;
	return 0;
}

int _clear_table(char **mass, int _size_w, int _size_h) {
    for (int i = 1; i < _size_h - 1; i++)
        for (int j = 1; j < _size_w - 1; j++)
            mass[i][j] = _TABLE_GROUND_C;
	return 0;
}
int _create_menu_button(char **mass, int _size_w, int _size_h, int _num) {
    _create_table_border(mass, _size_w, _size_h);
    return 0;
}

int _create_table() {
	static char table_mass[_TABLE_H][_TABLE_W] = { 0 };
	if (!_get_raund())
		if (_clear_table(table_mass, _TABLE_W, _TABLE_H)) return -1;
	char *ch = &table_mass[0][0];
	if (!(_is_current_user() % 2)) ch += (_TABLE_USER_H + _TABLE_POLE_H) * _TABLE_W;
    ch += (_is_current_user() % 3) * _TABLE_USER_W;
#ifdef _CALLBACK
#else
    char **_mass = new char* [_TABLE_USER_H];
    for (int i = 0; i < _TABLE_USER_H; i++, ch += _TABLE_W)
        _mass[i] = ch;
    _create_table_users(_mass, _TABLE_USER_W, _TABLE_USER_H);
    delete[] _mass;
	ch = &table_mass[_TABLE_USER_H][0];
	_mass = new char*[_TABLE_POLE_H];
	for (int i = 0; i < _TABLE_POLE_H; i++, ch += _TABLE_W)
		_mass[i] = ch;
	_create_table_pole(_mass, _TABLE_POLE_W, _TABLE_POLE_H);
	delete[] _mass;
	ch = &table_mass[_TABLE_USER_H * 2 + _TABLE_POLE_H][0];
	_mass = new char*[_TABLE_MENU_H];
	for (int i = 0; i < _TABLE_MENU_H; i++, ch += _TABLE_W)
		_mass[i] = ch;
	_create_table_menu(_mass, _TABLE_MENU_W, _TABLE_MENU_H);
	delete[] _mass;
	ch = &table_mass[_TABLE_USER_H][_TABLE_POLE_W];
	_mass = new char*[_TABLE_CROUPIER_H];
	for (int i = 0; i < _TABLE_CROUPIER_H; i++, ch += _TABLE_W)
		_mass[i] = ch;
	_create_table_croupier(_mass, _TABLE_CROUPIER_W, _TABLE_CROUPIER_H);
	delete[] _mass;
#endif // _CALLBACK
	return 0;
}

int _create_table_bank(char **mass, int _size_w, int _size_h) {
    _create_table_border(mass, _size_w, _size_h);
    int _digit = 0;
    for (int _money = _is_current_money(); _money > 0; _money /= 10, _digit++);
	char  *ch = mass[_size_w / 2];
	ch += (_size_h - _digit) / 2;
#ifdef GCC
	if (_itoa(_is_current_money(), ch, 10)) return -1;
#else
	if (_itoa_s(_is_current_money(), ch, _digit, 10)) return -1;
#endif // GCC
	ch[_digit] = _TABLE_GROUND_C;
    return 0;
}

int _create_table_border(char mass[_TABLE_H][_TABLE_W], int _size_w, int _size_h) {
	mass[0][0] = _LT_D_BORDER, mass[0][_size_w - 1] = _RT_D_BORDER, mass[_size_h - 1][0] = _LB_D_BORDER, mass[_size_h - 1][_size_w - 1] = _RB_D_BORDER;
	for (int i = 1; i < _size_w - 1; i++)
        mass[0][i] = mass[_size_h - 1][i] = _TB_D_BORDER;
	for (int i = 1; i < _size_h - 1; i++)
        mass[i][0] = mass[i][_size_w - 1] = _LR_D_BORDER;
	return 0;
}

int _create_table_border(char **mass, int _size_w, int _size_h) {
	mass[0][0] = _LT_O_BORDER, mass[0][_size_w - 1] = _LB_O_BORDER, mass[_size_h - 1][0] = _RT_O_BORDER, mass[_size_h - 1][_size_w - 1] = _RB_O_BORDER;
	for (int i = 1; i < _size_w - 1; i++)
        mass[0][i] = mass[_size_h - 1][i] = _TB_O_BORDER;
	for (int i = 1; i < _size_h - 1; i++)
        mass[i][0] = mass[i][_size_w - 1] = _LR_O_BORDER;
	return 0;
}

int _create_table_croupier(char **mass, int _size_w, int _size_h) {
	if (_create_table_border(mass, _size_w, _size_h)) return -1;
	char **_mass = new char*[_size_h - 2];
	for (int i = 0; i < _size_h - 2; i++)
		_mass[i] = &mass[i + 1][1];
	int res = 0;// _create_table_menu_button(_mass, _size_w - 2, _size_h - 2, _get_count_card_pole());
	delete[] _mass;
	return res;
}

int _create_table_menu(char **mass, int _size_w, int _size_h) {
	if (_create_table_border(mass, _size_w, _size_h)) return -1;
	char **_mass = new char*[_size_h - 2];
	for (int i = 0; i < _size_h - 2; i++)
		_mass[i] = &mass[i + 1][1];
	int res = _create_table_menu_button(_mass, _size_w - 2, _size_h - 2, _get_count_card_pole());
	delete[] _mass;
	return res;
}

int _create_table_menu_button(char **mass, int _size_w, int _size_h, int _button_count, int _num) {
    if (_button_count < _num) return 0;
    switch (_num) {
    case 0:
        _clear_table(mass, _size_w, _size_h);
        return _create_table_menu_button(mass, _size_w, _size_h, _button_count, _num + 1);
    default: {
        char *ch = mass[(_size_h - _MENU_BUTTON_H) / 2];
        ch += (_size_w - _button_count * _MENU_BUTTON_W) / 2 + _MENU_BUTTON_W * (_num - 1);
        char **_mass = new char* [_MENU_BUTTON_H];
        for (int i = 1; i <= _MENU_BUTTON_H; i++, ch += _TABLE_W)
            _mass[i] = ch;
        _create_menu_button(_mass, _MENU_BUTTON_W, _MENU_BUTTON_H, _num);
        delete[] _mass;
        return _create_table_menu_button(mass, _size_w, _size_h, _button_count, _num + 1);
    }
    }
	return 0;
}

int _create_table_pole(char **mass, int _size_w, int _size_h) {
	if (_create_table_border(mass, _size_w, _size_h)) return -1;
	char **_mass = new char*[_size_h - 2];
	for (int i = 0; i < _size_h - 2; i++)
		_mass[i] = &mass[i + 1][1];
	int res = _create_table_pole_card(_mass, _size_w - 2, _size_h - 2, _get_count_card_pole());
	delete[] _mass;
	return res;
}

int _create_table_pole_card(char **mass, int _size_w, int _size_h, int _card_count, int _num) {
    if (_card_count < _num) return 0;
    switch (_num) {
    case 0:
        _clear_table(mass, _size_w, _size_h);
        return _create_table_users_card(mass, _size_w, _size_h, _card_count, _num + 1);
    default: {
        char *ch = mass[(_size_h - _CARD_H) / 2];
        ch += (_size_w - _card_count * _CARD_W) / 2 + _CARD_W * (_num - 1);
        for (int i = 1; i <= _CARD_H; i++, ch += _TABLE_W) _create_card(ch, _get_pole_card(_num), i, _is_open_card());
        return _create_table_users_card(mass, _size_w, _size_h, _card_count, _num + 1);
    }
    }
	return 0;
}

int _create_table_users(char **mass, int _size_w, int _size_h) {
    if (_create_table_border(mass, _size_w, _size_h)) return -1;
    char *ch = &mass[0][0];
    ch += ((_TABLE_USER_H - _TABLE_USER_BANK_H) / 2) * _TABLE_W - _TABLE_USER_BANK_W - 1;
    char **_mass = new char* [_TABLE_USER_BANK_H];
    for (int i = 0; i < _TABLE_USER_BANK_H; i++, ch += _TABLE_W)
        _mass[i] = ch;
    if (_create_table_bank(_mass, _TABLE_USER_BANK_W, _TABLE_USER_BANK_H)) {
        delete[] _mass;
        return -1;
    }
    delete[] _mass;
    _mass = new char* [_size_h - 2];
    for (int i = 0; i < _size_h - 2; i++)
        _mass[i] = &mass[i + 1][1];
    int res = _create_table_users_card(_mass, _size_w - _TABLE_USER_BANK_W - 2, _size_h - 2, _get_count_card_user());
    delete[] _mass;
	return res;
}

int _create_table_users_card(char **mass, int _size_w, int _size_h, int _card_count, int _num) {
    if (_card_count < _num) return 0;
    switch (_num) {
    case 0:
        _clear_table(mass, _size_w, _size_h);
        return _create_table_users_card(mass, _size_w, _size_h, _card_count, _num + 1);
    case 1:
    case 2:
        int& (*func[2])() = {_is_current_cardA, _is_current_cardB};
        char *ch = mass[(_size_h - _CARD_H) / 2];
        ch += (_size_w - _card_count * _CARD_W) / 2 + _CARD_W * (_num - 1);
        for (int i = 1; i <= _CARD_H; i++, ch += _TABLE_W) _create_card(ch, func[_num - 1](), i, _is_open_card());
        return _create_table_users_card(mass, _size_w, _size_h, _card_count, _num + 1);
    }
	return 0;
}

int _distribute() {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < _get_count_user(); j++) {
			_set_current_user(j, true);
			int _card = _next_card();
			if (i) _refresh_user_info(j, _is_current_cardA(), _card, _is_open_card());
			else _refresh_user_info(j, _card, _is_current_cardB(), _is_open_card());
		}
	return 0;
}

void _init_card(int mass[], int _count) {
	for (int i = 0; i < _count; i++) mass[i] = i;
}

int _get_card(int _num, char *_color, char *_value) {
	if (_num >= _card_size()) return -1;
	if (_get_color(_num, _color) && _get_value(_num, _value)) return -1;
	return 0;
}

inline int _get_color(int _num, char *color) {
	*color = _CARD_S[_num % _card_size()];
	return 0;
}

int &_get_count_user() {
	static int _count_user = _COUNT_USER_MACHINE + 1;
	if (_count_user > _MAX_USER_MACHINE) _count_user = _COUNT_USER_MACHINE + 1;
	return _count_user;
}

int &_get_count_card() {
	static int _count = _COUNT_CARD;
	return _count;
}

int _get_count_card_pole() {
    int _count = 0;
    for (int i = 1; i <=5; i++)
        if (_get_pole_card(i) > -1) _count++;
        else break;
	return _count;
}

int _get_count_card_user() {
	return (_is_current_cardA() != -1) ? ((_is_current_cardB() != -1) ? (2) : (1)) : (0);
}

int &_get_count_packed() {
	static int _count = _COUNT_PACK;
	return _count;
}

int _get_current_card(int _index) {
    switch (_index) {
    case 1:
        return _is_current_cardA();
    case 2:
        return _is_current_cardB();
    default : {
        return -1;
    }
    }
}

int _get_pole_card(int _index) {
    static int& (*func[5])() = {_is_pole_card_1, _is_pole_card_2, _is_pole_card_3, _is_pole_card_4, _is_pole_card_5};
    if (_index < 0 && _index > 4) return -1;
    else return func[_index]();
}

int &_get_raund() {
	static int _raund = 0;
	return _raund;
}

inline int _get_value(int _num, char *value) {
	int val = _num % (_card_size() / 4);
	switch (val) {
	case 4:
		*value = _CARD_1;
		value++;
	default: {
		*value = _CARD_M[12 - val];
	}
	}
	return 0;
}

int &_is_cursor_card() {
	static int _card = -1;
	if (_card > _get_count_card() * _get_count_card()) _card = -1;
	if (_card < 0) _sorted_package(_mass_cards, _COUNT_CARD, _COUNT_PACK);
	_card++;
	return _card;
}

int &_is_current_cardA() {
	static int _card = -1;
	return _card;
}

int &_is_current_cardB() {
	static int _card = -1;
	return _card;
}

int &_is_current_money() {
	static int _money = 0;
	return _money;
}

int &_is_current_user() {
	static int _user_id = 0, _back = 0;
	if (_user_id > _get_count_user()) _user_id = _back;
	else _back = _user_id;
	return _user_id;
}

int &_is_my_user() {
	static int _id = 0, _back = 0;
	if (_id > _get_count_user()) _id = _back;
	else _back = _id;
	return _id;
}

bool &_is_open_card() {
	static bool _opened = false;
	if (_get_raund() < _MAX_RAUND) {
		if (_is_current_user() == _is_my_user()) _opened = true;
		else _opened = false;
	}
	return _opened;
}

int &_is_pole_card_1() {
    static int _card = -1;
    return _card;
}

int &_is_pole_card_2() {
    static int _card = -1;
    return _card;
}

int &_is_pole_card_3() {
    static int _card = -1;
    return _card;
}

int &_is_pole_card_4() {
    static int _card = -1;
    return _card;
}

int &_is_pole_card_5() {
    static int _card = -1;
    return _card;
}

bool &_is_select_card() {
	static bool _selected = false;
	return _selected;
}

int _next_card() {
	return _mass_cards[_is_cursor_card()];
}

int _set_current_user(int _id, bool _get) {
	if (_id > _get_count_user()) return -1;
	_is_current_user() = _id;
	if (_get) return _is_current_user();
	else return _refresh_user_info(_is_current_user(), _is_current_cardA(), _is_current_cardB(), _is_open_card(), true);
}

int _set_pole_card(int _card) {
    static int& (*func[5])() = {_is_pole_card_1, _is_pole_card_2, _is_pole_card_3, _is_pole_card_4, _is_pole_card_5};
    static int& (**_curr)() = &func[0];
    if (_curr >= &func[0] && _curr <= &func[4]) {
        (*_curr)() = _card;
        _curr++;
    } else _curr = func;
    return _card;
}

int _shift_mass(int mass[], int _count, int _pos) {
	if (_pos >= _count) return -1;
	for (int i = _pos; i < _count - 1; i++) mass[i] = mass[i + 1];
	return 0;
}

void show_screen(char **mass, int _size_w, int _size_h) {
	system("cls");
	for (int i = 0; i < _size_h; i++) {
		for (int j = 0; j < _size_w; j++) printf("%c", mass[i][j]);
		printf("\n");
	}
}

int _sorted_card(int mass[], int _count = 36) {
	if (!_card_size()) _card_size() = _count;
	if ((_card_size() % 4) || !_card_size()) return -1;
	int _mass[52] = { 0 };
	_init_card(_mass, _card_size());
	for (int i = 0, j = _rand_to(_card_size()), _max = _card_size(); i < _card_size(); i++, j = _rand_to(--_max)) {
		mass[i] = _mass[j];
		_shift_mass(_mass, _max, j);
	}
	return 0;
}

int _sorted_package(int mass[], int _count, int _count_pack) {
	int res = _sorted_card(mass, _count);
	return (_count_pack) ? (_sorted_package(&mass[_count], _count, _count_pack - 1)) : (res);
}

int _rand_to(int _max) {
	return rand() % _max;
}

int _refresh_user_info(int user_id, int cardA, int cardB, bool open, bool _get) {
	if (user_id > _get_count_user()) return -1;
	static int _user_card[_MAX_USER_MACHINE][2];
	static bool _user_open_card[_MAX_USER_MACHINE];
	if (!_get) {
		_user_card[user_id][0] = cardA;
		_user_card[user_id][1] = cardB;
		_user_open_card[user_id] = open;
	}
    if (user_id != _is_current_user()) return user_id;
    _is_current_cardA() = _user_card[user_id][0];
    _is_current_cardB() = _user_card[user_id][1];
    _is_open_card() = _user_open_card[user_id];
	return user_id;
}
