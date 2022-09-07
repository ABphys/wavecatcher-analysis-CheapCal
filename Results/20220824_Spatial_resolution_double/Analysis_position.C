
class Fitf {
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

				double k = static_cast<double>(kint);
				double sigmaK = sqrt(sigma0 * sigma0 + k * sigma1 * sigma1);
				//generalized poisson envelope
				double gp = mu * TMath::Power((mu + k * lambda), k - 1) * TMath::Exp(-(mu + k * lambda)) / TMath::Factorial(kint);

				sum += p[0] * gp * (1. / sqrt(2. * TMath::Pi()) / sigmaK) * TMath::Exp(-TMath::Power(((x[0] - (k * G + B)) / sqrt(2) / sigmaK), 2));
			}
			return sum;
		};
	};
	
double* FITT(TH1F*hist,double p0, double p1, double p2, double p3, double p4, double p5, double p6){
        Fitf fitf;
	TF1* f = new TF1("fitf", fitf, -10, 1200, 7); f->SetLineColor(3); //1e4, 1.5, 0.25, 6., 6., 40, 2 

				f->SetParName(0, "N_{0}");			//	f->SetParameter(0, 1e6);
				f->SetParName(1, "#mu");				f->SetParameter(1, p1);
				f->SetParName(2, "#lambda");				f->SetParameter(2, p2);
				f->SetParName(3, "#sigma_{0}");			f->SetParameter(3, p3);
				f->SetParName(4, "#sigma_{1}");			f->SetParameter(4, p4);
				f->SetParName(5, "Gain");				f->SetParameter(5, p5); //f->FixParameter(5, 40.);
				f->SetParName(6, "Pedestal");				f->SetParameter(6, p6);
				
				
        hist->Fit(f,"","",-10,800);
        f->Draw("SAME");
        double *results = new double[4]; 
        
        results[0] =  f->GetParameter(1);
        results[1] = f->GetParError(1) ;
        results[2] =  f->GetParameter(5);
        results[3] = f->GetParError(5) ;
        
        return results; 
        
}


