const addon = require('../build/Release/orm-core-addon.node')

const res = JSON.parse(addon.getIndexes());

console.log(res.scripts[0]);