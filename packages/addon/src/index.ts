import addon from '../build/Release/orm-core-addon.node';

export class RXD {
    static getIndexes(filePath: string) {
        const strData = addon.getIndexes(filePath);
        if (!strData) {
            return null;
        }
        const result = JSON.parse(strData);
        if (!result?.scripts) {
            return null;
        }
        return result.scripts;
    }
}

console.log(RXD.getIndexes('')[64]);
