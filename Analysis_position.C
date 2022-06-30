void Analysis_position() {
    
    TFile *outfile  = TFile::Open("Analysis.root","RECREATE");
    int Category;
    TTree *tree = new TTree("T","CERN 1988 staff data");
    tree->Branch("Comparison",&Category,"Category/I");
    

    TH1F *h1 = new TH1F("h1", "h1", 1000, 0,1200);
    h1->GetXaxis()->SetTitle("mV X ns");
    h1->GetYaxis()->SetTitle("Events");
    
    TH1F *h2 = new TH1F("h2", "h2", 1000, 0,1200);
    TH1F *h3 = new TH1F("h3", "h3", 1000, 0,1200);
    TH1F *h4 = new TH1F("h4", "h4", 1000, 0,1200);
    TH1F *h5 = new TH1F("h3", "h3", 1000, 0,1200);
    TH1F *h6 = new TH1F("h4", "h4", 1000, 0,1200);
   
    TFile *f1 = TFile::Open("Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3.root");
    h1 = (TH1F*)f1->Get("ChargeSpectrum channel_02");
    h3 = (TH1F*)f1->Get("ChargeSpectrum channel_03");
     
    TFile *f2 = TFile::Open("Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_2.root");
    h2 = (TH1F*)f2->Get("ChargeSpectrum channel_02");
    h4 = (TH1F*)f2->Get("ChargeSpectrum channel_03");
    
    TFile *f3 = TFile::Open("Trigger_6mV_TBup_Ch26_TBdown_Ch14_Readout_Ch2_Ch3_pos_3.root");
    h5 = (TH1F*)f3->Get("ChargeSpectrum channel_02");
    h6 = (TH1F*)f3->Get("ChargeSpectrum channel_03");
  
    
    TCanvas *c1 = new TCanvas("Charge Spectra Ch00","c1",10,10,2000,800);
    h1->SetLineColor(kRed);
    h2->SetLineColor(kYellow);
    h3->SetLineColor(kBlack);
    h4->SetLineColor(kOrange);
    h5->SetLineColor(kBlue);
    h6->SetLineColor(kGreen);
   /* h1->SetName("1.5 cm");
    h2->SetName("3.5 cm");
    h3->SetName("0.0 cm");
    h4->SetName("2.0 cm");
    h5->SetName("4.0 cm");
    h6->SetName("5.5 cm");*/
    
    h4->Draw();
    h3->Draw("SAME");
    h1->Draw("SAME");
    h2->Draw("SAME");
    h5->Draw("SAME");
    h6->Draw("SAME");
    
    auto legend = new TLegend(0.7,0.7,0.48,0.9);
    legend->AddEntry(h3,"0.0 cm","l");
    legend->AddEntry(h1,"1.5 cm","l");
    legend->AddEntry(h4,"2.0 cm","l");
    legend->AddEntry(h2,"3.5 cm","l");
    legend->AddEntry(h6,"4.0 cm","l");
    legend->AddEntry(h5,"5.5 cm","l");
    legend->Draw();
    
    string image = "Source_position.png";
    c1->SaveAs(image.c_str());
    
    
   
    return;
}
