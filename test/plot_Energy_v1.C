#include <math.h>
#include "PhysicsTools/Utilities/macros/setTDRStyle_v2.C"
#include "CMS_lumi.C"

void MakePlots_PU(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend);
void MakePlots_PU_wPFA2SF(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend);

void drawTPinPU(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection);
void drawDiffIeta(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection);
void drawDiffEt(TTree *t1, TTree *t2, TString det, TString name);
void drawEt2D(TTree *t1, TTree *t2, TString det, TString name);
void compareTPIeta_RHbased(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&mu_ratio, TString selection);
void compareTPIeta_TPbased(TString title, TTree *t1, TGraphErrors *&mu_ratio, TString selection);
void MakePlots_PFA2SF(TChain *t1, TChain *t2, TChain *t3);

TString hep17 = "(ieta<=28 && ieta>=17 && iphi>=63 && iphi<=66)";
TString nhep17 = "!(ieta<=29 && ieta>=17 && iphi>=63 && iphi<=66) * (abs(ieta)<=28 && abs(ieta)>=17)";
TString hb = "(abs(ieta)<=16)";
TString hf = "(abs(ieta)>28)";
TString mode = "phase3";
int ietaBin = 57;

Double_t CrystalBall(Double_t *x, Double_t *par) {
  return ROOT::Math::crystalball_function(x[0], par[0], par[1], par[2], par[3]);
}

void plot_Energy_v1(){

  setTDRStyle();
  gROOT->ForceStyle();

  //TFile *f =  new TFile("analyze.root", "open");
  TChain *t1 =  new TChain("compareReemulRecoSeverity9/matches");
  TChain *t2 =  new TChain("compareRawRecoSeverity9/matches");
  TChain *t3 =  new TChain("compareRawRecoSeverity9/tps");

//PFA2 
//  t1->Add("analyze_2023May12_PFA1p.root");
  t1->Add("/eos/uscms/store/user/tkwon/HCAL/analyze_2023Mar02_phaseP6ns_2TS_0.root");

//PFA1p
//  t2->Add("analyze_2023May12_PFA1p.root");
  t2->Add("/eos/uscms/store/user/tkwon/HCAL/analyze_2023Mar02_phaseP6ns_2TS_0.root");

//PFA1p vs PFA2 comparison event-by-event
//  t2->Add("analyze_2022Nov09.root");
  t3->Add("/eos/uscms/store/user/tkwon/HCAL/analyze_2023May30_phaseP6ns_2TS_*.root");

  TString m = "M0 M2 M3";

//  gStyle->SetOptStat(0);
//  gStyle->SetTitleFontSize(.02);
  gStyle->SetTitleXSize(100);
//  gStyle->SetTitleX(.15);
//  gStyle->SetTitleYOffset(1.5);
  gStyle->SetTitleYSize(100);
//  gStyle->SetTitleH(.07);
  gStyle->SetPadBottomMargin(.2);
  gStyle->SetPadLeftMargin(.15);
  gStyle->SetPadRightMargin(.15);
  gStyle->SetPadTopMargin(.1);
  gStyle->SetLineWidth(3);
//  gStyle->SetTitleFont(43);


//  drawDiffEt(t1, t2, hb, "HB");
//  drawDiffEt(t1, t2, "("+hep17 + "|" + nhep17 +")", "HE");
//  drawDiffEt(t1, t2, hf, "HF");

  cout<<t1->GetEntries()<<endl;
  cout<<t2->GetEntries()<<endl;
  MakePlots_PU(t1, t2, "(RH_energyM2 > 10. && RH_energyM2 < 128. && TP_energy > 1.)", "highE", "128 GeV > E_{T, RH} > 10");
  MakePlots_PU(t1, t2, "(RH_energyM2 < 10. && RH_energyM2 > 0.5 && TP_energy > 1.0)", "lowE", "10 GeV > E_{T, RH} > 0.5");
//  MakePlots_wPFA2SF(t1, t2, "(TP_energy < 128.0 && TP_energy > 10.0)", "highE", "[10, 128)");
//  MakePlots_wPFA2SF(t1, t2, "(TP_energy < 10.0 && TP_energy > 1.0)", "lowE", "[0, 10)");

}

void MakePlots_PFA2SF(TChain *t1, TChain *t2, TChain *t3){

  TGraphErrors *mu1_PFA2, *mu1_PFA1p, *mu1_ratio;
  TGraphErrors *mu2_PFA2, *mu2_PFA1p, *mu2_ratio;
  TGraphErrors *mu3_PFA2, *mu3_PFA1p, *mu3_ratio;
  TGraphErrors *mu4_PFA2, *mu4_PFA1p, *mu4_ratio;
  TGraphErrors *mu5_PFA2, *mu5_PFA1p, *mu5_ratio;
  TGraphErrors *mu6_PFA2, *mu6_PFA1p, *mu6_ratio;
  TGraphErrors *mu7_PFA2, *mu7_PFA1p, *mu7_ratio;
  TGraphErrors *mu8_PFA2, *mu8_PFA1p, *mu8_ratio;
  TGraphErrors *mu9_PFA2, *mu9_PFA1p, *mu9_ratio;
  TGraphErrors *mu10_PFA2, *mu10_PFA1p, *mu10_ratio;
  TGraphErrors *mu11_PFA2, *mu11_PFA1p, *mu11_ratio;
  TGraphErrors *mu12_PFA2, *mu12_PFA1p, *mu12_ratio;
  TGraphErrors *mu13_PFA2, *mu13_PFA1p, *mu13_ratio;

//TP by TP comparison
  compareTPIeta_TPbased("EtBin1", t3, mu1_ratio, "&& et_hw < 10.0 && et_hw > 1.0 && et_emu > 1.0");
  compareTPIeta_TPbased("EtBin2", t3, mu2_ratio, "&& et_hw < 10.0 && et_hw > 6.0 && et_emu > 1.0");
  compareTPIeta_TPbased("EtBin3", t3, mu3_ratio, "&& et_hw < 128.0 && et_hw > 10.0 && et_emu > 1.0");

//use RH as a proxy for TP comparison
//  compareTPIeta_RHbased("EtBin1", t1, t2, mu1_PFA2, mu1_PFA1p, mu1_ratio, "&& TP_energy < 6.0 && TP_energy > 0.5 && RH_energyM2 > 0.3");
//  compareTPIeta_RHbased("EtBin2", t1, t2, mu2_PFA2, mu2_PFA1p, mu2_ratio, "&& TP_energy < 10.0 && TP_energy > 6.0 && RH_energyM2 > 0.3");
//  compareTPIeta_RHbased("EtBin3", t1, t2, mu3_PFA2, mu3_PFA1p, mu3_ratio, "&& TP_energy < 128.0 && TP_energy > 10.0");

  TCanvas *c1 = new TCanvas("c1", "c1", 4000, 3200);
  c1->cd();

  mu1_ratio->Draw("AP");
  mu1_ratio->SetMarkerStyle(8);
  mu1_ratio->SetMarkerSize(4);
  mu1_ratio->SetMarkerColor(kBlack);
  mu1_ratio->SetLineColor(kBlack);
  mu1_ratio->SetTitle(";i#eta;PFA1'/PFA2");

  mu1_ratio->GetXaxis()->SetRangeUser(0.5, (float)(ietaBin+1)/2.);
  mu1_ratio->GetYaxis()->SetRangeUser(0.5, 1.5);

  mu2_ratio->Draw("P SAME");
  mu2_ratio->SetMarkerStyle(8);
  mu2_ratio->SetMarkerSize(4);
  mu2_ratio->SetMarkerColor(kBlue);
  mu2_ratio->SetLineColor(kBlue);

  mu3_ratio->Draw("P SAME");
  mu3_ratio->SetMarkerStyle(8);
  mu3_ratio->SetMarkerSize(4);
  mu3_ratio->SetMarkerColor(kRed);
  mu3_ratio->SetLineColor(kRed);

//  mu4_ratio->Draw("P SAME");
//  mu4_ratio->SetMarkerStyle(8);
//  mu4_ratio->SetMarkerSize(4);
//  mu4_ratio->SetMarkerColor(kGreen+2);

  mu1_ratio->Print();
  mu2_ratio->Print();
  mu3_ratio->Print();
//  mu4_ratio->Print();

  TLegend *legend_mu = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_mu->SetFillStyle(0);
  legend_mu->AddEntry(mu1_ratio, "0.5 < E_{T, TP} < 6", "p");
  legend_mu->AddEntry(mu2_ratio, "6 < E_{T, TP} < 10", "p");
  legend_mu->AddEntry(mu3_ratio, "10 < E_{T, TP} < 30", "p");
//  legend_mu->AddEntry(mu4_ratio, "30 < E_{T, TP} < 128", "p");

  legend_mu->SetLineColor(kWhite);
  legend_mu->SetBorderSize(0);
  legend_mu->SetTextFont(43);
  legend_mu->Draw();

  c1->Print("plots/PFA2PFA1p_SFs.png");

}

