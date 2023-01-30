#include <math.h>
#include "PhysicsTools/Utilities/macros/setTDRStyle_v2.C"
#include "CMS_lumi.C"

void MakePlots_PU(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend);
void drawTPinPU(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection);
void drawDiffIeta(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection);
void drawDiffEt(TTree *t1, TTree *t2, TString det, TString name);
void drawEt2D(TTree *t1, TTree *t2, TString det, TString name);

TString hep17 = "(ieta<=28 && ieta>=17 && iphi>=63 && iphi<=66)";
TString nhep17 = "!(ieta<=29 && ieta>=17 && iphi>=63 && iphi<=66) * (abs(ieta)<=28 && abs(ieta)>=17)";
TString hb = "(abs(ieta)<=16)";
TString hf = "(abs(ieta)>28)";
TString mode = "phase3";
int ietaBin = 81;

Double_t CrystalBall(Double_t *x, Double_t *par) {
  return ROOT::Math::crystalball_function(x[0], par[0], par[1], par[2], par[3]);
}

void plot_Energy_v1(){

  setTDRStyle();
  gROOT->ForceStyle();

  //TFile *f =  new TFile("analyze.root", "open");
  TChain *t1 =  new TChain("compareReemulRecoSeverity9/matches");
  TChain *t2 =  new TChain("compareRawRecoSeverity9/matches");


  //t1->Add("/eos/uscms/store/user/tkwon/RelValQCD_FlatPt_15_3000HS_14/crab_analyze_RAW2DIGI_DIGI_PFA1p/210224_074241/0000/*.root");
//  t1->Add("analyze.root");
  t1->Add("analyze_2023Jan27_phaseP6ns_2TS_v3.root");
//  t1->Add("analyze_2022Nov09.root");

  //t2->Add("/eos/uscms/store/user/tkwon/RelValQCD_FlatPt_15_3000HS_14/crab_analyze_RAW2DIGI_DIGI_PFA2/210224_074400/0000/*_woPU.root");
//  t2->Add("analyze.root");
  t2->Add("analyze_2023Jan27_phaseP6ns_2TS_v3.root");
//  t2->Add("analyze_2022Nov09.root");

  TString m = "M0 M2 M3";

  gStyle->SetOptStat(0);
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

  MakePlots_PU(t1, t2, "(TP_energy > 10. && TP_energy < 128.)", "highE", "[10, 128)");
  MakePlots_PU(t1, t2, "(TP_energy < 10. && TP_energy > 0.5)", "lowE", "[0.5, 10)");
}

void MakePlots_PU(TChain *t1, TChain *t2, TString selection, TString tag, TString t_legend){

  TGraphErrors *mu1_PFA2, *mu1_PFA1p;
  TGraphErrors *mu2_PFA2, *mu2_PFA1p;
  TGraphErrors *mu3_PFA2, *mu3_PFA1p;
  TGraphErrors *mu4_PFA2, *mu4_PFA1p;

  TGraphErrors *sigma1_PFA2, *sigma1_PFA1p;
  TGraphErrors *sigma2_PFA2, *sigma2_PFA1p;
  TGraphErrors *sigma3_PFA2, *sigma3_PFA1p;
  TGraphErrors *sigma4_PFA2, *sigma4_PFA1p;

//  drawDiffIeta("highestPU_lowE", t1, t2, mu4_PFA2, mu4_PFA1p, sigma4_PFA2, sigma4_PFA1p, "&& (nVtx > 60 && nVtx < 100)");
  drawTPinPU("lowPU_" + tag, t1, t2, mu1_PFA2, mu1_PFA1p, sigma1_PFA2, sigma1_PFA1p, "&& (nVtx > 0 && nVtx < 35) && " + selection);
  drawTPinPU("midPU_" + tag, t1, t2, mu2_PFA2, mu2_PFA1p, sigma2_PFA2, sigma2_PFA1p, "&& (nVtx > 35 && nVtx < 50) && " + selection);
  drawTPinPU("highPU_" + tag, t1, t2, mu3_PFA2, mu3_PFA1p, sigma3_PFA2, sigma3_PFA1p, "&& (nVtx > 50 && nVtx < 100) && " + selection);

//  drawDiffEt(t1, t2, hb, "HB");
//  drawDiffEt(t1, t2, "("+hep17 + "|" + nhep17 +")", "HE");
//  drawDiffEt(t1, t2, hf, "HF");
//  drawEt2D(t1, t2, hb, "HB");
//  drawEt2D(t1, t2, "("+hep17 + "|" + nhep17 +")", "HE");
//  drawEt2D(t1, t2, hf, "HF");

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
  }


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
  }


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
  legend_mu->AddEntry(mu1_PFA1p, "N_{vtx} #in [0, 35)", "p");
  legend_mu->AddEntry(mu2_PFA1p, "N_{vtx} #in [35, 50)", "p");
  legend_mu->AddEntry(mu3_PFA1p, "N_{vtx} #in [50, #infty)", "p");
