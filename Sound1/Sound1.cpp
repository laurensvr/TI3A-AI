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
	void octave(int a)
	{

	}
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
public:
	int beat = 0;
	unsigned SAMPLES = 0.25 * 44100; //Zetten naar de kleinste kortste noot.
	unsigned SAMPLE_RATE = 44100;
	unsigned AMPLITUDE = 6000;
	double TWO_PI = 6.28318;
	sf::SoundBuffer Buffer;
	sf::Sound Sound;
	int sw = 0;
	sf::Int16 waveOut1[44100 / 4];
	sf::Int16 waveOut2[44100 / 4];
	rawGenerator();
	void in(Tone, Tone, Tone);
	void in(Tone, Tone);
	void in(Tone);
	void in(Chord, Tone);
	void in(Chord);
	void playStream();
};

rawGenerator::rawGenerator(){

};

void rawGenerator::playStream()
{
	if (sw == 0){
		if (!Buffer.loadFromSamples(waveOut1, 0.25 * 44100, 1, 44100)) {
			std::cerr << "Loading failed!" << std::endl;
			//return 1;
		}
		std::cout << "Sound 1" << std::endl;
		sw = 0;
	}
	/*
	else
	{
		if (!Buffer.loadFromSamples(waveOut2, 0.50 * 44100, 1, 44100)) {
			std::cerr << "Loading failed!" << std::endl;
			//return 1;
		}
		std::cout << "Sound 2" << std::endl;
		sw = 0;
	}
	*/
	Sound.setBuffer(Buffer);
	//Sound.setLoop(true);
	Sound.play();
	beat++;
	//sf::sleep(sf::milliseconds(250));
	
}

