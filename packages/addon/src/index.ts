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
        for (const i of result.scripts) {
            i.id = +i.id;
        }
        return result.scripts;
    }

    static getContent(filePath: string, scriptId: number) {
        const strData = addon.getContent(filePath, scriptId);
        if (!strData) {
            return null;
        }
        return strData;
    }
}

// console.log(RXD.getIndexes('../'));
