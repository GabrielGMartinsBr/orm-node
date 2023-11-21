const path = require('path');
const fs = require('fs');

const params = {
    dir: './',
    src: './src',
    out: './build/Release',
    files: [
        'addon.cpp'
    ],
    compilerPath: '/usr/bin/clang++',
    includes: [
        '/usr/include/node',
        './src'
    ],
    flags: [
        '-g',
        '-std=gnu++11'
    ]
};

const directory = path.resolve(params.dir);
const includes = params.includes.map(i => `-I${path.resolve(i)}`);
const entries = params.files.map(i => {
    const srcFilePath = path.resolve(directory, params.src, i);
    const outFileName = i.replace(/\.[^/.]+$/, '.node');
    const outFilePath = path.resolve(directory, params.out, outFileName);
    const commandArr = [
        params.compilerPath,
        includes.join(' '),
        ...params.flags,
        `-o ${outFilePath}`,
        `-c ${srcFilePath}`
    ];
    return {
        directory,
        command: commandArr.join(' '),
        file: srcFilePath,
        output: outFilePath
    };
});

const compileCommandsContent = JSON.stringify(entries, null, 4);

fs.writeFileSync('./build/compile_commands.json', compileCommandsContent);