//Make Scale & Resolution in the function of PU
void MakePlots_PU(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend){

  TGraphErrors *mu1_PFA2, *mu1_PFA1p;
  TGraphErrors *mu2_PFA2, *mu2_PFA1p;
  TGraphErrors *mu3_PFA2, *mu3_PFA1p;
  TGraphErrors *mu4_PFA2, *mu4_PFA1p;

  TGraphErrors *sigma1_PFA2, *sigma1_PFA1p;
  TGraphErrors *sigma2_PFA2, *sigma2_PFA1p;
  TGraphErrors *sigma3_PFA2, *sigma3_PFA1p;
  TGraphErrors *sigma4_PFA2, *sigma4_PFA1p;

  drawTPinPU("lowPU_" + tag, t1, t2, mu1_PFA2, mu1_PFA1p, sigma1_PFA2, sigma1_PFA1p, "&& (nVtx > 0 && nVtx < 25) && RH_energyM2 > 0.3 && " + selection);
  drawTPinPU("midPU_" + tag, t1, t2, mu2_PFA2, mu2_PFA1p, sigma2_PFA2, sigma2_PFA1p, "&& (nVtx > 25 && nVtx < 50) && RH_energyM2 > 0.3 && " + selection);
  drawTPinPU("highPU_" + tag, t1, t2, mu3_PFA2, mu3_PFA1p, sigma3_PFA2, sigma3_PFA1p, "&& (nVtx > 50 && nVtx < 200) && RH_energyM2 > 0.3 && " + selection);

  TGraphErrors *musigma1_PFA1p = (TGraphErrors *) mu1_PFA1p->Clone();
  TGraphErrors *musigma2_PFA1p = (TGraphErrors *) mu2_PFA1p->Clone();
  TGraphErrors *musigma3_PFA1p = (TGraphErrors *) mu3_PFA1p->Clone();
//  TGraphErrors *musigma4_PFA1p = (TGraphErrors *) mu4_PFA1p->Clone();

  TGraphErrors *musigma1_PFA2 = (TGraphErrors *) mu1_PFA2->Clone();
  TGraphErrors *musigma2_PFA2 = (TGraphErrors *) mu2_PFA2->Clone();
  TGraphErrors *musigma3_PFA2 = (TGraphErrors *) mu3_PFA2->Clone();

  for (int i = 0; i < musigma1_PFA1p->GetN(); ++i){

    double pointX1, pointY1;
    double pointX2, pointY2;
    double pointX3, pointY3;
    double pointX4, pointY4;
    double pointX5, pointY5;
    double pointX6, pointY6;   
    double pointX7, pointY7;   
    double pointX8, pointY8;  
 
    mu1_PFA1p->GetPoint(i, pointX1, pointY1);
    mu2_PFA1p->GetPoint(i, pointX2, pointY2);
    mu3_PFA1p->GetPoint(i, pointX3, pointY3);
//    mu4_PFA1p->GetPoint(i, pointX4, pointY4);
    sigma1_PFA1p->GetPoint(i, pointX5, pointY5);
    sigma2_PFA1p->GetPoint(i, pointX6, pointY6);
    sigma3_PFA1p->GetPoint(i, pointX7, pointY7);
//    sigma4_PFA1p->GetPoint(i, pointX8, pointY8);

    musigma1_PFA1p->SetPoint(i, pointX1, pointY5/pointY1);
    musigma2_PFA1p->SetPoint(i, pointX2, pointY6/pointY2);
    musigma3_PFA1p->SetPoint(i, pointX3, pointY7/pointY3);
//    musigma4_PFA1p->SetPoint(i, pointX4, pointY8/pointY4);

    musigma1_PFA1p->SetPointError(i, 0, pointY5/pointY1*sqrt(pow(mu1_PFA1p->GetErrorY(i)/pointY1, 2) + pow(sigma1_PFA1p->GetErrorY(i)/pointY5, 2)));
    musigma2_PFA1p->SetPointError(i, 0, pointY6/pointY2*sqrt(pow(mu2_PFA1p->GetErrorY(i)/pointY2, 2) + pow(sigma2_PFA1p->GetErrorY(i)/pointY6, 2)));
    musigma3_PFA1p->SetPointError(i, 0, pointY7/pointY3*sqrt(pow(mu3_PFA1p->GetErrorY(i)/pointY3, 2) + pow(sigma3_PFA1p->GetErrorY(i)/pointY7, 2))); 
//    musigma3_PFA1p->SetPointError(i, 0, pointY8/pointY4*sqrt(pow(mu4_PFA1p->GetErrorY(i)/pointY4, 2) + pow(sigma4_PFA1p->GetErrorY(i)/pointY8, 2))); 
  cout<<"ieta: "<<pointX1<<", "<<pointY1<<", ";
  }
  cout<<endl;

  for (int i = 0; i < musigma1_PFA2->GetN(); ++i){

    double pointX1, pointY1;
    double pointX2, pointY2;
    double pointX3, pointY3;
    double pointX4, pointY4;
    double pointX5, pointY5;
    double pointX6, pointY6;   
    double pointX7, pointY7;   
    double pointX8, pointY8;  
 
    mu1_PFA2->GetPoint(i, pointX1, pointY1);
    mu2_PFA2->GetPoint(i, pointX2, pointY2);
    mu3_PFA2->GetPoint(i, pointX3, pointY3);
//    mu4_PFA2->GetPoint(i, pointX4, pointY4);
    sigma1_PFA2->GetPoint(i, pointX5, pointY5);
    sigma2_PFA2->GetPoint(i, pointX6, pointY6);
    sigma3_PFA2->GetPoint(i, pointX7, pointY7);
//    sigma4_PFA2->GetPoint(i, pointX8, pointY8);

    musigma1_PFA2->SetPoint(i, pointX1, pointY5/pointY1);
    musigma2_PFA2->SetPoint(i, pointX2, pointY6/pointY2);
    musigma3_PFA2->SetPoint(i, pointX3, pointY7/pointY3);
//    musigma4_PFA2->SetPoint(i, pointX4, pointY8/pointY4);

    musigma1_PFA2->SetPointError(i, 0, pointY5/pointY1*sqrt(pow(mu1_PFA2->GetErrorY(i)/pointY1, 2) + pow(sigma1_PFA2->GetErrorY(i)/pointY5, 2)));
    musigma2_PFA2->SetPointError(i, 0, pointY6/pointY2*sqrt(pow(mu2_PFA2->GetErrorY(i)/pointY2, 2) + pow(sigma2_PFA2->GetErrorY(i)/pointY6, 2)));
    musigma3_PFA2->SetPointError(i, 0, pointY7/pointY3*sqrt(pow(mu3_PFA2->GetErrorY(i)/pointY3, 2) + pow(sigma3_PFA2->GetErrorY(i)/pointY7, 2))); 
//    musigma3_PFA2->SetPointError(i, 0, pointY8/pointY4*sqrt(pow(mu4_PFA2->GetErrorY(i)/pointY4, 2) + pow(sigma4_PFA2->GetErrorY(i)/pointY8, 2))); 

  cout<<"ieta: "<<pointX1<<", "<<pointY1<<", ";
  }
  cout<<endl;


  TFile *f = new TFile("PFA1p_"+tag+".root", "RECREATE");

  mu1_PFA1p->Write();
  mu2_PFA1p->Write();
  mu3_PFA1p->Write();
//  mu4_PFA1p->Write();

  musigma1_PFA1p->Write();
  musigma2_PFA1p->Write();
  musigma3_PFA1p->Write();
//  musigma4_PFA1p->Write();

  f->Close();

  TFile *f2 = new TFile("PFA2_" + tag + ".root", "RECREATE");

  mu1_PFA2->Write();
  mu2_PFA2->Write();
  mu3_PFA2->Write();
//  mu4_PFA2->Write();

  musigma1_PFA2->Write();
  musigma2_PFA2->Write();
  musigma3_PFA2->Write();
//  musigma4_PFA2->Write();

  f2->Close();

  TCanvas *c_mu = new TCanvas("c_mu_" + tag, "c_mu_" + tag, 4000, 2000);
//  c_mu->SetGrid();
  c_mu->cd();
//  TPad *pad1_mu = new TPad("pad1_mu", "pad1_mu", 0, 0.3, 1, 1);
//  TPad *pad2_mu = new TPad("pad2_mu", "pad2_mu", 0, 0, 1, 0.3);

//  pad1_mu->SetBottomMargin(0);
//  pad2_mu->SetTopMargin(0);

//  pad1_mu->Draw();
//  pad2_mu->Draw();
//  pad1_mu->cd();


  mu1_PFA1p->Draw("AP E0");
  mu1_PFA1p->SetMarkerStyle(8);
  mu1_PFA1p->SetMarkerSize(3);
  mu1_PFA1p->SetMarkerColor(kBlue+1);
  mu1_PFA1p->SetLineColor(kBlue+1);
  mu1_PFA1p->SetTitle(";i#eta;#mu(E_{T, TP}/E_{T, RH})");
  mu1_PFA1p->GetYaxis()->SetLabelSize(85);
  mu1_PFA1p->GetXaxis()->SetLabelSize(85);
//  mu1_PFA1p->SetTextFont(42);
//  mu1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  mu1_PFA1p->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  mu1_PFA1p->GetYaxis()->SetRangeUser(0.5, 1.5);
  //g_mean9->SetMarkerSize(2);

  mu2_PFA1p->Draw("P E0 SAME");
  mu2_PFA1p->SetMarkerStyle(21);
  mu2_PFA1p->SetMarkerSize(3);
  mu2_PFA1p->SetMarkerColor(kGreen+2);
  mu2_PFA1p->SetLineColor(kGreen+2);
  mu2_PFA1p->SetLineWidth(4);

  mu3_PFA1p->Draw("P E0 SAME");
  mu3_PFA1p->SetMarkerStyle(22);
  mu3_PFA1p->SetMarkerSize(3);
  mu3_PFA1p->SetMarkerColor(kRed);
  mu3_PFA1p->SetLineColor(kRed);
  mu3_PFA1p->SetLineWidth(4);

/*  mu4_PFA1p->Draw("P E0 SAME");
  mu4_PFA1p->SetMarkerStyle(33);
  mu4_PFA1p->SetMarkerSize(3);
  mu4_PFA1p->SetMarkerColor(kYellow+1);
  mu4_PFA1p->SetLineColor(kYellow+1);
  mu4_PFA1p->SetLineWidth(4);
*/
  TLine *l =  new TLine((float)-ietaBin/2, 1, (float)ietaBin/2, 1);

  l->Draw("SAME");
  l->SetLineColor(kBlack);
  l->SetLineWidth(8);
  l->SetLineStyle(9);

  TLegend *legend_mu = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_mu->SetFillStyle(0);
  legend_mu->AddEntry(mu1_PFA1p, "N_{vtx} #in [0, 25)", "p");
  legend_mu->AddEntry(mu2_PFA1p, "N_{vtx} #in [25, 50)", "p");
  legend_mu->AddEntry(mu3_PFA1p, "N_{vtx} #in [50, #infty)", "p");
//  legend_mu->AddEntry(mu4_PFA1p, "N_{vtx} #in [60, #infty)", "p");

  legend_mu->SetLineColor(kWhite);
  legend_mu->SetBorderSize(0);
  legend_mu->SetTextFont(43);
  legend_mu->Draw();

  l->Draw("SAME");

  TPaveText* tbox_mu = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_mu->AddText("E_{T, RH} #in " + t_legend + " GeV");
  tbox_mu->SetFillStyle(0);
  tbox_mu->SetLineWidth(0);
  tbox_mu->SetTextSize(0.04);
  tbox_mu->SetTextFont(42);
  tbox_mu->SetTextAlign(10);
  tbox_mu->Draw();
  
  CMS_lumi(c_mu, 4, 11);

  c_mu->Print("plots/PFA1p_performance_Mu_"+ tag+".png"); 


  TCanvas *c_sigma = new TCanvas("c_sigma_" + tag, "c_sigma_" + tag, 4000, 2000);
//  c_mu->SetGrid();
  c_sigma->cd();
//  TPad *pad1_mu = new TPad("pad1_mu", "pad1_mu", 0, 0.3, 1, 1);
//  TPad *pad2_mu = new TPad("pad2_mu", "pad2_mu", 0, 0, 1, 0.3);

//  pad1_mu->SetBottomMargin(0);
//  pad2_mu->SetTopMargin(0);

//  pad1_mu->Draw();
//  pad2_mu->Draw();
//  pad1_mu->cd();


  musigma1_PFA1p->Draw("AP E0");
  musigma1_PFA1p->SetMarkerStyle(8);
  musigma1_PFA1p->SetMarkerSize(3);
  musigma1_PFA1p->SetMarkerColor(kBlue+1);
  musigma1_PFA1p->SetLineColor(kBlue+1);
  musigma1_PFA1p->SetTitle(";i#eta;#frac{#sigma}{#mu}(E_{T, TP}/E_{T, RH})");
  musigma1_PFA1p->GetYaxis()->SetLabelSize(85);
  musigma1_PFA1p->GetXaxis()->SetLabelSize(85);
//  musigma1_PFA1p->SetTextFont(42);
//  musigma1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  musigma1_PFA1p->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  musigma1_PFA1p->GetYaxis()->SetRangeUser(0.001, 0.25);
  //g_mean9->SetMarkerSize(2);

  musigma2_PFA1p->Draw("P E0 SAME");
  musigma2_PFA1p->SetMarkerStyle(21);
  musigma2_PFA1p->SetMarkerSize(3);
  musigma2_PFA1p->SetMarkerColor(kGreen+2);
  musigma2_PFA1p->SetLineColor(kGreen+2);
  musigma2_PFA1p->SetLineWidth(4);

  musigma3_PFA1p->Draw("P E0 SAME");
  musigma3_PFA1p->SetMarkerStyle(22);
  musigma3_PFA1p->SetMarkerSize(3);
  musigma3_PFA1p->SetMarkerColor(kRed);
  musigma3_PFA1p->SetLineColor(kRed);
  musigma3_PFA1p->SetLineWidth(4);

/*  musigma4_PFA1p->Draw("P E0 SAME");
  musigma4_PFA1p->SetMarkerStyle(33);
  musigma4_PFA1p->SetMarkerSize(3);
  musigma4_PFA1p->SetMarkerColor(kYellow+1);
  musigma4_PFA1p->SetLineColor(kYellow+1);
  musigma4_PFA1p->SetLineWidth(4);
*/
  TLegend *legend_sigma = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_sigma->SetFillStyle(0);
  legend_sigma->AddEntry(musigma1_PFA1p, "N_{vtx} #in [0, 25)", "p");
  legend_sigma->AddEntry(musigma2_PFA1p, "N_{vtx} #in [25, 50)", "p");
  legend_sigma->AddEntry(musigma3_PFA1p, "N_{vtx} #in [50, #infty)", "p");
//  legend_sigma->AddEntry(musigma4_PFA1p, "N_{vtx} #in [60, #infty)", "p");

  legend_sigma->SetLineColor(kWhite);
  legend_sigma->SetBorderSize(0);
  legend_sigma->SetTextFont(43);
  legend_sigma->Draw();

  TPaveText* tbox_sigma = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_sigma->AddText("E_{T, RH} #in " + t_legend +" GeV");
  tbox_sigma->SetFillStyle(0);
  tbox_sigma->SetLineWidth(0);
  tbox_sigma->SetTextSize(0.04);
  tbox_sigma->SetTextFont(42);
  tbox_sigma->SetTextAlign(10);
  tbox_sigma->Draw();
  
  CMS_lumi(c_sigma, 4, 11);

  c_sigma->Print("plots/PFA1p_performance_Sigma_"+tag+".png"); 


  TCanvas *c_PFA2mu = new TCanvas("c_PFA2mu_" + tag, "c_PFA2mu_" + tag, 4000, 2000);
//  c_PFA2mu->SetGrid();
  c_PFA2mu->cd();
//  TPad *pad1_mu = new TPad("pad1_mu", "pad1_mu", 0, 0.3, 1, 1);
//  TPad *pad2_mu = new TPad("pad2_mu", "pad2_mu", 0, 0, 1, 0.3);

//  pad1_mu->SetBottomMargin(0);
//  pad2_mu->SetTopMargin(0);

//  pad1_mu->Draw();
//  pad2_mu->Draw();
//  pad1_mu->cd();


  mu1_PFA1p->Draw("AP E0");
  mu1_PFA1p->SetMarkerStyle(8);
  mu1_PFA1p->SetMarkerSize(3);
  mu1_PFA1p->SetMarkerColorAlpha(kRed, 1.0);
  mu1_PFA1p->SetLineColorAlpha(kRed, 1.0);
  mu1_PFA1p->SetTitle(";i#eta;#mu(E_{T, TP}/E_{T, RH})");
  mu1_PFA1p->GetYaxis()->SetLabelSize(85);
  mu1_PFA1p->GetXaxis()->SetLabelSize(85);
//  mu1_PFA1p->SetTextFont(42);
//  mu1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  mu1_PFA1p->GetXaxis()->SetLimits(-28.5, 28.5);
//  mu1_PFA1p->GetXaxis()->SetRangeUser(-30, 30);

  mu1_PFA1p->GetXaxis()->SetRangeUser(-28.5, 28.5);
  mu1_PFA1p->GetYaxis()->SetRangeUser(0.3, 2.5);
  //g_mean9->SetMarkerSize(2);

//  mu2_PFA1p->Draw("P E0 SAME");
  mu2_PFA1p->SetMarkerStyle(21);
  mu2_PFA1p->SetMarkerSize(3);
  mu2_PFA1p->SetMarkerColorAlpha(kRed, 0.7);
  mu2_PFA1p->SetLineColorAlpha(kRed, 0.7);
  mu2_PFA1p->SetLineWidth(4);

//  mu3_PFA1p->Draw("P E0");
  mu3_PFA1p->SetMarkerStyle(22);
  mu3_PFA1p->SetMarkerSize(3);
  mu3_PFA1p->SetMarkerColorAlpha(kRed, 1.0);
  mu3_PFA1p->SetLineColorAlpha(kRed, 1.0);
  mu3_PFA1p->SetLineWidth(4);

  mu1_PFA2->Draw("P E0 SAME");
  mu1_PFA2->SetMarkerStyle(8);
  mu1_PFA2->SetMarkerSize(3);
  mu1_PFA2->SetMarkerColorAlpha(kBlue+1, 0.4);
  mu1_PFA2->SetLineColorAlpha(kBlue+1, 0.4);
//  mu1_PFA2->SetMarkerColorAlpha(kGreen+2, 1.0);
//  mu1_PFA2->SetLineColorAlpha(kGreen+2, 1.0);
//  mu2_PFA2->Draw("P E0 SAME");
  mu2_PFA2->SetMarkerStyle(21);
  mu2_PFA2->SetMarkerSize(3);
  mu2_PFA2->SetMarkerColorAlpha(kBlue+1, 0.7);
  mu2_PFA2->SetLineColorAlpha(kBlue+1, 0.7);
  mu2_PFA2->SetLineWidth(4);

  mu3_PFA2->Draw("P E0 SAME");
  mu3_PFA2->SetMarkerStyle(22);
  mu3_PFA2->SetMarkerSize(3);
  mu3_PFA2->SetMarkerColorAlpha(kBlue+1, 1.0);
  mu3_PFA2->SetLineColorAlpha(kBlue+1, 1.0);
  mu3_PFA2->SetLineWidth(4);

/*  mu4_PFA2->Draw("P E0 SAME");
  mu4_PFA1p->SetMarkerStyle(33);
  mu4_PFA1p->SetMarkerSize(3);
  mu4_PFA1p->SetMarkerColor(kYellow+1);
  mu4_PFA1p->SetLineColor(kYellow+1);
  mu4_PFA1p->SetLineWidth(4);
*/
  l->Draw("SAME");
  l->SetLineColor(kBlack);
  l->SetLineWidth(8);
  l->SetLineStyle(9);

  TLegend *legend_mu_PFA2 = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_mu_PFA2->SetFillStyle(0);
  legend_mu_PFA2->AddEntry(mu1_PFA1p, "PFA1'", "p");

  legend_mu_PFA2->AddEntry(mu1_PFA1p, "PFA1', N_{vtx} #in [0, 25)", "p");
  legend_mu_PFA2->AddEntry(mu2_PFA1p, "PFA1', N_{vtx} #in [25, 50)", "p");
  legend_mu_PFA2->AddEntry(mu3_PFA1p, "PFA1', N_{vtx} #in [50, #infty)", "p");
//  legend_mu_PFA2->AddEntry(mu1_PFA2, "PFA2 scaled", "p");
//  legend_mu_PFA2->AddEntry(mu3_PFA2, "PFA2", "p");

  legend_mu_PFA2->AddEntry(mu1_PFA2, "PFA2, N_{vtx} #in [0, 25)", "p");
  legend_mu_PFA2->AddEntry(mu2_PFA2, "PFA2, N_{vtx} #in [25, 50)", "p");
  legend_mu_PFA2->AddEntry(mu3_PFA2, "PFA2, N_{vtx} #in [50, #infty)", "p");
//  legend_mu_PFA2->AddEntry(mu4_PFA2, "N_{vtx} #in [60, #infty)", "p");

  legend_mu_PFA2->SetLineColor(kWhite);
  legend_mu_PFA2->SetBorderSize(0);
  legend_mu_PFA2->SetTextFont(43);
  legend_mu_PFA2->Draw();

  TPaveText* tbox_mu_PFA2 = new TPaveText(0.2, 0.64, 0.4, 0.72, "RNDC");
  tbox_mu_PFA2->AddText(t_legend + " GeV");
  tbox_mu_PFA2->SetFillStyle(0);
  tbox_mu_PFA2->SetLineWidth(0);
  tbox_mu_PFA2->SetTextSize(0.04);
  tbox_mu_PFA2->SetTextFont(42);
  tbox_mu_PFA2->SetTextAlign(10);
  tbox_mu_PFA2->Draw();

  TPaveText* tbox2_mu_PFA2 = new TPaveText(0.2, 0.56, 0.4, 0.64, "RNDC");
  tbox2_mu_PFA2->AddText("E_{T, TP} > 1.0 GeV");
  tbox2_mu_PFA2->SetFillStyle(0);
  tbox2_mu_PFA2->SetLineWidth(0);
  tbox2_mu_PFA2->SetTextSize(0.04);
  tbox2_mu_PFA2->SetTextFont(42);
  tbox2_mu_PFA2->SetTextAlign(10);
  tbox2_mu_PFA2->Draw();

  TPaveText* tbox3_mu_PFA2 = new TPaveText(0.2, 0.48, 0.4, 0.56, "RNDC");
  tbox3_mu_PFA2->AddText("E_{T, RH} > 0.3 GeV");
  tbox3_mu_PFA2->SetFillStyle(0);
  tbox3_mu_PFA2->SetLineWidth(0);
  tbox3_mu_PFA2->SetTextSize(0.04);
  tbox3_mu_PFA2->SetTextFont(42);
  tbox3_mu_PFA2->SetTextAlign(10);
//  tbox3_mu_PFA2->Draw();
  
  CMS_lumi(c_PFA2mu, 4, 11);

  c_PFA2mu->Print("plots/Performance_Mu_"+ tag+".png"); 


  TCanvas *c_PFA2sigma = new TCanvas("c_PFA2sigma_" + tag, "c_PFA2sigma_" + tag, 4000, 2000);
//  c_PFA2sigma->SetGrid();
  c_PFA2sigma->cd();
//  TPad *pad1_sigma = new TPad("pad1_sigma", "pad1_sigma", 0, 0.3, 1, 1);
//  TPad *pad2_sigma = new TPad("pad2_sigma", "pad2_sigma", 0, 0, 1, 0.3);

//  pad1_sigma->SetBottomMargin(0);
//  pad2_sigma->SetTopMargin(0);

//  pad1_sigma->Draw();
//  pad2_sigma->Draw();
//  pad1_sigma->cd();

  musigma1_PFA1p->GetXaxis()->SetLimits(-28.5, 28.5);
  musigma1_PFA1p->Draw("AP E0");
  musigma1_PFA1p->SetMarkerStyle(8);
  musigma1_PFA1p->SetMarkerSize(3);
  musigma1_PFA1p->SetMarkerColorAlpha(kRed, .4);
  musigma1_PFA1p->SetLineColorAlpha(kRed, .4);
  musigma1_PFA1p->SetTitle(";i#eta;#frac{#sigma}{#mu}(E_{T, TP}/E_{T, RH})");
  musigma1_PFA1p->GetYaxis()->SetLabelSize(85);
  musigma1_PFA1p->GetXaxis()->SetLabelSize(85);
//  musigma1_PFA1p->SetTextFont(42);
//  musigma1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  musigma1_PFA1p->GetXaxis()->SetLimits((float)-ietaBin/2, (float)ietaBin/2);
  musigma1_PFA1p->GetYaxis()->SetRangeUser(0.001, 1.0);
  //g_mean9->SetMarkerSize(2);

  musigma2_PFA1p->Draw("P E0 SAME");
  musigma2_PFA1p->SetMarkerStyle(21);
  musigma2_PFA1p->SetMarkerSize(3);
  musigma2_PFA1p->SetMarkerColorAlpha(kRed, 0.7);
  musigma2_PFA1p->SetLineColorAlpha(kRed, 0.7);
  musigma2_PFA1p->SetLineWidth(4);

  musigma3_PFA1p->Draw("P E0 SAME");
  musigma3_PFA1p->SetMarkerStyle(22);
  musigma3_PFA1p->SetMarkerSize(3);
  musigma3_PFA1p->SetMarkerColorAlpha(kRed, 1.0);
  musigma3_PFA1p->SetLineColorAlpha(kRed, 1.0);
  musigma3_PFA1p->SetLineWidth(4);

  musigma1_PFA2->Draw("P E0 SAME");
  musigma1_PFA2->SetMarkerStyle(8);
  musigma1_PFA2->SetMarkerSize(3);
  musigma1_PFA2->SetMarkerColorAlpha(kBlue+1, .4);
  musigma1_PFA2->SetLineColorAlpha(kBlue+1, .4);

  musigma2_PFA2->Draw("P E0 SAME");
  musigma2_PFA2->SetMarkerStyle(21);
  musigma2_PFA2->SetMarkerSize(3);
  musigma2_PFA2->SetMarkerColorAlpha(kBlue+1, 0.7);
  musigma2_PFA2->SetLineColorAlpha(kBlue+1, 0.7);
  musigma2_PFA2->SetLineWidth(4);

  musigma3_PFA2->Draw("P E0 SAME");
  musigma3_PFA2->SetMarkerStyle(22);
  musigma3_PFA2->SetMarkerSize(3);
  musigma3_PFA2->SetMarkerColorAlpha(kBlue+1, 1.0);
  musigma3_PFA2->SetLineColorAlpha(kBlue+1, 1.0);
  musigma3_PFA2->SetLineWidth(4);

/*  sigma4_PFA2->Draw("P E0 SAME");
  sigma4_PFA1p->SetMarkerStyle(33);
  sigma4_PFA1p->SetMarkerSize(3);
  sigma4_PFA1p->SetMarkerColor(kYellow+1);
  sigma4_PFA1p->SetLineColor(kYellow+1);
  sigma4_PFA1p->SetLineWidth(4);
*/
//  l->Draw("SAME");
  l->SetLineColor(kBlack);
  l->SetLineWidth(8);
  l->SetLineStyle(9);

  TLegend *legend_sigma_PFA2 = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_sigma_PFA2->SetFillStyle(0);
  legend_sigma_PFA2->AddEntry(musigma1_PFA1p, "PFA1', N_{vtx} #in [0, 25)", "p");
  legend_sigma_PFA2->AddEntry(musigma2_PFA1p, "PFA1', N_{vtx} #in [25, 50)", "p");
  legend_sigma_PFA2->AddEntry(musigma3_PFA1p, "PFA1', N_{vtx} #in [50, #infty)", "p");
  legend_sigma_PFA2->AddEntry(musigma1_PFA2, "PFA2, N_{vtx} #in [0, 25)", "p");
  legend_sigma_PFA2->AddEntry(musigma2_PFA2, "PFA2, N_{vtx} #in [25, 50)", "p");
  legend_sigma_PFA2->AddEntry(musigma3_PFA2, "PFA2, N_{vtx} #in [50, #infty)", "p");
//  legend_sigma_PFA2->AddEntry(sigma4_PFA2, "N_{vtx} #in [60, #infty)", "p");

  legend_sigma_PFA2->SetLineColor(kWhite);
  legend_sigma_PFA2->SetBorderSize(0);
  legend_sigma_PFA2->SetTextFont(43);
  legend_sigma_PFA2->Draw();

//  l->Draw("SAME");

  TPaveText* tbox_sigma_PFA2 = new TPaveText(0.2, 0.64, 0.4, 0.72, "RNDC");
  tbox_sigma_PFA2->AddText(t_legend + " GeV");
  tbox_sigma_PFA2->SetFillStyle(0);
  tbox_sigma_PFA2->SetLineWidth(0);
  tbox_sigma_PFA2->SetTextSize(0.04);
  tbox_sigma_PFA2->SetTextFont(42);
  tbox_sigma_PFA2->SetTextAlign(10);
  tbox_sigma_PFA2->Draw();
 
  TPaveText* tbox2_sigma_PFA2 = new TPaveText(0.2, 0.56, 0.4, 0.64, "RNDC");
  tbox2_sigma_PFA2->AddText("E_{T, TP} > 1.0 GeV");
  tbox2_sigma_PFA2->SetFillStyle(0);
  tbox2_sigma_PFA2->SetLineWidth(0);
  tbox2_sigma_PFA2->SetTextSize(0.04);
  tbox2_sigma_PFA2->SetTextFont(42);
  tbox2_sigma_PFA2->SetTextAlign(10);
  tbox2_sigma_PFA2->Draw();

  TPaveText* tbox3_sigma_PFA2 = new TPaveText(0.2, 0.48, 0.4, 0.56, "RNDC");
  tbox3_sigma_PFA2->AddText("E_{T, RH} > 0.3 GeV");
  tbox3_sigma_PFA2->SetFillStyle(0);
  tbox3_sigma_PFA2->SetLineWidth(0);
  tbox3_sigma_PFA2->SetTextSize(0.04);
  tbox3_sigma_PFA2->SetTextFont(42);
  tbox3_sigma_PFA2->SetTextAlign(10);
//  tbox3_sigma_PFA2->Draw();
 
  CMS_lumi(c_PFA2sigma, 4, 11);

  c_PFA2sigma->Print("plots/Performance_Sigma_"+ tag+".png"); 


}

