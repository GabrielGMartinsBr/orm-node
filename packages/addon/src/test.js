const addon = require('../build/Release/addon.node')
// const addon = require('../build/addon.node')


const res = JSON.parse(addon.hello());

console.log(res.scripts[0]);