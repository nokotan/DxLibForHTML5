# DxLibForHTML5

![Build Status](https://www.travis-ci.com/nokotan/DxLibForHTML5.svg?branch=master)

## 概要

DXライブラリをWebGLで動かしてみたい...

- iOS, Android版の描画バックエンドが OpenGLES
- iOS のサウンド再生バックエンドが OpenAL
- emscripten には OpenGLES, OpenAL, libpng, libjpeg, zlib, ogg, vorbis, bullet といった DXライブラリで使われている外部ライブラリがすべてそろっている

はい、emscripten を使ってビルドしてみます

## ビルド環境構築

### コンパイル済みバイナリのダウンロード

- [最新版のダウンロード](https://github.com/nokotan/DxLibForHTML5/releases/latest) (Windows, Linux, macOS共通)

### 必要条件

- [emscripten 2.0.4](https://emscripten.org/docs/getting_started/downloads.html)
- [Visual Studio](https://visualstudio.microsoft.com/ja/downloads/) または [Visual Studio Code](https://visualstudio.microsoft.com/ja/downloads/)

### 参考資料

| 開発環境 | リンク |
|:--:|:--:|
| Visual Studio | <https://dxlib.kamenokosoft.com/visual-studio.html> |
| VSCode | <https://dxlib.kamenokosoft.com/vscode.html> |

## ライブラリ本体の手動ビルド

### 必要条件

- emscripten 1.39.6^
- cmake
- git
- make (nmake, ninjaでも可)

### ビルド

- macOS, Linux

```bash
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake ..
emmake make
```

- Windows

nmake を使う場合

```bat
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake -G "MinGW Makefiles" ..
nmake
```

ninja を使う場合

```bat
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake -G "ninja" ..
ninja
```