//  legend_mu->AddEntry(mu4_PFA1p, "N_{vtx} #in [60, #infty)", "p");

  legend_mu->SetLineColor(kWhite);
  legend_mu->SetBorderSize(0);
  legend_mu->SetTextFont(43);
  legend_mu->Draw();

  l->Draw("SAME");

  TPaveText* tbox_mu = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_mu->AddText("E_{T, TP} #in " + t_legend + " GeV");
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
  legend_sigma->AddEntry(musigma1_PFA1p, "N_{vtx} #in [0, 35)", "p");
  legend_sigma->AddEntry(musigma2_PFA1p, "N_{vtx} #in [35, 50)", "p");
  legend_sigma->AddEntry(musigma3_PFA1p, "N_{vtx} #in [50, #infty)", "p");
//  legend_sigma->AddEntry(musigma4_PFA1p, "N_{vtx} #in [60, #infty)", "p");

  legend_sigma->SetLineColor(kWhite);
  legend_sigma->SetBorderSize(0);
  legend_sigma->SetTextFont(43);
  legend_sigma->Draw();

  TPaveText* tbox_sigma = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_sigma->AddText("E_{T, TP} #in " + t_legend +" GeV");
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
  mu1_PFA1p->SetMarkerColorAlpha(kRed, 1.);
  mu1_PFA1p->SetLineColorAlpha(kRed, 1.);
  mu1_PFA1p->SetTitle(";i#eta;#mu(E_{T, TP}/E_{T, RH})");
  mu1_PFA1p->GetYaxis()->SetLabelSize(85);
  mu1_PFA1p->GetXaxis()->SetLabelSize(85);
//  mu1_PFA1p->SetTextFont(42);
//  mu1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  mu1_PFA1p->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  mu1_PFA1p->GetYaxis()->SetRangeUser(0.3, 2.5);
  //g_mean9->SetMarkerSize(2);

  mu2_PFA1p->Draw("P E0 SAME");
  mu2_PFA1p->SetMarkerStyle(21);
  mu2_PFA1p->SetMarkerSize(3);
  mu2_PFA1p->SetMarkerColorAlpha(kRed, 0.6);
  mu2_PFA1p->SetLineColorAlpha(kRed, 0.6);
  mu2_PFA1p->SetLineWidth(4);

  mu3_PFA1p->Draw("P E0 SAME");
  mu3_PFA1p->SetMarkerStyle(22);
  mu3_PFA1p->SetMarkerSize(3);
  mu3_PFA1p->SetMarkerColorAlpha(kRed, 0.2);
  mu3_PFA1p->SetLineColorAlpha(kRed, 0.2);
  mu3_PFA1p->SetLineWidth(4);

  mu1_PFA2->Draw("P E0 SAME");
  mu1_PFA2->SetMarkerStyle(8);
  mu1_PFA2->SetMarkerSize(3);
  mu1_PFA2->SetMarkerColorAlpha(kBlue+1, 1.);
  mu1_PFA2->SetLineColorAlpha(kBlue+1, 1.);

  mu2_PFA2->Draw("P E0 SAME");
  mu2_PFA2->SetMarkerStyle(21);
  mu2_PFA2->SetMarkerSize(3);
  mu2_PFA2->SetMarkerColorAlpha(kBlue+1, 0.6);
  mu2_PFA2->SetLineColorAlpha(kBlue+1, 0.6);
  mu2_PFA2->SetLineWidth(4);

  mu3_PFA2->Draw("P E0 SAME");
  mu3_PFA2->SetMarkerStyle(22);
  mu3_PFA2->SetMarkerSize(3);
  mu3_PFA2->SetMarkerColorAlpha(kBlue+1, 0.2);
  mu3_PFA2->SetLineColorAlpha(kBlue+1, 0.2);
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
  legend_mu_PFA2->AddEntry(mu1_PFA1p, "PFA1', N_{vtx} #in [0, 35)", "p");
  legend_mu_PFA2->AddEntry(mu2_PFA1p, "PFA1', N_{vtx} #in [35, 50)", "p");
  legend_mu_PFA2->AddEntry(mu3_PFA1p, "PFA1', N_{vtx} #in [50, #infty)", "p");
  legend_mu_PFA2->AddEntry(mu1_PFA2, "PFA2, N_{vtx} #in [0, 35)", "p");
  legend_mu_PFA2->AddEntry(mu2_PFA2, "PFA2, N_{vtx} #in [35, 50)", "p");
  legend_mu_PFA2->AddEntry(mu3_PFA2, "PFA2, N_{vtx} #in [50, #infty)", "p");
