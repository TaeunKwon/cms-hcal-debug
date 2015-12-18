import ROOT as r
import sys

r.gROOT.SetBatch()
r.gStyle.SetOptStat(0)

infile, outfile = sys.argv[1:]

f = r.TFile(infile)

e = f.Get("analyze/evs")
t = f.Get("analyze/tps")
m = f.Get("analyze/ms")

c = r.TCanvas()
c.SaveAs(outfile + '[')
e.Draw("tp_v1_et:tp_v0_et>>hist", "", "COLZ")
r.gDirectory.Get("hist").SetTitle("HF 1x1 TP vs 2x3 TP (reemulated);#sum E_{T} HF, v0;#sum E_{T} HF, v1")
c.SaveAs(outfile)
t.Draw("ieta>>hist2", "et * (version==1)")
r.gDirectory.Get("hist2").SetTitle("HF 1x1 TP;ieta;#sum E_{T}")
c.SaveAs(outfile)
t.Draw("ieta>>hist3", "et * (version==0)")
r.gDirectory.Get("hist3").SetTitle("HF 2x3 TP;ieta;#sum E_{T}")
c.SaveAs(outfile)
m.Draw("et1x1:et2x3>>hist4", "et1x1<250", "COLZ")
c.SetLogz()
r.gDirectory.Get("hist4").SetTitle("#sum HF 1x1 in a single 2x3 TP;E_{T} 2x3 TP;#sum E_{T} 1x1 TP")
c.SaveAs(outfile)
m.Draw("et1x1:et2x3>>hist4_1", "et2x3<20", "COLZ")
r.gDirectory.Get("hist4_1").SetTitle("#sum HF 1x1 in a single 2x3 TP;E_{T} 2x3 TP;#sum E_{T} 1x1 TP")
c.SaveAs(outfile)
m.Draw("n1x1:ieta>>hist5(65, -32.5, 32.5, 5, 2.5, 7.5)", "", "COLZ")
r.gDirectory.Get("hist5").SetTitle("HF 1x1 count per 2x3 TP;ieta;Count")
c.SaveAs(outfile)
m.Draw("ieta>>hist6", "et1x1", "")
m.Draw("ieta>>hist7", "et2x3", "same")
r.gDirectory.Get("hist6").SetTitle("HF 1x1 (red) vs 2x3 (blue) TP;ieta;#sum E_{T}")
r.gDirectory.Get("hist6").SetLineColor(r.kRed)
r.gDirectory.Get("hist7").SetLineColor(r.kBlue)
c.SaveAs(outfile)
m.Draw("et1x1>>hist8", "et1x1 < 250")
m.Draw("et2x3>>hist9", "", "same")
r.gDirectory.Get("hist8").SetTitle("HF 1x1 (red) vs 2x3 (blue) TP E_{T} spectrum;#sum E_{T};Count")
r.gDirectory.Get("hist8").SetLineColor(r.kRed)
r.gDirectory.Get("hist9").SetLineColor(r.kBlue)
c.SetLogy()
c.SaveAs(outfile)
t.Draw("et>>hist10", "version==1")
r.gDirectory.Get("hist10").SetTitle("HF 1x1 TP E_{T} spectrum;#sum E_{T};Count")
r.gDirectory.Get("hist10").SetLineColor(r.kRed)
c.SaveAs(outfile)
c.SaveAs(outfile + ']')
