#include "WATER_PUMP.h"

WATERPUMP::WATERPUMP(void)
{

}

WATERPUMP::WATERPUMP(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
	digitalWrite(_pin,0);
	_on = false;
	_val = 128;
	_parametre_tempo = 0;
	_tempo = 0;
}

WATERPUMP::~WATERPUMP(void)
{

}

void WATERPUMP::PUMP_ON(void)
{
	_on = true;
}

void WATERPUMP::PUMP_OFF(void)
{
	_on = false;
}

bool WATERPUMP::is_pump_on(void)
{
	return _on;
}

void WATERPUMP::set_val(int val)
{
	_val = val;
}

int WATERPUMP::get_val(void)
{
	return _val;
}

void WATERPUMP::set_tempo(int tempo)
{
	_parametre_tempo = tempo;
}

int WATERPUMP::get_current_tempo(void)
{
	return _tempo;
}

void WATERPUMP::tick(void)
{
	if(is_pump_on())
	{
		analogWrite(_pin, _val);
		if(!_tempo)
		{
			_tempo = _parametre_tempo;
			PUMP_OFF();
			analogWrite(_pin, 0);
		}
		else _tempo--;
	}
}