//  legend_mu_PFA2->AddEntry(mu4_PFA2, "N_{vtx} #in [60, #infty)", "p");

  legend_mu_PFA2->SetLineColor(kWhite);
  legend_mu_PFA2->SetBorderSize(0);
  legend_mu_PFA2->SetTextFont(43);
  legend_mu_PFA2->Draw();

  l->Draw("SAME");

  TPaveText* tbox_mu_PFA2 = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_mu_PFA2->AddText("E_{T, TP} #in " + t_legend + " GeV");
  tbox_mu_PFA2->SetFillStyle(0);
  tbox_mu_PFA2->SetLineWidth(0);
  tbox_mu_PFA2->SetTextSize(0.04);
  tbox_mu_PFA2->SetTextFont(42);
  tbox_mu_PFA2->SetTextAlign(10);
  tbox_mu_PFA2->Draw();
  
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


  musigma1_PFA1p->Draw("AP E0");
  musigma1_PFA1p->SetMarkerStyle(8);
  musigma1_PFA1p->SetMarkerSize(3);
  musigma1_PFA1p->SetMarkerColorAlpha(kRed, 1.);
  musigma1_PFA1p->SetLineColorAlpha(kRed, 1.);
  musigma1_PFA1p->SetTitle(";i#eta;#frac{#sigma}{#mu}(E_{T, TP}/E_{T, RH})");
  musigma1_PFA1p->GetYaxis()->SetLabelSize(85);
  musigma1_PFA1p->GetXaxis()->SetLabelSize(85);
//  musigma1_PFA1p->SetTextFont(42);
//  musigma1_PFA1p->SetTitle(";i#eta;E_{T, TP} / E_{T, RH}");

  musigma1_PFA1p->GetXaxis()->SetRangeUser((float)-ietaBin/2, (float)ietaBin/2);
  musigma1_PFA1p->GetYaxis()->SetRangeUser(0.001, 0.4);
  //g_mean9->SetMarkerSize(2);

  musigma2_PFA1p->Draw("P E0 SAME");
  musigma2_PFA1p->SetMarkerStyle(21);
  musigma2_PFA1p->SetMarkerSize(3);
  musigma2_PFA1p->SetMarkerColorAlpha(kRed, 0.6);
  musigma2_PFA1p->SetLineColorAlpha(kRed, 0.6);
  musigma2_PFA1p->SetLineWidth(4);

  musigma3_PFA1p->Draw("P E0 SAME");
  musigma3_PFA1p->SetMarkerStyle(22);
  musigma3_PFA1p->SetMarkerSize(3);
  musigma3_PFA1p->SetMarkerColorAlpha(kRed, 0.2);
  musigma3_PFA1p->SetLineColorAlpha(kRed, 0.2);
  musigma3_PFA1p->SetLineWidth(4);

  musigma1_PFA2->Draw("P E0 SAME");
  musigma1_PFA2->SetMarkerStyle(8);
  musigma1_PFA2->SetMarkerSize(3);
  musigma1_PFA2->SetMarkerColorAlpha(kBlue+1, 1.);
  musigma1_PFA2->SetLineColorAlpha(kBlue+1, 1.);

  musigma2_PFA2->Draw("P E0 SAME");
  musigma2_PFA2->SetMarkerStyle(21);
  musigma2_PFA2->SetMarkerSize(3);
  musigma2_PFA2->SetMarkerColorAlpha(kBlue+1, 0.6);
  musigma2_PFA2->SetLineColorAlpha(kBlue+1, 0.6);
  musigma2_PFA2->SetLineWidth(4);

  musigma3_PFA2->Draw("P E0 SAME");
  musigma3_PFA2->SetMarkerStyle(22);
  musigma3_PFA2->SetMarkerSize(3);
  musigma3_PFA2->SetMarkerColorAlpha(kBlue+1, 0.2);
  musigma3_PFA2->SetLineColorAlpha(kBlue+1, 0.2);
  musigma3_PFA2->SetLineWidth(4);

