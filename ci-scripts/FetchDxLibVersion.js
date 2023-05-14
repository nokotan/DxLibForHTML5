#!/usr/bin/env node

const fetch = require("node-fetch");
const { JSDOM } = require("jsdom");

/**
 * @returns {string}
 */
async function FetchVersion() 
{
    const dxlibRawPage = await fetch("https://dxlib.xsrv.jp").then(res => res.text());
    const dxlibPage = new JSDOM(dxlibRawPage);
    const dxlibPageFirstTd = dxlibPage.window.document.body.querySelector("td");

    const versionRegex = /(?<![\.])[0-9]+\.[0-9]+[a-z]?(?![\.])/;
    return dxlibPageFirstTd.innerHTML.match(versionRegex)[0];
}

async function Main()
{
    const version = await FetchVersion();
    console.log(version);
}

Main();

module.exports = {
    FetchVersion
};
