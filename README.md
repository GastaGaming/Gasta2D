# Gasta2D
Gasta2D is simple game engine that uses SDL2
### How to get going
These steps helps you get going first copy repo
```
git clone https://github.com/GastaGaming/Gasta2D.git
git cd Gasta2D
```
### Next download SDL2
These teps are for Windows, linux can use wget command
```
mkdir SDL2
powershell -Command "Invoke-WebRequest https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip -OutFile SDL2/SDL2.zip"
unzip SDL2/SDL2.zip -d SDL2
powershell -Command "Invoke-WebRequest https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip -OutFile SDL2/SDL2_image.zip"
unzip SDL2/SDL2_image.zip -d SDL2
powershell -Command "Invoke-WebRequest https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip -OutFile SDL2/SDL2_mixer.zip"
unzip SDL2/SDL2_mixer.zip -dSDL2
powershell -Command "Invoke-WebRequest https://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.1-VC.zip -OutFile SDL2/SDL2_net.zip"
unzip SDL2/SDL2_net.zip -d SDL2
powershell -Command "Invoke-WebRequest https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip -OutFile SDL2/SDL2_ttf.zip"
unzip SDL2/SDL2_ttf.zip -d SDL2
```
### Next configure sdl for cmake
```
Remove version numbers and rename directories accordingly
100. SDL2/
     - SDL2/
	 - SDL2_image/
	 - SDL2_mixer/
	 - SDL2_net/
	 - SDL2_ttf/

Then copy configure files from cmake_help to corect path using .bat file
cmake_help/WindowsHelper.bat
```
### Run CMAKE and set build path to in same path as source
#Doxygen
http://cs.harding.edu/gfoust/doxygen.html
http://cs.harding.edu/gfoust/simple_doxygen.txt
http://www.doxygen.nl/manual/config.html
### If doxygen fails to run dot needs graphviz-2.38 installed and %PATH
for %f in (*dot) do dot %~nxf -Tpng -o %~nf.png
