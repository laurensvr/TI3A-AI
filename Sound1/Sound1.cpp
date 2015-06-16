#include "stdafx.h"
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <SFML/System.hpp>
#include <fstream>

using namespace std;

class Tone
{
public:
	double frequency;
	std::string name;
	std::string getName(){
		return name;
	}
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
	std::string getName(){
		return name;
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
private:
	static const unsigned SAMPLES = 0.25 * 44100; //Zetten naar de kleinste kortste noot.
	static const unsigned SAMPLE_RATE = 44100;
	static const unsigned AMPLITUDE = 6000;
	const double TWO_PI = 6.28318;
	sf::Int16 waveOut[SAMPLES];
public:
	sf::SoundBuffer Buffer;
	sf::Sound Sound;
	int sw = 0;



	void in(Tone, Tone, Tone);
	void in(Tone, Tone);
	void in(Tone);
	void in(Chord, Tone);
	void in(Chord);
	void playStream();
};

void rawGenerator::playStream()
{
	if (sw == 0){
		if (!Buffer.loadFromSamples(waveOut, SAMPLES, 1, 44100)) {
			std::cerr << "Loading failed!" << std::endl;
			//return 1;
		}
		std::cout << "Sound 1" << std::endl;
		sw = 0;
	}


	Sound.setBuffer(Buffer);
	//Sound.setLoop(true);
	Sound.play();


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
		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI)) * AMPLITUDE;
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
		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI)) * AMPLITUDE;
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
		waveOut[i] = (sin(x * TWO_PI)) * AMPLITUDE;
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
		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI)) * AMPLITUDE;
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

		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI) + sin(w * TWO_PI)) * AMPLITUDE;
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
	int hight = 0;
	int Count = 0;
	for (int i = 0; i <= 88; i = i + 1)
	{
		string Hight;
		double k = (e - 49) / 12;
		double var = pow(2.0, k) * 440;
		switch (Count){
			case 0:
			{
				Hight = "A" + std::to_string(hight);
				break;
			}
			case 1:
			{
				Hight = "A#" + std::to_string(hight);
				break;
			}
			case 2:
			{
				Hight = "B" + std::to_string(hight);
				break;
			}
			case 3:
			{
				Hight = "C" + std::to_string(hight);
				break;
			}
			case 4:
			{
				Hight = "C#" + std::to_string(hight);
				break;
			}
			case 5:
			{
				Hight = "D" + std::to_string(hight);
				break;
			}
			case 6:
			{
				Hight = "D#" + std::to_string(hight);
				break;
			}
			case 7:
			{
				Hight = "E" + std::to_string(hight);
				break;
			}
			case 8:
			{
				Hight = "F" + std::to_string(hight);
				break;
			}
			case 9:
			{
				Hight = "F#" + std::to_string(hight);
				break;
			}
			case 10:
			{
				Hight = "G" + std::to_string(hight);
				break;
			}
			case 11:
			{
				Hight = "G#" + std::to_string(hight);
				break;
			}
		}
		key[i].set(Hight, var);
		e = e + 1;
		Count++;
		if (Count == 12)
		{
			hight++;
			Count = 0;
		}
		cout << "Hight: " << Hight << "+ count: " << i << endl;
	}

	//TODO: complete chords
	Chord chord[73];

	chord[1].set("MC1", key[40 - 24], key[44 - 24], key[47 - 24]);
	chord[2].set("MC#1 ", key[41 - 24], key[45 - 24], key[36 - 24]);
	chord[3].set("MD1 ", key[42 - 24], key[46 - 24], key[49 - 24]);
	chord[4].set("MD#1 ", key[31 - 24], key[35 - 24], key[37 - 24]);
	chord[5].set("ME1 ", key[32 - 24], key[36 - 24], key[39 - 24]);
	chord[6].set("MF1 ", key[33 - 24], key[37 - 24], key[40 - 24]);
	chord[7].set("MF#1 ", key[34 - 24], key[38 - 24], key[41 - 24]);
	chord[8].set("MG1 ", key[35 - 24], key[39 - 24], key[42 - 24]);
	chord[9].set("MG#1 ", key[36 - 24], key[40 - 24], key[43 - 24]);
	chord[10].set("MA1 ", key[37 - 24], key[41 - 24], key[44 - 24]);
	chord[11].set("MA#1 ", key[38 - 24], key[42 - 24], key[45 - 24]);
	chord[12].set("MB1 ", key[39 - 24], key[43 - 24], key[46 - 24]);

	chord[13].set("MC2 ", key[40 - 12], key[44 - 12], key[47 - 12]);
	chord[14].set("MC#2 ", key[41 - 12], key[45 - 12], key[36 - 12]);
	chord[15].set("MD2 ", key[42 - 12], key[46 - 12], key[49 - 12]);
	chord[16].set("MD#2 ", key[31 - 12], key[35 - 12], key[37 - 12]);
	chord[17].set("ME2 ", key[32 - 12], key[36 - 12], key[39 - 12]);
	chord[18].set("MF2 ", key[33 - 12], key[37 - 12], key[40 - 12]);
	chord[19].set("MF#2 ", key[34 - 12], key[38 - 12], key[41 - 12]);
	chord[20].set("MG2 ", key[35 - 12], key[39 - 12], key[42 - 12]);
	chord[21].set("MG#2 ", key[36 - 12], key[40 - 12], key[43 - 12]);
	chord[22].set("MA2 ", key[37 - 12], key[41 - 12], key[44 - 12]);
	chord[23].set("MA#2 ", key[38 - 12], key[42 - 12], key[45 - 12]);
	chord[24].set("MB2 ", key[39 - 12], key[43 - 12], key[46 - 12]);

	chord[25].set("MC3 ", key[40], key[44], key[47]);
	chord[26].set("MC#3 ", key[41], key[45], key[36]);
	chord[27].set("MD3 ", key[42], key[46], key[49]);
	chord[28].set("MD#3 ", key[31], key[35], key[37]);
	chord[29].set("ME3 ", key[32], key[36], key[39]);
	chord[30].set("MF3 ", key[33], key[37], key[40]);
	chord[31].set("MF#3 ", key[34], key[38], key[41]);
	chord[32].set("MG3 ", key[35], key[39], key[42]);
	chord[33].set("MG#3 ", key[36], key[40], key[43]);
	chord[34].set("MA3 ", key[37], key[41], key[44]);
	chord[35].set("MA#3 ", key[38], key[42], key[45]);
	chord[36].set("MB3 ", key[39], key[43], key[46]);

	chord[37].set("MC4 ", key[40 + 12], key[44 + 12], key[47 + 12]);
	chord[38].set("MC#4 ", key[41 + 12], key[45 + 12], key[36 + 12]);
	chord[39].set("MD4 ", key[42 + 12], key[46 + 12], key[49 + 12]);
	chord[40].set("MD#4 ", key[31 + 12], key[35 + 12], key[37 + 12]);
	chord[41].set("ME4 ", key[32 + 12], key[36 + 12], key[39 + 12]);
	chord[42].set("MF4 ", key[33 + 12], key[37 + 12], key[40 + 12]);
	chord[43].set("MF#4 ", key[34 + 12], key[38 + 12], key[41 + 12]);
	chord[44].set("MG4 ", key[35 + 12], key[39 + 12], key[42 + 12]);
	chord[45].set("MG#4 ", key[36 + 12], key[40 + 12], key[43 + 12]);
	chord[46].set("MA4 ", key[37 + 12], key[41 + 12], key[44 + 12]);
	chord[47].set("MA#4 ", key[38 + 12], key[42 + 12], key[45 + 12]);
	chord[48].set("MB4 ", key[39 + 12], key[43 + 12], key[46 + 12]);

	chord[49].set("MC5 ", key[40 + 24], key[44 + 24], key[47 + 24]);
	chord[50].set("MC#5 ", key[41 + 24], key[45 + 24], key[36 + 24]);
	chord[51].set("MD5 ", key[42 + 24], key[46 + 24], key[49 + 24]);
	chord[52].set("MD#5 ", key[31 + 24], key[35 + 24], key[37 + 24]);
	chord[53].set("ME5 ", key[32 + 24], key[36 + 24], key[39 + 24]);
	chord[54].set("MF5 ", key[33 + 24], key[37 + 24], key[40 + 24]);
	chord[55].set("MF#5 ", key[34 + 24], key[38 + 24], key[41 + 24]);
	chord[56].set("MG5 ", key[35 + 24], key[39 + 24], key[42 + 24]);
	chord[57].set("MG#5 ", key[36 + 24], key[40 + 24], key[43 + 24]);
	chord[58].set("MA5 ", key[37 + 24], key[41 + 24], key[44 + 24]);
	chord[59].set("MA#5 ", key[38 + 24], key[42 + 24], key[45 + 24]);
	chord[60].set("MB5 ", key[39 + 24], key[43 + 24], key[46 + 24]);

	chord[61].set("MC6 ", key[40 + 36], key[44 + 36], key[47 + 36]);
	chord[62].set("MC#6 ", key[41 + 36], key[45 + 36], key[36 + 36]);
	chord[63].set("MD6 ", key[42 + 36], key[46 + 36], key[49 + 36]);
	chord[64].set("MD#6 ", key[31 + 36], key[35 + 36], key[37 + 36]);
	chord[65].set("ME6 ", key[32 + 36], key[36 + 36], key[39 + 36]);
	chord[66].set("MF6 ", key[33 + 36], key[37 + 36], key[40 + 36]);
	chord[67].set("MF#6 ", key[34 + 36], key[38 + 36], key[41 + 36]);
	chord[68].set("MG6 ", key[35 + 36], key[39 + 36], key[42 + 36]);
	chord[69].set("MG#6 ", key[36 + 36], key[40 + 36], key[43 + 36]);
	chord[70].set("MA6 ", key[37 + 36], key[41 + 36], key[44 + 36]);
	chord[71].set("MA#6 ", key[38 + 36], key[42 + 36], key[45 + 36]);
	chord[72].set("MB6 ", key[39 + 36], key[43 + 36], key[46 + 36]);
	/* initialize random seed: */
	std::srand(time(NULL));

	
	rawGenerator r;
	
	ofstream fileSyntax, fileVariation1, fileVariation2;
	fileSyntax.open("syntax.txt");
	fileVariation1.open("variation1.txt");
	fileVariation2.open("variation2.txt");
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
				rChord = rand() % 72 + 1;
				rChordDuration = rand() % 3 + 1;
			}
			if (rToneDuration <= 0)
			{
				rTone = rand() % 10 + 41;
				rToneDuration = rand() % 3 + 1;
			}

			r.in(chord[rChord]); //Play a random Chord with a random duration
			//r.in(chord[rChord], key[rTone]); //Play a random Chord + a random Tone both with a random duration
			//r.in(key[(rand() % 88) + 1], key[(rand() % 88) + 1], key[(rand() % 88) + 1]); //Play three random keys changes every single beat.
			//r.in(key[(rand() % 88) + 1], key[(rand() % 88) + 1]);
			
			fileSyntax << chord[rChord].getName() << " " << key[rTone].getName() << endl;
			fileVariation1 << chord[rChord+1].getName() << " " << key[rTone+1].getName() << endl;
			fileVariation2 << chord[rChord-1].getName() << " " << key[rTone-1].getName() << endl;
			
			r.playStream();
			Clock.restart();

			rChordDuration--;
			rToneDuration--;
		}


	}
	fileSyntax.close();
	fileVariation1.close();
	fileVariation2.close();

	system("pause");
	return 1;
}
