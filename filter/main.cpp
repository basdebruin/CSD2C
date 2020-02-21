#include <iostream>
#include <thread>
#include <cstdlib> //for rand()
#include "jack_module.h"
#include "math.h"
#include "lpf.h"

#define PI_2 6.28318530717959


int main(int argc, char ** argv) {
	// create a JackModule instance
	JackModule jack;

	// init the jack, use program name as JACK client name
	jack.init(argv[0]);
	double samplerate = jack.getSamplerate();


	float c = 22000;

	// cutoff, res, sr
	LPF lpf(c, 0.8, samplerate);


	//assign a function to the JackModule::onProces
	jack.onProcess = [&](jack_default_audio_sample_t * inBuf,
		jack_default_audio_sample_t * outBuf, jack_nframes_t nframes) {

			c-=10;
			lpf.setCutoff(c);

			for (unsigned int i = 0; i < nframes; i++) {

				// noise
				float r = (float) (std::rand() % 1000) / 500.0 - 1.0;
				// lpf naar outbuf
				float sample = lpf.rcUpdate(r);
				outBuf[i] = sample;

			}

			return 0;
	};

	jack.autoConnect();

	//keep the program running and listen for user input, q = quit
	std::cout << "\n\nPress 'q' when you want to quit the program.\n";
	bool running = true;
	while (running) {
		switch (std::cin.get()) {
			case 'q':
				running = false;
				jack.end();
				break;
		}
	}

	//end the program
	return 0;
} // main()