#!/usr/bin/env node

const { promisify } = require("util")
const { readFile, writeFile } = require("fs");
const { decode } = require("iconv-lite");

const writeFileAsync = promisify(writeFile);
const readFileAsync = promisify(readFile);

const FilesFromiOS = [
    "DxGraphicsFilterHTML5.cpp",
    "DxGraphicsFilterHTML5.h",
    "DxGraphicsHTML5.cpp",
    "DxGraphicsHTML5.h",
    "DxMaskHTML5.cpp",
    "DxMaskHTML5.h",
    "DxModelHTML5.cpp",
    "DxModelHTML5.h",
    "DxMovieHTML5.cpp",
    "DxMovieHTML5.h",
    "DxShaderCodeBin_Base3D_HTML5.cpp",
    "DxShaderCodeBin_Base_HTML5.cpp",
    "DxShaderCodeBin_Filter_HTML5.cpp",
    "DxShaderCodeBin_Live2D_Cubism4_HTML5.cpp",
    "DxShaderCodeBin_Model_HTML5.cpp",
    "DxShaderCodeBin_RgbaMix_HTML5.cpp",
    "DxShader_Common_HTML5.h",
    "DxShader_DataType_HTML5.h",
    "DxShader_FS_HTML5.h",
    "DxShader_VS_HTML5.h",
    "DxSoundConvertHTML5.cpp",
    "DxSoundConvertHTML5.h",
    "DxSoundHTML5.cpp",
    "DxSoundHTML5.h",
    "DxSystemHTML5.cpp",
    "DxSystemHTML5.h"
];

async function Main()
{
    let promises = [];

    for (const fileName of FilesFromiOS)
    {
        const baseName = fileName.replace("HTML5", "iOS");
        
        promises.push((async () => {
            const fileData = await readFileAsync(`../src/iOS/${baseName}`);
            const fileText = decode(fileData, "utf8");

            let replacedText = fileText.replace(/iOS/g, "HTML5");
            replacedText = replacedText.replace(/IOS/g, "HTML5");
            replacedText = replacedText.replace(/ANDR/g, "HTML5");

            await writeFileAsync(`../src/HTML5/${fileName}`, replacedText);
        })());
    }

    await Promise.all(promises);
}

Main();