/*  sigma4_PFA2->Draw("P E0 SAME");
  sigma4_PFA1p->SetMarkerStyle(33);
  sigma4_PFA1p->SetMarkerSize(3);
  sigma4_PFA1p->SetMarkerColor(kYellow+1);
  sigma4_PFA1p->SetLineColor(kYellow+1);
  sigma4_PFA1p->SetLineWidth(4);
*/
  l->Draw("SAME");
  l->SetLineColor(kBlack);
  l->SetLineWidth(8);
  l->SetLineStyle(9);

  TLegend *legend_sigma_PFA2 = new TLegend(0.52,0.7, 0.84, 0.85);
  legend_sigma_PFA2->SetFillStyle(0);
  legend_sigma_PFA2->AddEntry(musigma1_PFA1p, "PFA1', N_{vtx} #in [0, 35)", "p");
  legend_sigma_PFA2->AddEntry(musigma2_PFA1p, "PFA1', N_{vtx} #in [35, 50)", "p");
  legend_sigma_PFA2->AddEntry(musigma3_PFA1p, "PFA1', N_{vtx} #in [50, #infty)", "p");
  legend_sigma_PFA2->AddEntry(musigma1_PFA2, "PFA2, N_{vtx} #in [0, 35)", "p");
  legend_sigma_PFA2->AddEntry(musigma2_PFA2, "PFA2, N_{vtx} #in [35, 50)", "p");
  legend_sigma_PFA2->AddEntry(musigma3_PFA2, "PFA2, N_{vtx} #in [50, #infty)", "p");
//  legend_sigma_PFA2->AddEntry(sigma4_PFA2, "N_{vtx} #in [60, #infty)", "p");

  legend_sigma_PFA2->SetLineColor(kWhite);
  legend_sigma_PFA2->SetBorderSize(0);
  legend_sigma_PFA2->SetTextFont(43);
  legend_sigma_PFA2->Draw();

  l->Draw("SAME");

  TPaveText* tbox_sigma_PFA2 = new TPaveText(0.2, 0.62, 0.4, 0.72, "RNDC");
  tbox_sigma_PFA2->AddText("E_{T, TP} #in " + t_legend + " GeV");
  tbox_sigma_PFA2->SetFillStyle(0);
  tbox_sigma_PFA2->SetLineWidth(0);
  tbox_sigma_PFA2->SetTextSize(0.04);
  tbox_sigma_PFA2->SetTextFont(42);
  tbox_sigma_PFA2->SetTextAlign(10);
  tbox_sigma_PFA2->Draw();
  
  CMS_lumi(c_PFA2sigma, 4, 11);

  c_PFA2sigma->Print("plots/Performance_Sigma_"+ tag+".png"); 


}

