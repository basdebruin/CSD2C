#include <iostream>
#include <thread>
#include <cstdlib> //for rand()
#include "Jack/jack_module.h"
#include "math.h"
#include "filter/lpf.h"
#include "OSC/osc.h"

#define PI_2 6.28318530717959

float x;
float y;

class localOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  string msgpath=path;
// recieves the message with path and prints it
    cout << "path: " << msgpath << endl;
    if(!msgpath.compare("/x")){
      x = argv[0]->f;
    }
    if(!msgpath.compare("/y")){
        y = argv[0]->f;
    }

    return 0;
  } // realcallback()
};


int main(int argc, char ** argv) {
	// create a JackModule instance
	JackModule jack;

	// init the jack, use program name as JACK client name
	jack.init(argv[0]);
	double samplerate = jack.getSamplerate();
	localOSC osc;
	string serverport="7777";

  osc.init(serverport);
 	osc.set_callback("/x","f");
  osc.set_callback("/y","f");

	osc.start();
	cout << "Listening on port " << serverport << endl;


	float c = 800;

	// cutoff, res, sr
	LPF lpf(c, 0.0, samplerate);


	//assign a function to the JackModule::onProces
	jack.onProcess = [&](jack_default_audio_sample_t * inBuf,
		jack_default_audio_sample_t * outBuf, jack_nframes_t nframes) {

			for (unsigned int i = 0; i < nframes; i++) {
        float oscCut;
				// noise
				// float r = (float) (std::rand() % 1000) / 500.0 - 1.0;
				// lpf naar outbuf
				float sample = lpf.update(inBuf[i]);
				outBuf[i] = sample * y;
        oscCut = x *20000;
        lpf.setCutoff(oscCut);
			}

			return 0;
	};

	jack.autoConnect();

	//keep the program running and listen for user input, q = quit
	std::cout << "\n\nPress 'q' when you want to quit the program.\n";
	std::cout << "Use A-J to change cutoff freq" << std::endl;
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
