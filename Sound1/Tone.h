#ifndef TONE_H
#define TONE_H
class Tone
{
private:
	double frequency;
	std::string name;
public:
	std::string getName();
	void set(std::string, double);
	double getFrequency();
};	

std::string Tone::getName()
{
	return name;
}

void Tone::set(std::string a, double b)
{
	name = a;
	frequency = b;
}

double Tone::getFrequency()
{
	return frequency;
}
#endif