//Make Scale with PFA2 SF
void MakePlots_wPFA2SF(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend){

  TGraphErrors *mu1_PFA2, *mu1_PFA1p;
  TGraphErrors *mu2_PFA2, *mu2_PFA1p;

  TGraphErrors *sigma1_PFA2, *sigma1_PFA1p;
  TGraphErrors *sigma2_PFA2, *sigma2_PFA1p;

  Double_t SFs_lowEt[28] = {
//0.849111,0.867898,0.859763,0.85979,0.859604,0.866086,0.873119,0.864557,0.878112,0.883406,0.885876,0.880825,0.888808,0.888329,0.860672,0.843137,0.940367,0.938778,0.965347,0.962491,0.975012,0.966371,0.962229,0.944891,0.945013,0.91148,0.973893,0.728643,
0.826812,0.844321,0.837029,0.836978,0.836718,0.843171,0.849735,0.841512,0.854298,0.858982,0.861287,0.856494,0.863794,0.863232,0.837966,0.821827,0.910376,0.908766,0.932646,0.930139,0.940966,0.933504,0.929901,0.914913,0.915212,0.886068,0.940299,0.714692,
//0.763718, 0.76942, 0.772677, 0.770556, 0.769595, 0.774324, 0.779436, 0.768836, 0.778523, 0.778271, 0.775974, 0.766902, 0.767275, 0.762328, 0.730827, 0.716761, 0.842161, 0.833367, 0.852386, 0.850423, 0.849795, 0.835663, 0.823901, 0.794035, 0.791369, 0.744608, 0.83589, 0.580481, 
  };
  Double_t SFs_midEt[28] = {
//0.886588,0.903883,0.907548,0.90644,0.912769,0.926852,0.936476,0.923212,0.945647,0.952564,0.95519,0.956761,0.96958,0.97597,0.967375,0.940895,0.982577,0.981288,0.994008,0.982565,1.00789,1.00333,1.00556,0.986957,0.986364,0.965789,0.995455,0.935366,
0.881094,0.896274,0.89911,0.899217,0.903927,0.91558,0.924665,0.91321,0.931125,0.936957,0.938546,0.940867,0.950739,0.956053,0.948794,0.927011,0.958605,0.957239,0.971074,0.958285,0.976053,0.972333,0.975556,0.961304,0.964091,0.947895,0.975909,0.920366,
//0.873166, 0.890189, 0.894107, 0.895415, 0.89805, 0.903563, 0.910846, 0.908902, 0.923284, 0.925241, 0.929395, 0.931077, 0.939857, 0.943558, 0.941334, 0.91728, 0.948294, 0.951202, 0.956401, 0.958107, 0.95098, 0.95343, 0.964179, 0.957958, 0.952035, 0.943954, 0.937916, 0.898559, 
  };
  Double_t SFs_highEt[28] = {
//0.920566,0.935942,0.941777,0.942126,0.950459,0.961558,0.970614,0.962329,0.978571,0.988421,0.998718,0.983838,0.99557,1.01034,1.00305,0.968824,0.994144,1.00549,1.00818,0.996429,1.01667,1.0125,1.01,1.01667,1,1.00556,0.95,0.9625,
0.915377,0.92893,0.931605,0.934816,0.939885,0.950528,0.959561,0.951493,0.964955,0.972632,0.982487,0.970101,0.978924,0.989828,0.983902,0.955529,0.977523,0.985427,0.986455,0.981429,0.981667,0.98625,0.987,0.993333,0.9825,0.988333,0.951667,0.935,
//0.912069, 0.927928, 0.931831, 0.9228, 0.930444, 0.948214, 0.955979, 0.942658, 0.956531, 0.951276, 0.962527, 0.964139, 0.977598, 0.979592, 0.97327, 0.955279, 0.968884, 0.975863, 0.977868, 0.97833, 0.99375, 0.937008, 0.981168, 0.977961, 1, 0.99449, 0.9875, 0.942857, 
  };


  Int_t ieta_, ieta;
  Int_t tp_soi_, tp_soi;
  Double_t nVtx_, nVtx;
  Double_t TP_energy_, TP_energy;
  Double_t RH_energyM2_, RH_energyM2;

  TTree *t = new TTree("matches", "matches");

  t1->SetBranchAddress("TP_energy", &TP_energy_);
  t1->SetBranchAddress("RH_energyM2", &RH_energyM2_);
  t1->SetBranchAddress("ieta", &ieta_);
  t1->SetBranchAddress("nVtx", &nVtx_);
  t1->SetBranchAddress("tp_soi", &tp_soi_);

  t->Branch("TP_energy", &TP_energy);
  t->Branch("RH_energyM2", &RH_energyM2);
  t->Branch("ieta", &ieta);
  t->Branch("nVtx", &nVtx);
  t->Branch("tp_soi", &tp_soi);

  for (int i=0; i < t1->GetEntries(); ++i){

    if (i%100000 == 0)  cout<<100.*i/t1->GetEntries()<<"\%"<<"("<<i<<"/"<<t1->GetEntries()<<")"<<" is done..."<<endl;

    t1->GetEntry(i);
    if (TP_energy_ > 0.5 && TP_energy_ < 6.) TP_energy = TP_energy_*SFs_lowEt[abs(ieta_)];
    else if (TP_energy_ > 6.0 && TP_energy_ < 10.) TP_energy = TP_energy_*SFs_midEt[abs(ieta_)];
    else if (TP_energy_ > 10. && TP_energy_ < 128.) TP_energy = TP_energy_*SFs_highEt[abs(ieta_)];
    else TP_energy = TP_energy_;
    RH_energyM2 = RH_energyM2_;
    ieta = ieta_;
    tp_soi = tp_soi_;
    nVtx = nVtx_;

    t->Fill();
  }

  TFile f_test("test.root","recreate");

  t->Write();

  f_test.Close();

  TFile f_scaled("test.root","open");

  TTree *t_scaled = (TTree *)f_scaled.Get("matches");

  t_scaled->Print(); 

  drawTPinPU(tag, t_scaled, t2, mu1_PFA2, mu1_PFA1p, sigma1_PFA2, sigma1_PFA1p, "&& RH_energyM2 > 0.3 && " + selection);
  drawTPinPU(tag, t1, t2, mu2_PFA2, mu2_PFA1p, sigma2_PFA2, sigma2_PFA1p, "&& RH_energyM2 > 0.3 && " + selection);

  TCanvas *c_PFA2mu = new TCanvas("c_PFA2mu_" + tag, "c_PFA2mu_" + tag, 4000, 2000);
  c_PFA2mu->cd();

  mu1_PFA1p->Draw("AP E0");
  mu1_PFA1p->SetMarkerStyle(8);
  mu1_PFA1p->SetMarkerSize(3);
  mu1_PFA1p->SetMarkerColorAlpha(kRed, 1.0);
  mu1_PFA1p->SetLineColorAlpha(kRed, 1.0);
  mu1_PFA1p->SetTitle(";i#eta;#mu(E_{T, TP}/E_{T, RH})");
  mu1_PFA1p->GetYaxis()->SetLabelSize(85);
  mu1_PFA1p->GetXaxis()->SetLabelSize(85);
//  mu1_PFA1p->SetTextFont(42);
//  mu1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  mu1_PFA1p->GetXaxis()->SetLimits(-28.5, 28.5);
//  mu1_PFA1p->GetXaxis()->SetRangeUser(-30, 30);

  mu1_PFA1p->GetXaxis()->SetRangeUser(-28.5, 28.5);
  mu1_PFA1p->GetYaxis()->SetRangeUser(0.3, 2.5);
  //g_mean9->SetMarkerSize(2);

  mu1_PFA2->Draw("P E0 SAME");
  mu1_PFA2->SetMarkerStyle(8);
  mu1_PFA2->SetMarkerSize(3);
  mu1_PFA2->SetMarkerColorAlpha(kGreen+2, 1.0);
  mu1_PFA2->SetLineColorAlpha(kGreen+2, 1.0);
  mu2_PFA2->Draw("P E0 SAME");
  mu2_PFA2->SetMarkerStyle(21);
  mu2_PFA2->SetMarkerSize(3);
  mu2_PFA2->SetMarkerColorAlpha(kBlue+1, 1.0);
  mu2_PFA2->SetLineColorAlpha(kBlue+1, 1.0);
  mu2_PFA2->SetLineWidth(4);

  TLine *l =  new TLine((float)-ietaBin/2, 1, (float)ietaBin/2, 1);

  l->Draw("SAME");
  l->SetLineColor(kBlack);
  l->SetLineWidth(8);
  l->SetLineStyle(9);

  TLegend *legend_mu_PFA2 = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_mu_PFA2->SetFillStyle(0);
  legend_mu_PFA2->AddEntry(mu1_PFA1p, "PFA1'", "p");
  legend_mu_PFA2->AddEntry(mu1_PFA2, "PFA2 scaled", "p");
  legend_mu_PFA2->AddEntry(mu2_PFA2, "PFA2", "p");
  legend_mu_PFA2->Draw();

  TPaveText* tbox_mu_PFA2 = new TPaveText(0.2, 0.64, 0.4, 0.72, "RNDC");
  tbox_mu_PFA2->AddText(t_legend + " GeV");
  tbox_mu_PFA2->SetFillStyle(0);
  tbox_mu_PFA2->SetLineWidth(0);
  tbox_mu_PFA2->SetTextSize(0.04);
  tbox_mu_PFA2->SetTextFont(42);
  tbox_mu_PFA2->SetTextAlign(10);
  tbox_mu_PFA2->Draw();

  TPaveText* tbox2_mu_PFA2 = new TPaveText(0.2, 0.56, 0.4, 0.64, "RNDC");
  tbox2_mu_PFA2->AddText("E_{T, TP} > 1.0 GeV");
  tbox2_mu_PFA2->SetFillStyle(0);
  tbox2_mu_PFA2->SetLineWidth(0);
  tbox2_mu_PFA2->SetTextSize(0.04);
  tbox2_mu_PFA2->SetTextFont(42);
  tbox2_mu_PFA2->SetTextAlign(10);
  tbox2_mu_PFA2->Draw();

  TPaveText* tbox3_mu_PFA2 = new TPaveText(0.2, 0.48, 0.4, 0.56, "RNDC");
  tbox3_mu_PFA2->AddText("E_{T, RH} > 0.3 GeV");
  tbox3_mu_PFA2->SetFillStyle(0);
  tbox3_mu_PFA2->SetLineWidth(0);
  tbox3_mu_PFA2->SetTextSize(0.04);
  tbox3_mu_PFA2->SetTextFont(42);
  tbox3_mu_PFA2->SetTextAlign(10);
//  tbox3_mu_PFA2->Draw();
  
  CMS_lumi(c_PFA2mu, 4, 11);

  c_PFA2mu->Print("plots/Performance_Mu_"+ tag+".png"); 

}


