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
		Tone zero;
		zero.set("x", 0.00);
		
		name = a;
		tone1 = b;
		tone2 = c;
		tone3 = d;
		tone4 = zero;

	}
	void set(std::string a, Tone b, Tone c, Tone d, Tone e)
	{
		name = a;
		tone1 = b;
		tone2 = c;
		tone3 = d;
		tone4 = e;
	}
};

class rawGenerator
{
private:
	static const unsigned SAMPLES = 0.25 * 44100; //Zetten naar de kleinste kortste noot.
	static const unsigned SAMPLE_RATE = 44100;
	static const unsigned AMPLITUDE = 4000;
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
	double x = 0, y = 0, z = 0, w = 0;

	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);
	const double increment4 = (a.tone4.getFrequency() / SAMPLE_RATE);
	cout << "Creating a mix of: " << a.name << endl;

	for (unsigned i = 0; i < SAMPLES; i++)
	{
		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI) + sin(w * TWO_PI))* AMPLITUDE;
		x += increment1;
		y += increment2;
		z += increment3;
		w += increment4;
	}
}

void rawGenerator::in(Chord a, Tone b)
{
	double x = 0, y = 0, z = 0, w = 0, v = 0;
	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);
	const double increment4 = (a.tone4.getFrequency() / SAMPLE_RATE);
	const double increment5 = (b.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.name << endl;


	for (unsigned i = 0; i < SAMPLES; i++)
	{

		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI) + sin(w * TWO_PI) + sin(v * TWO_PI)) * AMPLITUDE;
		x += increment1;
		y += increment2;
		z += increment3;
		v += increment4;
		w += increment5;
	}
}

