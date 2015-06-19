#ifndef GENERATOR_H
#define GENERATOR_H
class rawGenerator
{
private:
	static const unsigned SAMPLES = 11 * 44100; //Zetten naar de kleinste kortste noot.
	static const unsigned SAMPLE_RATE = 44100;
	static const unsigned AMPLITUDE = 4000;
	static const unsigned BEAT_LENGTH = 0.25 * 44100;
	const double TWO_PI = 6.28318;
	sf::Int16 waveOut[SAMPLES];
public:
	sf::SoundBuffer Buffer;
	sf::Sound Sound;

	void setBeats(int length);
	unsigned int pointer = 0;
	unsigned int amountOfBeats = 0;
	void in(Tone, Tone, Tone);
	void in(Tone, Tone);
	void in(Tone);
	void in(Chord, Tone);
	void in(Chord);
	void in2(Chord);
	void playStream();
};

void rawGenerator::setBeats(int a)
{
	switch (a)
	{
	case 0:
		amountOfBeats = 0;
		break;
	case 1:
		amountOfBeats = 1;
		break;
	case 2:
		amountOfBeats = 2;
		break;
	case 3:
		amountOfBeats = 4;
		break;
	case 4:
		amountOfBeats = 8;
		break;
	}
};
void rawGenerator::playStream()
{

	if (!Buffer.loadFromSamples(waveOut, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
		//return 1;
	}
	std::cout << "Sound 1" << std::endl;
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
	const double increment1 = a.getFrequency() / SAMPLE_RATE;
	const double increment2 = b.getFrequency() / SAMPLE_RATE;

	cout << "Creating a mix of: " << a.getName() << " + " << b.getName() << endl;

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

	cout << "Creating a mix of: " << a.getName() << endl;

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

void rawGenerator::in2(Chord a)
{
	double x = 0, y = 0, z = 0, w = 0;

	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);
	const double increment4 = (a.tone4.getFrequency() / SAMPLE_RATE);
	cout << "Creating a mix of: " << a.name << endl;

	for (unsigned i = pointer; i < (pointer +( BEAT_LENGTH * amountOfBeats)); i++)
	{
		waveOut[i] = (sin(x * TWO_PI) + sin(y * TWO_PI) + sin(z * TWO_PI) + sin(w * TWO_PI))* AMPLITUDE;
		x += increment1;
		y += increment2;
		z += increment3;
		w += increment4;
	}
	pointer += BEAT_LENGTH * amountOfBeats;
}

void rawGenerator::in(Chord a, Tone b)
{
	double x = 0, y = 0, z = 0, w = 0, v = 0;
	const double increment1 = (a.tone1.getFrequency() / SAMPLE_RATE);
	const double increment2 = (a.tone2.getFrequency() / SAMPLE_RATE);
	const double increment3 = (a.tone3.getFrequency() / SAMPLE_RATE);
	const double increment4 = (a.tone4.getFrequency() / SAMPLE_RATE);
	const double increment5 = (b.getFrequency() / SAMPLE_RATE);

	cout << "Creating a mix of: " << a.getName() << " + " << b.getName() << endl;


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
#endif