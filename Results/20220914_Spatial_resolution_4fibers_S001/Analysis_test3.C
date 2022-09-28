#include <iostream>
using namespace std;

class Fitf_2 {
public:
	// as used by jan (missing after-pulses and dark counts)

	double operator() (double* x, double* p) {
		//0 - N0: Normalization (~Number of events)
		//1 - mu: for generalized poisson distribution
		//2 - lambda: Borel-branching parameter for prompt crosstalk probability 1-exp(-lambda)

		//3,4 -sigma0, sigma1
		//5 - G: gain
		//6 - B: Pedestal
		double sum = 0;
		for (int kint = 0; kint <= 50; kint++) {
			double mu = p[1];
			double lambda = p[2];

			double sigma0 = p[3];
			double sigma1 = p[4];

			double G = p[5];
			double B = p[6];
			
			double mu_dk = p[7];
			double N0_dk = p[8];

			double k = static_cast<double>(kint);
			double sigmaK = sqrt(sigma0 * sigma0 + k * sigma1 * sigma1);
			//generalized poisson envelope
			double gp = (mu * TMath::Power((mu + k * lambda), k - 1) * TMath::Exp(-(mu + k * lambda))+ N0_dk* mu_dk * TMath::Power((mu_dk + k * lambda), k - 1) * TMath::Exp(-(mu_dk + k * lambda))) / TMath::Factorial(kint);

			sum += p[0] * gp * (1. / sqrt(2. * TMath::Pi()) / sigmaK) * TMath::Exp(-TMath::Power(((x[0] - (k * G + B)) / sqrt(2) / sigmaK), 2));
		}
		return sum;
	};
};

	
double* FITT(TH1F*hist,double p0, double p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8){
        Fitf_2 fitf;
	TF1* f = new TF1("fitf", fitf, -10, 1200, 9); f->SetLineColor(3); //1e4, 1.5, 0.25, 6., 6., 40, 2 

				f->SetParName(0, "N_{0}");				f->SetParameter(0, 6e5);
				f->SetParLimits(0,500000,950000);
				f->SetParName(1, "#mu");				f->SetParameter(1, p1);
				f->SetParLimits(1,2,13);	
							
				f->SetParName(2, "#lambda");				f->SetParameter(2, p2);
				f->SetParLimits(2,0.13,0.2);
				f->SetParName(3, "#sigma_{0}");			f->SetParameter(3, p3);
				f->SetParLimits(3,0,15);
				
				f->SetParName(4, "#sigma_{1}");			f->SetParameter(4, p4);
				f->SetParLimits(4,0,10);
				
				f->SetParName(5, "Gain");				f->SetParameter(5, p5); //f->FixParameter(5, 40.);
				f->SetParLimits(5,50,55);
				
				f->SetParName(6, "Pedestal");				f->SetParameter(6, p6);
				f->SetParLimits(6,-10,5);
				
				f->SetParName(7, "#mu_darkcount");				f->SetParameter(7, p7);
				f->SetParLimits(7,0.2,0.5);
				
				f->SetParName(8, "N_{0}_darkcount");				f->SetParameter(8, p8);
				f->SetParLimits(8,0.1,0.25);				
				
        hist->Fit(f,"","",150,800);
        f->Draw("SAME");
        double *results = new double[4]; 
        
        results[0] =  f->GetParameter(1);
        results[1] = f->GetParError(1) ;
        results[2] =  f->GetParameter(5);
        results[3] = f->GetParError(5) ;
        
        return results; 
        
}

