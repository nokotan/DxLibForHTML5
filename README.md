# DxLibForHTML5

## 概要

DXライブラリをHTML5で動かしてみたい...

- iOS, Android版の描画バックエンドが OpenGLES
- iOS のサウンド再生バックエンドが OpenAL
- emscripten には OpenGLES, OpenAL, libpng, libjpeg, zlib, ogg, vorbis, bullet といった DXライブラリで使われている外部ライブラリがすべてそろっている

はい、emscripten を使ってビルドしてみます

## 必要条件

- emscripten 1.39.6^
- cmake
- git (Windows のみ)
- make (Windows のみ)

## ビルド

- macOS, Linux

```bash
mkdir Build
cd Build
emcmake cmake ..
emmake make
```

- Windows (未テスト)

```bat
mkdir Build
cd Build
emcmake cmake -G "Unix Makefiles" ..
emmake make
```
