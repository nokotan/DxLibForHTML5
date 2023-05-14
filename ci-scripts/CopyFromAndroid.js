#!/usr/bin/env node

const { promisify } = require("util")
const { readFile, writeFile } = require("fs");
const { decode } = require("iconv-lite");

const writeFileAsync = promisify(writeFile);
const readFileAsync = promisify(readFile);

const FilesFromAndroid = [
    "DxBaseFuncHTML5.cpp",
    "DxBaseFuncHTML5.h",
    "DxBaseImageHTML5.cpp",
    "DxBaseImageHTML5.h",
    "DxFileHTML5.cpp",
    "DxFileHTML5.h",
    "DxFontHTML5.cpp",
    "DxFontHTML5.h",
    "DxInputHTML5.cpp",
    "DxInputHTML5.h",
    "DxLive2DCubism4HTML5.cpp",
    "DxLive2DCubism4HTML5.h",
    "DxLogHTML5.cpp",
    "DxLogHTML5.h",
    "DxMemoryHTML5.cpp",
    "DxMemoryHTML5.h",
    "DxNetworkHTML5.cpp",
    "DxNetworkHTML5.h",
    "DxThreadHTML5.cpp",
    "DxThreadHTML5.h",
    "DxUseCLibOggHTML5.cpp",
    "DxUseCLibOggHTML5.h",
];

async function Main()
{
    let promises = [];

    for (const fileName of FilesFromAndroid)
    {
        const baseName = fileName.replace("HTML5", "Android");
        promises.push((async () => {
            const fileData = await readFileAsync(`../Android/${baseName}`);
            const fileText = decode(fileData, "Shift_JIS");

            let replacedText = fileText.replace(/ANDROID/g, "HTML5");
            replacedText = replacedText.replace(/ANDR/g, "HTML5");
            replacedText = replacedText.replace(/Android/g, "HTML5");

            await writeFileAsync(`../HTML5/${fileName}`, replacedText);
        })());
    }

    await Promise.all(promises);
}

Main();