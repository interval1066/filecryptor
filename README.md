# filecryptor
Simple, per item encryption application in Qt for Linux. Just wanted a simple app with AES-256 encryption code to encrypt individual items so here one is. Not too interested in an entire disk encryption scheme, lots of solutions for that. Plus I get to pick the encryption code. Was planning on porting to the NDK but I need to translate some x86 assembly to Android's NEON instruction set, will take more time and research.

No PKI, no super infrastructure stuff, just something with a nice interface to experiment with. I envisioned using this as a starting point for porting different encryption algorithms to various platforms. IN NO WAY would I use this as my main encryption application, there are a lot better applications for that. Might not be a bad starting point for better application though.

#To do:
- [ ] Workout of profile action (still needs a little design work)
- [ ] Adapt the encryption/decryption action to buffered file device (the current code just encrypts/decrypts a string)

