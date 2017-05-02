#Equalizer ver3.0

### Obligatory includes : '<QTimer> , <equalizer.h>'

### Initializing :

Equalizer works with double array within 0..20 range. The client has to initialize Equalizer object and add it to a layout. Then QTimer is created that uses slot iterate() to invoke setChunk() method iteratively. Method setChunk() starts off animation and painting of a single state of equalizer. In order to adjust equalizer to the sound, the client would have to test different values of timerDuration(mainwindow.cpp) and animationDuration(equalizer.cpp).
