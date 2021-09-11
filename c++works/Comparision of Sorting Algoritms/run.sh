[[ -f "Comparision.png" ]] && rm Comparision.png

g++ -std=c++11 mainfile.cpp -o  mainfile ./plots/pbPlots.cpp ./plots/supportLib.cpp -lm
./mainfile
[[ -f "Comparision.png" ]] && xdg-open Comparision.png
# [[ -f "image1.png" ]] && rm image1.png
