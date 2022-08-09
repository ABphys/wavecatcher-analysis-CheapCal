
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
				
				
        hist->Fit(f,"","",200,800);
        cout<<"jfkasljfakljsflajf "<<f->GetParameter(1)<<endl;
        f->Draw("SAME");
        double *results = new double[2]; 
        results[0] =  f->GetParameter(5);
        results[1] = f->GetParError(5) ;
        
        return results; 
        
}


void Analysis_position() {

    TFile *outfile  = TFile::Open("Analysis_filter.root","RECREATE");
    int Category;
    TTree *tree = new TTree("T","CERN 1988 staff data");
    tree->Branch("Comparison",&Category,"Category/I");
    

    TH1F *h1 = new TH1F("h1", "0.75cm", 1000, 0,1500);
    h1->GetXaxis()->SetTitle("mV X ns");
    h1->GetYaxis()->SetTitle("Events");
    
    TH1F *h2 = new TH1F("h2", "1.75cm", 1000, 0,1500);
    TH1F *h3 = new TH1F("h3", "1.5cm", 1000, 0,1500);
    TH1F *h4 = new TH1F("h4", "0.0cm", 1000, 0,1500);
    TH1F *h5 = new TH1F("h5", "3.5cm", 1000, 0,1500);
    TH1F *h6 = new TH1F("h6", "2.0cm", 1000, 0,1500);
    TH1F *h7 = new TH1F("h7", "5.5cm", 1000, 0,1500);
    TH1F *h8 = new TH1F("h8", "4.0cm", 1000, 0,1500);
    TH1F *h9 = new TH1F("h9", "0.0cm", 1000, 0,1500);
    TH1F *h10 = new TH1F("h10", "1.5cm", 1000, 0,1500);
    TH1F *h11 = new TH1F("h11", "2.0cm", 1000, 0,1500);
    TH1F *h12 = new TH1F("h12", "3.5cm", 1000, 0,1500);
    TH1F *h13 = new TH1F("h13", "2.5cm", 1000, 0,1500);
    TH1F *h14 = new TH1F("h14", "1.0cm", 1000, 0,1500);
    TH1F *h15 = new TH1F("h13", "1.0cm", 1000, 0,1500);
    TH1F *h16 = new TH1F("h14", "2.5cm", 1000, 0,1500);
    
    
   
    TFile *f1 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_0.root");
    h1 = (TH1F*)f1->Get("ChargeSpectrum channel_02"); //0.75cm 
    h2 = (TH1F*)f1->Get("ChargeSpectrum channel_03"); //0.75cm
     
    TFile *f2 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_1.root");
    h3 = (TH1F*)f2->Get("ChargeSpectrum channel_02"); // 1.5cm
    h4 = (TH1F*)f2->Get("ChargeSpectrum channel_03"); // 0.0cm
    
    TFile *f3 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_2.root");
    h5 = (TH1F*)f3->Get("ChargeSpectrum channel_02"); //3.5cm	
    h6 = (TH1F*)f3->Get("ChargeSpectrum channel_03"); //2.0cm
    
    TFile *f4 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_3.root");
    h7 = (TH1F*)f4->Get("ChargeSpectrum channel_02"); // 5.5cm	
    h8 = (TH1F*)f4->Get("ChargeSpectrum channel_03"); //4.0cm	
    
    TFile *f5 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4.root");
    h9 = (TH1F*)f5->Get("ChargeSpectrum channel_02"); // 0.0cm
    h10 = (TH1F*)f5->Get("ChargeSpectrum channel_03"); // 1.5cm
    
    TFile *f6 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_5.root");
    h11 = (TH1F*)f6->Get("ChargeSpectrum channel_02"); // 2.0cm	
    h12 = (TH1F*)f6->Get("ChargeSpectrum channel_03"); // 3.5cm

    TFile *f7 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_1_5_again.root");
    h13 = (TH1F*)f7->Get("ChargeSpectrum channel_02"); // 2.5cm
    h14 = (TH1F*)f7->Get("ChargeSpectrum channel_03"); // 1.0cm
    
    TFile *f8 = TFile::Open("Coincidence_TB_Ch14_Ch26_10mV_Readout_Ch2_Ch3_Pos_4_5.root");
    h15 = (TH1F*)f8->Get("ChargeSpectrum channel_02"); // 1.0cm
    h16 = (TH1F*)f8->Get("ChargeSpectrum channel_03"); // 2.5cm
    
    
   
   /* h1->SetLineColor(kRed);
    h2->SetLineColor(kBlack);
    h3->SetLineColor(kRed);
    h4->SetLineColor(kBlack);
    h5->SetLineColor(kRed);
    h6->SetLineColor(kBlack);
    h7->SetLineColor(kRed);
    h8->SetLineColor(kBlack);
    h9->SetLineColor(kRed);
    h10->SetLineColor(kBlack);
    h11->SetLineColor(kRed);
    h12->SetLineColor(kBlack);
    h13->SetLineColor(kRed); //2.5cm
    h14->SetLineColor(kBlack); //1.0cm
    */
    /*
    h1->SetLineColor(8); //0.75cm
    h2->SetLineColor(3); //0.75cm
    h3->SetLineColor(46); //1.5cm
    h4->SetLineColor(4); //0.0cm
    h5->SetLineColor(9);  //3.5cm
    h6->SetLineColor(6); //2.0cm
    h7->SetLineColor(5); //5.5cm
    h8->SetLineColor(5); //4.0cm
    h9->SetLineColor(46); //0.0cm
    h10->SetLineColor(8);  //1.5cm
    h11->SetLineColor(3); //2.0cm
    h12->SetLineColor(4); //3.5cm
    */
    
    
    h1->SetLineColor(kGreen); //0.75cm
    h2->SetLineColor(kGreen); //0.75cm
    h3->SetLineColor(kRed); //1.5cm
    h4->SetLineColor(kRed); //0.0cm
    h5->SetLineColor(kBlue);  //3.5cm
    h6->SetLineColor(kBlue); //2.0cm
    h7->SetLineColor(kBlack); //5.5cm
    h8->SetLineColor(kBlack); //4.0cm
    h9->SetLineColor(kRed); //0.0cm
    h10->SetLineColor(kRed);  //1.5cm
    h11->SetLineColor(kBlue); //2.0cm
    h12->SetLineColor(kBlue); //3.5cm
    h13->SetLineColor(36); //2.5cm
    h14->SetLineColor(36); //1.0cm
    h15->SetLineColor(36); //1.0cm
    h16->SetLineColor(36); //2.5cm
    
    vector<double> par [7];
    
    
    double_t cm_Ch2[8]={0.,0.75,1.0,1.5,2.0,2.5,3.5,5.5};
    double_t cm_Ch3[8]={0.,0.75,1.0,1.5,2.0,2.5,3.5,4.0};
    double_t mean_Ch2[8];
    double_t mean_Ch3[8];
    double_t err_Ch2[8];
    double_t err_Ch3[8];
    
    double *fit = new double[2];
    
    TCanvas *c1_Ch2 = new TCanvas("Charge Spectra Ch2","c1_Ch2",10,10,2000,800);
    
    h9->Draw();
    h1->Draw("SAME");
    h11->Draw("SAME");
    h15->Draw("SAME");
    
    fit=FITT(h9,0,2,.2,2.2,3.4,30.,0.);
    mean_Ch2[0]=int(h9->GetBinCenter(h9->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[0]= int(h9->GetBinCenter(h9->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h1,0,2,.2,2.2,3.4,30.,0.);
    mean_Ch2[1]=int(h1->GetBinCenter(h1->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[1]= int(h1->GetBinCenter(h1->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h15,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch2[2]=int(h15->GetBinCenter(h15->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[2]= int(h15->GetBinCenter(h15->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h11,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch2[4]=int(h11->GetBinCenter(h11->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[4]= int(h11->GetBinCenter(h11->GetMaximumBin())/fit[0])*fit[1];

  /*  h3->Draw("SAME");
    h5->Draw("SAME");
    h7->Draw("SAME");
*/
    auto legend_Ch2 = new TLegend(0.7,0.7,1,1);
    legend_Ch2->AddEntry(h9,"0.0 cm - P4","l");
    legend_Ch2->AddEntry(h1,"0.75 cm - P0","l");
    legend_Ch2->AddEntry(h15,"1.0 cm - P4.5","l");
   // legend_Ch2->AddEntry(h3,"1.5 cm - P1","l");
    legend_Ch2->AddEntry(h11,"2.0 cm - P5","l");
  //  legend_Ch2->AddEntry(h5,"3.5 cm - P2","l");
   // legend_Ch2->AddEntry(h7,"5.5 cm - P3","l");
    legend_Ch2->Draw();
    
    string image = "Source_position_Ch2.png";
    c1_Ch2->SaveAs(image.c_str());
    
    TCanvas *c1_Ch3 = new TCanvas("Charge Spectra Ch3","c1_Ch3",10,10,2000,800);

    h6->Draw();
    h2->Draw("SAME");
    h14->Draw("SAME");
    h4->Draw("SAME");
    h8->Draw("SAME");
    
    fit=FITT(h4,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch3[0]=int(h4->GetBinCenter(h4->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[0]= int(h4->GetBinCenter(h4->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h2,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch3[1]=int(h2->GetBinCenter(h2->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[1]= int(h2->GetBinCenter(h2->GetMaximumBin())/fit[0])*fit[1];

    fit=FITT(h14,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch3[2]=int(h14->GetBinCenter(h14->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[2]= int(h14->GetBinCenter(h14->GetMaximumBin())/fit[0])*fit[1];

    fit=FITT(h6,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch3[4]=7*fit[0];//int(h6->GetBinCenter(h6->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[4]= 7*fit[1]; //int(h6->GetBinCenter(h6->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h8,0,2,.2,2.2,3.4,45.,0.);
    mean_Ch3[7]=int(h8->GetBinCenter(h8->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[7]= int(h8->GetBinCenter(h8->GetMaximumBin())/fit[0])*fit[1];
    
   /* h10->Draw("SAME");
    h12->Draw("SAME");*/
    
    auto legend_Ch3 = new TLegend(0.7,0.7,1,1);
    legend_Ch3->AddEntry(h4,"0.0 cm - P1","l");
    legend_Ch3->AddEntry(h2,"0.75 cm - P0","l");
    legend_Ch3->AddEntry(h14,"1.0 cm - P1.5","l");
   // legend_Ch3->AddEntry(h10,"1.5 cm - P4","l");    
    legend_Ch3->AddEntry(h6,"2.0 cm - P2","l");    
    //legend_Ch3->AddEntry(h12,"3.5 cm - P5","l");
    legend_Ch3->AddEntry(h8,"4.0 cm - P3","l");
    legend_Ch3->Draw();
    
    
    
    image = "Source_position_Ch3.png";
    c1_Ch3->SaveAs(image.c_str());
    
    
    TCanvas *c1_Ch2_post = new TCanvas("Charge Spectra Ch2 post fiber","c1_Ch2_post",10,10,2000,800);
    
    
    h5->Draw();
    h13->Draw("SAME");
    h3->Draw("SAME");
    h7->Draw("SAME");
    
    fit=FITT(h3,0,2,.2,2.2,3.4,55.,0.);
    mean_Ch2[3]=int(h3->GetBinCenter(h3->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[3]= int(h3->GetBinCenter(h3->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h13,0,2,.2,2.2,3.4,50.,0.);
    mean_Ch2[5]=int(h13->GetBinCenter(h13->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[5]= int(h13->GetBinCenter(h13->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h5,0,2,.2,2.2,3.4,50.,0.);
    mean_Ch2[6]=5*fit[0];//int(h5->GetBinCenter(h5->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[6]= 5*fit[1];//int(h5->GetBinCenter(h5->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h7,0,2,.2,2.2,3.4,55.,0.);
    mean_Ch2[7]=int(h7->GetBinCenter(h7->GetMaximumBin())/fit[0])*fit[0];
    err_Ch2[7]= int(h7->GetBinCenter(h7->GetMaximumBin())/fit[0])*fit[1];
    
    auto legend_Ch2_post = new TLegend(0.7,0.7,1,1);
    legend_Ch2_post->AddEntry(h3,"1.5 cm - P1","l");
    legend_Ch2_post->AddEntry(h13,"2.5 cm - P1.5","l");
    legend_Ch2_post->AddEntry(h5,"3.5 cm - P2","l");
    legend_Ch2_post->AddEntry(h7,"5.5 cm - P3","l");
    legend_Ch2_post->Draw();
    
    image = "Source_position_Ch2_post.png";
    c1_Ch2_post->SaveAs(image.c_str());
    
    TCanvas *c1_Ch3_post = new TCanvas("Charge Spectra Ch3 post fiber","c1_Ch3_post",10,10,2000,800);

    
    h10->Draw();
    h12->Draw("SAME");
    h16->Draw("SAME");
    
    fit=FITT(h10,0,2,.2,2.2,3.4,50.,0.);
    mean_Ch3[3]=int(h10->GetBinCenter(h10->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[3]= int(h10->GetBinCenter(h10->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h16,0,2,.2,2.2,3.4,55.,0.);
    mean_Ch3[5]=int(h16->GetBinCenter(h16->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[5]= int(h16->GetBinCenter(h16->GetMaximumBin())/fit[0])*fit[1];
    
    fit=FITT(h12,0,2,.2,2.2,3.4,55.,0.);
    mean_Ch3[6]=int(h12->GetBinCenter(h12->GetMaximumBin())/fit[0])*fit[0];
    err_Ch3[6]= int(h12->GetBinCenter(h12->GetMaximumBin())/fit[0])*fit[1];
   
    auto legend_Ch3_post = new TLegend(0.7,0.7,1,1);
    legend_Ch3_post->AddEntry(h10,"1.5 cm - P4","l");
    legend_Ch3_post->AddEntry(h16,"2.5 cm - P4.5","l");
    legend_Ch3_post->AddEntry(h12,"3.5 cm - P5","l");    
    legend_Ch3_post->Draw();
    
    
    image = "Source_position_Ch3_post.png";
    c1_Ch3_post->SaveAs(image.c_str());
    
    
    TCanvas *c3 = new TCanvas("Charge Spectra no filter all","c3",10,10,2000,1500);

    c3->Divide(2,4);
    c3->cd(1);
    
    
    h4->Draw();
    h9->Draw("SAME");
    
    c3->cd(2);
    
    
    
    h1->Draw();
    h2->Draw("SAME");    
    
    c3->cd(3);
    
    h14->Draw();
    h15->Draw("SAME");
    
    
    c3->cd(4);
    
    h3->Draw();
    h10->Draw("SAME"); 
      
    
    c3->cd(5);
    
    h6->Draw();  
    h11->Draw("SAME");
    
    c3->cd(6);
    
    h13->Draw();  
    h16->Draw("SAME");
    
    c3->cd(7);
    
    h5->Draw();  
    h12->Draw("SAME");
    
    
    
    image = "Source_position_channel.png";
   // c3->SaveAs(image.c_str());
   
    fstream my_file;
    my_file.open("results_fit.txt");
    my_file<<"Ch2 cm	Ch2	Ch2 err	Ch3 cm	Ch3	Ch3 err"<<endl;
    
    for(int i=0;  i<8;  i++){
    	my_file<<cm_Ch2[i]<<"	"<<mean_Ch2[i]<<"	"<<err_Ch2[i]<<"	"<<cm_Ch3[i]<<"	"<<mean_Ch3[i]<<"	"<<err_Ch3[i]<<endl;
    }
    
    TCanvas *c4 = new TCanvas("Mean charge all","c4",10,10,2000,800);
    TGraphErrors *g = new TGraphErrors(8,cm_Ch2,mean_Ch2,0,err_Ch2);
    TGraphErrors *g1 = new TGraphErrors(8,cm_Ch3,mean_Ch3,0,err_Ch3);
    
    g->GetXaxis()->SetTitle("cm");
    g->GetYaxis()->SetTitle("Peak");    
    g->GetYaxis()->SetRangeUser(-10,800);    
    
    g->SetLineColor(kRed);
    g1->SetLineColor(kBlack);
    
    auto len = new TLegend(0.7,0.7,1,1);
    len->AddEntry(g,"Ch2","l");
    len->AddEntry(g1,"Ch3","l");    
    
    
    g->Draw("AC*");
    g1->Draw("C*");
    len->Draw("SAME"); 
    image = "Charge_all_mean.png";
    c4->SaveAs(image.c_str());
    
    
   
    return;
}
