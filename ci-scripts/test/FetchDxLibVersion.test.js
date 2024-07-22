const fs = require("fs");
const path = require("path");

jest.mock('node-fetch');

const fetch = require("node-fetch");
const { Response } = jest.requireActual('node-fetch');

function createMockReturnValue() {
    return Promise.resolve(
        new Response(
            fs.readFileSync(
                path.resolve(__dirname, "DxLib.index.html")
            )
        )
    );
}

fetch.mockReturnValue(createMockReturnValue());

test("should get DxLib version", async () => {
    const FetchDxLibVersion = require("../FetchDxLibVersion");
    fetch.mockReturnValue(createMockReturnValue());
    
    const version = await FetchDxLibVersion.FetchVersion();
    expect(version).toBe("3.24b");
});