void drawTPinPU(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection){    

  t1->Print(); 

    TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();
    t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta7"+rh_en+Form("(%d, %f, %f, 400, 0, 20.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
    t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta8"+rh_en+Form("(%d, %f, %f, 400, 0, 20.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");

/*    if (!title.Contains("highE")){
      t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta7"+rh_en+Form("(%d, %f, %f, 100, 0, 2.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
      t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta8"+rh_en+Form("(%d, %f, %f, 100, 0, 2.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
    }
    else{
      t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta7"+rh_en+Form("(%d, %f, %f, 100, 0.7, 1.3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
      t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta8"+rh_en+Form("(%d, %f, %f, 100, 0.7, 1.3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
    } 
*/
    TH2F *diffieta7 = (TH2F*)gDirectory->Get("diffieta7"+rh_en);
    TH2F *diffieta8 = (TH2F*)gDirectory->Get("diffieta8"+rh_en);

    TGraphErrors *g_mean7 = new TGraphErrors(ietaBin);
    TGraphErrors *g_mean8 = new TGraphErrors(ietaBin);

    TGraphErrors *g_sigma7 = new TGraphErrors(ietaBin);
    TGraphErrors *g_sigma8 = new TGraphErrors(ietaBin);

    for (int i=1; i < diffieta7->GetNbinsX()+1;++i){

      TString ind; ind.Form("%d",i);

//      gStyle->SetOptFit(0011);
      gStyle->SetOptStat("emr");

      TH1F *h71 = (TH1F *)diffieta7->ProjectionY("h7"+ind, i, i);

      if (h71->GetEntries() > 0){

      TF1 *func = new TF1("fitFunction", "gaus", 0.7, 1.1);
      func->SetParameter(0, h71->Integral());
      func->SetParameter(1, h71->GetMean());
      func->SetParameter(2, 0.1);

//      func->SetParLimits(0, h81->Integral(), h81->Integral());
//      func->SetParLimits(1, 0.4, 1.2);
//      func->SetParLimits(2, 0.01, 0.15);


      TCanvas *c7 = new TCanvas("c7_"+ind, "c_"+ind, 2000, 2000);
      c7->SetLogy();
//      h71->Fit(func, "B");
      h71->SetTitle("");
      h71->GetXaxis()->SetTitle("E_{T, TP}/E_{T, RH}");
      h71->GetYaxis()->SetTitle("events");

//      h71->GetXaxis()->SetRangeUser(0, 3);
//      h71->GetXaxis()->SetLimits(0, 3);
      h71->Draw();

      double tail = h71->Integral(h71->FindBin(5), h71->GetNbinsX());

       TPaveText* tbox = new TPaveText(0.18, 0.85, 0.35, 0.95, "RNDC");
//        TPaveText* tbox = new TPaveText(0.65, 0.75, 0.80, 0.85, "RNDC");
        tbox->AddText(Form("PFA1', ieta = %.0f, tail/total=%.3f", diffieta7->GetXaxis()->GetBinCenter(i), tail/h71->Integral()));
        tbox->SetFillStyle(0);
        tbox->SetLineWidth(0);
        tbox->SetTextSize(0.04);
        tbox->SetTextFont(42);
        tbox->SetTextAlign(10);

//      tbox->Draw();

      h71->SetNdivisions(205);
      c7->Print("ieta/ieta"+ind+"_PFA2_"+title+".png");
      
      TF1 *gFit71 = (TF1 *)h71->GetFunction("gaus");
    
      g_mean7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), h71->GetMean());
      g_sigma7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), h71->GetStdDev());

//       g_mean7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), func->GetParameter(1));
//      g_sigma7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), func->GetParameter(2));

      g_mean7->SetPointError(i, 0, 0);
      g_sigma7->SetPointError(i, 0, 0);
      }


      TH1F *h81 = (TH1F *)diffieta8->ProjectionY("h8"+ind, i, i);
      if (h81->GetEntries() > 0){

      TCanvas *c8 = new TCanvas("c8_"+ind, "c_"+ind, 2000, 2000);
      c8->SetLogy();
//      h81->Fit(func, "B");
      h81->SetTitle("");
      h81->GetXaxis()->SetTitle("E_{T, TP}/E_{T, RH}");
      h81->GetYaxis()->SetTitle("events");

//      h81->GetXaxis()->SetRangeUser(0, 3);
//      h81->GetXaxis()->SetLimits(0, 3);
      h81->Draw();

      double tail = h81->Integral(h81->FindBin(5), h81->GetNbinsX());

       TPaveText* tbox = new TPaveText(0.18, 0.85, 0.35, 0.95, "RNDC");
//        TPaveText* tbox = new TPaveText(0.65, 0.85, 0.80, 0.85, "RNDC");
        tbox->AddText(Form("PFA1', ieta = %.0f, tail/total=%.3f", diffieta8->GetXaxis()->GetBinCenter(i), tail/h81->Integral()));
        tbox->SetFillStyle(0);
        tbox->SetLineWidth(0);
        tbox->SetTextSize(0.04);
        tbox->SetTextFont(42);
        tbox->SetTextAlign(10);

      tbox->Draw();

      h81->SetNdivisions(205);
      c8->Print("ieta/ieta"+ind+"_PFA1p_"+title+".png");
      
      TF1 *gFit81 = (TF1 *)h81->GetFunction("gaus");
    
      g_mean8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetMean());
      g_sigma8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetStdDev());