void Analysis_position() {

    TFile *outfile  = TFile::Open("Analysis_filter.root","RECREATE");
    int Category;
    TTree *tree = new TTree("T","CERN 1988 staff data");
    tree->Branch("Comparison",&Category,"Category/I");
    
    TH1F *h7_ch2 = new TH1F("h7", "0.0cm", 1000, 0,1500);
    TH1F *h8_ch3 = new TH1F("h8", "1.5cm", 1000, 0,1500);
    TH1F *h7_ch4 = new TH1F("h7", "0.0cm", 1000, 0,1500);
    TH1F *h8_ch5 = new TH1F("h8", "1.5cm", 1000, 0,1500);

   
    TH1F *h9 = new TH1F("h9", "0.0cm", 1000, 0,1500);
    h9->GetXaxis()->SetTitle("mV X ns");
    h9->GetYaxis()->SetTitle("Events");
    
    TH1F *h10 = new TH1F("h10", "1.5cm", 1000, 0,1500);
    TH1F *h11_ch2 = new TH1F("h11", "0.0cm", 1000, 0,1500);
    TH1F *h12_ch3 = new TH1F("h12", "1.5cm", 1000, 0,1500);
    TH1F *h11_ch4 = new TH1F("h11", "0.0cm", 1000, 0,1500);
    TH1F *h12_ch5 = new TH1F("h12", "1.5cm", 1000, 0,1500);
    TH1F *h13_ch2 = new TH1F("h13", "0.0cm", 1000, 0,1500);
    TH1F *h14_ch3 = new TH1F("h14", "1.5cm", 1000, 0,1500);    
    TH1F *h13_ch4 = new TH1F("h13", "0.0cm", 1000, 0,1500);
    TH1F *h14_ch5 = new TH1F("h14", "1.5cm", 1000, 0,1500); 
    
    TH1F *h15_ch2 = new TH1F("h15", "0.0cm", 1000, 0,1500);
    TH1F *h16_ch3 = new TH1F("h16", "1.5cm", 1000, 0,1500);    
    TH1F *h15_ch4 = new TH1F("h15", "0.0cm", 1000, 0,1500);
    TH1F *h16_ch5 = new TH1F("h16", "1.5cm", 1000, 0,1500);  
    
    TH1F *h15_bis_ch2 = new TH1F("h15", "0.0cm", 1000, 0,1500);
    TH1F *h16_bis_ch3 = new TH1F("h16", "1.5cm", 1000, 0,1500);    
    TH1F *h15_bis_ch4 = new TH1F("h15", "0.0cm", 1000, 0,1500);
    TH1F *h16_bis_ch5 = new TH1F("h16", "1.5cm", 1000, 0,1500);       
   
    TH1F *h17_ch4 = new TH1F("h17", "0.0cm", 1000, 0,1500);
    TH1F *h18_ch5 = new TH1F("h18", "1.5cm", 1000, 0,1500);    
    TH1F *h17_ch2 = new TH1F("h17", "0.0cm", 1000, 0,1500);
    TH1F *h18_ch3 = new TH1F("h18", "1.5cm", 1000, 0,1500);  
    
    TH1F *h19_ch2 = new TH1F("h19", "0.0cm", 1000, 0,1500);
    TH1F *h20_ch3 = new TH1F("h20", "1.5cm", 1000, 0,1500);    
    TH1F *h19_ch4 = new TH1F("h19", "0.0cm", 1000, 0,1500);
    TH1F *h20_ch5 = new TH1F("h20", "1.5cm", 1000, 0,1500);  
    
    TH1F *h21_ch2 = new TH1F("h21", "0.0cm", 1000, 0,1500);
    TH1F *h22_ch3 = new TH1F("h22", "1.5cm", 1000, 0,1500);    
    TH1F *h21_ch4 = new TH1F("h21", "0.0cm", 1000, 0,1500);
    TH1F *h22_ch5 = new TH1F("h22", "1.5cm", 1000, 0,1500);  
    
    
    TH1F *h23_ch2 = new TH1F("h23", "0.0cm", 1000, 0,1500);
    TH1F *h24_ch3 = new TH1F("h24", "1.5cm", 1000, 0,1500);    
    TH1F *h23_ch4 = new TH1F("h23", "0.0cm", 1000, 0,1500);
    TH1F *h24_ch5 = new TH1F("h24", "1.5cm", 1000, 0,1500);  
    
    
    TFile *f3 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4.root");
    h7_ch2 = (TH1F*)f3->Get("ChargeSpectrum channel_02"); // 0.0cm
    h8_ch3 = (TH1F*)f3->Get("ChargeSpectrum channel_03"); // 1.5cm
    
    TFile *f4 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_switched.root");
    h7_ch4 = (TH1F*)f4->Get("ChargeSpectrum channel_04"); // 0.0cm
    h8_ch5 = (TH1F*)f4->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    TFile *f5 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_old.root");
    h9 = (TH1F*)f5->Get("ChargeSpectrum channel_02"); // 0.0cm
    h10 = (TH1F*)f5->Get("ChargeSpectrum channel_03"); // 1.5cm
    
    TFile *f6 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_switched_new_holes.root");
    h11_ch2 = (TH1F*)f6->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h12_ch3 = (TH1F*)f6->Get("ChargeSpectrum channel_03"); // 1.5cm
    h11_ch4 = (TH1F*)f6->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h12_ch5 = (TH1F*)f6->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    TFile *f7 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_switched_SiPM.root");
    h13_ch2 = (TH1F*)f7->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h14_ch3 = (TH1F*)f7->Get("ChargeSpectrum channel_03"); // 1.5cm
    h13_ch4 = (TH1F*)f7->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h14_ch5 = (TH1F*)f7->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    
    TFile *f8 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_switched_PCB.root");
    h15_ch2 = (TH1F*)f8->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h16_ch3 = (TH1F*)f8->Get("ChargeSpectrum channel_03"); // 1.5cm
    h15_ch4 = (TH1F*)f8->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h16_ch5 = (TH1F*)f8->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    TFile *f8_bis = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_switched_SiPM_2.root");
    h15_bis_ch2 = (TH1F*)f8_bis->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h16_bis_ch3 = (TH1F*)f8_bis->Get("ChargeSpectrum channel_03"); // 1.5cm
    h15_bis_ch4 = (TH1F*)f8_bis->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h16_bis_ch5 = (TH1F*)f8_bis->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    TFile *f9 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Ch4_Ch5_Pos_4_switched_PCB_4_bias_55V.root"); // switched channels 
    h17_ch2 = (TH1F*)f9->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h18_ch3 = (TH1F*)f9->Get("ChargeSpectrum channel_03"); // 1.5cm
    h17_ch4 = (TH1F*)f9->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h18_ch5 = (TH1F*)f9->Get("ChargeSpectrum channel_05"); // 1.5cm
    

     TFile *f10 = TFile::Open("~/software/wavecatcher-analysis-CheapCal/Results/20220905_Tests/Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Ch4_Ch5_Pos_4_bias_55V_switched_Readout_cables.root");
    h19_ch2 = (TH1F*)f10->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h20_ch3 = (TH1F*)f10->Get("ChargeSpectrum channel_03"); // 1.5cm
    h19_ch4 = (TH1F*)f10->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h20_ch5 = (TH1F*)f10->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    
    
    TFile *f11 = TFile::Open("~/software/wavecatcher-analysis-CheapCal/Results/20220905_Tests/Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Ch4_Ch5_Pos_4_bias_55V_switched_Readout_just_cables.root");
    h21_ch2 = (TH1F*)f11->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h22_ch3 = (TH1F*)f11->Get("ChargeSpectrum channel_03"); // 1.5cm
    h21_ch4 = (TH1F*)f11->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h22_ch5 = (TH1F*)f11->Get("ChargeSpectrum channel_05"); // 1.5cm
    
    /*

     TFile *f12 = TFile::Open("~/software/wavecatcher-analysis-CheapCal/Results/20220905_Tests/Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Ch4_Ch5_Pos_4_bias_55V_switched_Readout_cables.root");
    h23_ch2 = (TH1F*)f12->Get("ChargeSpectrum channel_02"); // 0.0cm	
    h24_ch3 = (TH1F*)f12->Get("ChargeSpectrum channel_03"); // 1.5cm
    h23_ch4 = (TH1F*)f12->Get("ChargeSpectrum channel_04"); // 0.0cm	
    h24_ch5 = (TH1F*)f12->Get("ChargeSpectrum channel_05"); // 1.5cm
    */
    
    h7_ch2->SetLineColor(kBlue); //0.0cm
    h8_ch3->SetLineColor(kBlue);  //1.5cm
    h7_ch4->SetLineColor(kBlue); //0.0cm
    h8_ch5->SetLineColor(kBlue);  //1.5cm
    h9->SetLineColor(kOrange); //0.0cm
    h10->SetLineColor(kOrange);  //1.5cm
    h11_ch2->SetLineColor(kBlue); //0.0cm
    h12_ch3->SetLineColor(kBlue); //1.5cm
    h11_ch4->SetLineColor(kBlue); //0.0cm
    h12_ch5->SetLineColor(kBlue); //1.5cm
    h13_ch2->SetLineColor(kBlack); //0.0cm
    h14_ch3->SetLineColor(kBlack); //1.5cm
    h13_ch4->SetLineColor(kBlack); //0.0cm
    h14_ch5->SetLineColor(kBlack); //1.5cm
    h15_ch2->SetLineColor(kRed); //0.0cm
    h16_ch3->SetLineColor(kRed); //1.5cm
    h15_ch4->SetLineColor(kRed); //0.0cm
    h16_ch5->SetLineColor(kRed); //1.5cm
    h15_bis_ch2->SetLineColor(kRed); //0.0cm
    h16_bis_ch3->SetLineColor(kRed); //1.5cm
    h15_bis_ch4->SetLineColor(kRed); //0.0cm
    h16_bis_ch5->SetLineColor(kRed); //1.5cm
    h17_ch4->SetLineColor(kRed); //0.0cm
    h18_ch5->SetLineColor(kRed); //1.5cm
    h17_ch2->SetLineColor(kRed); //0.0cm
    h18_ch3->SetLineColor(kRed); //1.5cm
    h19_ch2->SetLineColor(kRed); //0.0cm
    h20_ch3->SetLineColor(kRed); //1.5cm
    h19_ch4->SetLineColor(kRed); //0.0cm
    h20_ch5->SetLineColor(kRed); //1.5cm
    h21_ch2->SetLineColor(kRed); //0.0cm
    h22_ch3->SetLineColor(kRed); //1.5cm
    h21_ch4->SetLineColor(kRed); //0.0cm
    h22_ch5->SetLineColor(kRed); //1.5cm
    h23_ch2->SetLineColor(kRed); //0.0cm
    h24_ch3->SetLineColor(kRed); //1.5cm
    h23_ch4->SetLineColor(kRed); //0.0cm
    h24_ch5->SetLineColor(kRed); //1.5cm
        
    
    double *fit = new double[4];
    
    double*res_old = new double[2];
    double*res_switched = new double[2];
    double*res_nochange = new double[2];
    double*res_switched_sipm = new double[2];
    double*res_switched_PCB = new double[2];
    double*res_switched_PCB_bis = new double[2];
    
    
    double*err_old = new double[2];
    double*err_switched = new double[2];
    double*err_nochange = new double[2];
    double*err_switched_sipm = new double[2];
    double*err_switched_PCB = new double[2];
    double*err_switched_PCB_bis = new double[2];
    
    double*res_switched_new = new double[2];
    double*res_nochange_new = new double[2];
    double*res_switched_sipm_new = new double[2];
    double*res_switched_PCB_new = new double[2];
     double*res_switched_PCB_new_bis = new double[2];
    
    double*err_switched_new = new double[2];
    double*err_nochange_new = new double[2];
    double*err_switched_sipm_new = new double[2];
    double*err_switched_PCB_new = new double[2];
    double*err_switched_PCB_new_bis = new double[2];
    
    double*gain_old = new double[2];
    double*gain_switched = new double[2];
    double*gain_nochange = new double[2];
    double*gain_switched_sipm = new double[2];
    double*gain_switched_PCB = new double[2];
    double*gain_switched_PCB_bis = new double[2];
    
    double*err_gain_old = new double[2];
    double*err_gain_switched = new double[2];
    double*err_gain_nochange = new double[2];
    double*err_gain_switched_sipm = new double[2];
    double*err_gain_switched_PCB = new double[2];
    double*err_gain_switched_PCB_bis = new double[2];
    
    
    
    double*gain_switched_new = new double[2];
    double*gain_nochange_new = new double[2];
    double*gain_switched_sipm_new = new double[2];
    double*gain_switched_PCB_new = new double[2];
    double*gain_switched_PCB_new_bis = new double[2];
        
    double*err_gain_switched_new = new double[2];
    double*err_gain_nochange_new = new double[2];
    double*err_gain_switched_sipm_new = new double[2];
    double*err_gain_switched_PCB_new = new double[2];
    double*err_gain_switched_PCB_new_bis = new double[2];
    
    
    double*res_switched_channel = new double[2];
    double*err_switched_channel = new double[2];
    double*res_switched_channel_new = new double[2];
    double*err_switched_channel_new = new double[2];
    double*gain_switched_channel = new double[2];
    double*err_gain_switched_channel = new double[2];
    double*gain_switched_channel_new = new double[2];
    double*err_gain_switched_channel_new = new double[2];
    
    double*res_switched_cable = new double[2];
    double*err_switched_cable = new double[2];
    double*res_switched_cable_new = new double[2];
    double*err_switched_cable_new = new double[2];
    double*gain_switched_cable = new double[2];
    double*err_gain_switched_cable = new double[2];
    double*gain_switched_cable_new = new double[2];
    double*err_gain_switched_cable_new = new double[2];
        
    double*res_switched_just_cable = new double[2];
    double*err_switched_just_cable = new double[2];
    double*res_switched_just_cable_new = new double[2];
    double*err_switched_just_cable_new = new double[2];
    double*gain_switched_just_cable = new double[2];
    double*err_gain_switched_just_cable = new double[2];
    double*gain_switched_just_cable_new = new double[2];
    double*err_gain_switched_just_cable_new = new double[2];
        
    double*res_switched_side = new double[2];
    double*err_switched_side = new double[2];
    double*res_switched_side_new = new double[2];
    double*err_switched_side_new = new double[2];
    double*gain_switched_side = new double[2];
    double*err_gain_switched_side = new double[2];
    double*gain_switched_side_new = new double[2];
    double*err_gain_switched_side_new = new double[2];    
            
    double cm[2]={0,1.5};
    
    
    TCanvas *c1 = new TCanvas("Charge Spectra Ch2","c1",10,10,2000,800);
    
    c1->Divide(2,2);
    
    c1->cd(1);
    
    h13_ch2->Draw();
    h11_ch2->Draw("SAME");
    h7_ch2->Draw("SAME");
    h15_ch2->Draw("SAME");
    h9->Draw("SAME");
    h17_ch4->Draw("SAME");
    h19_ch4->Draw("SAME");
    h21_ch2->Draw("SAME");
    h23_ch2->Draw("SAME");
    
    
    fit=FITT(h7_ch2,8,8,.2,6,3.4,58.,-10);
    res_switched[0]=fit[0];
    err_switched[0]=fit[1];
    gain_switched[0]=fit[2];
    err_gain_switched[0]=fit[3];
    
    fit=FITT(h9,8,8,.2,6,3.4,58.,-10);
    res_old[0]=fit[0];
    err_old[0]=fit[1];
    gain_old[0]=fit[2];
    err_gain_old[0]=fit[3];
    
    fit=FITT(h11_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_nochange[0]=fit[2];
    err_gain_nochange[0]=fit[3];
    res_nochange[0]=fit[0];
    err_nochange[0]=fit[1];
    
    fit=FITT(h13_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_sipm[0]=fit[2];
    err_gain_switched_sipm[0]=fit[3];
    res_switched_sipm[0]=fit[0];
    err_switched_sipm[0]=fit[1];
    
    fit=FITT(h15_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_PCB[0]=fit[2];
    err_gain_switched_PCB[0]=fit[3];
    res_switched_PCB[0]=fit[0];
    err_switched_PCB[0]=fit[1];
    
    fit=FITT(h15_bis_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_PCB_bis[0]=fit[2];
    err_gain_switched_PCB_bis[0]=fit[3];
    res_switched_PCB_bis[0]=fit[0];
    err_switched_PCB_bis[0]=fit[1];
    
    fit=FITT(h17_ch4,9,7,.2,6,3.4,60.,-10.);
    gain_switched_channel[0]=fit[2];
    err_gain_switched_channel[0]=fit[3];
    res_switched_channel[0]=fit[0];
    err_switched_channel[0]=fit[1];
    
    
    fit=FITT(h19_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_cable[0]=fit[2];
    err_gain_switched_cable[0]=fit[3];
    res_switched_cable[0]=fit[0];
    err_switched_cable[0]=fit[1];
    
    fit=FITT(h21_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_just_cable[0]=fit[2];
    err_gain_switched_just_cable[0]=fit[3];
    res_switched_just_cable[0]=fit[0];
    err_switched_just_cable[0]=fit[1];
    
  /*  fit=FITT(h23_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_side[0]=fit[2];
    err_gain_switched_side[0]=fit[3];
    res_switched_side[0]=fit[0];
    err_switched_side[0]=fit[1];*/
    
    

    auto legend_Ch2 = new TLegend(0.7,0.5,0.9,0.9);
    legend_Ch2->AddEntry(h9,"0.0 cm - P1 - old - right ends - with reflective foil","l"); //P4
    legend_Ch2->AddEntry(h11_ch2,"0.0 cm - P1 - both ends","l"); //P4
    legend_Ch2->AddEntry(h13_ch2,"0.0 cm - P1 - both ends - switched SiPMs","l"); //P4
    legend_Ch2->AddEntry(h15_ch2,"0.0 cm - P1 - both ends - switched PCBs 1","l"); //P4
    legend_Ch2->AddEntry(h15_bis_ch2,"0.0 cm - P1 - both ends - switched PCBs 2","l"); //P4
    legend_Ch2->AddEntry(h17_ch4,"0.0 cm - P1 - both ends - switched channels","l"); //P4
    legend_Ch2->AddEntry(h19_ch2,"0.0 cm - P1 - both ends - switched cables","l"); //P4
    legend_Ch2->AddEntry(h21_ch2,"0.0 cm - P1 - both ends - switched just cables","l"); //P4
    legend_Ch2->AddEntry(h23_ch2,"0.0 cm - P1 - both ends - switched sides","l"); //P4
    legend_Ch2->Draw();
    
    c1->cd(2);
    h14_ch3->Draw();
    h12_ch3->Draw("SAME");
    h8_ch3->Draw("SAME");
    h10->Draw("SAME");
    h16_ch3->Draw("SAME");
    h18_ch5->Draw("SAME");
    h20_ch5->Draw("SAME");
    h22_ch3->Draw("SAME");
    h24_ch3->Draw("SAME");
    
    fit=FITT(h10,8,8,.2,6,3.4,58.,-10.);
    res_old[1]=fit[0];
    err_old[1]=fit[1];
    gain_old[1]=fit[2];
    err_gain_old[1]=fit[3];
    
    fit=FITT(h8_ch3,8,8,.2,6,3.4,58.,-10.);
    res_switched[1]=fit[0];
    err_switched[1]=fit[1];
    gain_switched[1]=fit[2];
    err_gain_switched[1]=fit[3];
    
    fit=FITT(h12_ch3,9,8,.2,6,3.4,60.,-10.);
    gain_nochange[1]=fit[2];
    err_gain_nochange[1]=fit[3];
    res_nochange[1]=fit[0];
    err_nochange[1]=fit[1];
    
    fit=FITT(h14_ch3,9,7,.2,6,3.4,60.,-10.);
    gain_switched_sipm[1]=fit[2];
    err_gain_switched_sipm[1]=fit[3];
    res_switched_sipm[1]=fit[0];
    err_switched_sipm[1]=fit[1];
    
    fit=FITT(h16_ch3,9,7,.2,6,3.4,60.,-10.);
    gain_switched_PCB[1]=fit[2];
    err_gain_switched_PCB[1]=fit[3];
    res_switched_PCB[1]=fit[0];
    err_switched_PCB[1]=fit[1];
    
    fit=FITT(h16_bis_ch3,9,7,.2,6,3.4,60.,-10.);
    gain_switched_PCB_bis[1]=fit[2];
    err_gain_switched_PCB_bis[1]=fit[3];
    res_switched_PCB_bis[1]=fit[0];
    err_switched_PCB_bis[1]=fit[1];
    
    fit=FITT(h18_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_channel[1]=fit[2];
    err_gain_switched_channel[1]=fit[3];
    res_switched_channel[1]=fit[0];
    err_switched_channel[1]=fit[1];
    
    fit=FITT(h20_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_cable[1]=fit[2];
    err_gain_switched_cable[1]=fit[3];
    res_switched_cable[1]=fit[0];
    err_switched_cable[1]=fit[1];
    
    fit=FITT(h22_ch3,9,7,.2,6,3.4,60.,-10.);
    gain_switched_just_cable[1]=fit[2];
    err_gain_switched_just_cable[1]=fit[3];
    res_switched_just_cable[1]=fit[0];
    err_switched_just_cable[1]=fit[1];
    
    /*fit=FITT(h24_ch3,9,5,.2,6,3.4,55.,-10.);
    gain_switched_side[1]=fit[2];
    err_gain_switched_side[1]=fit[3];
    res_switched_side[1]=fit[0];
    err_switched_side[1]=fit[1];*/
    
    

    auto legend = new TLegend(0.7,0.7,1,1);
    legend->AddEntry(h10,"1.5 cm - P1 - old - right ends - with reflective foil","l"); //P4
    legend->AddEntry(h12_ch3,"1.5 cm - P1 - both ends","l"); //P4
    legend->AddEntry(h14_ch3,"1.5 cm - P1 - both ends - switched SiPMs","l"); //P4
    legend->AddEntry(h16_ch3,"1.5 cm - P1 - both ends - switched PCB 1","l"); //P4
    legend->AddEntry(h16_bis_ch3,"1.5 cm - P1 - both ends - switched PCB 2","l"); //P4
    legend->AddEntry(h18_ch5,"1.5 cm - P1 - both ends - switched channels","l"); //P4
    legend->AddEntry(h20_ch3,"1.5 cm - P1 - both ends - switched cables","l"); //P4
    legend->AddEntry(h22_ch3,"1.5 cm - P1 - both ends - switched just cables","l"); //P4
    legend->AddEntry(h24_ch3,"1.5 cm - P1 - both ends - switched sides","l"); //P4
    legend->Draw();
    
    
    c1->cd(3);
    
    h11_ch4->Draw();
    h13_ch4->Draw("SAME");
    h7_ch4->Draw("SAME");
    h15_ch4->Draw("SAME");
    h17_ch2->Draw("SAME");
    h19_ch2->Draw("SAME");
    h21_ch4->Draw("SAME");
    h23_ch4->Draw("SAME");
    
    fit=FITT(h7_ch4,9,5,.2,6,3.4,45.,-10.);
    gain_switched_new[0]=fit[2];
    err_gain_switched_new[0]=fit[3];
    res_switched_new[0]=fit[0];
    err_switched_new[0]=fit[1];
    
    fit=FITT(h11_ch4,9,6,.2,6,3.4,45.,-10.);
    gain_nochange_new[0]=fit[2];
    err_gain_nochange_new[0]=fit[3];
    res_nochange_new[0]=fit[0];
    err_nochange_new[0]=fit[1];
    
    fit=FITT(h13_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_sipm_new[0]=fit[2];
    err_gain_switched_sipm_new[0]=fit[3];
    res_switched_sipm_new[0]=fit[0];
    err_switched_sipm_new[0]=fit[1];
    
    fit=FITT(h15_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_PCB_new[0]=fit[2];
    err_gain_switched_PCB_new[0]=fit[3];
    res_switched_PCB_new[0]=fit[0];
    err_switched_PCB_new[0]=fit[1];
    
    fit=FITT(h15_bis_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_PCB_new_bis[0]=fit[2];
    err_gain_switched_PCB_new_bis[0]=fit[3];
    res_switched_PCB_new_bis[0]=fit[0];
    err_switched_PCB_new_bis[0]=fit[1];
    
    fit=FITT(h17_ch2,8,6,.2,6,3.4,55.,-10.);
    gain_switched_channel_new[0]=fit[2];
    err_gain_switched_channel_new[0]=fit[3];
    res_switched_channel_new[0]=fit[0];
    err_switched_channel_new[0]=fit[1];
    
    fit=FITT(h19_ch2,9,7,.2,6,3.4,60.,-10.);
    gain_switched_cable_new[0]=fit[2];
    err_gain_switched_cable_new[0]=fit[3];
    res_switched_cable_new[0]=fit[0];
    err_switched_cable_new[0]=fit[1];
    
    fit=FITT(h21_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_just_cable_new[0]=fit[2];
    err_gain_switched_just_cable_new[0]=fit[3];
    res_switched_just_cable_new[0]=fit[0];
    err_switched_just_cable_new[0]=fit[1];
    
  /*  fit=FITT(h23_ch4,8,6,.2,6,3.4,55.,-10.);
    gain_switched_side_new[0]=fit[2];
    err_gain_switched_side_new[0]=fit[3];
    res_switched_side_new[0]=fit[0];
    err_switched_side_new[0]=fit[1];*/
    
    c1->cd(4);
    
    h12_ch5->Draw();
    h14_ch5->Draw("SAME");
    h8_ch5->Draw("SAME");
    h16_ch5->Draw("SAME");
    h18_ch3->Draw("SAME");
    h20_ch3->Draw("SAME");
    h24_ch5->Draw("SAME");
    h22_ch5->Draw("SAME");
    
    fit=FITT(h8_ch5,9,6,.2,6,3.4,45.,-10.);
    gain_switched_new[1]=fit[2];
    err_gain_switched_new[1]=fit[3];
    res_switched_new[1]=fit[0];
    err_switched_new[1]=fit[1];
    
    fit=FITT(h12_ch5,9,6,.2,2.2,3.4,50.,-10.);
    gain_nochange_new[1]=fit[2];
    err_gain_nochange_new[1]=fit[3];
    res_nochange_new[1]=fit[0];
    err_nochange_new[1]=fit[1];
    
    fit=FITT(h14_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_sipm_new[1]=fit[2];
    err_gain_switched_sipm_new[1]=fit[3];
    res_switched_sipm_new[1]=fit[0];
    err_switched_sipm_new[1]=fit[1];
    
    fit=FITT(h16_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_PCB_new[1]=fit[2];
    err_gain_switched_PCB_new[1]=fit[3];
    res_switched_PCB_new[1]=fit[0];
    err_switched_PCB_new[1]=fit[1];
    
    
    fit=FITT(h16_bis_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_PCB_new_bis[1]=fit[2];
    err_gain_switched_PCB_new_bis[1]=fit[3];
    res_switched_PCB_new_bis[1]=fit[0];
    err_switched_PCB_new_bis[1]=fit[1];
    
    
    fit=FITT(h18_ch3,9,5,.2,6,3.4,55.,-10.);
    gain_switched_channel_new[1]=fit[2];
    err_gain_switched_channel_new[1]=fit[3];
    res_switched_channel_new[1]=fit[0];
    err_switched_channel_new[1]=fit[1];
    
    fit=FITT(h20_ch3,9,5,.2,6,3.4,55.,-10.);
    gain_switched_cable_new[1]=fit[2];
    err_gain_switched_cable_new[1]=fit[3];
    res_switched_cable_new[1]=fit[0];
    err_switched_cable_new[1]=fit[1];
    
    fit=FITT(h22_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_just_cable_new[1]=fit[2];
    err_gain_switched_just_cable_new[1]=fit[3];
    res_switched_just_cable_new[1]=fit[0];
    err_switched_just_cable_new[1]=fit[1];
    
 /*   fit=FITT(h24_ch5,9,5,.2,6,3.4,55.,-10.);
    gain_switched_side_new[1]=fit[2];
    err_gain_switched_side_new[1]=fit[3];
    res_switched_side_new[1]=fit[0];
    err_switched_side_new[1]=fit[1];*/
    
    string image = "Collimator.png";
    c1->SaveAs(image.c_str());
    
  
    TCanvas *c4 = new TCanvas("Mean charge all","c4",10,10,2000,800);
    TGraphErrors *g = new TGraphErrors(2,cm,res_old,0,err_old);
    
    TGraphErrors *g7 = new TGraphErrors(2,cm,res_switched,0,err_switched);
    TGraphErrors *g8 = new TGraphErrors(2,cm,res_switched_new,0,err_switched_new);
    
    TGraphErrors *g1 = new TGraphErrors(2,cm,res_nochange,0,err_nochange);
    TGraphErrors *g2 = new TGraphErrors(2,cm,res_nochange_new,0,err_nochange_new);
    
    TGraphErrors *g3 = new TGraphErrors(2,cm,res_switched_sipm,0,err_switched_sipm);
    TGraphErrors *g4 = new TGraphErrors(2,cm,res_switched_sipm_new,0,err_switched_sipm_new);
    
    TGraphErrors *g5 = new TGraphErrors(2,cm,res_switched_PCB,0,err_switched_PCB);
    TGraphErrors *g6 = new TGraphErrors(2,cm,res_switched_PCB_new,0,err_switched_PCB_new);
    
    
    TGraphErrors *g9 = new TGraphErrors(2,cm,res_switched_PCB_bis,0,err_switched_PCB_bis);
    TGraphErrors *g10 = new TGraphErrors(2,cm,res_switched_PCB_new_bis,0,err_switched_PCB_new_bis);
    
    
    TGraphErrors *g11 = new TGraphErrors(2,cm,res_switched_channel,0,err_switched_channel);
    TGraphErrors *g12 = new TGraphErrors(2,cm,res_switched_channel_new,0,err_switched_channel_new);
    
    TGraphErrors *g13 = new TGraphErrors(2,cm,res_switched_cable,0,err_switched_cable);
    TGraphErrors *g14 = new TGraphErrors(2,cm,res_switched_cable_new,0,err_switched_cable_new);
    
    TGraphErrors *g15 = new TGraphErrors(2,cm,res_switched_just_cable,0,err_switched_just_cable);
    TGraphErrors *g16 = new TGraphErrors(2,cm,res_switched_just_cable_new,0,err_switched_just_cable_new);
    
    TGraphErrors *g17 = new TGraphErrors(2,cm,res_switched_side,0,err_switched_side);
    TGraphErrors *g18 = new TGraphErrors(2,cm,res_switched_side_new,0,err_switched_side_new);
    
    
    g1->GetXaxis()->SetTitle("cm");
    g1->GetYaxis()->SetTitle("Npe");    
    g->GetYaxis()->SetRangeUser(4.5,8);    
    g->GetXaxis()->SetRangeUser(-8,8);   
    
    g2->GetYaxis()->SetRangeUser(4.5,8);    
    g2->GetXaxis()->SetRangeUser(-8,8); 
    
    g->GetYaxis()->SetTitle("Npe per event");    
    g->GetXaxis()->SetTitle("Distance from the fiber [cm]");    
    g->SetTitle("Old scintillator side - Npe"); 
    
    g2->GetYaxis()->SetTitle("Npe per event");    
    g2->GetXaxis()->SetTitle("Distance from the fiber [cm]");    
    g2->SetTitle("New scintillator side - Npe"); 
         
    g->SetLineColor(kOrange);
    g->SetMarkerSize(1.2);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kOrange);
    g1->SetLineColor(kBlue);
    g1->SetMarkerSize(1.2);
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kBlue);
    g2->SetLineColor(kBlue);
    g2->SetMarkerSize(1.2);
    g2->SetMarkerStyle(20);
    g2->SetMarkerColor(kBlue);
    
    g3->SetLineColor(kBlack);
    g3->SetMarkerSize(1.2);
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(kBlack);
    g4->SetLineColor(kBlack);
    g4->SetMarkerSize(1.2);
    g4->SetMarkerStyle(20);
    g4->SetMarkerColor(kBlack);
    
    g5->SetLineColor(kRed);
    g5->SetMarkerSize(1.2);
    g5->SetMarkerStyle(20);
    g5->SetMarkerColor(kRed);
    g6->SetLineColor(kRed);
    g6->SetMarkerSize(1.2);
    g6->SetMarkerStyle(20);
    g6->SetMarkerColor(kRed);
    
    
    g7->SetLineColor(kGreen);
    g7->SetMarkerSize(1.2);
    g7->SetMarkerStyle(20);
    g7->SetMarkerColor(kGreen);
    g8->SetLineColor(kBlue);
    g8->SetMarkerSize(1.2);
    g8->SetMarkerStyle(20);
    g8->SetMarkerColor(kBlue);
    
    
    g9->SetLineColor(kRed);
    g9->SetMarkerSize(1.2);
    g9->SetMarkerStyle(20);
    g9->SetMarkerColor(kRed);
    g10->SetLineColor(kRed);
    g10->SetMarkerSize(1.2);
    g10->SetMarkerStyle(20);
    g10->SetMarkerColor(kRed);
    
    
    g11->SetLineColor(kRed);
    g11->SetMarkerSize(1.2);
    g11->SetMarkerStyle(24);
    g11->SetMarkerColor(kRed);
    g12->SetLineColor(kRed);
    g12->SetMarkerSize(1.2);
    g12->SetMarkerStyle(24);
    g12->SetMarkerColor(kRed);
    
    g13->SetLineColor(kRed);
    g13->SetMarkerSize(1.2);
    g13->SetMarkerStyle(25);
    g13->SetMarkerColor(kRed);
    g14->SetLineColor(kRed);
    g14->SetMarkerSize(1.2);
    g14->SetMarkerStyle(25);
    g14->SetMarkerColor(kRed);
    
    g15->SetLineColor(kRed);
    g15->SetMarkerSize(1.2);
    g15->SetMarkerStyle(26);
    g15->SetMarkerColor(kRed);
    g16->SetLineColor(kRed);
    g16->SetMarkerSize(1.2);
    g16->SetMarkerStyle(26);
    g16->SetMarkerColor(kRed);
    
    g17->SetLineColor(kRed);
    g17->SetMarkerSize(1.2);
    g17->SetMarkerStyle(27);
    g17->SetMarkerColor(kRed);
    g18->SetLineColor(kRed);
    g18->SetMarkerSize(1.2);
    g18->SetMarkerStyle(27);
    g18->SetMarkerColor(kRed);
        
    auto len = new TLegend(0.4,0.5,0.8,0.9);
    len->AddEntry(g,"old: PCB_old/SiPM_old/Teflon_old (reflecive foil)","p");
    
    len->AddEntry(g7,"PCB_old/SiPM_old/Teflon_old ","p");   
    
    len->AddEntry(g1,"PCB_old/SiPM_old/Teflon_new ","p");   
    
    len->AddEntry(g3,"PCB_old/SiPM_new/Teflon_old","p");    
    
    len->AddEntry(g5,"PCB_new/SiPM_old/Teflon_new","p");    
    
    len->AddEntry(g11,"PCB_new/SiPM_old/Teflon_new - switched channels","p");      
    
    len->AddEntry(g13,"PCB_new/SiPM_old/Teflon_new - switched cables","p"); 
    len->AddEntry(g15,"PCB_new/SiPM_old/Teflon_new - switched just cables","p"); 
    
    len->AddEntry(g17,"PCB_new/SiPM_old/Teflon_new - switched sides","p"); 
    
    c4->Divide(2,2);
    c4->cd(1);
    g->Draw("AP");
    g1->Draw("P");
    g3->Draw("P");
    g5->Draw("P");
    g7->Draw("P");
    g9->Draw("P");
    g11->Draw("P");
    g13->Draw("P");
    g15->Draw("P");
    g17->Draw("P");
    len->Draw("SAME");
    
    
    
    auto len1 = new TLegend(0.4,0.5,0.8,0.9);
    
    len1->AddEntry(g2,"PCB_new/SiPM_new/Teflon_old","p"); 
    
    len1->AddEntry(g4,"PCB_new/SiPM_old/Teflon_new","p");  
    
    len1->AddEntry(g6,"PCB_old/SiPM_new/Teflon_old","p"); 
    
    len1->AddEntry(g12,"PCB_old/SiPM_new/Teflon_old - switched channels","p");  
    
    len1->AddEntry(g14,"PCB_old/SiPM_new/Teflon_old - switched cables","p");  
    
    len1->AddEntry(g16,"PCB_new/SiPM_old/Teflon_new - switched just cables","p"); 
    
    len1->AddEntry(g18,"PCB_new/SiPM_old/Teflon_new - switched sides","p");
    
    c4->cd(2);
    g2->Draw("AP");
    g4->Draw("P");
    g6->Draw("P");
    g8->Draw("P");
    g10->Draw("P");
    g12->Draw("P");
    g14->Draw("P");
    g16->Draw("P");
    g18->Draw("P");
    
    len1->Draw("SAME");
    
    
    
    
        
    TGraphErrors *T = new TGraphErrors(2,cm,gain_old,0,err_gain_old);
    
    TGraphErrors *T7 = new TGraphErrors(2,cm,gain_switched,0,err_gain_switched);
    TGraphErrors *T8 = new TGraphErrors(2,cm,gain_switched_new,0,err_gain_switched_new);
    
    TGraphErrors *T1 = new TGraphErrors(2,cm,gain_nochange,0,err_gain_nochange);
    TGraphErrors *T2 = new TGraphErrors(2,cm,gain_nochange_new,0,err_gain_nochange_new);
    
    TGraphErrors *T3 = new TGraphErrors(2,cm,gain_switched_sipm,0,err_gain_switched_sipm);
    TGraphErrors *T4 = new TGraphErrors(2,cm,gain_switched_sipm_new,0,err_gain_switched_sipm_new);
    
    TGraphErrors *T5 = new TGraphErrors(2,cm,gain_switched_PCB,0,err_gain_switched_PCB);
    TGraphErrors *T6 = new TGraphErrors(2,cm,gain_switched_PCB_new,0,err_gain_switched_PCB_new);
    
    TGraphErrors *T9 = new TGraphErrors(2,cm,gain_switched_PCB_bis,0,err_gain_switched_PCB_bis);
    TGraphErrors *T10 = new TGraphErrors(2,cm,gain_switched_PCB_new_bis,0,err_gain_switched_PCB_new_bis);
    
    TGraphErrors *T11 = new TGraphErrors(2,cm,gain_switched_channel,0,err_gain_switched_channel);
    TGraphErrors *T12 = new TGraphErrors(2,cm,gain_switched_channel_new,0,err_gain_switched_channel_new);
    
     TGraphErrors *T13 = new TGraphErrors(2,cm,gain_switched_cable,0,err_gain_switched_cable);
    TGraphErrors *T14 = new TGraphErrors(2,cm,gain_switched_cable_new,0,err_gain_switched_cable_new);
    
    TGraphErrors *T15 = new TGraphErrors(2,cm,gain_switched_just_cable,0,err_gain_switched_just_cable);
    TGraphErrors *T16 = new TGraphErrors(2,cm,gain_switched_just_cable_new,0,err_gain_switched_just_cable_new);
    
     TGraphErrors *T17 = new TGraphErrors(2,cm,gain_switched_side,0,err_gain_switched_side);
    TGraphErrors *T18 = new TGraphErrors(2,cm,gain_switched_side_new,0,err_gain_switched_side_new);
    
    
    T->GetXaxis()->SetTitle("Distance from the fiber [cm]");
    T->GetYaxis()->SetTitle("mVxns"); 
    T2->GetXaxis()->SetTitle("Distance from the fiber [cm]");
    T2->GetYaxis()->SetTitle("mVxns");
    T->SetTitle("Old scintillator side - Gain"); 
    T2->SetTitle("New scintillator side - Gain");  
     
    T->GetYaxis()->SetRangeUser(40,60);    
    T->GetXaxis()->SetRangeUser(-8,8);  
    T2->GetYaxis()->SetRangeUser(40,60);    
    T2->GetXaxis()->SetRangeUser(-8,8);    
    
        
    T->SetLineColor(kOrange);
    T->SetMarkerSize(1.2);
    T->SetMarkerStyle(20);
    T->SetMarkerColor(kOrange);
    T1->SetLineColor(kBlue);
    T1->SetMarkerSize(1.2);
    T1->SetMarkerStyle(20);
    T1->SetMarkerColor(kBlue);
    T2->SetLineColor(kBlue);
    T2->SetMarkerSize(1.2);
    T2->SetMarkerStyle(20);
    T2->SetMarkerColor(kBlue);
    
    T3->SetLineColor(kBlack);
    T3->SetMarkerSize(1.2);
    T3->SetMarkerStyle(20);
    T3->SetMarkerColor(kBlack);
    T4->SetLineColor(kBlack);
    T4->SetMarkerSize(1.2);
    T4->SetMarkerStyle(20);
    T4->SetMarkerColor(kBlack);
    T5->SetLineColor(kRed);
    T5->SetMarkerSize(1.2);
    T5->SetMarkerStyle(20);
    T5->SetMarkerColor(kRed);
    T6->SetLineColor(kRed);
    T6->SetMarkerSize(1.2);
    T6->SetMarkerStyle(20);
    T6->SetMarkerColor(kRed);
    
    
    T7->SetLineColor(kGreen);
    T7->SetMarkerSize(1.2);
    T7->SetMarkerStyle(20);
    T7->SetMarkerColor(kGreen);
    T8->SetLineColor(kBlue);
    T8->SetMarkerSize(1.2);
    T8->SetMarkerStyle(20);
    T8->SetMarkerColor(kBlue);
    
    T9->SetLineColor(kRed);
    T9->SetMarkerSize(1.2);
    T9->SetMarkerStyle(20);
    T9->SetMarkerColor(kRed);
    T10->SetLineColor(kRed);
    T10->SetMarkerSize(1.2);
    T10->SetMarkerStyle(20);
    T10->SetMarkerColor(kRed);
    
    T11->SetLineColor(kRed);
    T11->SetMarkerSize(1.2);
    T11->SetMarkerStyle(24);
    T11->SetMarkerColor(kRed);
    T12->SetLineColor(kRed);
    T12->SetMarkerSize(1.2);
    T12->SetMarkerStyle(24);
    T12->SetMarkerColor(kRed);
    
    T13->SetLineColor(kRed);
    T13->SetMarkerSize(1.2);
    T13->SetMarkerStyle(25);
    T13->SetMarkerColor(kRed);
    T14->SetLineColor(kRed);
    T14->SetMarkerSize(1.2);
    T14->SetMarkerStyle(25);
    T14->SetMarkerColor(kRed);
    
    T15->SetLineColor(kRed);
    T15->SetMarkerSize(1.2);
    T15->SetMarkerStyle(26);
    T15->SetMarkerColor(kRed);
    T16->SetLineColor(kRed);
    T16->SetMarkerSize(1.2);
    T16->SetMarkerStyle(26);
    T16->SetMarkerColor(kRed);
    
    T17->SetLineColor(kRed);
    T17->SetMarkerSize(1.2);
    T17->SetMarkerStyle(27);
    T17->SetMarkerColor(kRed);
    T18->SetLineColor(kRed);
    T18->SetMarkerSize(1.2);
    T18->SetMarkerStyle(27);
    T18->SetMarkerColor(kRed);
        
    c4->cd(3);
    T->Draw("AP");
    T1->Draw("P");
    T3->Draw("P");
    T5->Draw("P");
    T7->Draw("P");
    T9->Draw("P");
    T11->Draw("P");
    T13->Draw("P");
    T15->Draw("P");
    T17->Draw("P");
    
    c4->cd(4);
    T2->Draw("AP");
    T4->Draw("P");
    T6->Draw("P");
    T8->Draw("P");
    T10->Draw("P");
    T12->Draw("P");
    T14->Draw("P");
    T16->Draw("P");
    T18->Draw("P");
    
    image = "Charge_all_mean.png";
    c4->SaveAs(image.c_str());
    
    
   
    return;
}
