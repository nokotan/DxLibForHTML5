#!/usr/bin/env node

const fetch = require("node-fetch");
const process = require("process");

/**
 * @returns {string}
 */
async function FetchLatestTag()
{
    const rawTags 
        = await fetch("https://api.github.com/repos/nokotan/DxLibForHTML5/tags", 
                { 
                    method: "GET",
                    headers: {
                        "Authorization": `token ${process.env.GITHUB_TOKEN}`
                    }
                })
            .then(res => res.text());
    console.error(`Server Response: ${rawTags}`)
    const tags = JSON.parse(rawTags);
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