//       g_mean8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), func->GetParameter(1));
//      g_sigma8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), func->GetParameter(2));

      g_mean8->SetPointError(i, 0, 0);
      g_sigma8->SetPointError(i, 0, 0);

      }

    }

    TGraph *g_mean_ratio =  new TGraph(ietaBin);
    TGraph *g_sigma_ratio =  new TGraph(ietaBin);

    for (int i = 0; i < g_mean7->GetN(); ++i){

    double pointX1, pointY1;
    double pointX2, pointY2;
    double pointX3, pointY3;
    double pointX4, pointY4;
    
    g_mean7->GetPoint(i, pointX1, pointY1);
    g_mean8->GetPoint(i, pointX2, pointY2);
    g_sigma7->GetPoint(i, pointX3, pointY3);
    g_sigma8->GetPoint(i, pointX4, pointY4);

    g_mean_ratio->SetPoint(i, pointX1, pointY2/pointY1);
    g_sigma_ratio->SetPoint(i, pointX3, pointY4/pointY3);

  }

  TLine *l =  new TLine((float)-ietaBin/2, 1, (float)ietaBin/2, 1);

  TCanvas *c7 = new TCanvas("c7", "c7", 4000, 3200);
  c7->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1);
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
  pad1->Draw();
  pad2->Draw();
  pad1->SetGrid();
  pad1->cd();

  g_mean8->Draw("AP");
  g_mean8->SetMarkerStyle(8);
  g_mean8->SetMarkerSize(4);
  g_mean8->SetMarkerColor(kBlack);
  g_mean8->SetTitle(";i#eta;");

  g_mean8->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  g_mean8->GetYaxis()->SetRangeUser(0.1, 2);
  //g_mean9->SetMarkerSize(2);

  g_mean7->Draw("P SAME");
  g_mean7->SetMarkerStyle(107);
  g_mean7->SetMarkerSize(4);
  g_mean7->SetMarkerColor(kBlack);
  g_mean7->SetLineWidth(4);
  l->Draw("SAME");
  l->SetLineColor(kRed);
  l->SetLineWidth(8);
  TLegend *legend7 = new TLegend(0.72,0.78, 0.84, 0.89);
  legend7->SetFillStyle(0);
  legend7->AddEntry(g_mean7, "PFA2 mean", "p");
  legend7->AddEntry(g_mean8, "PFA1' mean", "p");
  legend7->SetLineColor(kWhite);
  //legend7->Draw();

  pad2->cd();
  pad2->SetGrid();
  g_mean_ratio->Draw("AP");
  g_mean_ratio->SetTitle(";;");
  g_mean_ratio->GetYaxis()->SetRangeUser(0.1, 1.5);
  g_mean_ratio->SetMarkerSize(3);
  g_mean_ratio->SetMarkerColor(kBlue);
  l->Draw("SAME");

  c7->Print("plots/Energy_Scale_"+title+".png"); 

  TCanvas *c8 = new TCanvas("c8", "c8", 4000, 3200);
  c8->cd();
  TPad *pad11 = new TPad("pad11", "pad11", 0, 0.3, 1, 1);
  TPad *pad12 = new TPad("pad12", "pad12", 0, 0, 1, 0.3);
  pad11->Draw();
  pad12->Draw();
  pad11->SetGrid();
  pad11->cd();

  g_sigma8->Draw("AP");
  g_sigma8->SetMarkerStyle(8);
  g_sigma8->SetMarkerSize(4);
  g_sigma8->SetMarkerColor(kBlack);
  g_sigma8->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  g_sigma8->GetYaxis()->SetRangeUser(0.01, 0.4);
  g_sigma8->SetTitle(";i#eta;");
  TLegend *legend8 = new TLegend(0.72,0.78, 0.84, 0.89);
  legend8->SetFillStyle(0);
  legend8->AddEntry(g_sigma7, "PFA2 sigma", "p");
  legend8->AddEntry(g_sigma8, "PFA1' sigma", "p");
  legend8->SetLineColor(kWhite);
  //legend8->Draw();
  //g_sigma9->SetMarkerSize(2);

  g_sigma7->Draw("P SAME");
  g_sigma7->SetMarkerStyle(107);
  g_sigma7->SetMarkerSize(4);
  //l->Draw("SAME");


  pad12->cd();
  pad12->SetGrid();
  g_sigma_ratio->Draw("AP");
  g_sigma_ratio->SetTitle(";;");
  g_sigma_ratio->GetYaxis()->SetRangeUser(0.1, 1.5);
  g_sigma_ratio->SetMarkerSize(3);
  g_sigma_ratio->SetMarkerColor(kBlue);
  l->Draw("SAME");

  c8->Print("plots/Energy_Resolution_"+title+".png"); 

  mu_PFA2 = (TGraphErrors *) g_mean7->Clone();
  mu_PFA1p = (TGraphErrors *) g_mean8->Clone();

  sigma_PFA2 = (TGraphErrors *) g_sigma7->Clone();
  sigma_PFA1p = (TGraphErrors *) g_sigma8->Clone();

}

