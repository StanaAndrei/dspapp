# dspapp

To use(linux only) download the repo than run <<make>>.

This app works via cl args. <br>
Examples: <br>
- ```$ dspapp.exe --vol file.wav 300``` <br>
- ```$ dspapp.exe --modulation file.wav .5 [.5]``` modulation: ring mod/tremolo <br>
- ```$ dspapp.exe --delay file.wav 300 [300] .5``` delay based effects: echo/flanger <br>
- ```$ dspapp.exe --dft file.wav``` computes dft <br>
- ```$ dspapp.exe --morse-dev file.wav``` decodes morse file <br>
- ```$ dspapp.exe --morse-enc "text to encode"``` encodes to morse <br>