void drawTPinPU(TString title, TTree *t1, TTree *t2, TGraphErrors *&mu_PFA2, TGraphErrors *&mu_PFA1p, TGraphErrors *&sigma_PFA2, TGraphErrors *&sigma_PFA1p, TString selection){

    TString rh_en = "RH_energyM2";// + ((TObjString *)(ms->At(i)))->String();
      t1->Draw("TP_energy/"+rh_en+":ieta>>diffieta7"+rh_en+Form("(%d, %f, %f, 100, 0, 5.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");
      t2->Draw("TP_energy/"+rh_en+":ieta>>diffieta8"+rh_en+Form("(%d, %f, %f, 100, 0, 5.0)", ietaBin, (float)-ietaBin/2, (float)ietaBin/2), "tp_soi<255" + selection, "COLZ");

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

      gStyle->SetOptFit(0011);
      TH1F *h71 = (TH1F *)diffieta7->ProjectionY("h7"+ind, i, i);

      if (h71->GetEntries() > 0){
      TCanvas *c7 = new TCanvas("c7_"+ind, "c_"+ind, 800, 800);
      h71->Fit("gaus");
      h71->SetTitle("");
      h71->Draw();

      h71->SetNdivisions(205);
      c7->Print("ieta/ieta"+ind+"_PFA2_"+title+".png");
      
      TF1 *gFit71 = (TF1 *)h71->GetFunction("gaus");
    
      g_mean7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), h71->GetMean());
      g_sigma7->SetPoint(i, diffieta7->GetXaxis()->GetBinCenter(i), h71->GetStdDev());

      g_mean7->SetPointError(i, 0, 0);
      g_sigma7->SetPointError(i, 0, 0);
      }


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
      h81->SetNdivisions(205);
      c8->Print("ieta/ieta"+ind+"_PFA1p_"+title+".png");

      TF1 *gFit81 = (TF1 *)h81->GetFunction("fitFunction");     

       g_mean8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetMean());//func->GetParameter(1));
      g_sigma8->SetPoint(i, diffieta8->GetXaxis()->GetBinCenter(i), h81->GetStdDev());//func->GetParameter(2));

      g_mean8->SetPointError(i, 0, 0);//gFit81->GetParError(1));
      g_sigma8->SetPointError(i, 0, 0);//gFit81->GetParError(2));

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
    t1->Draw("TP_energy/"+rh_en+"/((abs(ieta)>29)? 1. : 1.):TP_energy>>diffieta10"+rh_en+"(75, 0, 150, 50, 0, 2)", "TP_energy > 0.5 && tp_soi<255 &&" +det, "COLZ");
    t2->Draw("TP_energy/"+rh_en+"/((abs(ieta)>29)? 1. : 1.):TP_energy>>diffieta11"+rh_en+"(75, 0, 150, 50, 0, 2)", "TP_energy > 0.5 && tp_soi<255 &&" +det, "COLZ");

    TH1F *diffieta2 = (TH1F*)gDirectory->Get("diffieta10"+rh_en);
    TH1F *diffieta4 = (TH1F*)gDirectory->Get("diffieta11"+rh_en);

    TH1F *mean2 = new TH1F("mean2", "mean2", 75, 0, 150);
    TH1F *mean4 = new TH1F("mean4", "mean4", 75, 0, 150);

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

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
    c2->SetLogz();
    diffieta2->Draw("COLZ");
    diffieta2->SetTitle(";E_{T, TP};E_{T, TP} / E_{T, RH}");
    diffieta2->GetXaxis()->SetRangeUser(0, 128);
    diffieta2->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta2->SetContour(1000);
    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    g_mean2->SetMarkerSize(0.8);
    l->Draw("SAME");
    c2->Print("plots/Energy_Diff_TP_"+rh_en+"_less10_"+name+"_PFA2.png"); 
      
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
    c4->SetLogz();
    diffieta4->Draw("COLZ");
    diffieta4->SetTitle(";E_{T, TP};E_{T, TP} / E_{T, RH}");
    diffieta4->GetXaxis()->SetRangeUser(0, 128);
    diffieta4->GetYaxis()->SetRangeUser(0.1, 2);
    diffieta4->SetContour(1000);
    g_mean4->Draw("P SAME");
    g_mean4->SetMarkerStyle(8);
    g_mean4->SetMarkerSize(0.8);
    g_mean4->SetMarkerColor(kBlack);
    g_mean2->Draw("P SAME");
    g_mean2->SetMarkerStyle(4);
    l->Draw("SAME");
    c4->Print("plots/Energy_Diff_TP_"+rh_en+"_less10_"+name+"_PFA1p.png"); 

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

