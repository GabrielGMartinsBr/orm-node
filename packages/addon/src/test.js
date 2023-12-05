const addon = require('../build/Release/orm-core-addon.node')

const fPath = '../../data/Scripts.rxdata';

const res = JSON.parse(addon.getIndexes(fPath));


for (const i of res.scripts) {
    i.id = +i.id;
}

const content = addon.getContent(fPath, res.scripts[1].id);
console.log(content);