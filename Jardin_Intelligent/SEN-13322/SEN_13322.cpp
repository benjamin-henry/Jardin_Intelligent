#include "SEN_13322.h"

SEN_13322::SEN_13322()
{}

SEN_13322::SEN_13322(int pin)
{
	pinMode(pin, INPUT);
	_pin = pin;
	_data = 0;
	_threshold = 128;
	_parametre_tempo = 300;
	_tempo = 300;
}

SEN_13322::~SEN_13322(void)
{

}

void SEN_13322::read_data(void)
{
	_data = analogRead(_pin);
}

int SEN_13322::get_data(void)
{
	return _data;
}

int SEN_13322::read_n_get_data(void)
{	_data = 0;
	// on fait 16 prises de mesures via ADC et on fait la moyenne
	for(int sample = 0; sample < 16; sample++)
	{
		_data += analogRead(_pin);
	}
	_data >>= 4; 
	//Décaler le résultat de 4 bits vers la droite divise le résultat par 16 (2^4 = 2 x 2 x 2 x 2 = 16)
	//En fait, on divise par deux dés qu'on décale de 1 bit à droite. (on perd donc 1 bit de précision)
	//Le même principe est pour la multipication : on multiplie par deux quand on décale de 1 bit vers la gauche
	return _data;
}

void SEN_13322::set_threshold(int thresh)
{
	_threshold = thresh;
}

int SEN_13322::get_threshold(void)
{
	return _threshold;
}

void SEN_13322::set_tempo(int tempo)
{
	_parametre_tempo = tempo;
}

int SEN_13322::get_current_tempo(void)
{
	return _tempo;
}

void SEN_13322::tick(void)
{
	if(!_tempo)
	{
		_ready = true;
		_tempo = _parametre_tempo;
	}
	_tempo--; //tempo-- revient à écrire _tempo = tempo - 1. On aurait pu aussi écrire _tempo -= 1. 
}

bool SEN_13322::is_ready(void)
{
	return _ready;
}