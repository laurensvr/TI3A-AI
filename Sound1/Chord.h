#ifndef CHORD_H
#define CHORD_H
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
#endif