//PFA2 vs PFA1' TP-by-TP comparision
void compareTPIeta_TPbased(TString title, TTree *t1, TGraphErrors *&mu_ratio, TString selection){

  TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();

  t1->Draw("et_hw/et_emu:abs(ieta)>>diffieta1" + rh_en + Form("(%d, %f, %f, 300, 0., 30.)", 28, 0.5, 28.5), "abs(ieta) <= 28 && soi_hw < 255 && soi_emu < 255" + selection, "COLZ");

    TH2F *diffieta1 = (TH2F*)gDirectory->Get("diffieta1"+rh_en);

    TGraphErrors *g_mean1 = new TGraphErrors(28);
    TGraphErrors *g_mean2 = new TGraphErrors(28);
    TGraphErrors *g_mean3 = new TGraphErrors(28);

    for (int i=1; i < diffieta1->GetNbinsX()+1;++i){

      TString ind; ind.Form("%d",i);

      gStyle->SetOptFit(0011);
      TH1F *h71 = (TH1F *)diffieta1->ProjectionY("h7"+ind, i, i);

      Double_t PFA2_mean = 0.1, PFA2_mean_error = 0.1;

      if (h71->GetEntries() > 0){
      TCanvas *c7 = new TCanvas("c7_"+ind, "c_"+ind, 800, 800);
      TF1 *func = new TF1("func", "gaus", 0.7, 1.1);
      func->SetParameter(0, h71->Integral());
      func->SetParameter(1, h71->GetMean());
      func->SetParameter(2, 0.1);

//      h71->Fit("func", "B");
      h71->SetTitle("");
      h71->Draw();
      c7->Print("ieta/ieta"+ind+"_PFA2_"+title+".png");
      
      TF1 *gFit71 = (TF1 *)h71->GetFunction("gaus");
    
      g_mean1->SetPoint(i, diffieta1->GetXaxis()->GetBinCenter(i), h71->GetMean());
      g_mean1->SetPointError(i, 0, h71->GetStdDev()/sqrt(h71->Integral()));

//      g_mean2->SetPoint(i, diffieta2->GetXaxis()->GetBinCenter(i), func->GetParameter(1));
//      g_mean2->SetPointError(i, 0, func->GetParError(1));
 
      PFA2_mean = func->GetParameter(1);
      PFA2_mean_error = func->GetParError(1);

      }

    }

    TCanvas *c1 = new TCanvas("c1", "c1", 4000, 3200);
    c1->cd();

    diffieta1->Draw("COLZ");
    g_mean1->Draw("P SAME");
    g_mean1->SetMarkerStyle(107);
    g_mean1->SetMarkerSize(4);
    g_mean1->SetMarkerColor(kBlack);

    diffieta1->GetYaxis()->SetRangeUser(0.1, 3.);
    diffieta1->SetTitle(";i#eta;PFA1'/PFA2");

    diffieta1->GetXaxis()->SetRangeUser(0, (float)ietaBin/2);
//    gmean1->GetYaxis()->SetRangeUser(0.1, 3);

    c1->Print("plots/PFA1pPFA2_ratio_"+title+".png");

    mu_ratio = (TGraphErrors *) g_mean1->Clone();
}

//PFA2 vs PFA1' with "RH" as a bridge
void compareTPIeta_RHbased(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&mu_ratio, TString selection){

  TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();

  t1->Draw("TP_energy/" + rh_en + ":abs(ieta)>>diffieta1" + rh_en + Form("(%d, %f, %f, 2000, 0., 20.)", 28, 0.5, 28.5), "abs(ieta) <= 28 && tp_soi<255 && RH_energyM2 > 0.3" + selection, "COLZ");
  t2->Draw("TP_energy/" + rh_en + ":abs(ieta)>>diffieta2" + rh_en + Form("(%d, %f, %f, 2000, 0., 20.,)", 28, 0.5, 28.5), "abs(ieta) <= 28 && tp_soi<255 && RH_energyM2 > 0.3" + selection, "COLZ");


    TH2F *diffieta1 = (TH2F*)gDirectory->Get("diffieta1"+rh_en);
    TH2F *diffieta2 = (TH2F*)gDirectory->Get("diffieta2"+rh_en);

    TGraphErrors *g_mean1 = new TGraphErrors(28);
    TGraphErrors *g_mean2 = new TGraphErrors(28);
    TGraphErrors *g_mean3 = new TGraphErrors(28);

    for (int i=1; i < diffieta1->GetNbinsX()+1;++i){

      TString ind; ind.Form("%d",i);

      gStyle->SetOptFit(0011);
      TH1F *h71 = (TH1F *)diffieta1->ProjectionY("h7"+ind, i, i);

      Double_t PFA2_mean = 0.1, PFA2_mean_error = 0.1;

      if (h71->GetEntries() > 0){
      TCanvas *c7 = new TCanvas("c7_"+ind, "c_"+ind, 800, 800);
      TF1 *func = new TF1("func", "gaus", 0.7, 1.1);
      func->SetParameter(0, h71->Integral());
      func->SetParameter(1, h71->GetMean());
      func->SetParameter(2, 0.1);

      h71->Fit("func", "B");
      h71->SetTitle("");
      h71->Draw();
      c7->Print("ieta/ieta"+ind+"_PFA2_"+title+".png");
      
      TF1 *gFit71 = (TF1 *)h71->GetFunction("gaus");
    
//      g_mean1->SetPoint(i, diffieta1->GetXaxis()->GetBinCenter(i), h71->GetMean());
//      g_mean1->SetPointError(i, 0, h71->GetStdDev()/sqrt(h71->Integral()));

      g_mean2->SetPoint(i, diffieta2->GetXaxis()->GetBinCenter(i), func->GetParameter(1));
      g_mean2->SetPointError(i, 0, func->GetParError(1));
 
      PFA2_mean = func->GetParameter(1);
      PFA2_mean_error = func->GetParError(1);

      }

    //func->SetParameters(1e+4, 1, 0.05, 0.02, 10);

      TH1F *h81 = (TH1F *)diffieta2->ProjectionY("h8"+ind, i, i);
      if (h81->GetEntries() > 0){

      TF1 *func = new TF1("fitFunction", "gaus", 0.7, 1.1);
      func->SetParameter(0, h81->Integral());
      func->SetParameter(1, h81->GetMean());
      func->SetParameter(2, 0.1);

//      func->SetParLimits(0, h81->Integral(), h81->Integral());
      func->SetParLimits(1, 0.4, 1.2);
      func->SetParLimits(2, 0.01, 0.15);


      TCanvas *c8 = new TCanvas("c8_"+ind, "c_"+ind, 800, 800);
//      h81->Fit(func, "B");
      h81->SetTitle("");
      h81->Draw();
      c8->Print("ieta/ieta"+ind+"_PFA1p_"+title+".png");

//      TF1 *gFit81 = (TF1 *)h81->GetFunction("fitFunction");     

      g_mean2->SetPoint(i, diffieta2->GetXaxis()->GetBinCenter(i), h81->GetMean());//func->GetParameter(1));
      g_mean2->SetPointError(i, 0, h81->GetStdDev()/sqrt(h81->Integral()));//gFit81->GetParError(1));
      }

//      g_mean3->SetPoint(i, diffieta1->GetXaxis()->GetBinCenter(i), h81->GetMean()/h71->GetMean());//func->GetParameter(1));
//      g_mean3->SetPointError(i, 0, h81->GetMean()/h71->GetMean()*sqrt(pow(h81->GetStdDev()/h81->GetMean(), 2)/h81->Integral() + pow(h71->GetStdDev()/h71->GetMean(), 2)/h71->Integral()));//gFit81->GetParError(1));

      g_mean3->SetPoint(i, diffieta1->GetXaxis()->GetBinCenter(i), h81->GetMean()/PFA2_mean);//func->GetParameter(1));
      g_mean3->SetPointError(i, 0, h81->GetMean()/PFA2_mean*sqrt(pow(h81->GetStdDev()/h81->GetMean(), 2)/h81->Integral() + pow(PFA2_mean_error/PFA2_mean, 2)));//gFit81->GetParError(1));


    }

    TCanvas *c1 = new TCanvas("c1", "c1", 4000, 3200);
    c1->cd();

    diffieta1->Draw("COLZ");
    g_mean1->Draw("P SAME");
    g_mean1->SetMarkerStyle(8);
    g_mean1->SetMarkerSize(4);
    g_mean1->SetMarkerColor(kBlack);
    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(8);
    g_mean2->SetMarkerSize(4);
    g_mean2->SetMarkerColor(kRed);

    diffieta1->GetYaxis()->SetRangeUser(0.1, 3.);
    diffieta1->SetTitle(";i#eta;PFA2");

    diffieta1->GetXaxis()->SetRangeUser(0, (float)ietaBin/2);
//    gmean1->GetYaxis()->SetRangeUser(0.1, 3);

    c1->Print("plots/PFA2_mean_"+title+".png");


    TCanvas *c7 = new TCanvas("c7", "c7", 4000, 3200);
    c7->cd();

    g_mean3->Draw("AP");
    g_mean3->SetTitle(";i#eta;PFA2/PFA1'");
    g_mean3->SetMarkerStyle(8);
    g_mean3->SetMarkerSize(4);
    g_mean3->SetMarkerColor(kBlack);

    g_mean3->GetXaxis()->SetRangeUser(0, (float)ietaBin/2);
//    gmean3->GetYaxis()->SetRangeUser(0.1, 3);

    c7->Print("plots/PFA1PFA2_SF_"+title+".png");

    mu_PFA2 = (TGraphErrors *) g_mean1->Clone();
    mu_PFA1p = (TGraphErrors *) g_mean2->Clone();
    mu_ratio = (TGraphErrors *) g_mean3->Clone();
}


