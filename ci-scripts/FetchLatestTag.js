#!/usr/bin/env node

const fetch = require("node-fetch");

/**
 * @returns {string}
 */
async function FetchLatestTag()
{
    const rawTags = await fetch("https://api.github.com/repos/nokotan/DxLibForHTML5/tags").then(res => res.text());
    console.log(`Server Response: {rawTags}`)
    const tags = JSON.parse(rawTags) || '3.22a';
    const tagNames = tags
        .map(tag => tag.name)
        .filter(name => name.match(/[0-9]+\.[0-9]+[a-z]?/));
    
    return tagNames[0];
}

async function Main()
{
    const version = await FetchLatestTag();
    console.log(version);
}

Main();