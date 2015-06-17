#ifndef GENERATOR_H
#define GENERATOR_H
class rawGenerator
{
private:
	static const unsigned SAMPLES = 10 * 44100; //Zetten naar de kleinste kortste noot.
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