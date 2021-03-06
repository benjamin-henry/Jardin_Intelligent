#include "Plante.h"

PLANTE::PLANTE(void){}

PLANTE::PLANTE(int sensor_pin, int sensor_type, int pump_pin)
{
	_sensor = SEN_13322(sensor_pin, sensor_type);
	_pump = WATERPUMP(pump_pin);
}

PLANTE::~PLANTE()
{

}

void PLANTE::set_sensor_threshold(int thresh)
{
	_sensor.set_threshold(thresh);
}

int PLANTE::get_sensor_threshold(void)
{
	_sensor.get_threshold();
}

void PLANTE::set_sensor_tempo(int tempo)
{
	_sensor.set_tempo(tempo);
}

int PLANTE::get_sensor_tempo(void)
{
	_sensor.get_current_tempo();
}

void PLANTE::set_pump_tempo(int tempo)
{
	_pump.set_tempo(tempo);
}

int PLANTE::get_pump_tempo(void)
{
	_pump.get_current_tempo();
}

void PLANTE::tick(void)
{
	_sensor.tick();	
	if(_sensor.is_ready())
	{
		if(_sensor.get_type() == RESISTIVE)
		{
			if(_sensor.get_data() <= _sensor.get_threshold())
			{
				_pump.PUMP_ON();
			}
		}

		if(_sensor.get_type() == CAPACITIVE)
		{
			if(_sensor.get_data() >= _sensor.get_threshold())
			{
				_pump.PUMP_ON();
			}
		}
		_sensor.set_ready_flag(0);
	}
	_pump.tick();
}
