## Building application:
You can build executable file with Makefile (with g++)

## How to use it?
Encoding novel:
./main -en -i test/TomSawyer -o test/encodedNovel -k test/keyTom 

Decoding novel:
./main -de -i test/encodedNovel -o test/decodedNovel -k test/keyTom

Decoding small cipher:
./main -de -i test/cipher3 -o test/testDecode3 -k test/key3

Breaking encoded novel:
./main -br -i test/encodedNovel -o test/brokenNovel
