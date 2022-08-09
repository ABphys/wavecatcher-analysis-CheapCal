
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

	
	bool isDC = false;
	
	vector<int> Chs;
	vector<double> thresholds = {0,0,0,0};
	vector<double> thresholds_ampl = {0,0,0,0};
	vector<bool> highlow = {false,false,false,false};

	string path = "/home/marte/software/wavecatcher-analysis-CheapCal/Data/";
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
	break;
	}
	case(1):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_one_Fibre_with_source";
	break;
	}
	case(2):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_Ch0_Ch1_Th_5mV_without_source_more_delay";
	break;
	}
	case(3):{
	folder = "20220602_Source";
	dataname = "55V_Coincidence_Ch0_Ch1_Th_5mV_less_delay";
	break;
	}
	case(4):{
	folder = "20220602_Source";
	dataname = "55V_Darkcount"; //At 40 degrees
	break;
	}
	case(5):{
	folder = "20220602_Source";
	dataname = "55V_Lasertriggered"; //at normal temperature 
	break;
	}
	case(6):{
	folder = "20220601_Darkcount";
	dataname = "Darkcount_Ch0_Ch2155V"; //at normal temperature 
	break;
	}
	case(7):{
	folder = "20220602_Source";
	dataname = "Darkcount_Ch0_Ch2155V_2"; //at normal temperature 
	break;
	}
	
	
	
	case(8):{
	folder = "20220608_Distante_channels";
	dataname = "Darkcount_lowT_55V"; //at normal temperature 
	break;
	}
	case(9):{
	folder = "20220608_Distante_channels";
	dataname = "Darkcount_highT_55V"; //at high temperature 
	break;
	}
	case(10):{
	folder = "20220608_Distante_channels";
	dataname = "Darkcount_lowT_55V"; //at normal temperature 
	break;
	}
	case(11):{
	folder = "20220608_Distante_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available"; //at high temperature 
	break;
	}
	case(12):{
	folder = "20220608_Distante_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available_source"; //at normal temperature 
	break;
	}
	case(13):{
	folder = "20220608_Distante_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available_source_2"; //at high temperature 
	break;
	}
	
	
	
	case(14):{
	folder = "20220609_Distante_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available"; //at high temperature 
	break;
	}
	case(15):{
	folder = "20220609_Distante_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available_source"; //at normal temperature 
	break;
	}
	case(16):{
	folder = "20220609_Distante_channels";
	dataname = "55V_Darkcount_low_T"; //at normal temperature 
	break;
	}
	case(17):{
	folder = "20220609_Distante_channels";
	dataname = "55V_Darkcount_high_T"; //at normal temperature 
	break;
	}
	
	
	
	case(18):{
	folder = "20220610_Distance_channels";
	dataname = "Darkcounts_55V_Ch0-1-2-4"; //at normal temperature 
	isDC = true;
	break;
	}
	case(19):{
	folder = "20220610_Distance_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available_timed"; //same time 
	break;
	}
	case(20):{
	folder = "20220610_Distance_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available";  
	break;
	}
	case(21):{
	folder = "20220610_Distance_channels";
	dataname = "2fibers_Ch0_Ch2_also_Ch1_Ch4_available_source"; 
	break;
	}
	case(22):{
	folder = "20220610_Distance_channels";
	dataname = "1fiber_also_Ch1_Ch4_available_source"; // check the cross 
	break;
	}
	
	case(23):{
	folder = "20220614_Wrapped";
	dataname = "55V_Darkcount"; //at high temperature 
	isDC = true;
	break;
	}
	case(24):{
	folder = "20220614_Wrapped";
	dataname = "Coincidence_Ch2_Ch3";
	break;
	}
	case(25):{
	folder = "20220614_Wrapped";
	dataname = "Coincidence_Ch2_Ch3_source";  
	break;
	}
	case(26):{
	folder = "20220614_Wrapped";
	dataname = "Trigger_Ch2_source"; 
	break;
	}
	case(27):{
	folder = "20220614_Wrapped";
	dataname = "Trigger_Ch3_source"; // check the cross 
	Chs = {0,1,2,4};
	break;
	}
	
	
	//old trigger position 200-250 for the maximum searching -- 0 delay 
	
	//new trigger position 110-140 for the maximum searching -- 5 delay 
	
	
	case(28):{
	folder = "20220616_Triggerbox";
	dataname = "Triggerbox_Ch0_30mV-Ch2-Ch3_fiber_source"; 
	Chs = {0,2,3};
	break;
	}
	
	
	case(29):{
	folder = "20220617_Triggerbox_different_threshold";
	dataname = "Ch14_Ch26_TB_Ch2_fiber_5mV-readout_Ch3_fiber"; 
	Chs = {2,3};
	break;
	}
	
	// After adding reflective foil
	
	case(30):{
	folder = "20220620_Triggerbox_and_Fibre";
	dataname = "Trigger_Ch2_Ch14_Ch26_Readout_Ch3_again"; 
	Chs = {2,3,14,26};
	break;
	}
	
	
	
	
	
	case(31):{
	folder = "20220624_Spatial_resolution_2_Trigger/Hot";
	dataname = "Trigger_20mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3"; // P1 -- 20mV
	Chs = {2,3,14,26};
	break;
	}
	
	case(32):{
	folder = "20220624_Spatial_resolution_2_Trigger/Hot";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3"; // P1 hot
	Chs = {2,3};
	break;
	}
	
	case(33):{
	folder = "20220624_Spatial_resolution_2_Trigger/Hot";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_2"; // P2 hot
	Chs = {2,3};
	break;
	}
	
	case(34):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_3"; // P3 hot
	Chs = {2,3};
	break;
	}
	
	case(35):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_0"; // P0 
	Chs = {2,3};
	break;
	}
	
	case(36):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_4"; // P4
	Chs = {2,3};
	break;
	}
	case(37):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_5"; // P5
	Chs = {2,3,14,26};
	break;
	}
	
	case(38):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_1"; // P1 coldish 31deg 
	Chs = {2,3};
	break;
	}
	case(39):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_2"; // P2 cold 
	Chs = {2,3};
	break;
	}
	case(40):{
	folder = "20220624_Spatial_resolution_2_Trigger";
	dataname = "Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_3"; // P3 cold 
	Chs = {2,3};
	break;
	}
	
	case(41):{
	folder = "20220706_Darkcount_newT";
	dataname = "Darkcount_27C_28C"; // after using the fan 
	Chs = {2,3};
	isDC=true;
	break;
	}
	
	
	case(42):{
	folder = "20220714_Test_30mV";
	dataname = "Triggerbox_Ch0_30mV-Ch2-Ch3_fiber_source"; // test TB UP 30mV
	Chs = {2,3,14,26};
	break;
	}
	
	case(43):{
	folder = "20220714_Test_30mV";
	dataname = "Triggerbox_Ch0_30mV-Ch2-Ch3_fiber_source_dark"; // test TB UP 30mV
	Chs = {2,3,14,26};
	break;
	}
	
	// Again all the position since there was light 
	
	case(44):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_0"; // P0 
	Chs = {2,3,14,26};
	break;
	}
	
	case(45):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4"; // P4
	Chs = {2,3,14,26};
	break;
	}
	case(46):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_1"; // P1
	Chs = {2,3,14,26};
	break;
	}
	
	case(47):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_1_5_again"; // P1.5 
	Chs = {2,3};
	break;
	}
	case(48):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_2"; // P2  
	Chs = {2,3};
	break;
	}
	case(49):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_3"; // P3  
	Chs = {2,3};
	break;
	}
	case(50):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_5"; // P4  
	Chs = {2,3};
	break;
	}
	case(51):{
	folder = "20220718__Spatial_resolution";
	dataname = "Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_5"; // P5
	Chs = {2,3};
	break;
	}
	
	
	
	
	
	
	
	
    }
	// the splitting in the path has a reason. It is needed to later save and name the data in a usefull place
	path_to_folder = path + folder + "/";	
	path_to_data =path_to_folder + dataname +"/" ;
	
	// initialize class
	ReadRun mymeas(0);

	// read data
	// Alessia saving root file
	mymeas.ReadFile(path_to_data, true, 0,"/home/marte/software/wavecatcher-analysis-CheapCal/Results/" +folder + "/" + dataname+ ".root");  
	// Ben saving root file 
       //mymeas.ReadFile(path_to_data, true, 0, path_to_data+ "/results.root"); // saves root output in the datafolder as results.root 
	
	// only plot certain channels
	mymeas.plot_active_channels = Chs;

	//apply baseline correction to ALL waveforms <- NEEDED but slow when not compiled
	int which_blc = 1;
	//if (!isDC) which_blc = 2;
	if (which_blc == 0) {
		mymeas.SmoothAll(5);
		mymeas.CorrectBaseline(95., 105.);	
	}
	else if (which_blc == 1) {
		mymeas.CorrectBaselineMinSlopeRMS(50, false, 5, 300, 10, false);
	}
	else {
		mymeas.CorrectBaselineMin(50, false, 1., 300, 0, false);
	}

	// check how many events are above a certain threshold
	mymeas.FractionEventsAboveThreshold(2, true, true, 100, 150);

	////plotting

	// plot sums of all events per channel
	//mymeas.PlotChannelSums(true, false, true, intwindowminus, intwindowplus, findmaxfrom, findmaxto);
	mymeas.PlotChannelSums(true);
	// investigate charge spectrum. should see photo electron peaks here
	float intwindowminus = 20.;	// lower integration window in ns rel. to max
	float intwindowplus = 65.;	// upper integration window in ns rel. to max
	float findmaxfrom = 100.;	// assume signal from laser arrives between here ...
	float findmaxto = 160.;	// ... and here (depends on trigger delay setting)

	if (isDC) {
		findmaxfrom = 20 + intwindowminus;
		findmaxto = 280. - intwindowplus;
	}

        //Filter function 
