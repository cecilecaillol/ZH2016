./Make.sh Final_selection.cc
./Final_selection.exe /data/ccaillol/ZH_oct30/Data.root files_nominal/data_obs.root data_obs data_obs 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZH125.root files_nominal/ZH125.root ZH125 ZH125 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZH110.root files_nominal/ZH110.root ZH110 ZH110 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZH120.root files_nominal/ZH120.root ZH120 ZH120 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZH130.root files_nominal/ZH130.root ZH130 ZH130 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZH140.root files_nominal/ZH140.root ZH140 ZH140 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZHWW125.root files_nominal/ZHWW125.root ZHWW125 ZHWW125 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZZ4L.root files_nominal/ZZ4L.root ZZ4L ZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ2e2mu.root files_nominal/GGZZ2e2mu.root GGZZ2e2mu GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ4mu.root files_nominal/GGZZ4mu.root GGZZ4mu GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ2mu2tau.root files_nominal/GGZZ2mu2tau.root GGZZ2mu2tau GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ2e2tau.root files_nominal/GGZZ2e2tau.root GGZZ2e2tau GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ4tau.root files_nominal/GGZZ4tau.root GGZZ4tau GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/GGZZ4e.root files_nominal/GGZZ4e.root GGZZ4e GGZZ 0
./Final_selection.exe /data/ccaillol/ZH_oct30/WWZ.root files_nominal/WWZ.root WWZ VVV 0
./Final_selection.exe /data/ccaillol/ZH_oct30/WZZ.root files_nominal/WZZ.root WZZ VVV 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ZZZ.root files_nominal/ZZZ.root ZZZ VVV 0
./Final_selection.exe /data/ccaillol/ZH_oct30/ttZ.root files_nominal/ttZ.root ttZ VVV 0
hadd -f files_nominal/ZZ.root files_nominal/ZZ4L.root files_nominal/GGZZ2e2mu.root files_nominal/GGZZ4mu.root files_nominal/GGZZ2mu2tau.root files_nominal/GGZZ2e2tau.root files_nominal/GGZZ4tau.root files_nominal/GGZZ4e.root files_nominal/WWZ.root files_nominal/WZZ.root files_nominal/ZZZ.root files_nominal/ZHWW125.root files_nominal/ttZ.root
root -l -b -q Measure_FR_Landau.cc
./Make.sh ApplyFRmethod_Landau.cc
./ApplyFRmethod_Landau.exe files_nominal/data_obs.root files_nominal/Reducible.root
python PrintNorm.py
hadd -f moyen.root files_nominal/ZZ.root files_nominal/data_obs.root files_nominal/Reducible.root files_nominal/ZH125.root files_nominal/ZH110.root files_nominal/ZH120.root files_nominal/ZH130.root files_nominal/ZH140.root
python Create_SSred.py


