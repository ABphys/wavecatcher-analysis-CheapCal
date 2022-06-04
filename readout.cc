
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <TCanvas.h>

using namespace std;

void readout(int which) // main
{
	//int which = 0; 
	// better create separate file just for DC measurements

	
	bool isDC = true;
	double thres=0;
//	bool isnew;

	string path = "/home/marte/software/wavecatcher-analysis-main/Data/";
	string folder;
	string dataname;
	string path_to_folder;
	string path_to_data;
	fstream my_file;
	
	
	
	//If this file did not exist until now, this lines will create a file named (name of the folder)_results.txt to print the results in it.
	my_file.open(path +"/" + folder +"/" + folder +"_results.txt", ios::app); //::app will append to file ::out will override file
	if (!my_file) {
		my_file << "Name" << " " << "First Channel in kHz"<< " " << "Second Channel in kHz" << " " << "Gain first Channel in kHz" << " " << "Gain second Channel in kHz" <<"\n";
	}
	my_file.close();
	
   switch(which){
	
	case(0):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_one_Fibre_software_triggered";
	thres = -3;
	break;
	}
	case(1):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_one_Fibre_with_source";
	thres = -3;
	break;
	}
	case(2):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_Ch0_Ch1_Th_5mV_without_source_more_delay";
	thres = -3;
	break;
	}
	case(3):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_Ch0_Ch1_Th_5mV_less_delay";
	thres = -3;
	break;
	}
	case(4):{
	folder = "20220602_Source";
	dataname = "55V_Darkcount"; //At 40 degrees
	thres = -3;
	break;
	}
	case(5):{
	folder = "20220602_Source";
	dataname = "Darkcount_Ch0_Ch2155V_2"; //at normal temperature 
	thres = -3;
	break;
	}

    }
	// the splitting in the path has a reason. It is needed to later save and name the data in a usefull place
	path_to_folder = path + folder + "/";	
	path_to_data =path_to_folder + dataname +"/" ;
	//isDC = true;
	
	
	
	
	// initialize class
	ReadRun mymeas(0);

	// read data
	mymeas.ReadFile(path_to_data, true, 0, "/home/marte/software/wavecatcher-analysis-main/Results/" +folder + "/" + dataname+ ".root"); // saves root output in the datafolder as results.root

	// only plot certain channels
	mymeas.plot_active_channels = {0,1};

	//apply baseline correction to ALL waveforms <- NEEDED but slow when not compiled
	int which_blc = 1;
	if (!isDC) which_blc = 2;
	if (which_blc == 0) {
		mymeas.SmoothAll(5);
		mymeas.CorrectBaseline(95., 105.);	//
	}
	else if (which_blc == 1) {
		mymeas.CorrectBaselineMinSlopeRMS(100, false, 5, 900, 500, false);
	}
	else {
		mymeas.CorrectBaselineMin(80, false, 1., 250, 10, false);
	}

	// check how many events are above a certain threshold
	mymeas.FractionEventsAboveThreshold(2, true, true, 100, 150);

	////plotting

	// plot sums of all events per channel
	mymeas.PlotChannelSums(true);

	// investigate charge spectrum. should see photo electron peaks here
	float intwindowminus = 10.;	// lower integration window in ns rel. to max
	float intwindowplus = 30.;	// upper integration window in ns rel. to max
	float findmaxfrom = 200.;	// assume signal from laser arrives between here ...
	float findmaxto = 250.;	// ... and here (depends on trigger delay setting)

	if (isDC) {
		findmaxfrom = 20 + intwindowminus;
		findmaxto = 280. - intwindowplus;
	}

	// plot all channels
	if (isDC) {
		//mymeas.PrintChargeSpectrum_pars = { 2e5, 0.6, 0.1, 3.5, 6, 30, -30, 1., 1 };
		mymeas.PrintChargeSpectrum_pars = { 1e5, 0.3, 0.2, 6., 6., 40., 0 };
		mymeas.PrintChargeSpectrum(path_to_folder, dataname, intwindowminus, intwindowplus, findmaxfrom, findmaxto, -20, 150, 200, 5, 150, 99, -1);
		mymeas.PrintAmplitudeSpectrum(path_to_folder, dataname, 0, 0, findmaxfrom, findmaxto, 0, 20, 200);  //to have the mV in the graph you need to set intwindowminus = intwindowminus 
	}
	else {
		mymeas.PrintChargeSpectrum_pars = { 1e4, 1.5, 0.25, 6., 6., 40, 2 };
		mymeas.PrintChargeSpectrum(path_to_folder, dataname, intwindowminus, intwindowplus, findmaxfrom, findmaxto, -30, 350, 200);
		mymeas.PrintAmplitudeSpectrum(path_to_folder, dataname, intwindowminus, intwindowplus, findmaxfrom, findmaxto, 0, 20, 200);
	}
	// setting a threshold of 999 enables that the threshold is calculated with the gain/2 + pedestial from the fit
	mymeas.PrintChargeSpectrumPMTthreshold(path_to_folder, dataname, intwindowminus, intwindowplus, findmaxfrom, findmaxto, -20, 150, 200, mymeas.fit_results[0]->Parameter(6) + mymeas.fit_results[0]->Parameter(5)/2.);
	mymeas.PrintChargeSpectrumPMTthreshold(0, 0, findmaxfrom, findmaxto, 0, 15, 200, 5);
	
	//fstream my_file;
	my_file.open(path +"/" + folder +"/" + folder +"_results.txt", ios::app); //::app will append to file ::out will override file
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		cout << "File created successfully!";
		my_file << dataname << " " << mymeas.darkcount_results[0]<< " " << mymeas.darkcount_results[1] << " "<< mymeas.fit_results[0]->Parameter(5)<< " " << mymeas.fit_results[1]->Parameter(5) <<  "\n"; //Add to file: Name of measurement, Darkcount first channel, Darkcount second channel
		my_file.close();
	}
	
	// plot waveforms of individual events
	//plot range
	double ymin = -5;
	double ymax = 25;
	// plot waveforms for certain events with integration window
	gROOT->SetBatch(kTRUE); // only write to root file
	for (int i = 1; i < mymeas.nevents; i += static_cast<int>(mymeas.nevents / 50)) {
		mymeas.PrintChargeSpectrumWF(intwindowminus, intwindowplus, findmaxfrom, findmaxto, i, ymin, ymax);
	}
	gROOT->SetBatch(kFALSE);
	
}
