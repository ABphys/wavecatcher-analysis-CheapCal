void Analysis() {
    
    TFile *outfile  = TFile::Open("Analysis.root","RECREATE");
    int Category;
    TTree *tree = new TTree("T","CERN 1988 staff data");
    tree->Branch("Comparison",&Category,"Category/I");
    

    TH1F *h1 = new TH1F("h1", "h1", 2, 1, 3);
    h1->GetXaxis()->SetTitle("mV X ns");
    h1->GetYaxis()->SetTitle("Events");
    h1->GetXaxis()->SetRange(0,370);
    h1->GetYaxis()->SetRange(0,8000);
    
    TH1F *h2 = new TH1F("h2", "h2", 2, 1, 3);
    h2->GetXaxis()->SetRange(0,370);
    h2->GetYaxis()->SetRange(0,8000);
    
    TH1F *h3 = new TH1F("h3", "h3", 2, 1, 3);
    h3->GetXaxis()->SetTitle("mV X ns");
    h3->GetYaxis()->SetTitle("Events");
    h3->GetXaxis()->SetRange(0,370);
    h3->GetYaxis()->SetRange(0,8000);
    
    TH1F *h4 = new TH1F("h4", "h4", 2, 1, 3);
    h4->GetXaxis()->SetRange(0,370);
    h4->GetYaxis()->SetRange(0,8000);
   
    TFile *f_source = TFile::Open("2fibers_Ch0_Ch2_also_Ch1_Ch4_available_source.root");
    h1 = (TH1F*)f_source->Get("ChargeSpectrum channel_00");
    h3 = (TH1F*)f_source->Get("ChargeSpectrum channel_02");
     
    TFile *f_nosource = TFile::Open("2fibers_Ch0_Ch2_also_Ch1_Ch4_available.root");
    h2 = (TH1F*)f_nosource->Get("ChargeSpectrum channel_00");
    h4 = (TH1F*)f_nosource->Get("ChargeSpectrum channel_02");
  
    
    TCanvas *c1 = new TCanvas("Charge Spectra Ch00","c1",10,10,1200,800);
    h1->SetLineColor(kRed);
    h1->SetName("Source");
    h2->SetName("Without source");
    h2->Draw();
    h1->Draw("SAME");
    auto legend = new TLegend(0.7,0.7,0.48,0.9);
    legend->AddEntry(h1,"Source","l");
    legend->AddEntry(h2,"Without source","l");
    legend->Draw();
    
    string image = "2fibers_Channel_00.png";
    c1->SaveAs(image.c_str());
    
    TCanvas *c2 = new TCanvas("Charge Spectra Ch01","c2",10,10,1200,800);
    h3->SetLineColor(kRed);
    
    h4->Draw();
    h3->Draw("SAME");
    auto legend1 = new TLegend(0.7,0.7,0.48,0.9);
    legend1->AddEntry(h3,"Source","l");
    legend1->AddEntry(h4,"Without source","l");
    legend1->Draw();
    
    image = "2fibers_Channel_01.png";
    c2->SaveAs(image.c_str());
    
    /*TCanvas *c3 = new TCanvas("Charge spectra without source","c3",10,10,1200,800);
    h2->SetLineColor(kBlack);
    h4->Draw();
    h2->Draw("SAME");
    
    auto legend2 = new TLegend(0.7,0.7,0.48,0.9);
    legend2->AddEntry(h2,"Ch1 -no source","l");
    legend2->AddEntry(h4,"Ch4 - no source","l");
    legend2->Draw();
    
    image = "2fibers_Channels_without_source.png";
    c3->SaveAs(image.c_str());		
   
   TCanvas *c4 = new TCanvas("Charge spectra with source","c4",10,10,1200,800);
    h1->SetLineColor(kBlack);
    h3->Draw();
    h1->Draw("SAME");
    
    auto legend3 = new TLegend(0.7,0.7,0.48,0.9);
    legend3->AddEntry(h1,"Ch1 - source","l");
    legend3->AddEntry(h3,"Ch4 - source","l");
    legend3->Draw();
    
    image = "2fibers_Channels_with_source.png";
    c4->SaveAs(image.c_str());		
   */
   
    return;
}
