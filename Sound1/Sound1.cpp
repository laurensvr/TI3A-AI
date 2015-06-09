#include "stdafx.h"
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <SFML/System.hpp>

using namespace std;

class Tone 
{
public:
	double frequency;
	std::string name;
	void set(std::string a, double b)
	{
		name = a;
		frequency = b;
	}
};

class Chord 
{
public:
	std::string name;
	Tone tone1;
	Tone tone2;
	Tone tone3;
	Tone tone4;
	void set(std::string a, Tone b, Tone c, Tone d)
	{
		name = a;
		tone1 = b;
		tone2 = c;
		tone3 = d;
	}
};


//Synthese
int main() 
{
	//TODO: Fill in these keys 1-88
	Tone key[88];
	key[1].set("A0", 27.5000);
	key[2].set("As0", 29.1352);
	key[3].set("B0", 30.8677);

	//TODO: FILL IN CHORDS
	Chord chord[17];
	chord[1].set("test", key[1], key[2], key[3]);

	const unsigned SAMPLES = 0.50 * 44100; //Zetten naar de kleinste kortste noot.
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 6000;

	sf::Int16 raw1[SAMPLES];
	sf::Int16 raw2[SAMPLES];
	sf::Int16 raw3[SAMPLES];
	sf::Int16 raw4[SAMPLES];

	const double TWO_PI = 6.28318;
	const double increment1 = 527.47 / SAMPLE_RATE;
	const double increment2 = 418.65 / SAMPLE_RATE;
	const double increment3 = 352.04 / SAMPLE_RATE;

	double x = 0;
	double y = 0;
	double z = 0;
	//8 of 16 maten van 4 tellen
	//fourier synthese
	for (unsigned i = 0; i < SAMPLES; i++)
	{
		raw1[i] = AMPLITUDE * sin(x*TWO_PI);
		raw2[i] = AMPLITUDE * sin(y*TWO_PI);
		raw3[i] = AMPLITUDE * sin(z*TWO_PI);
		raw4[i] = raw1[i] + raw2[i] + raw3[i];
		x += increment1;
		y += increment2;
		z += increment3;
	}
	sf::SoundBuffer Buffer;
	sf::Sound Sound;
	int i = 0;
	while (1)
	{

		if (i == 0){
			if (!Buffer.loadFromSamples(raw4, SAMPLES, 1, SAMPLE_RATE)) {
				std::cerr << "Loading failed!" << std::endl;
				//return 1;
			}
			std::cout << "Sound 1" << std::endl;
			Sound.setPitch(1);
			i = 1;
		}
		else
		{
			if (!Buffer.loadFromSamples(raw2, SAMPLES, 1, SAMPLE_RATE)) {
				std::cerr << "Loading failed!" << std::endl;
				//return 1;
			}
			std::cout << "Sound 2" << std::endl;
			Sound.setPitch(1.2);
			i = 0;
		}

		Sound.setBuffer(Buffer);
		//Sound.setLoop(true);
		Sound.play();
		sf::sleep(sf::milliseconds(500));
		Sound.stop();
	}
	return 0;
}