//Synthese
int main()
{
	Tone key[89];
	double e = 1;
	int height = 0;
	int count = 0;
	for (int i = 0; i <= 88; i = i + 1)
	{
		string rHeight;
		double k = (e - 49) / 12;
		double var = pow(2.0, k) * 440;
		switch (count){
		case 0:
		{
			rHeight = "TA" + std::to_string(height);
			break;
		}
		case 1:
		{
			rHeight = "TA#" + std::to_string(height);
			break;
		}
		case 2:
		{
			rHeight = "TB" + std::to_string(height);
			break;
		}
		case 3:
		{
			rHeight = "TC" + std::to_string(height);
			break;
		}
		case 4:
		{
			rHeight = "TC#" + std::to_string(height);
			break;
		}
		case 5:
		{
			rHeight = "TD" + std::to_string(height);
			break;
		}
		case 6:
		{
			rHeight = "TD#" + std::to_string(height);
			break;
		}
		case 7:
		{
			rHeight = "TE" + std::to_string(height);
			break;
		}
		case 8:
		{
			rHeight = "TF" + std::to_string(height);
			break;
		}
		case 9:
		{
			rHeight = "TF#" + std::to_string(height);
			break;
		}
		case 10:
		{
			rHeight = "TG" + std::to_string(height);
			break;
		}
		case 11:
		{
			rHeight = "TG#" + std::to_string(height);
			break;
		}
		}
		key[i].set(rHeight, var);
		e = e + 1;
		count++;
		if (count == 12)
		{
			height++;
			count = 0;
		}
	}

	//TODO: complete chords

	Chord chord[101];
	
	chord[1].set("C1", key[40-24], key[44-24], key[47-24]);
	chord[2].set("C#1 ", key[41-24], key[45-24], key[36-24]);
	chord[3].set("D1 ", key[42-24], key[46-24], key[49-24]);
	chord[4].set("D#1 ", key[31-24], key[35-24], key[37-24]);
	chord[5].set("E1 ", key[32-24], key[36-24], key[39-24]);
	chord[6].set("F1 ", key[33-24], key[37-24], key[40-24]);
	chord[7].set("F#1 ", key[34-24], key[38-24], key[41-24]);
	chord[8].set("G1 ", key[35-24], key[39-24], key[42-24]);
	chord[9].set("G#1 ", key[36-24], key[40-24], key[43-24]);
	chord[10].set("A1 ", key[37-24], key[41-24], key[44-24]);
	chord[11].set("A#1 ", key[38-24], key[42-24], key[45-24]);
	chord[12].set("B1 ", key[39-24], key[43-24], key[46-24]);

	chord[13].set("C2 ", key[40-12], key[44-12], key[47-12]);
	chord[14].set("C#2 ", key[41-12], key[45-12], key[36-12]);
	chord[15].set("D2 ", key[42-12], key[46-12], key[49-12]);
	chord[16].set("D#2 ", key[31-12], key[35-12], key[37-12]);
	chord[17].set("E2 ", key[32-12], key[36-12], key[39-12]);
	chord[18].set("F2 ", key[33-12], key[37-12], key[40-12]);
	chord[19].set("F#2 ", key[34-12], key[38-12], key[41-12]);
	chord[20].set("G2 ", key[35-12], key[39-12], key[42-12]);
	chord[21].set("G#2 ", key[36-12], key[40-12], key[43-12]);
	chord[22].set("A2 ", key[37-12], key[41-12], key[44-12]);
	chord[23].set("A#2 ", key[38-12], key[42-12], key[45-12]);
	chord[24].set("B2 ", key[39-12], key[43-12], key[46-12]);

	
	chord[25].set("C3 ", key[40], key[44], key[47]);
	chord[26].set("C#3 ", key[41], key[45], key[36]);
	chord[27].set("CM7 ", key[40], key[44], key[47], key [51]);
	chord[28].set("CD7 ", key[40], key[44], key[47], key [50]);
	chord[29].set("Cm7 ", key[40], key[43], key[47], key [50]);
	chord[30].set("Cd7 ", key[40], key[43], key[46], key [49]);
	chord[31].set("D3 ", key[42], key[46], key[49]);
	chord[32].set("D#3 ", key[31], key[35], key[37]);
	chord[33].set("DM7 ", key[42], key[46], key[49], key [53]);
	chord[34].set("DD7 ", key[42], key[46], key[49], key [52]);
	chord[35].set("Dm7 ", key[42], key[45], key[49], key [52]);
	chord[36].set("Dd7 ", key[42], key[45], key[48], key [51]);
	chord[37].set("E3 ", key[32], key[36], key[39]);
	chord[38].set("EM7 ", key[44], key[48], key[51], key [55]);
	chord[39].set("ED7 ", key[44], key[48], key[51], key [54]);
	chord[40].set("Em7 ", key[44], key[47], key[51], key [54]);
	chord[41].set("Ed7 ", key[44], key[47], key[50], key [53]);
	chord[42].set("F3 ", key[33], key[37], key[40]);
	chord[43].set("F#3 ", key[34], key[38], key[41]);
	chord[44].set("FM7 ", key[45], key[49], key[52], key [56]);
	chord[45].set("FD7 ", key[45], key[49], key[52], key [55]);
	chord[46].set("Fm7 ", key[45], key[48], key[52], key [55]);
	chord[47].set("Fd7 ", key[45], key[48], key[51], key [54]);
	chord[48].set("G3 ", key[35], key[39], key[42]);
	chord[49].set("G#3 ", key[36], key[40], key[43]);
	chord[50].set("GM7 ", key[47], key[51], key[54], key [58]);
	chord[51].set("GD7 ", key[47], key[51], key[54], key [57]);
	chord[52].set("Gm7 ", key[47], key[50], key[54], key [57]);
	chord[53].set("Gd7 ", key[47], key[50], key[53], key [56]);
	chord[54].set("A3 ", key[37], key[41], key[44]);
	chord[55].set("A#3 ", key[38], key[42], key[45]);
	chord[56].set("AM7 ", key[37], key[41], key[44], key [48]);
	chord[57].set("AD7 ", key[37], key[41], key[44], key [47]);
	chord[58].set("Am7 ", key[37], key[40], key[44], key [47]);
	chord[59].set("Ad7 ", key[37], key[40], key[43], key [46]);
	chord[60].set("B3 ", key[39], key[43], key[46]);
	chord[61].set("BM7 ", key[39], key[43], key[46], key [50]);
	chord[62].set("BD7 ", key[39], key[43], key[46], key [49]);
	chord[63].set("Bm7 ", key[39], key[42], key[46], key [49]);
	chord[64].set("Bd7 ", key[39], key[42], key[45], key [48]);

	chord[65].set("C4 ", key[40+12], key[44+12], key[47+12]);
	chord[66].set("C#4 ", key[41+12], key[45+12], key[36+12]);
	chord[67].set("D4 ", key[42+12], key[46+12], key[49+12]);
	chord[68].set("D#4 ", key[31+12], key[35+12], key[37+12]);
	chord[69].set("E4 ", key[32+12], key[36+12], key[39+12]);
	chord[70].set("F4 ", key[33+12], key[37+12], key[40+12]);
	chord[71].set("F#4 ", key[34+12], key[38+12], key[41+12]);
	chord[72].set("G4 ", key[35+12], key[39+12], key[42+12]);
	chord[73].set("G#4 ", key[36+12], key[40+12], key[43+12]);
	chord[74].set("A4 ", key[37+12], key[41+12], key[44+12]);
	chord[75].set("A#4 ", key[38+12], key[42+12], key[45+12]);
	chord[76].set("B4 ", key[39+12], key[43+12], key[46+12]);

	chord[77].set("C5 ", key[40+24], key[44+24], key[47+24]);
	chord[78].set("C#5 ", key[41+24], key[45+24], key[36+24]);
	chord[79].set("D5 ", key[42+24], key[46+24], key[49+24]);
	chord[80].set("D#5 ", key[31+24], key[35+24], key[37+24]);
	chord[81].set("E5 ", key[32+24], key[36+24], key[39+24]);
	chord[82].set("F5 ", key[33+24], key[37+24], key[40+24]);
	chord[83].set("F#5 ", key[34+24], key[38+24], key[41+24]);
	chord[84].set("G5 ", key[35+24], key[39+24], key[42+24]);
	chord[85].set("G#5 ", key[36+24], key[40+24], key[43+24]);
	chord[86].set("A5 ", key[37+24], key[41+24], key[44+24]);
	chord[87].set("A#5 ", key[38+24], key[42+24], key[45+24]);
	chord[88].set("B5 ", key[39+24], key[43+24], key[46+24]);

	chord[89].set("C6 ", key[40+36], key[44+36], key[47+36]);
	chord[90].set("C#6 ", key[41+36], key[45+36], key[36+36]);
	chord[91].set("D6 ", key[42+36], key[46+36], key[49+36]);
	chord[92].set("D#6 ", key[31+36], key[35+36], key[37+36]);
	chord[93].set("E6 ", key[32+36], key[36+36], key[39+36]);
	chord[94].set("F6 ", key[33+36], key[37+36], key[40+36]);
	chord[95].set("F#6 ", key[34+36], key[38+36], key[41+36]);
	chord[96].set("G6 ", key[35+36], key[39+36], key[42+36]);
	chord[97].set("G#6 ", key[36+36], key[40+36], key[43+36]);
	chord[98].set("A6 ", key[37+36], key[41+36], key[44+36]);
	chord[99].set("A#6 ", key[38+36], key[42+36], key[45+36]);
	chord[100].set("B6 ", key[39+36], key[43+36], key[46+36]);
	
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
	string syntaxChord;
	string variation1Chord;
	string variation2Chord;
	string syntaxTone;
	string variation1Tone;
	string variation2Tone;
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
				fileSyntax << "M" << rChordDuration << chord[rChord].getName() << "\t";
				fileVariation1<< "M" << rChordDuration << chord[rChord + 1].getName() << "\t";
				fileVariation2 << "M" << rChordDuration << chord[rChord - 1].getName() << "\t";
			}
			else 
			{
				fileSyntax << "  \t";
			}
			if (rToneDuration <= 0)
			{
				rTone = rand() % 10 + 41;
				rToneDuration = rand() % 3 + 1;
				fileSyntax << "T" << rToneDuration << key[rTone].getName() ;
				fileVariation1 << "T" << rToneDuration << key[rTone + 1].getName();
				fileVariation2 << "T" << rToneDuration << key[rTone - 1].getName() << endl;
			} 
			else 
			{
				fileSyntax << "\t";
			}
			r.in(chord[rChord]); //Play a random Chord with a random duration
			//r.in(chord[rChord], key[rTone]); //Play a random Chord + a random Tone both with a random duration
			//r.in(key[(rand() % 88) + 1], key[(rand() % 88) + 1], key[(rand() % 88) + 1]); //Play three random keys changes every single beat.
			//r.in(key[(rand() % 88) + 1], key[(rand() % 88) + 1]);
			fileSyntax << endl;
			fileVariation1 << endl;
			fileVariation2 << endl;
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
