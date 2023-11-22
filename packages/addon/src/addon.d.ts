declare module '*.node' {
    interface Addon {
        getIndexes: (filePath: string) => string;
    }
    const addon: Addon;
    export default addon;
}