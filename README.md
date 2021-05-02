# filecryptor
Simple, per item encryption application in Qt for Linux. Just wanted a simple app with AES-256 encryption code to encrypt individual items so here one is. Not too interested in an entire disk encryption scheme, lots of solutions for that. Plus I get to pick the encryption code. Was planning on porting to the NDK but I need to translate some x86 assembly to Android's NEON instruction set, will take more time and research.

No PKI, no super infrastructure stuff, just something with a nice interface to experiment with. I envisioned using this as a starting point for porting different encryption algorithms to various platforms. IN NO WAY would I use this as my main encryption application, there are a lot better applications for that. Might not be a bad starting point for better application though.

Added a new settings manager class that takes an arbitrary settings object to encaspulate the settings. Never felt right about having to couple that with the rest of the system. Finally settled on a facade pattern for it.

No, the code isn't commented. No, its not something I do with production/retail code.

Due to unforseen circumstances I've been able to return to this and get it done, maybe. The thing that's been holding me back is lack of interest and the fact that QIODevice::readLine reads lines, of course. That's what its supposed to do. But today I've had time to play around with the APIs and get it to read fixed record lengths from any file type (QIODevice::read(length) is the key), and get it to do what I want, read exact sizes of data, which is nessessary for the encryption code to work. Huzzah. I'm just not that familiar with the QT QIODevice apis. Yet. Getting there.

## To do:
- [X] Profile serialization way too complex, implement as a facade pattern
- [ ] Switch over or add cmake style build scripts
- [X] Workout of profile action (still needs a little design work)
- [X] Adapt the encryption/decryption action to buffered file device
- [ ] Add menu accelerators
- [X] Integration of high speed data copying Qt apis
- [ ] Add progress dialog for processing thread
- [ ] nautilus/thunar/dolphin right click context integration(?)