void drawDiffIeta(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection){

    TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();
    t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta1"+rh_en + Form("(%d, %f, %f, 100, 0, 3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy > 10 && tp_soi<255" + selection, "COLZ");
    t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta2"+rh_en+Form("(%d, %f, %f, 100, 0, 3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy > 0.5 && TP_energy < 10 && tp_soi<255" + selection, "COLZ");
    t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta3"+rh_en+Form("(%d, %f, %f, 100, 0, 3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy > 10 && tp_soi<255" + selection, "COLZ");
    t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta4"+rh_en+Form("(%d, %f, %f, 100, 0, 3)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy > 0.5 && TP_energy < 10 && tp_soi<255" + selection, "COLZ");
    t1->Draw("TP_energy/"+rh_en+"/((abs(ieta) < 29)? 1. : 1.):ieta>>diffieta7"+rh_en+Form("(%d, %f, %f, 0.2, 0, 1.5)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy < 10 && TP_energy > 0.5 && tp_soi<255" + selection, "COLZ");
    t2->Draw("TP_energy/"+rh_en+"/((abs(ieta) < 29)? 1. : 1.):ieta>>diffieta8"+rh_en+Form("(%d, %f, %f, 0.2, 0, 1.5)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "TP_energy < 10 && TP_energy > 0.5 && tp_soi<255" + selection, "COLZ");

/*    t1->Draw("TP_energy:ieta>>diffieta1"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && tp_soi<255", "COLZ");
    t1->Draw("TP_energy:ieta>>diffieta2"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && TP_energy < 128 && tp_soi<255", "COLZ");
    t2->Draw("TP_energy:ieta>>diffieta3"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && tp_soi<255", "COLZ");
    t2->Draw("TP_energy:ieta>>diffieta4"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && TP_energy < 128 && tp_soi<255", "COLZ");
    t1->Draw("TP_energy:ieta>>diffieta7"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && TP_energy < 128 && tp_soi<255", "COLZ");
    t2->Draw("TP_energy:ieta>>diffieta8"+rh_en+"(87, -40, 40, 100, 0, 128)", "TP_energy > 0.5 && TP_energy < 128 && tp_soi<255", "COLZ");
*/
    TH2F *diffieta1 = (TH2F*)gDirectory->Get("diffieta1"+rh_en);
    TH2F *diffieta2 = (TH2F*)gDirectory->Get("diffieta2"+rh_en);
    TH2F *diffieta3 = (TH2F*)gDirectory->Get("diffieta3"+rh_en);
    TH2F *diffieta4 = (TH2F*)gDirectory->Get("diffieta4"+rh_en);
    TH2F *diffieta7 = (TH2F*)gDirectory->Get("diffieta7"+rh_en);
    TH2F *diffieta8 = (TH2F*)gDirectory->Get("diffieta8"+rh_en);

/*    TH1F *mean1 = new TH1F("mean1", "mean1", 59, -29, 29);
    TH1F *mean2 = new TH1F("mean2", "mean2", 59, -29, 29);
    TH1F *mean3 = new TH1F("mean3", "mean3", 59, -29, 29);
    TH1F *mean4 = new TH1F("mean4", "mean4", 59, -29, 29);

    TH1F *mean7 = new TH1F("mean7", "mean7", 59, -29, 29);
    TH1F *mean8 = new TH1F("mean8", "mean8", 59, -29, 29);
    TH1F *sigma7 = new TH1F("sigma7", "sigma7", 59, -29, 29);
    TH1F *sigma8 = new TH1F("sigma8", "sigma8", 59, -29, 29);
*/


    TGraphErrors *g_mean1 = new TGraphErrors(ietaBin);
    TGraphErrors *g_mean2 = new TGraphErrors(ietaBin);
    TGraphErrors *g_mean3 = new TGraphErrors(ietaBin);
    TGraphErrors *g_mean4 = new TGraphErrors(ietaBin);

    TGraphErrors *g_mean7 = new TGraphErrors(ietaBin);
    TGraphErrors *g_mean8 = new TGraphErrors(ietaBin);

    TGraphErrors *g_sigma7 = new TGraphErrors(ietaBin);
    TGraphErrors *g_sigma8 = new TGraphErrors(ietaBin);

    for (int i=1; i < diffieta1->GetNbinsX()+1;++i){
      Float_t mean_t1 = 0.;
      Float_t entries_t1 = 0.;
      Float_t mean_t2 = 0.;
      Float_t entries_t2 = 0.;
      Float_t mean_t3 = 0.;
      Float_t entries_t3 = 0.;
      Float_t mean_t4 = 0.;
      Float_t entries_t4 = 0.;
      Float_t mean_t7 = 0.;
      Float_t entries_t7 = 0.;
      Float_t mean_t8 = 0.;
      Float_t entries_t8 = 0.;


      for (int j=1; j < diffieta1->GetNbinsY()+1;++j){
        entries_t1+=diffieta1->GetBinContent(i, j);
        mean_t1 += diffieta1->GetYaxis()->GetBinCenter(j)*diffieta1->GetBinContent(i, j);
        entries_t2+=diffieta2->GetBinContent(i, j);
        mean_t2 += diffieta2->GetYaxis()->GetBinCenter(j)*diffieta2->GetBinContent(i, j);
        entries_t3+=diffieta3->GetBinContent(i, j);
        mean_t3 += diffieta3->GetYaxis()->GetBinCenter(j)*diffieta3->GetBinContent(i, j);
        entries_t4+=diffieta4->GetBinContent(i, j);
        mean_t4 += diffieta4->GetYaxis()->GetBinCenter(j)*diffieta4->GetBinContent(i, j);
        entries_t7+=diffieta7->GetBinContent(i, j);
        mean_t7 += diffieta7->GetYaxis()->GetBinCenter(j)*diffieta7->GetBinContent(i, j);
        entries_t8+=diffieta8->GetBinContent(i, j);
        mean_t8 += diffieta8->GetYaxis()->GetBinCenter(j)*diffieta8->GetBinContent(i, j);

      }
      if (entries_t1!=0) mean_t1/=entries_t1;
      else mean_t1 = 0;
      if (entries_t2!=0) mean_t2/=entries_t2;
      else mean_t2 = 0;
      if (entries_t3!=0) mean_t3/=entries_t3;
      else mean_t3 = 0;
      if (entries_t4!=0) mean_t4/=entries_t4;
      else mean_t4 = 0;
      if (entries_t7!=0) mean_t7/=entries_t7;
      else mean_t7 = 0;
      if (entries_t8!=0) mean_t8/=entries_t8;
      else mean_t8 = 0;

      if (mean_t1 > 0.1) g_mean1->SetPoint(i, diffieta1->GetXaxis()->GetBinCenter(i), mean_t1);
      if (mean_t2 > 0.1) g_mean2->SetPoint(i, diffieta2->GetXaxis()->GetBinCenter(i), mean_t2);
      if (mean_t3 > 0.1) g_mean3->SetPoint(i, diffieta3->GetXaxis()->GetBinCenter(i), mean_t3);
      if (mean_t4 > 0.1) g_mean4->SetPoint(i, diffieta4->GetXaxis()->GetBinCenter(i), mean_t4);
      //if (mean_t7 > 0.1) mean7->Fill(diffieta7->GetXaxis()->GetBinCenter(i), mean_t7);
      //if (mean_t8 > 0.1) mean8->Fill(diffieta8->GetXaxis()->GetBinCenter(i), mean_t8);
      //if (mean_t9 > 0.1) mean9->Fill(diffieta9->GetXaxis()->GetBinCenter(i), mean_t9);

      /*Float_t sigma_t7 = 0.;
      Float_t sigma_t8 = 0.;

      for (int j=1; j < diffieta1->GetNbinsY()+1;++j){
        sigma_t7 += pow(diffieta7->GetYaxis()->GetBinCenter(j)-mean_t7, 2)*diffieta7->GetBinContent(i, j);
        sigma_t8 += pow(diffieta8->GetYaxis()->GetBinCenter(j)-mean_t8, 2)*diffieta8->GetBinContent(i, j);
      }
      if (entries_t7!=0){
        sigma_t7 = sqrt(sigma_t7/(entries_t7 -1));
      }
      if (entries_t8!=0){
        sigma_t8 = sqrt(sigma_t8/(entries_t8 -1));
      }
      */
      TString ind; ind.Form("%d",i);

      gStyle->SetOptFit(0011);
      TH1F *h71 = (TH1F *)diffieta7->ProjectionY("h7"+ind, i, i);

      if (h71->GetEntries() > 0){
      TCanvas *c7 = new TCanvas("c7_"+ind, "c_"+ind, 800, 800);
      h71->Fit("gaus");
      h71->SetTitle("");
      h71->Draw();
      c7->Print("ieta/ieta"+ind+"_PFA2_"+title+".png");
      
      TF1 *gFit71 = (TF1 *)h71->GetFunction("gaus");
    
      g_mean7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), gFit71->GetParameter(1));
      g_sigma7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), gFit71->GetParameter(2));

      g_mean7->SetPointError(i, 0, gFit71->GetParError(1));
      g_sigma7->SetPointError(i, 0, gFit71->GetParError(2));
      }

    //func->SetParameters(1e+4, 1, 0.05, 0.02, 10);

      TH1F *h81 = (TH1F *)diffieta8->ProjectionY("h8"+ind, i, i);
      if (h81->GetEntries() > 0){

      TF1 *func = new TF1("fitFunction", "gaus", 0.7, 1.1);
      func->SetParameter(0, h81->Integral());
      func->SetParameter(1, h81->GetMean());
      func->SetParameter(2, 0.1);

//      func->SetParLimits(0, h81->Integral(), h81->Integral());
      func->SetParLimits(1, 0.4, 1.2);
      func->SetParLimits(2, 0.01, 0.15);


      TCanvas *c8 = new TCanvas("c8_"+ind, "c_"+ind, 800, 800);
      h81->Fit(func, "B");
      h81->SetTitle("");
      h81->Draw();
      c8->Print("ieta/ieta"+ind+"_PFA1p_"+title+".png");

      TF1 *gFit81 = (TF1 *)h81->GetFunction("fitFunction");     

       g_mean8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetMean());//func->GetParameter(1));
      g_sigma8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetStdDev());//func->GetParameter(2));

      g_mean8->SetPointError(i, 0, 0);//gFit81->GetParError(1));
      g_sigma8->SetPointError(i, 0, 0);//gFit81->GetParError(2));
      }
      //if (sigma_t7 > 0.01) sigma7->Fill(diffieta7->GetXaxis()->GetBinCenter(i), sigma_t7);
      //if (sigma_t8 > 0.01) sigma8->Fill(diffieta8->GetXaxis()->GetBinCenter(i), sigma_t8);
      //if (sigma_t9 > 0.01) sigma9->Fill(diffieta9->GetXaxis()->GetBinCenter(i), sigma_t9);

    }

    TGraph *g_mean_ratio =  new TGraph(ietaBin);
    TGraph *g_sigma_ratio =  new TGraph(ietaBin);

    for (int i = 0; i < g_mean7->GetN(); ++i){

    double pointX1, pointY1;
    double pointX2, pointY2;
    double pointX3, pointY3;
    double pointX4, pointY4;
    
    g_mean7->GetPoint(i, pointX1, pointY1);
    g_mean8->GetPoint(i, pointX2, pointY2);
    g_sigma7->GetPoint(i, pointX3, pointY3);
    g_sigma8->GetPoint(i, pointX4, pointY4);

    g_mean_ratio->SetPoint(i, pointX1, pointY2/pointY1);
    g_sigma_ratio->SetPoint(i, pointX3, pointY4/pointY3);

  }

    TLine *l =  new TLine((float)-ietaBin/2, 1, (float)ietaBin/2, 1);

    TCanvas *c1 = new TCanvas("c1", "c1", 1600, 800);
    c1->SetLogz();
    diffieta1->Draw("COLZ");
    diffieta1->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");
    diffieta1->SetTitle("Test");
    diffieta1->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    diffieta1->SetContour(1000);
    diffieta1->GetYaxis()->SetRangeUser(0.1, 2);
    g_mean1->Draw("P SAME");
    g_mean1->SetMarkerStyle(4);
    l->Draw("SAME");
    l->SetLineStyle(kDashed);
    l->SetLineWidth(2);
    TLegend *legend1 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend1->SetFillStyle(0);
    legend1->SetLineColor(kWhite);
    legend1->AddEntry(g_mean1, "PFA2 mean", "p");
    //legend1->Draw();

    c1->Print("plots/Energy_Diff_"+rh_en+"_large10_PFA2_"+title+".png");
      
    TCanvas *c2 = new TCanvas("c2", "c2", 1600, 800);
    c2->SetLogz();
    diffieta2->Draw("COLZ");
    diffieta2->SetTitle("dsad;i#eta;E_{T, TP} / E_{T, RH}");
    diffieta2->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    diffieta2->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta2->SetContour(1000);
    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    l->Draw("SAME");
    TLegend *legend2 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend2->SetFillStyle(0);
    legend2->SetLineColor(kWhite);
    legend2->AddEntry(g_mean2, "PFA2 mean", "p");
    //legend2->Draw();

    c2->Print("plots/Energy_Diff_"+rh_en+"_less10_PFA2_"+title+".png"); 

    TCanvas *c3 = new TCanvas("c3", "c3", 1600, 800);
    c3->SetLogz();
    diffieta3->Draw("COLZ");
    diffieta3->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");
    diffieta3->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    diffieta3->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta3->SetContour(1000);
    g_mean3->Draw("P SAME");
    g_mean3->SetMarkerStyle(8);
    g_mean3->SetMarkerColor(kBlack);
    g_mean1->Draw("P SAME");
    g_mean1->SetMarkerStyle(4);
    l->Draw("SAME");
    TLegend *legend3 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend3->SetFillStyle(0);
    legend3->AddEntry(g_mean1, "PFA2 mean", "p");
    legend3->AddEntry(g_mean3, "PFA1 mean", "p");
    legend3->SetLineColor(kWhite);
    //legend3->Draw();

    c3->Print("plots/Energy_Diff_"+rh_en+"_large10_PFA1p_"+title+".png");
      
    TCanvas *c4 = new TCanvas("c4", "c4", 1600, 800);
    c4->SetLogz();
    diffieta4->Draw("COLZ");
    diffieta4->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");
    diffieta4->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    diffieta4->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta4->SetContour(1000);
    g_mean4->Draw("P SAME");
    g_mean4->SetMarkerStyle(8);
    g_mean4->SetMarkerColor(kBlack);
    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    l->Draw("SAME");
    TLegend *legend4 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend4->SetFillStyle(0);
    legend4->AddEntry(g_mean2, "PFA2 mean", "p");
    legend4->AddEntry(g_mean4, "PFA1 mean", "p");
    legend4->SetLineColor(kWhite);
    //legend4->Draw();

    c4->Print("plots/Energy_Diff_"+rh_en+"_less10_PFA1p_"+title+".png"); 
   
    gStyle->SetTitleFontSize(1.);
  
    TCanvas *c7 = new TCanvas("c7", "c7", 4000, 3200);
    c7->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1);
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
    pad1->Draw();
    pad2->Draw();
    pad1->SetGrid();
    pad1->cd();

    g_mean8->Draw("AP");
    g_mean8->SetMarkerStyle(8);
    g_mean8->SetMarkerSize(4);
    g_mean8->SetMarkerColor(kBlack);
    g_mean8->SetTitle(";i#eta;");

    g_mean8->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    g_mean8->GetYaxis()->SetRangeUser(0.1, 2);
    //g_mean9->SetMarkerSize(2);

    g_mean7->Draw("P SAME");
    g_mean7->SetMarkerStyle(107);
    g_mean7->SetMarkerSize(4);
    g_mean7->SetMarkerColor(kBlack);
    g_mean7->SetLineWidth(4);
    l->Draw("SAME");
    l->SetLineColor(kRed);
    l->SetLineWidth(8);
    TLegend *legend7 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend7->SetFillStyle(0);
    legend7->AddEntry(g_mean7, "PFA2 mean", "p");
    legend7->AddEntry(g_mean8, "PFA1' mean", "p");
    legend7->SetLineColor(kWhite);
    //legend7->Draw();

    pad2->cd();
    pad2->SetGrid();
    g_mean_ratio->Draw("AP");
    g_mean_ratio->SetTitle(";;");
    g_mean_ratio->GetYaxis()->SetRangeUser(0.1, 1.5);
    g_mean_ratio->SetMarkerSize(3);
    g_mean_ratio->SetMarkerColor(kBlue);
    l->Draw("SAME");

    c7->Print("plots/Energy_Scale_"+title+".png"); 

    TCanvas *c8 = new TCanvas("c8", "c8", 4000, 3200);
    c8->cd();
    TPad *pad11 = new TPad("pad11", "pad11", 0, 0.3, 1, 1);
    TPad *pad12 = new TPad("pad12", "pad12", 0, 0, 1, 0.3);
    pad11->Draw();
    pad12->Draw();
    pad11->SetGrid();
    pad11->cd();

    g_sigma8->Draw("AP");
    g_sigma8->SetMarkerStyle(8);
    g_sigma8->SetMarkerSize(4);
    g_sigma8->SetMarkerColor(kBlack);
    g_sigma8->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
    g_sigma8->GetYaxis()->SetRangeUser(0.01, 0.4);
    g_sigma8->SetTitle(";i#eta;");
    TLegend *legend8 = new TLegend(0.72,0.78, 0.84, 0.89);
    legend8->SetFillStyle(0);
    legend8->AddEntry(g_sigma7, "PFA2 sigma", "p");
    legend8->AddEntry(g_sigma8, "PFA1' sigma", "p");
    legend8->SetLineColor(kWhite);
    //legend8->Draw();
    //g_sigma9->SetMarkerSize(2);

    g_sigma7->Draw("P SAME");
    g_sigma7->SetMarkerStyle(107);
    g_sigma7->SetMarkerSize(4);
    //l->Draw("SAME");


    pad12->cd();
    pad12->SetGrid();
    g_sigma_ratio->Draw("AP");
    g_sigma_ratio->SetTitle(";;");
    g_sigma_ratio->GetYaxis()->SetRangeUser(0.1, 1.5);
    g_sigma_ratio->SetMarkerSize(3);
    g_sigma_ratio->SetMarkerColor(kBlue);
    l->Draw("SAME");

    c8->Print("plots/Energy_Resolution_"+title+".png"); 

    mu_PFA2 = (TGraphErrors *) g_mean7->Clone();
    mu_PFA1p = (TGraphErrors *) g_mean8->Clone();

    sigma_PFA2 = (TGraphErrors *) g_sigma7->Clone();
    sigma_PFA1p = (TGraphErrors *) g_sigma8->Clone();

}


