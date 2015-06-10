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
	sf::Int16 waveOut1[44100 / 2];
	sf::Int16 waveOut2[44100 / 2];

	void in(Tone, Tone, Tone);
	void in(Tone, Tone);
	void in(Tone);
	void in(Chord, Tone);
	void in(Chord);
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
		sw = 0;
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

void rawGenerator::in(Chord a)
{
	double x = 0, y = 0, z = 0;

	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.name << endl;
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

void rawGenerator::in(Chord a, Tone b)
{
	double x = 0, y = 0, z = 0, w = 0;
	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);
	const double increment4 = (b.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.name << endl;
	cout << "Creating a mix of: " << increment1 << " + " << increment2 << " + " << increment3 << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Sample rate: " << SAMPLE_RATE << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{

		waveOut1[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI) + sin(w * TWO_PI)) * AMPLITUDE;
		x += increment1;
		y += increment2;
		z += increment3;
		w += increment4;
	}
}

//Synthese
int main()
{

	Tone key[89];
	double e = 1;
	for (int i = 0; i<=88; i = i + 1){

		double k = (e - 49) / 12;
		double var = pow(2.0, k) * 440;
		key[i].set("1", var);
		e = e + 1;
	}

	//TODO: complete chords
	Chord chord[18];
	chord[1].set("C chord", key[40], key[44], key[47]);
	chord[2].set("C# chord", key[41], key[45], key[36]);
	chord[3].set("Db chord", key[29], key[33], key[36]);
	chord[4].set("D chord", key[42], key[46], key[49]);
	chord[5].set("D# chord", key[31], key[35], key[37]);
	chord[6].set("Eb chord", key[31], key[35], key[37]);
	chord[7].set("E chord", key[32], key[36], key[39]);
	chord[8].set("F chord", key[33], key[37], key[40]);
	chord[9].set("F# chord", key[34], key[38], key[41]);
	chord[10].set("Gb chord", key[34], key[38], key[41]);
	chord[11].set("G chord", key[35], key[39], key[42]);
	chord[12].set("G# chord", key[36], key[40], key[43]);
	chord[13].set("Ab chord", key[36], key[40], key[43]);
	chord[14].set("A chord", key[37], key[41], key[44]);
	chord[15].set("A# chord", key[38], key[42], key[45]);
	chord[16].set("Bb chord", key[38], key[42], key[45]);
	chord[17].set("B chord", key[39], key[43], key[46]);
	
	rawGenerator r;

	for (int i = 1; i < 18; i++){
		r.in(chord[i], key[rand() % 88]);
		r.playStream();
	}
	system("pause");
	return 1;
}
