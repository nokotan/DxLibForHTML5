#!/bin/bash

mkdir dist

mkdir dist/lib
cp build/libDxLib.a dist/lib/
cp build/libDxUseCLib.a dist/lib/
cp build/libDxDrawFunc.a dist/lib/

mkdir dist/include
cp DxCompileConfig.h dist/include/
cp DxDataType.h dist/include/
cp DxDataTypeHTML5.h dist/include/
cp DxFunctionHTML5.h dist/include/
cp DxLib.h dist/include/

cd dist

zip -r ../DxLibForHTML5.zip *
tar -cvzf ../DxLibForHTML5.tgz *
