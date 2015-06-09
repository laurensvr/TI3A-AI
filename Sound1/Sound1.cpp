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
	double getFrequency(){
		return frequency;
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

class rawGenerator
{
private:
	const unsigned SAMPLES = 0.50 * 44100; //Zetten naar de kleinste kortste noot.
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 6000;
	const double TWO_PI = 6.28318;
public:
	int sw = 0;
	sf::Int16 waveOut1[44100/2];
	sf::Int16 waveOut2[44100 / 2];

	void in(Tone, Tone, Tone);
	void in(Tone, Tone);
	void in(Tone);
	void in(Chord, Tone);
	void playStream();
};
void rawGenerator::playStream()
{
	sf::SoundBuffer Buffer;
	sf::Sound Sound;

	if (sw == 0){
		if (!Buffer.loadFromSamples(waveOut1, 0.50 * 44100, 1, 44100)) {
			std::cerr << "Loading failed!" << std::endl;
			//return 1;
		}
		std::cout << "Sound 1" << std::endl;
		sw = 1;
	}
	else
	{
		if (!Buffer.loadFromSamples(waveOut2, 0.50 * 44100, 1, 44100)) {
			std::cerr << "Loading failed!" << std::endl;
			//return 1;
		}
		std::cout << "Sound 2" << std::endl;
		sw = 0;
	}

	Sound.setBuffer(Buffer);
	//Sound.setLoop(true);
	Sound.play();
	sf::sleep(sf::milliseconds(500));
	Sound.stop();

}
void rawGenerator::in(Tone a, Tone b, Tone c)
{
	double x = 0, y = 0, z = 0;
	const double increment1 = (a.getFrequency() / SAMPLE_RATE);
	const double increment2 = (b.getFrequency() / SAMPLE_RATE);
	const double increment3 = (c.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.getFrequency() << " + " << b.getFrequency() << " + " << c.getFrequency() << endl;
	cout << "Creating a mix of: " << increment1 << " + " << increment2 << " + " << increment3 << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Sample rate: " << SAMPLE_RATE << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{
		waveOut1[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI)) * AMPLITUDE;
		x += increment1;
		y += increment2;
		z += increment3;
	}
}

void rawGenerator::in(Tone a, Tone b)
{
	double x = 0, y = 0, z = 0;
	const double increment1 = (a.getFrequency() / SAMPLE_RATE);
	const double increment2 = (b.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.getFrequency() << " + " << b.getFrequency() << endl;
	cout << "Creating a mix of: " << increment1 << " + " << increment2 << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Sample rate: " << SAMPLE_RATE << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{
		waveOut2[i] = (sin(x * TWO_PI) + sin(y * TWO_PI)) * AMPLITUDE;
		x += increment1;
		y += increment2;
	}
}

void rawGenerator::in(Tone a)
{
	double x = 0, y = 0, z = 0;

	const double increment1 = (a.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.getFrequency() << endl;
	cout << "Creating a mix of: " << increment1 << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Sample rate: " << SAMPLE_RATE << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{
		waveOut2[i] = (sin(x * TWO_PI)) * AMPLITUDE;
		x += increment1;
	}
}

//Synthese
int main() 
{
	//TODO: Fill in these keys 1-88
	Tone key[88];
	//These need to be recreated. start with the lowest note not CEG.
	key[1].set("C", 527.47);
	key[2].set("E", 418.65);
	key[3].set("G", 352.04);

	//TODO: FILL IN CHORDS
	Chord chord[17];
	chord[1].set("test", key[1], key[2], key[3]);

	rawGenerator r;
	r.in(key[1], key[2], key[3]);
	r.playStream();
	r.in(key[1], key[3]);
	r.playStream();
	r.in(key[1], key[2]);
	r.playStream();
	r.in(key[1]);
	r.playStream();
	double x = 0, y = 0, z = 0;
	system("pause");
	return 1;
}