void rawGenerator::in(Tone a, Tone b, Tone c)
{
	double x = 0, y = 0, z = 0;
	const double increment1 = (a.getFrequency() / SAMPLE_RATE);
	const double increment2 = (b.getFrequency() / SAMPLE_RATE);
	const double increment3 = (c.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.getFrequency() << " + " << b.getFrequency() << " + " << c.getFrequency() << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Beat:        " << beat << endl;

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
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Beat:        " << beat << endl;

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
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Beat:        " << beat << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{
		waveOut1[i] = (sin(x * TWO_PI)) * AMPLITUDE;
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
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Beat:        " << beat << endl;

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
	cout << "Creating a mix of: " << a.name << " + " << b.getFrequency() << endl;
	cout << "Samples:     " << SAMPLES << endl;
	cout << "Beat:        " << beat << endl;

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
	for (int i = 0; i<=88; i = i + 1)
	{
		double k = (e - 49) / 12;
		double var = pow(2.0, k) * 440;
		key[i].set("i", var);
		e = e + 1;
	}

	//TODO: complete chords
	Chord chord[50+1];

	chord[1].set("C chord", key[40-12], key[44-12], key[47-12]);
	chord[2].set("C# chord", key[41-12], key[45-12], key[36-12]);
	chord[3].set("Db chord", key[29-12], key[33-12], key[36-12]);
	chord[4].set("D chord", key[42-12], key[46-12], key[49-12]);
	chord[5].set("D# chord", key[31-12], key[35-12], key[37-12]);
	chord[6].set("Eb chord", key[31-12], key[35-12], key[37-12]);
	chord[7].set("E chord", key[32-12], key[36-12], key[39-12]);
	chord[8].set("F chord", key[33-12], key[37-12], key[40-12]);
	chord[9].set("F# chord", key[34-12], key[38-12], key[41-12]);
	chord[10].set("Gb chord", key[34-12], key[38-12], key[41-12]);
	chord[11].set("G chord", key[35-12], key[39-12], key[42-12]);
	chord[12].set("G# chord", key[36-12], key[40-12], key[43-12]);
	chord[13].set("Ab chord", key[36-12], key[40-12], key[43-12]);
	chord[14].set("A chord", key[37-12], key[41-12], key[44-12]);
	chord[15].set("A# chord", key[38-12], key[42-12], key[45-12]);
	chord[16].set("Bb chord", key[38-12], key[42-12], key[45-12]);
	chord[17].set("B chord", key[39-12], key[43-12], key[46-12]);
	
	chord[18].set("C chord", key[40], key[44], key[47]);
	chord[19].set("C# chord", key[41], key[45], key[36]);
	chord[20].set("Db chord", key[29], key[33], key[36]);
	chord[21].set("D chord", key[42], key[46], key[49]);
	chord[22].set("D# chord", key[31], key[35], key[37]);
	chord[23].set("Eb chord", key[31], key[35], key[37]);
	chord[24].set("E chord", key[32], key[36], key[39]);
	chord[25].set("F chord", key[33], key[37], key[40]);
	chord[26].set("F# chord", key[34], key[38], key[41]);
	chord[27].set("Gb chord", key[34], key[38], key[41]);
	chord[28].set("G chord", key[35], key[39], key[42]);
	chord[29].set("G# chord", key[36], key[40], key[43]);
	chord[30].set("Ab chord", key[36], key[40], key[43]);
	chord[31].set("A chord", key[37], key[41], key[44]);
	chord[32].set("A# chord", key[38], key[42], key[45]);
	chord[33].set("Bb chord", key[38], key[42], key[45]);
	chord[34].set("B chord", key[39], key[43], key[46]);

	chord[35].set("C chord", key[40 + 12], key[44 + 12], key[47 + 12]);
	chord[36].set("C# chord", key[41 + 12], key[45 + 12], key[36 + 12]);
	chord[37].set("Db chord", key[29 + 12], key[33 + 12], key[36 + 12]);
	chord[38].set("D chord", key[42 + 12], key[46 + 12], key[49 + 12]);
	chord[39].set("D# chord", key[31 + 12], key[35 + 12], key[37 + 12]);
	chord[40].set("Eb chord", key[31 + 12], key[35 + 12], key[37 + 12]);
	chord[41].set("E chord", key[32 + 12], key[36 + 12], key[39 + 12]);
	chord[42].set("F chord", key[33 + 12], key[37 + 12], key[40 + 12]);
	chord[43].set("F# chord", key[34 + 12], key[38 + 12], key[41 + 12]);
	chord[43].set("Gb chord", key[34 + 12], key[38 + 12], key[41 + 12]);
	chord[44].set("G chord", key[35 + 12], key[39 + 12], key[42 + 12]);
	chord[45].set("G# chord", key[36 + 12], key[40 + 12], key[43 + 12]);
	chord[46].set("Ab chord", key[36 + 12], key[40 + 12], key[43 + 12]);
	chord[47].set("A chord", key[37 + 12], key[41 + 12], key[44 + 12]);
	chord[48].set("A# chord", key[38 + 12], key[42 + 12], key[45 + 12]);
	chord[49].set("Bb chord", key[38 + 12], key[42 + 12], key[45 + 12]);
	chord[50].set("B chord", key[39 + 12], key[43 + 12], key[46 + 12]);
	
	rawGenerator r;
	int rChordDuration = rand() % 3 + 1;
	int rToneDuration = rand() % 3 + 1;
	int rChord = rand() % 50 + 1;
	int rTone = rand() % 88 + 1;
	int rOctave = 0;

	sf::Clock Clock;
	sf::Time time;
	while (1)
	{
		time = Clock.getElapsedTime();
		if (time.asMicroseconds() >= 250000)
		{
			if (rChordDuration <= 0)
			{
				rChord = rand() % 50 + 1;
				rChordDuration = rand() % 3 + 1;
			}
			if (rToneDuration <= 0)
			{
				rTone = rand() % 10 + 41;
				rToneDuration = rand() % 3 + 1;
			}

			//r.in(chord[rChord]); //Play a random Chord with a random duration
			r.in(chord[rChord], key[rTone]); //Play a random Chord + a random Tone both with a random duration
			//r.in(key[(rand() % 88) + 1], key[(rand() % 88) + 1], key[(rand() % 88) + 1]); //Play three random keys changes every single beat.
			r.playStream();

			Clock.restart();

			rChordDuration--;
			rToneDuration--;
		}


	}

	system("pause");
	return 1;
}