//       mymeas.SkipEventsPerChannel(thresholds_ampl, true); //per amplitude
	//mymeas.IntegralFilter(thresholds,highlow, 95, 205,true); //per charge 
	
	
	
	// plot all channels
	if (isDC) {
		mymeas.PrintChargeSpectrum_pars = { 1e5, 0.3, 0.2, 6., 6., 40., 0 };
		mymeas.PrintChargeSpectrum(path_to_folder, dataname, intwindowminus, intwindowplus, findmaxfrom, findmaxto, -20, 150, 200, 5, 150, 99, -1);
		mymeas.PrintAmplitudeSpectrum(path_to_folder, dataname, 0, 0, findmaxfrom, findmaxto, 0, 20, 200);  //to have the mV in the graph you need to set intwindowminus = intwindowminus 
	}
	else {
		mymeas.PrintChargeSpectrum_pars = { 1e4, 1.5, 0.25, 6., 6., 40, 2 };
		mymeas.PrintChargeSpectrum(path_to_folder, dataname+ "", intwindowminus, intwindowplus, findmaxfrom, findmaxto, -30, 1200, 200,30,900,2,0);
		//mymeas.PrintChargeSpectrum(path_to_folder, dataname, 0, 0, findmaxfrom, findmaxto, 0, 100, 1000);
	}
	// setting a threshold of 999 enables that the threshold is calculated with the gain/2 + pedestial from the fit
	
	
	if(isDC){
		mymeas.PrintChargeSpectrumPMTthreshold(path_to_folder, dataname,intwindowminus, intwindowplus, findmaxfrom, findmaxto, -20, 150, 200, 999);
		mymeas.PrintChargeSpectrumPMTthreshold(path_to_folder, dataname+"_1.5pe",intwindowminus, intwindowplus, findmaxfrom, findmaxto, -20, 150, 200, mymeas.fit_results[0]->Parameter(6) + 1.5 * mymeas.fit_results[0]->Parameter(5));
		
		
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
	
	
	// This is to plot waveforms of individual chosen events:
	/*vector<int> events_plot = {99002,54495,43524,59091,43421,43188};

	for (int i = 0; i < events_plot.size(); i++) {
    	mymeas.PrintChargeSpectrumWF(intwindowminus, intwindowplus, findmaxfrom, findmaxto, events_plot[i], ymin, ymax);
	}*/
	
}