void drawDiffEt(TTree *t1, TTree *t2, TString det, TString name){
    TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();

    TH2F *diffieta2 = new TH2F("diffieta2","diffieta2", 128, 0, 128, 400, 0, 20);
    TH2F *diffieta4 = new TH2F("diffieta4","diffieta4", 128, 0, 128, 400, 0, 20);

    t2->Draw("TP_energy/"+rh_en+":"+rh_en+">>diffieta2", "TP_energy > 0.5 && tp_soi<255 && nVtx < 30 &&" +det, "COLZ");
    t2->Draw("TP_energy/"+rh_en+":"+rh_en+">>diffieta4", "TP_energy > 0.5 && tp_soi<255 && nVtx > 50 &&" +det, "COLZ");
//    t2->Draw("TP_energy/"+rh_en+":TP_energy>>diffieta4", "TP_energy > 0.5 && tp_soi<255 && nVtx < 30 &&" +det, "COLZ");

//    TH2F *diffieta4 = (TH2F*)gDirectory->Get("diffieta11"+rh_en);

    TH1F *mean2 = new TH1F("mean2", "mean2", 150, 0, 150);
    TH1F *mean4 = new TH1F("mean4", "mean4", 150, 0, 150);

    for (int i=1; i < diffieta2->GetNbinsX()+1;++i){
      Float_t mean_t2 = 0.;
      Float_t entries_t2 = 0.;
      Float_t mean_t4 = 0.;
      Float_t entries_t4 = 0.;

      for (int j=1; j < diffieta2->GetNbinsY()+1;++j){
        entries_t2+=diffieta2->GetBinContent(i, j);
        mean_t2 += diffieta2->GetYaxis()->GetBinCenter(j)*diffieta2->GetBinContent(i, j);
        entries_t4+=diffieta4->GetBinContent(i, j);
        mean_t4 += diffieta4->GetYaxis()->GetBinCenter(j)*diffieta4->GetBinContent(i, j);

      }
      if (entries_t2!=0) mean_t2/=entries_t2;
      else mean_t2 = 0;
      if (entries_t4!=0) mean_t4/=entries_t4;
      else mean_t4 = 0;

      if (mean_t2 > 0.1) mean2->Fill(diffieta2->GetXaxis()->GetBinCenter(i), mean_t2);
      if (mean_t4 > 0.1) mean4->Fill(diffieta4->GetXaxis()->GetBinCenter(i), mean_t4);

    }

    TLine *l =  new TLine(0, 1, 128, 1);

    TGraph *g_mean2 = new TGraph(mean2);
    TGraph *g_mean4 = new TGraph(mean4);

    gStyle->SetOptStat(0);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
    c2->SetLogz();
    diffieta2->Draw("COLZ");
    diffieta2->SetTitle(";E_{T, RH};E_{T, TP} / E_{T, RH}");
//    diffieta2->GetXaxis()->SetRangeUser(0, 128);
    diffieta2->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta2->SetContour(1000);

    g_mean4->Draw("P SAME");
    g_mean4->SetMarkerStyle(8);
    g_mean4->SetMarkerSize(0.8);
    g_mean4->SetMarkerColor(kBlack);

    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    g_mean2->SetMarkerSize(0.8);
    l->Draw("SAME");
    c2->Print("plots/TP_"+rh_en+name+"_PFA2.png"); 
      
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
    c4->SetLogz();
    diffieta4->Draw("COLZ");
    diffieta4->SetTitle(";E_{T, RH};E_{T, TP} / E_{T, RH}");
    diffieta4->GetXaxis()->SetRangeUser(0, 128);
    diffieta4->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta4->SetContour(1000);
    g_mean4->Draw("P SAME");
    g_mean4->SetMarkerStyle(8);
    g_mean4->SetMarkerSize(0.8);
    g_mean4->SetMarkerColor(kBlack);
//    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    l->Draw("SAME");
    c4->Print("plots/TP_"+rh_en+name+"_PFA1p.png"); 

}


void drawEt2D(TTree *t1, TTree *t2, TString det, TString name){
    TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();
    t1->Draw(rh_en+":TP_energy/((abs(ieta)>29)? 1. : 1.)>>diffieta13"+rh_en+"(150, 0, 150, 150, 0, 150)", "TP_energy > 0.5 && tp_soi<255 &&" +det, "COLZ");
    t2->Draw(rh_en+":TP_energy/((abs(ieta)>29)? 1. : 1.)>>diffieta14"+rh_en+"(150, 0, 150, 150, 0, 150)", "TP_energy > 0.5 && tp_soi<255 &&" +det, "COLZ");

    TH2F *diffieta2 = (TH2F*)gDirectory->Get("diffieta13"+rh_en);
    TH2F *diffieta4 = (TH2F*)gDirectory->Get("diffieta14"+rh_en);

    TH2F *mean2 = new TH2F("mean2", "mean2", 150, 0, 150, 150, 0, 150);
    TH2F *mean4 = new TH2F("mean4", "mean4", 150, 0, 150, 150, 0, 150);

    for (int i=1; i < diffieta2->GetNbinsX()+1;++i){
      Float_t mean_t2 = 0.;
      Float_t entries_t2 = 0.;
      Float_t mean_t4 = 0.;
      Float_t entries_t4 = 0.;

      for (int j=1; j < diffieta2->GetNbinsY()+1;++j){
        entries_t2+=diffieta2->GetBinContent(i, j);
        mean_t2 += diffieta2->GetYaxis()->GetBinCenter(j)*diffieta2->GetBinContent(i, j);
        entries_t4+=diffieta4->GetBinContent(i, j);
        mean_t4 += diffieta4->GetYaxis()->GetBinCenter(j)*diffieta4->GetBinContent(i, j);

      }
      if (entries_t2!=0) mean_t2/=entries_t2;
      else mean_t2 = 0;
      if (entries_t4!=0) mean_t4/=entries_t4;
      else mean_t4 = 0;

      if (mean_t2 > 0.1) mean2->Fill(diffieta2->GetXaxis()->GetBinCenter(i), mean_t2);
      if (mean_t4 > 0.1) mean4->Fill(diffieta4->GetXaxis()->GetBinCenter(i), mean_t4);

    }

    TLine *l =  new TLine(0, 0, 150, 150);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
    c2->SetLogz();
    diffieta2->Draw("COLZ");
    diffieta2->SetTitle(";E_{T, TP};E_{T, RH}");
    diffieta2->SetContour(1000);
    //mean2->Draw("P SAME");
    //mean2->SetMarkerStyle(8);
    l->Draw("SAME");
    c2->Print("plots/2D_TP_"+rh_en+"_less10_"+name+"_PFA2_.png"); 
      
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
    c4->SetLogz();
    diffieta4->Draw("COLZ");
    diffieta4->SetTitle(";E_{T, TP};E_{T, RH}");
    diffieta4->SetContour(1000);
    //mean4->Draw("P SAME");
    //mean4->SetMarkerStyle(8);
    //mean2->Draw("P SAME");
    //mean2->SetMarkerStyle(4);
    l->Draw("SAME");
    c4->Print("plots/2D_TP_"+rh_en+"_less10_"+name+"_PFA1p_.png"); 

 /*   TH1 *h1_PFA2 = diffieta2->ProjectionX("", 5, 5);

    TCanvas *c5 = new TCanvas("c5", "c5", 800, 800);
    h1_PFA2->Draw("HIST");
    h1_PFA2->GetXaxis()->SetRangeUser(0, 10);
    h1_PFA2->SetTitle(";E_{T, RH}");
    c5->Print("plots/RH_dist"+rh_en+"_5GeV_"+name+"_PFA2.png"); 

    TH1 *h1_PFA1p = diffieta2->ProjectionX("", 5, 5);

    TCanvas *c6 = new TCanvas("c6", "c6", 800, 800);
    h1_PFA1p->Draw("HIST");
    h1_PFA1p->GetXaxis()->SetRangeUser(0, 10);
    h1_PFA1p->SetTitle(";E_{T, RH}");
    c6->Print("plots/RH_dist"+rh_en+"_5GeV_"+name+"_PFA1p.png"); 


    TH1 *h2_PFA2 = diffieta2->ProjectionX("", 25, 25);

    TCanvas *c7 = new TCanvas("c7", "c7", 800, 800);
    h2_PFA2->Draw("HIST");
    h2_PFA2->GetXaxis()->SetRangeUser(20, 30);
    h2_PFA2->SetTitle(";E_{T, RH}");
    c7->Print("plots/RH_dist"+rh_en+"_25GeV_"+name+"_PFA2.png"); 

    TH1 *h2_PFA1p = diffieta2->ProjectionX("", 25, 25);

    TCanvas *c8 = new TCanvas("c8", "c8", 800, 800);
    h2_PFA1p->Draw("HIST");
    h2_PFA1p->GetXaxis()->SetRangeUser(20, 30);
    h2_PFA1p->SetTitle(";E_{T, RH}");
    c8->Print("plots/RH_dist"+rh_en+"_25GeV_"+name+"_PFA1p.png"); 

    TH1 *h3_PFA2 = diffieta2->ProjectionX("", 100, 100);

    TCanvas *c9 = new TCanvas("c9", "c9", 800, 800);
    h3_PFA2->Draw("HIST");
    h3_PFA2->GetXaxis()->SetRangeUser(95, 105);
    h3_PFA2->SetTitle(";E_{T, RH}");
    c9->Print("plots/RH_dist"+rh_en+"_100GeV_"+name+"_PFA2.png"); 

    TH1 *h3_PFA1p = diffieta2->ProjectionX("", 100, 100);

    TCanvas *c10 = new TCanvas("c10", "c10", 800, 800);
    h3_PFA1p->Draw("HIST");
    h3_PFA1p->GetXaxis()->SetRangeUser(95, 105);
    h3_PFA1p->SetTitle(";E_{T, RH}");
    c10->Print("plots/RH_dist"+rh_en+"_100GeV_"+name+"_PFA1p.png"); 
*/

}