void Analysis_test3() {

   // TFile *outfile  = TFile::Open("Analysis_filter/results.root","RECREATE");
    int Category;
    TTree *tree = new TTree("T","CERN 1988 staff data");
    tree->Branch("Comparison",&Category,"Category/I");
    
    
    string path = "~/software/wavecatcher-analysis-CheapCal/Results/";
    string folder;
    string dataname;
    string path_to_data;
    string channelname;
    string feature_tag;
    double *fit = new double[4]; //Save fit results
    double pos_fiber_arr[8][2] = {{0,0},{1,0},{2,1.5},{3,1.5},{4,12},{5,13.5},{6,13.5},{7,12}};	//Positions of the Fibre {channel , position}
    double pos_source;  //Position of the source
    
   
   
   
    // THIS HAS TO BE AJUSTED MANUALLY{
    double measurement_range[2] = {0,13};		//Range of measurements {fist measurement, last measurement}
    int active_channels[] = {0,1,2,3,4,5,6,7};	//List of channels you want to look at
    //}
    double fp[9] = {10000,5.5,.7,8,3.4,58.,-10,0.3,0.1};

    double results_arr[int(measurement_range[1]+1 - measurement_range[0])][int(sizeof(active_channels)/sizeof(active_channels[0]))][6];	//Array to save results for later plotting  results_arr[number of measurments][number of channels][number of saved parameters]
    
    auto legend_h_ch = new TLegend(0.5,0.6,0.9,0.9); 
    TCanvas *c2 = new TCanvas("Charge Spectra Ch2","c2",10,10,2000,800);
    
    c2->Divide(4,2);	//4X2 subplots to show 8 channels
    
    for(int k= measurement_range[0]; k <= measurement_range[1]; k++){		//loop over all selected measurements
	for ( int which_ch= 0; which_ch < sizeof(active_channels)/sizeof(active_channels[0]); which_ch++) { //loop over all selected channel
    
    		if(k<100){folder = "20220914_Spatial_resolution_4fibers_S001";}
        switch(k){
		case(0):{dataname = "S001M001.root";pos_source=0; break; }
    		case(1):{dataname = "S001M002.root";pos_source=1.5; break; }
    		case(2):{dataname = "S001M003.root";pos_source=12; break; }
    		case(3):{dataname = "S001M004.root";pos_source=13.5; break; }
    		case(4):{dataname = "S001M005.root";pos_source=6.75; break; }
    		case(5):{dataname = "S001M006.root";pos_source=2.5; break; }
    		case(6):{dataname = "S001M007.root";pos_source=3.5; break; }
    		case(7):{dataname = "S001M008.root";pos_source=4.5; break; }
    		case(8):{dataname = "S001M009.root";pos_source=11; break; }
    		case(9):{dataname = "S001M010.root";pos_source=10; break; }
    		case(10):{dataname = "S001M011.root";pos_source=9; break; }
    		case(11):{dataname = "S001M012.root";pos_source=12.75; break; }
    		case(12):{dataname = "S001M013.root";pos_source=14; break; }
    		case(13):{dataname = "S001M014.root";pos_source=-0.5; break; }

    	

		}
	feature_tag = "Measurement"+to_string(k); //substitute for actual useful measurement describtion
	path_to_data =path + folder + "/" + dataname ;	
    
    	if (sqrt(pow(pos_fiber_arr[active_channels[which_ch]][1] - pos_source,2.0)) <= 2){fp[0]= 600000; fp[1] = 8; fp[2] = 0.2; fp[3] = 1; fp[4] = 3.4; fp[5] = 58.; fp[6] = -10;fp[7] = 0.3; fp[8] = 0.1;}
    	else{fp[0]= 600000; fp[1] = 2.5; fp[2] = 0.2; fp[3] = 1; fp[4] = 3.4; fp[5] = 58.; fp[6] = -10;fp[7] = 0.3; fp[8] = 0.1;}

 
    	//manipulation of cannel name string
    	if(which_ch<10) channelname = "ChargeSpectrum channel_0" + to_string(active_channels[which_ch]);
    	else channelname = "ChargeSpectrum channel_" + to_string(active_channels[which_ch]);
    
    
    	TH1F *h_ch = new TH1F("h_ch", "0.0cm", 1000, 0,1500);
    	TFile *f3 = TFile::Open(path_to_data.c_str()); //call data from path_to_data
    	h_ch = (TH1F*)f3->Get(channelname.c_str()); //call channel from this data

	
    	h_ch->SetLineColor(k+1); // we need +1 here, because color 0 is white, white is not usefull for plotting ;) 
	
    	//Set histogramm axis range
    	h_ch->GetXaxis()->SetRangeUser(0, 999);
    	h_ch->GetYaxis()->SetRangeUser(0, 4000);

   	c2->cd(active_channels[which_ch]+1);	//choose subplot according to channel (+1 because subplots start with 1 not with 0)
    	h_ch->Draw("SAME");	//draw histogram 
	fit=FITT(h_ch,fp[0],fp[1],fp[2],fp[3],fp[4],fp[5],fp[6],fp[7],fp[8]);
    	
    	//fit=FITT(h_ch,10000,5.5,.7,6,3.4,58.,-10); //Fit and startparameter (histogram, N_0, mu, lambda, sigma_0, sigma_1, gain, pedestal)
    
    	if(which_ch==0){	//condition to plot legend only once     
    		legend_h_ch->AddEntry(h_ch,feature_tag.c_str(),"l");
    		}
      	legend_h_ch->Draw("SAME");
   
  
    	//Saving all fit results
    	results_arr[k][which_ch][0] = sqrt(pow(pos_fiber_arr[active_channels[which_ch]][1] - pos_source,2.0)); //distance between fibre and source
    	results_arr[k][which_ch][1] = 0;	//error (source-fibre distance)
    	results_arr[k][which_ch][2] = fit[0];	//mu
    	results_arr[k][which_ch][3] = fit[1];	//error (mu)
    	results_arr[k][which_ch][4] = fit[2];	//gain
    	results_arr[k][which_ch][5] = fit[3];	//error (gain)
    	//cout << results_arr[k][which_ch][2] << "and" << which_ch <<"\n";
    	cout<<"------------------------------------------------------------------------------------------------"<<endl;
    	cout<<"Ch: "<< which_ch<<"  --   measure: "<<k<<" -- cm: "<<results_arr[k][which_ch][0]<<endl;
    	cout<<"------------------------------------------------------------------------------------------------"<<endl;    
 	}  	
    }
    
    /*for(int k= measurement_range[0]; k <= measurement_range[1]; k++){		//loop over all selected measurements
	for (int which_ch= 0; which_ch < sizeof(active_channels)/sizeof(active_channels[0]); which_ch++) {
	cout << results_arr[k][which_ch][2] << "and" << which_ch <<"\n";
	}}*/

   //new plot for mu and gain
   auto *c = new TCanvas();
   c->SetWindowSize(1500, 800);
   auto legend_mu = new TLegend(0.5,0.6,0.9,0.9);
   auto legend_gain = new TLegend(0.5,0.6,0.9,0.9);
   c->Divide(4,2);
   auto mg = new TMultiGraph();
   auto mg2 = new TMultiGraph();
   
   string tag[8] = {"alpha","alpha","beta","beta","gamma","delta","delta","gamma"};
    for (unsigned int which_ch= 0; which_ch < sizeof(active_channels)/sizeof(active_channels[0]); which_ch++) {	//loop over selected channels
    auto *g1 = new TGraphErrors();
    for(int k= measurement_range[0]; k <= measurement_range[1]; k++){	//loop over selected measurements 
     	feature_tag = "Measurement"+to_string(k); //substitute for actual useful measurement describtion
     
   	 //Subplot for mu 	//this Line is not needed here but good to illustrate the structure
   	
   	g1->SetPoint(k,results_arr[k][which_ch][0],results_arr[k][which_ch][2]);	//creating a point_0 at (distance fibre-source, mu)
   	g1->SetPointError(k,results_arr[k][which_ch][1],results_arr[k][which_ch][3]);// creating errorbars for point_0 (error(source-fibre sistance), errir(mu))
   	}
   	//setting marker style
   	string ch = "Channel "+ to_string(which_ch) + ": " + tag[which_ch] +  " - ";
   	if(which_ch % 2 == 0) ch+= "left/new side";
   	if(which_ch % 2 == 1) ch+="right/old side ";
   	g1->SetTitle(ch.c_str());
   	g1->GetXaxis()->SetTitle("Distance fiber [cm]");
   	g1->GetYaxis()->SetTitle("Npe");
   	g1->GetYaxis()->SetRangeUser(1.5,12);
   	g1->SetMarkerSize(1.);
   	g1->SetMarkerStyle(20);
   	g1->SetMarkerColor(kBlack);
   	c->cd(which_ch+1);
   	    c->cd(which_ch+1)->SetLeftMargin(0.1);
   	g1->Draw(" AP");

   } 
   c->SaveAs("Npe.png");
   
    auto *c1 = new TCanvas();
    c1->SetWindowSize(1500, 800);
    c1->Divide(4,2);
    for (unsigned int which_ch = 0; which_ch < sizeof(active_channels)/sizeof(active_channels[0]); which_ch++) {	//loop over selected channels
    auto *g2 = new TGraphErrors();
    for(int k= measurement_range[0]; k <= measurement_range[1]; k++){	//loop over selected measurements 
     	feature_tag = "Measurement"+to_string(k); //substitute for actual useful measurement describtion
     
   	 //Subplot for mu 	//this Line is not needed here but good to illustrate the structure
   	
   	g2->SetPoint(k,results_arr[k][which_ch][0],results_arr[k][which_ch][4]);
   	g2->SetPointError(k,results_arr[k][which_ch][1],results_arr[k][which_ch][5]);// creating errorbars for point_0 (error(source-fibre sistance), errir(mu))
   	}
   	//setting marker style
   	string ch = "Channel "+ to_string(which_ch) + ": " + tag[which_ch] +  " - ";
   	if(which_ch % 2 == 0) ch+= "left/new side";
   	if(which_ch % 2 == 1) ch+="right/old side ";
   	g2->SetTitle(ch.c_str());
   	g2->GetXaxis()->SetTitle("Distance fiber [cm]");
   	g2->GetYaxis()->SetTitle("Gain [mv x ns]");
   	//g1->GetYaxis()->SetUserRange(40,60);
   	g2->SetMarkerSize(1.);
   	g2->SetMarkerStyle(25);
   	g2->SetMarkerColor(kBlack);
   	c1->cd(which_ch+1);
   	c1->cd(which_ch+1)->SetLeftMargin(0.1);
   	g2->Draw(" AP");

   } 
   
   c1->SaveAs("Gain.png");
}




