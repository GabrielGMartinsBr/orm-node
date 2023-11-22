const addon = require('../build/Release/addon.node')

const res = JSON.parse(addon.getIndexes());

console.log(res.scripts[0]);