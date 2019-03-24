#include "WATER_PUMP.h"

WATERPUMP::WATERPUMP(void)
{

}

WATERPUMP::WATERPUMP(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
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
		digitalWrite(_pin, _val);
		_tempo--;
		if(!_tempo)
		{
			_tempo = _parametre_tempo;
			PUMP_OFF();
		}
	}

}